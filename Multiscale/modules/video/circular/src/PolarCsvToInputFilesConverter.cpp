#include "multiscale/exception/FileOpenException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/video/circular/PolarCsvToInputFilesConverter.hpp"
#include "multiscale/util/iterator/NumberIteratorType.hpp"
#include "multiscale/util/iterator/LexicographicNumberIterator.hpp"
#include "multiscale/util/iterator/StandardNumberIterator.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <string>

using namespace multiscale::video;
using namespace multiscale;
using namespace std;


PolarCsvToInputFilesConverter::PolarCsvToInputFilesConverter(const string &inputFilepath,
                                                             const string &outputFilepath,
                                                             unsigned int nrOfConcentricCircles,
                                                             unsigned int nrOfSectors,
                                                             unsigned int nrOfConcentrationsForPosition,
                                                             unsigned int selectedConcentrationIndex,
                                                             bool useLogScaling,
                                                             NumberIteratorType numberIteratorType) {
    this->inputFilepath                 = inputFilepath;
    this->outputFilepath                = outputFilepath;

    this->nrOfConcentricCircles         = nrOfConcentricCircles;
    this->nrOfSectors                   = nrOfSectors;
    this->nrOfConcentrationsForPosition = nrOfConcentrationsForPosition;

    this->concentrationsIndex           = 0;
    this->selectedConcentrationIndex    = selectedConcentrationIndex;
    this->maximumConcentration          = 1;

    this->useLogScaling                 = useLogScaling;

    initIterators(numberIteratorType);
}

PolarCsvToInputFilesConverter::~PolarCsvToInputFilesConverter() {
    delete circlesIterator;
    delete sectorsIterator;
}

void PolarCsvToInputFilesConverter::convert() {
    ifstream fin;

    validateSelectedConcentrationIndex();
    validateInput(fin);

    initMaximumConcentration(fin);
    initInputFile(fin);
    processInputFile(fin);

    fin.close();
}

void PolarCsvToInputFilesConverter::initInputFile(ifstream &fin) {
    fin.open(inputFilepath, ios_base::in);

    if (!fin.is_open()) {
        MS_throw(FileOpenException, ERR_INPUT_OPEN);
    }
}

