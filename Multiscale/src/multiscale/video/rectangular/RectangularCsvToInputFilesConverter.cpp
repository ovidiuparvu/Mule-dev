#include "multiscale/exception/RectangularCsvToInputFilesConverterException.hpp"
#include "multiscale/video/rectangular/RectangularCsvToInputFilesConverter.hpp"
#include "multiscale/util/iterator/NumberIteratorType.hpp"
#include "multiscale/util/iterator/LexicographicNumberIterator.hpp"
#include "multiscale/util/iterator/StandardNumberIterator.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <limits>

using namespace multiscale::video;
using namespace multiscale;
using namespace std;


RectangularCsvToInputFilesConverter::RectangularCsvToInputFilesConverter(const string &inputFilepath,
                                                                         const string &outputFilepath,
                                                                         unsigned int height,
                                                                         unsigned int width,
                                                                         unsigned int nrOfConcentrationsForPosition,
                                                                         unsigned int selectedConcentrationIndex,
                                                                         bool useLogScaling,
                                                                         NumberIteratorType numberIteratorType) {
    this->inputFilepath                 = inputFilepath;
    this->outputFilepath                = outputFilepath;

    this->height                        = height;
    this->width                         = width;
    this->nrOfConcentrationsForPosition = nrOfConcentrationsForPosition;

    this->concentrationsIndex           = 0;
    this->selectedConcentrationIndex    = selectedConcentrationIndex;
    this->maximumConcentration          = 1;

    this->useLogScaling                 = useLogScaling;

    initIterators(numberIteratorType);
}

RectangularCsvToInputFilesConverter::~RectangularCsvToInputFilesConverter() {
    delete rowsIterator;
    delete columnsIterator;
}

void RectangularCsvToInputFilesConverter::convert() {
    ifstream fin;

    validateSelectedConcentrationIndex();
    validateInput(fin);

    initMaximumConcentration(fin);
    initInputFile(fin);
    processInputFile(fin);

    fin.close();
}

void RectangularCsvToInputFilesConverter::initInputFile(ifstream &fin) {
    fin.open(inputFilepath, ios_base::in);

    if (!fin.is_open()) {
        throw RectangularCsvToInputFilesConverterException(ERR_INPUT_OPEN);
    }
}

void RectangularCsvToInputFilesConverter::initMaximumConcentration(ifstream &fin) {
    double maximumConcentration = numeric_limits<double>::min();
    string currentLine;

    fin.open(inputFilepath, ios_base::in);

    if (!fin.is_open()) {
        throw RectangularCsvToInputFilesConverterException(ERR_INPUT_OPEN);
    }

    while (!fin.eof()) {
        getline(fin, currentLine);

        // Consider processing the line only if it has content
        if (!currentLine.empty()) {
            updateMaximumConcentration(currentLine, maximumConcentration);
        }
    }

    fin.close();

    this->maximumConcentration = maximumConcentration;
}

void RectangularCsvToInputFilesConverter::initOutputFile(ofstream &fout, unsigned int index, double &simulationTime) {
    fout.open(
                (
                    (outputFilepath + OUTPUT_FILE_SEPARATOR) +
                    StringManipulator::toString(index) +
                    OUTPUT_EXTENSION
                ),
                ios_base::trunc
            );

    assert(fout.is_open());

    fout << height << OUTPUT_SEPARATOR
         << width  << OUTPUT_SEPARATOR
         << simulationTime << endl;
}

void RectangularCsvToInputFilesConverter::initIterators(const NumberIteratorType &numberIteratorType) {
    switch (numberIteratorType) {
    case multiscale::STANDARD:
        rowsIterator = new StandardNumberIterator(height);
        columnsIterator = new StandardNumberIterator(width);
        break;

    case multiscale::LEXICOGRAPHIC:
        rowsIterator = new LexicographicNumberIterator(height);
        columnsIterator = new LexicographicNumberIterator(width);
        break;

    default:
        break;
    }
}

void RectangularCsvToInputFilesConverter::validateSelectedConcentrationIndex() {
    if (selectedConcentrationIndex >= nrOfConcentrationsForPosition) {
        throw RectangularCsvToInputFilesConverterException(ERR_SELECTED_CONCENTRATION_INDEX);
    }
}

void RectangularCsvToInputFilesConverter::validateInput(ifstream &fin) {
    unsigned int lineNumber = 0;
    string currentLine;

    fin.open(inputFilepath, ios_base::in);

    if (!fin.is_open()) {
        throw RectangularCsvToInputFilesConverterException(ERR_INPUT_OPEN);
    }

    while (!fin.eof()) {
        getline(fin, currentLine);

        lineNumber++;

        // Consider processing the line only if it has content
        if (!currentLine.empty()) {
            validateInputLine(currentLine, lineNumber);
        }
    }

    fin.close();
}

