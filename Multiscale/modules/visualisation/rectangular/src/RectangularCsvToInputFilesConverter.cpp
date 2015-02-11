#include "multiscale/exception/FileOpenException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/visualisation/rectangular/RectangularCsvToInputFilesConverter.hpp"
#include "multiscale/util/iterator/NumberIteratorType.hpp"
#include "multiscale/util/iterator/LexicographicNumberIterator.hpp"
#include "multiscale/util/iterator/StandardNumberIterator.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace multiscale::visualisation;
using namespace multiscale;


RectangularCsvToInputFilesConverter::RectangularCsvToInputFilesConverter(const std::string &inputFilepath,
                                                                         const std::string &outputFilepath,
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
    std::ifstream fin;

    validateSelectedConcentrationIndex();
    validateInput(fin);

    initMaximumConcentration(fin);
    initInputFile(fin);
    processInputFile(fin);

    fin.close();
}

void RectangularCsvToInputFilesConverter::initInputFile(std::ifstream &fin) {
    fin.open(inputFilepath, std::ios_base::in);

    if (!fin.is_open()) {
        MS_throw(FileOpenException, ERR_INPUT_OPEN);
    }
}

void RectangularCsvToInputFilesConverter::initMaximumConcentration(std::ifstream &fin) {
    double maximumConcentration = std::numeric_limits<double>::min();
    std::string currentLine;

    fin.open(inputFilepath, std::ios_base::in);

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

void RectangularCsvToInputFilesConverter::initOutputFile(std::ofstream &fout, unsigned int index,
                                                         double &simulationTime) {
    fout.open(
        (
            (outputFilepath + OUTPUT_FILE_SEPARATOR) +
            StringManipulator::toString(index) +
            OUTPUT_EXTENSION
        ),
        std::ios_base::trunc
    );

    assert(fout.is_open());

    fout << height << OUTPUT_SEPARATOR
         << width  << OUTPUT_SEPARATOR
         << simulationTime << std::endl;
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
        MS_throw(InvalidInputException, ERR_SELECTED_CONCENTRATION_INDEX);
    }
}

void RectangularCsvToInputFilesConverter::validateInput(std::ifstream &fin) {
    unsigned int lineNumber = 0;
    std::string currentLine;

    fin.open(inputFilepath, std::ios_base::in);

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

void RectangularCsvToInputFilesConverter::validateInputLine(const std::string &currentLine,
                                                            unsigned int lineNumber) {
    std::vector<std::string> tokens = StringManipulator::split(currentLine, INPUT_FILE_SEPARATOR);

    if (tokens.size() < ((height * width * nrOfConcentrationsForPosition) + 1)) {
        MS_throw(InvalidInputException, ERR_NR_CONCENTRATIONS);
    }

    for (auto it = tokens.begin(); it != tokens.end(); it++) {
        double value = std::stod(*it);

        if (value < 0) {
            MS_throw(InvalidInputException,
                     std::string(ERR_INVALID_VALUE_LINE)  +
                     StringManipulator::toString<unsigned int>(lineNumber) +
                     std::string(ERR_INVALID_VALUE_TOKEN) + (*it)
            );
        }
    }
}

void RectangularCsvToInputFilesConverter::processInputFile(std::ifstream &fin) {
    std::string currentLine;

    unsigned int index = 1;

    while (!fin.eof()) {
        getline(fin, currentLine);

        // Consider processing the line only if it has content
        if (!currentLine.empty()) {
            processLine(currentLine, index++);
        }
    }
}

void RectangularCsvToInputFilesConverter::processLine(const std::string &line, unsigned int outputIndex) {
    std::ofstream fout;
    double simulationTime;

    std::vector<double> concentrations = splitLineInConcentrations(line, simulationTime);

    initOutputFile(fout, outputIndex, simulationTime);

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < (width - 1); j++) {
            fout << std::setprecision(OUTPUT_PRECISION)
                 << concentrations[(i * width) + j] << OUTPUT_SEPARATOR;
        }

        fout << std::setprecision(OUTPUT_PRECISION)
             << concentrations[(i * width) + width - 1] << std::endl;
    }
}