void PolarCsvToInputFilesConverter::initMaximumConcentration(ifstream &fin) {
    double maximumConcentration = numeric_limits<double>::min();
    string currentLine;

    fin.open(inputFilepath, ios_base::in);

    if (!fin.is_open()) {
        MS_throw(FileOpenException, ERR_INPUT_OPEN);
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

void PolarCsvToInputFilesConverter::initOutputFile(ofstream &fout, unsigned int index, double &simulationTime) {
    fout.open(
                (
                    (outputFilepath + OUTPUT_FILE_SEPARATOR) +
                    StringManipulator::toString(index) +
                    OUTPUT_EXTENSION
                ),
                ios_base::trunc
            );

    assert(fout.is_open());

    fout << nrOfConcentricCircles << OUTPUT_SEPARATOR
         << nrOfSectors           << OUTPUT_SEPARATOR
         << simulationTime        << endl;
}

void PolarCsvToInputFilesConverter::initIterators(const NumberIteratorType &numberIteratorType) {
    switch (numberIteratorType) {
    case multiscale::STANDARD:
        circlesIterator = new StandardNumberIterator(nrOfConcentricCircles);
        sectorsIterator = new StandardNumberIterator(nrOfSectors);
        break;

    case multiscale::LEXICOGRAPHIC:
        circlesIterator = new LexicographicNumberIterator(nrOfConcentricCircles);
        sectorsIterator = new LexicographicNumberIterator(nrOfSectors);
        break;

    default:
        break;
    }
}

void PolarCsvToInputFilesConverter::validateSelectedConcentrationIndex() {
    if (selectedConcentrationIndex >= nrOfConcentrationsForPosition) {
        MS_throw(InvalidInputException, ERR_SELECTED_CONCENTRATION_INDEX);
    }
}

void PolarCsvToInputFilesConverter::validateInput(ifstream &fin) {
    unsigned int lineNumber = 0;
    string currentLine;

    fin.open(inputFilepath, ios_base::in);

    if (!fin.is_open()) {
        MS_throw(FileOpenException, ERR_INPUT_OPEN);
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

void PolarCsvToInputFilesConverter::validateInputLine(const string &currentLine, unsigned int lineNumber) {
    vector<string> tokens = StringManipulator::split(currentLine, INPUT_FILE_SEPARATOR);

    if (tokens.size() < (((nrOfConcentricCircles - 1) * nrOfSectors + 1) * nrOfConcentrationsForPosition)) {
        MS_throw(InvalidInputException, ERR_NR_CONCENTRATIONS);
    }

    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        double value = stod(*it);

        if (value < 0) {
            MS_throw(InvalidInputException,
                     string(ERR_INVALID_VALUE_LINE)  +
                     StringManipulator::toString<unsigned int>(lineNumber) +
                     string(ERR_INVALID_VALUE_TOKEN) + (*it)
            );
        }
    }
}

void PolarCsvToInputFilesConverter::processInputFile(ifstream &fin) {
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

void PolarCsvToInputFilesConverter::processLine(const string &line, unsigned int outputIndex) {
    ofstream fout;
    double simulationTime;

    vector<double> concentrations = splitLineInConcentrations(line, simulationTime);

    initOutputFile(fout, outputIndex, simulationTime);

    fout << concentrations[0] << endl;

    for (unsigned int i = 1; i < nrOfConcentricCircles; i++) {
        for (unsigned int j = 0; j < (nrOfSectors - 1); j++) {
            fout << concentrations[(i - 1) * nrOfSectors + j + 1] << OUTPUT_SEPARATOR;
        }

        fout << concentrations[i * nrOfSectors] << endl;
    }
}

vector<double> PolarCsvToInputFilesConverter::splitLineInConcentrations(const string &line, double &simulationTime) {
    vector<double> concentrations(((nrOfSectors * (nrOfConcentricCircles - 1)) + 1));

    vector<string> tokens = StringManipulator::split(line, INPUT_FILE_SEPARATOR);

    simulationTime = computeSimulationTime(tokens[0]);
    concentrationsIndex = 1;

    circlesIterator->reset();

    while (circlesIterator->hasNext()) {
        unsigned int circleIndex = circlesIterator->number();

        sectorsIterator->reset();

        if (circleIndex == 1) {
            splitFirstPartInConcentrations(concentrations, tokens, circleIndex);
        } else {
            splitOtherPartsInConcentrations(concentrations, tokens, circleIndex);
        }
    }

    return concentrations;
}

void PolarCsvToInputFilesConverter::splitFirstPartInConcentrations(vector<double> &concentrations,
                                                                   const vector<string> &tokens,
                                                                   unsigned int circleIndex) {
    unsigned int sectorIndex = 1;

    double concentration = computeNextPositionConcentration(circleIndex,
                                                            concentrationsIndex,
                                                            tokens);

    concentrations[((circleIndex - 1) * nrOfSectors) + (sectorIndex - 1)] = concentration;

    concentrationsIndex++;
}

void PolarCsvToInputFilesConverter::splitOtherPartsInConcentrations(vector<double> &concentrations,
                                                                    const vector<string> &tokens,
                                                                    unsigned int circleIndex) {
    while (sectorsIterator->hasNext()) {
        unsigned int sectorIndex = sectorsIterator->number();

        double concentration = computeNextPositionConcentration(circleIndex,
                                                                concentrationsIndex,
                                                                tokens);

        concentrations[((circleIndex - 2) * nrOfSectors) + sectorIndex] = concentration;

        concentrationsIndex++;
    }
}

inline double PolarCsvToInputFilesConverter::computeSimulationTime(const string &token) {
    double simulationTime = stod(token);

    if (simulationTime < 0) {
        MS_throw(InvalidInputException, ERR_NEG_SIM_TIME);
    }

    return simulationTime;
}

inline double PolarCsvToInputFilesConverter::computeNextPositionConcentration(unsigned int circleIndex,
                                                                              int concentrationIndex,
                                                                              const vector<string> &tokens) {
    double concentration = 0;
    double totalConcentration = 0;

    // Read the concentrations
    for (unsigned int i = 0; i < nrOfConcentrationsForPosition; i++) {
        double tmpConcentration = computeConcentration(
                                      tokens[(nrOfConcentrationsForPosition * (concentrationIndex - 1)) + 1 + i],
                                      circleIndex
                                  );

        // Set the concentration A for computing "A / sum(concentrations)"
        if (i == selectedConcentrationIndex) {
            concentration = tmpConcentration;
        }

        totalConcentration += tmpConcentration;
    }

    // Return normalised concentration
    if (nrOfConcentrationsForPosition == 1) {
        return computeNormalisedConcentration(totalConcentration, circleIndex);
    } else {
        return (totalConcentration != 0) ? (concentration/totalConcentration) : 0;
    }
}

inline double PolarCsvToInputFilesConverter::computeConcentration(const string &concentration, int circleIndex) {
    return ((nrOfConcentrationsForPosition == 1) && (useLogScaling))
                ? computeScaledConcentration(concentration, circleIndex)
                : computeNonScaledConcentration(concentration, circleIndex);
}

inline double PolarCsvToInputFilesConverter::computeNonScaledConcentration(const string &concentration, int circleIndex) {
    double amount = stod(concentration);

    return computeConcentrationWrtArea(amount, circleIndex);
}

inline double PolarCsvToInputFilesConverter::computeScaledConcentration(const string &concentration, int circleIndex) {
    double amount = stod(concentration);

    double scaledConcentration = computeConcentrationWrtArea(amount, circleIndex);

    // Convert all concentrations which are lower than 1 to 1,
    // such that we don't obtain negative values after applying log
    if (scaledConcentration < 1) {
        scaledConcentration = 1;
    }

    return log2(scaledConcentration);
}

inline double PolarCsvToInputFilesConverter::computeConcentrationWrtArea(double amount, int circleIndex) {
    return amount / ((2 * (circleIndex - 1)) + 1);
}

inline double PolarCsvToInputFilesConverter::computeNormalisedConcentration(double concentration, int circleIndex) {
    return (concentration / maximumConcentration);
}

void PolarCsvToInputFilesConverter::updateMaximumConcentration(const string &currentLine, double &maximumConcentration) {
    double simulationTime;

    vector<double> concentrations = splitLineInConcentrations(currentLine, simulationTime);

    for (vector<double>::iterator it = concentrations.begin(); it != concentrations.end(); it++) {
        if ((*it) > maximumConcentration) {
            maximumConcentration = (*it);
        }
    }
}


// Constants
const int PolarCsvToInputFilesConverter::RADIUS_MIN  = 1;

const string PolarCsvToInputFilesConverter::OUTPUT_EXTENSION        = ".in";
const string PolarCsvToInputFilesConverter::OUTPUT_SEPARATOR        = " ";
const string PolarCsvToInputFilesConverter::OUTPUT_FILE_SEPARATOR   = "_";
const string PolarCsvToInputFilesConverter::INPUT_FILE_SEPARATOR    = ",";

const string PolarCsvToInputFilesConverter::ERR_NEG_CONCENTRATION               = "All concentrations must be non-negative.";
const string PolarCsvToInputFilesConverter::ERR_SELECTED_CONCENTRATION_INDEX    = "The selected concentration index (0-based indexing) should be smaller than the number of concentrations.";
const string PolarCsvToInputFilesConverter::ERR_NR_CONCENTRATIONS               = "The number of concentrations in the input file does not match the values of the input parameters height and width.";
const string PolarCsvToInputFilesConverter::ERR_NEG_SIM_TIME                    = "The simulation time must be non-negative.";
const string PolarCsvToInputFilesConverter::ERR_INPUT_OPEN                      = "The input file could not be opened.";
const string PolarCsvToInputFilesConverter::ERR_INVALID_VALUE_LINE              = "Invalid value on line: ";
const string PolarCsvToInputFilesConverter::ERR_INVALID_VALUE_TOKEN             = ", value: ";