void RectangularCsvToInputFilesConverter::validateInputLine(const string &currentLine, unsigned int lineNumber) {
    vector<string> tokens = StringManipulator::split(currentLine, INPUT_FILE_SEPARATOR);

    if (tokens.size() < ((height * width * nrOfConcentrationsForPosition) + 1)) {
        throw RectangularCsvToInputFilesConverterException(ERR_NR_CONCENTRATIONS);
    }

    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        double value = stod(*it);

        if (value < 0) {
            throw RectangularCsvToInputFilesConverterException(
                    string(ERR_INVALID_VALUE_LINE)  +
                    StringManipulator::toString<unsigned int>(lineNumber) +
                    string(ERR_INVALID_VALUE_TOKEN) + (*it)
                  );
        }
    }
}

void RectangularCsvToInputFilesConverter::processInputFile(ifstream &fin) {
    string currentLine;

    unsigned int index = 1;

    while (!fin.eof()) {
        getline(fin, currentLine);

        // Consider processing the line only if it has content
        if (!currentLine.empty()) {
            processLine(currentLine, index++);
        }
    }
}

void RectangularCsvToInputFilesConverter::processLine(const string &line, unsigned int outputIndex) {
    ofstream fout;
    double simulationTime;

    vector<double> concentrations = splitLineInConcentrations(line, simulationTime);

    initOutputFile(fout, outputIndex, simulationTime);

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < (width - 1); j++) {
            fout << concentrations[(i * width) + j] << OUTPUT_SEPARATOR;
        }

        fout << concentrations[(i * width) + width - 1] << endl;
    }
}

vector<double> RectangularCsvToInputFilesConverter::splitLineInConcentrations(const string &line, double &simulationTime) {
    vector<double> concentrations(height * width);

    vector<string> tokens = StringManipulator::split(line, INPUT_FILE_SEPARATOR);

    simulationTime = computeSimulationTime(tokens[0]);
    concentrationsIndex = 1;

    rowsIterator->reset();

    while (rowsIterator->hasNext()) {
        unsigned int rowIndex = rowsIterator->number();

        columnsIterator->reset();

        splitLineInConcentrations(concentrations, tokens, rowIndex);
    }

    return concentrations;
}

void RectangularCsvToInputFilesConverter::splitLineInConcentrations(vector<double> &concentrations,
                                                                    vector<string> &tokens,
                                                                    unsigned int rowIndex) {
    while (columnsIterator->hasNext()) {
        unsigned int sectorIndex = columnsIterator->number();

        double concentration = computeNextPositionConcentration(concentrationsIndex,
                                                                tokens);

        concentrations[((rowIndex - 1) * width) + sectorIndex - 1] = concentration;

        concentrationsIndex++;
    }
}

inline double RectangularCsvToInputFilesConverter::computeSimulationTime(const string &token) {
    double simulationTime = stod(token);

    if (simulationTime < 0) {
        throw RectangularCsvToInputFilesConverterException(ERR_NEG_SIM_TIME);
    }

    return simulationTime;
}

inline double RectangularCsvToInputFilesConverter::computeNextPositionConcentration(int concentrationIndex,
                                                                             vector<string> &tokens) {
    double concentration = 0;
    double totalConcentration = 0;

    // Read the concentrations
    for (unsigned int i = 0; i < nrOfConcentrationsForPosition; i++) {
        double tmpConcentration = computeConcentration(tokens[(nrOfConcentrationsForPosition *
                                                              (concentrationIndex - 1)) +
                                                              1 + i]
                                                      );
        // Set the concentration A for computing "A / sum(concentrations)"
        if (i == selectedConcentrationIndex) {
            concentration = tmpConcentration;
        }

        totalConcentration += tmpConcentration;
    }

    // Return normalised concentration
    if (nrOfConcentrationsForPosition == 1) {
        return computeNormalisedConcentration(totalConcentration);
    } else {
        return (totalConcentration != 0) ? (concentration/totalConcentration) : 0;
    }
}

inline double RectangularCsvToInputFilesConverter::computeConcentration(const string &concentration) {
    return ((nrOfConcentrationsForPosition == 1) && (useLogScaling))
                ? computeScaledConcentration(concentration)
                : computeNonScaledConcentration(concentration);
}

inline double RectangularCsvToInputFilesConverter::computeNonScaledConcentration(const string &concentration) {
    return stod(concentration);
}

inline double RectangularCsvToInputFilesConverter::computeScaledConcentration(const string &concentration) {
    double scaledConcentration = stod(concentration);

    // Convert all concentrations which are lower than 1 to 1,
    // such that we don't obtain negative values after applying log
    if (scaledConcentration < 1) {
        scaledConcentration = 1;
    }

    return log2(scaledConcentration);
}

inline double RectangularCsvToInputFilesConverter::computeNormalisedConcentration(double concentration) {
    return (concentration / maximumConcentration);
}

void RectangularCsvToInputFilesConverter::updateMaximumConcentration(const string &currentLine, double &maximumConcentration) {
    double simulationTime;

    vector<double> concentrations = splitLineInConcentrations(currentLine, simulationTime);

    for (vector<double>::iterator it = concentrations.begin(); it != concentrations.end(); it++) {
        if ((*it) > maximumConcentration) {
            maximumConcentration = (*it);
        }
    }
}