std::vector<double> RectangularCsvToInputFilesConverter::splitLineInConcentrations(const std::string &line,
                                                                                   double &simulationTime) {
    std::vector<double> concentrations(height * width);

    std::vector<std::string> tokens = StringManipulator::split(line, INPUT_FILE_SEPARATOR);

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

void RectangularCsvToInputFilesConverter::splitLineInConcentrations(std::vector<double> &concentrations,
                                                                    std::vector<std::string> &tokens,
                                                                    unsigned int rowIndex) {
    while (columnsIterator->hasNext()) {
        unsigned int sectorIndex = columnsIterator->number();

        double concentration = computeNextPositionConcentration(concentrationsIndex,
                                                                tokens);

        concentrations[((rowIndex - 1) * width) + sectorIndex - 1] = concentration;

        concentrationsIndex++;
    }
}

double RectangularCsvToInputFilesConverter::computeSimulationTime(const std::string &token) {
    double simulationTime = stod(token);

    if (simulationTime < 0) {
        MS_throw(InvalidInputException, ERR_NEG_SIM_TIME);
    }

    return simulationTime;
}

double RectangularCsvToInputFilesConverter::computeNextPositionConcentration(int concentrationIndex,
                                                                             std::vector<std::string> &tokens) {
    double concentration = 0;
    double totalConcentration = 0;

    // Read the concentrations
    for (unsigned int i = 0; i < nrOfConcentrationsForPosition; i++) {
        double tmpConcentration = computeConcentration(tokens[((nrOfConcentrationsForPosition) *
                                                       (concentrationIndex - 1)) + 1 + i]);

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
        return (Numeric::division(concentration, totalConcentration));
    }
}

double RectangularCsvToInputFilesConverter::computeConcentration(const std::string &concentration) {
    return ((nrOfConcentrationsForPosition == 1) && (useLogScaling))
                ? computeScaledConcentration(concentration)
                : computeNonScaledConcentration(concentration);
}

double RectangularCsvToInputFilesConverter::computeNonScaledConcentration(const std::string &concentration) {
    return stod(concentration);
}

double RectangularCsvToInputFilesConverter::computeScaledConcentration(const std::string &concentration) {
    double scaledConcentration = stod(concentration);

    // Convert all concentrations which are lower than 1 to 1,
    // such that we don't obtain negative values after applying log
    if (scaledConcentration < 1) {
        scaledConcentration = 1;
    }

    return std::log2(scaledConcentration);
}

double RectangularCsvToInputFilesConverter::computeNormalisedConcentration(double concentration) {
    return (concentration / maximumConcentration);
}

void RectangularCsvToInputFilesConverter::updateMaximumConcentration(const std::string &currentLine,
                                                                     double &maximumConcentration) {
    double simulationTime;

    std::vector<double> concentrations = splitLineInConcentrations(currentLine, simulationTime);

    for (std::vector<double>::iterator it = concentrations.begin(); it != concentrations.end(); it++) {
        if ((*it) > maximumConcentration) {
            maximumConcentration = (*it);
        }
    }
}


// Constants
const int         RectangularCsvToInputFilesConverter::OUTPUT_PRECISION        = std::numeric_limits<double>::max_digits10;

const std::string RectangularCsvToInputFilesConverter::OUTPUT_EXTENSION        = ".in";
const std::string RectangularCsvToInputFilesConverter::OUTPUT_SEPARATOR        = " ";
const std::string RectangularCsvToInputFilesConverter::OUTPUT_FILE_SEPARATOR   = "_";
const std::string RectangularCsvToInputFilesConverter::INPUT_FILE_SEPARATOR    = ",";

const std::string RectangularCsvToInputFilesConverter::ERR_NEG_CONCENTRATION               = "All concentrations must be non-negative.";
const std::string RectangularCsvToInputFilesConverter::ERR_SELECTED_CONCENTRATION_INDEX    = "The selected concentration index (0-based indexing) should be smaller than the number of concentrations.";
const std::string RectangularCsvToInputFilesConverter::ERR_NR_CONCENTRATIONS               = "The number of concentrations in the input file does not match the values of the input parameters height and width.";
const std::string RectangularCsvToInputFilesConverter::ERR_NEG_SIM_TIME                    = "The simulation time must be non-negative.";
const std::string RectangularCsvToInputFilesConverter::ERR_INPUT_OPEN                      = "The input file could not be opened.";
const std::string RectangularCsvToInputFilesConverter::ERR_INVALID_VALUE_LINE              = "Invalid value on line: ";
const std::string RectangularCsvToInputFilesConverter::ERR_INVALID_VALUE_TOKEN             = ", value: ";
