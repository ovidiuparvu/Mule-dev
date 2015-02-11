#include "multiscale/exception/FileOpenException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/visualisation/circular/PolarCsvToInputFilesConverter.hpp"
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
#include <string>

using namespace multiscale::visualisation;
using namespace multiscale;


PolarCsvToInputFilesConverter::PolarCsvToInputFilesConverter(const std::string &inputFilepath,
                                                             const std::string &outputFilepath,
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
    std::ifstream fin;

    validateSelectedConcentrationIndex();
    validateInput(fin);

    initMaximumConcentration(fin);
    initInputFile(fin);
    processInputFile(fin);

    fin.close();
}

void PolarCsvToInputFilesConverter::initInputFile(std::ifstream &fin) {
    fin.open(inputFilepath, std::ios_base::in);

    if (!fin.is_open()) {
        MS_throw(FileOpenException, ERR_INPUT_OPEN);
    }
}

void PolarCsvToInputFilesConverter::initMaximumConcentration(std::ifstream &fin) {
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

void PolarCsvToInputFilesConverter::initOutputFile(std::ofstream &fout, unsigned int index,
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

    fout << nrOfConcentricCircles << OUTPUT_SEPARATOR
         << nrOfSectors           << OUTPUT_SEPARATOR
         << simulationTime        << std::endl;
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

void PolarCsvToInputFilesConverter::validateInput(std::ifstream &fin) {
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

void PolarCsvToInputFilesConverter::validateInputLine(const std::string &currentLine,
                                                      unsigned int lineNumber) {
    std::vector<std::string> tokens = StringManipulator::split(currentLine, INPUT_FILE_SEPARATOR);

    if (tokens.size() < (((nrOfConcentricCircles - 1) * nrOfSectors + 1) * nrOfConcentrationsForPosition)) {
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

void PolarCsvToInputFilesConverter::processInputFile(std::ifstream &fin) {
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

void PolarCsvToInputFilesConverter::processLine(const std::string &line, unsigned int outputIndex) {
    std::ofstream fout;
    double simulationTime;

    std::vector<double> concentrations = splitLineInConcentrations(line, simulationTime);

    initOutputFile(fout, outputIndex, simulationTime);

    fout << std::setprecision(OUTPUT_PRECISION)
         << concentrations[0] << std::endl;

    for (unsigned int i = 1; i < nrOfConcentricCircles; i++) {
        for (unsigned int j = 0; j < (nrOfSectors - 1); j++) {
            fout << std::setprecision(OUTPUT_PRECISION)
                 << concentrations[(i - 1) * nrOfSectors + j + 1] << OUTPUT_SEPARATOR;
        }

        fout << std::setprecision(OUTPUT_PRECISION)
             << concentrations[i * nrOfSectors] << std::endl;
    }
}

std::vector<double> PolarCsvToInputFilesConverter::splitLineInConcentrations(const std::string &line,
                                                                             double &simulationTime) {
    std::vector<double> concentrations(((nrOfSectors * (nrOfConcentricCircles - 1)) + 1));

    std::vector<std::string> tokens = StringManipulator::split(line, INPUT_FILE_SEPARATOR);

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

void PolarCsvToInputFilesConverter::splitFirstPartInConcentrations(std::vector<double> &concentrations,
                                                                   const std::vector<std::string> &tokens,
                                                                   unsigned int circleIndex) {
    unsigned int sectorIndex = 1;

    double concentration = computeNextPositionConcentration(circleIndex,
                                                            concentrationsIndex,
                                                            tokens);

    concentrations[((circleIndex - 1) * nrOfSectors) + (sectorIndex - 1)] = concentration;

    concentrationsIndex++;
}

void PolarCsvToInputFilesConverter::splitOtherPartsInConcentrations(std::vector<double> &concentrations,
                                                                    const std::vector<std::string> &tokens,
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

double PolarCsvToInputFilesConverter::computeSimulationTime(const std::string &token) {
    double simulationTime = stod(token);

    if (simulationTime < 0) {
        MS_throw(InvalidInputException, ERR_NEG_SIM_TIME);
    }

    return simulationTime;
}

double PolarCsvToInputFilesConverter::computeNextPositionConcentration(unsigned int circleIndex,
                                                                       int concentrationIndex,
                                                                       const std::vector<std::string> &tokens) {
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
        return (Numeric::division(concentration, totalConcentration));
    }
}

double PolarCsvToInputFilesConverter::computeConcentration(const std::string &concentration,
                                                           int circleIndex) {
    return ((nrOfConcentrationsForPosition == 1) && (useLogScaling))
                ? computeScaledConcentration(concentration, circleIndex)
                : computeNonScaledConcentration(concentration, circleIndex);
}

double PolarCsvToInputFilesConverter::computeNonScaledConcentration(const std::string &concentration,
                                                                    int circleIndex) {
    double amount = std::stod(concentration);

    return computeConcentrationWrtArea(amount, circleIndex);
}

double PolarCsvToInputFilesConverter::computeScaledConcentration(const std::string &concentration,
                                                                 int circleIndex) {
    double amount = std::stod(concentration);

    double scaledConcentration = computeConcentrationWrtArea(amount, circleIndex);

    // Convert all concentrations which are lower than 1 to 1,
    // such that we don't obtain negative values after applying log
    if (scaledConcentration < 1) {
        scaledConcentration = 1;
    }

    return std::log2(scaledConcentration);
}

double PolarCsvToInputFilesConverter::computeConcentrationWrtArea(double amount, int circleIndex) {
    return amount / ((2 * (circleIndex - 1)) + 1);
}

double PolarCsvToInputFilesConverter::computeNormalisedConcentration(double concentration, int circleIndex) {
    return (concentration / maximumConcentration);
}

void PolarCsvToInputFilesConverter::updateMaximumConcentration(const std::string &currentLine,
                                                               double &maximumConcentration) {
    double simulationTime;

    std::vector<double> concentrations = splitLineInConcentrations(currentLine, simulationTime);

    for (auto it = concentrations.begin(); it != concentrations.end(); it++) {
        if ((*it) > maximumConcentration) {
            maximumConcentration = (*it);
        }
    }
}


// Constants
const int PolarCsvToInputFilesConverter::RADIUS_MIN = 1;

const int PolarCsvToInputFilesConverter::OUTPUT_PRECISION = std::numeric_limits<double>::max_digits10;

const std::string PolarCsvToInputFilesConverter::OUTPUT_EXTENSION        = ".in";
const std::string PolarCsvToInputFilesConverter::OUTPUT_SEPARATOR        = " ";
const std::string PolarCsvToInputFilesConverter::OUTPUT_FILE_SEPARATOR   = "_";
const std::string PolarCsvToInputFilesConverter::INPUT_FILE_SEPARATOR    = ",";

const std::string PolarCsvToInputFilesConverter::ERR_NEG_CONCENTRATION               = "All concentrations must be non-negative.";
const std::string PolarCsvToInputFilesConverter::ERR_SELECTED_CONCENTRATION_INDEX    = "The selected concentration index (0-based indexing) should be smaller than the number of concentrations.";
const std::string PolarCsvToInputFilesConverter::ERR_NR_CONCENTRATIONS               = "The number of concentrations in the input file does not match the values of the input parameters height and width.";
const std::string PolarCsvToInputFilesConverter::ERR_NEG_SIM_TIME                    = "The simulation time must be non-negative.";
const std::string PolarCsvToInputFilesConverter::ERR_INPUT_OPEN                      = "The input file could not be opened.";
const std::string PolarCsvToInputFilesConverter::ERR_INVALID_VALUE_LINE              = "Invalid value on line: ";
const std::string PolarCsvToInputFilesConverter::ERR_INVALID_VALUE_TOKEN             = ", value: ";
