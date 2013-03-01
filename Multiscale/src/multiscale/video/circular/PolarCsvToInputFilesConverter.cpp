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

using namespace multiscale::video;
using namespace multiscale;
using namespace std;

// Constructor for the class
PolarCsvToInputFilesConverter::PolarCsvToInputFilesConverter(const string &inputFilepath,
                                                             const string &outputFilepath,
                                                             unsigned int nrOfConcentricCircles,
                                                             unsigned int nrOfSectors,
                                                             unsigned int nrOfConcentrationsForPosition,
                                                             unsigned int selectedConcentrationIndex,
                                                             NumberIteratorType numberIteratorType) {
    this->inputFilepath                 = inputFilepath;
    this->outputFilepath                = outputFilepath;

    this->nrOfConcentricCircles         = nrOfConcentricCircles;
    this->nrOfSectors                   = nrOfSectors;
    this->nrOfConcentrationsForPosition = nrOfConcentrationsForPosition;

    this->concentrationsIndex           = 0;
    this->selectedConcentrationIndex    = selectedConcentrationIndex;
    this->maximumConcentration          = 1;

    initIterators(numberIteratorType);
}

// Destructor for the class
PolarCsvToInputFilesConverter::~PolarCsvToInputFilesConverter() {
    delete circlesIterator;
    delete sectorsIterator;
}

// Convert the ".csv" file to input files
void PolarCsvToInputFilesConverter::convert() {
    ifstream fin;

    validateSelectedConcentrationIndex();
    validateInput(fin);

    initMaximumConcentration(fin);
    initInputFile(fin);
    processInputFile(fin);

    fin.close();
}

// Initialise the input file
void PolarCsvToInputFilesConverter::initInputFile(ifstream &fin) {
    fin.open(inputFilepath.c_str(), ios_base::in);

    if (!fin.is_open()) throw ERR_INPUT_OPEN;
}

// Initialise the maximum concentration value
void PolarCsvToInputFilesConverter::initMaximumConcentration(ifstream &fin) {
    double maximumConcentration = numeric_limits<double>::min();
    string currentLine;

    fin.open(inputFilepath.c_str(), ios_base::in);

    if (!fin.is_open()) throw ERR_INPUT_OPEN;

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

// Initialise the output file
void PolarCsvToInputFilesConverter::initOutputFile(ofstream &fout, unsigned int index, double &simulationTime) {
    fout.open(
                (
                    (outputFilepath + OUTPUT_FILE_SEPARATOR) +
                    StringManipulator::toString(index) +
                    OUTPUT_EXTENSION
                ).c_str(),
                ios_base::trunc
            );

    assert(fout.is_open());

    fout << nrOfConcentricCircles << OUTPUT_SEPARATOR
         << nrOfSectors           << OUTPUT_SEPARATOR
         << simulationTime        << endl;
}

// Initialise the iterators
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

// Check if the selectedConcentrationIndex < nrOfConcentrationsForPosition
void PolarCsvToInputFilesConverter::validateSelectedConcentrationIndex() {
    if (selectedConcentrationIndex >= nrOfConcentrationsForPosition)
        throw ERR_SELECTED_CONCENTRATION_INDEX;
}

// Validate the input file
void PolarCsvToInputFilesConverter::validateInput(ifstream &fin) {
    unsigned int lineNumber = 0;
    string currentLine;

    fin.open(inputFilepath.c_str(), ios_base::in);

    if (!fin.is_open()) throw ERR_INPUT_OPEN;

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

// Validate the provided line
void PolarCsvToInputFilesConverter::validateInputLine(const string &currentLine, unsigned int lineNumber) {
    vector<string> tokens = StringManipulator::split(currentLine, INPUT_FILE_SEPARATOR);

    if (tokens.size() < (((nrOfConcentricCircles - 1) * nrOfSectors + 1) * nrOfConcentrationsForPosition))
        throw ERR_NR_CONCENTRATIONS;

    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        double value = atof((*it).c_str());

        if (value < 0)
            throw string(ERR_INVALID_VALUE_LINE)  +
                  StringManipulator::toString<unsigned int>(lineNumber) +
                  string(ERR_INVALID_VALUE_TOKEN) + (*it);
    }
}

// Process the given input file
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

// Process the current line
void PolarCsvToInputFilesConverter::processLine(const string &line, unsigned int outputIndex) {
    ofstream fout;
    double simulationTime;

    vector<double> concentrations = splitLineInConcentrations(line, simulationTime);

    initOutputFile(fout, outputIndex, simulationTime);

    fout << concentrations[0] << endl;

    for (unsigned int i = 1; i < nrOfConcentricCircles; i++) {
        for (int j = 0; j < (nrOfSectors - 1); j++) {
            fout << concentrations[(i - 1) * nrOfSectors + j + 1] << OUTPUT_SEPARATOR;
        }

        fout << concentrations[i * nrOfSectors] << endl;
    }
}

// Split the line in concentrations and simulation time
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

// Split the first part of the line into concentrations
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

// Split the next/other parts of the line into concentrations
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

// Compute the simulation time and verify if it is valid
inline double PolarCsvToInputFilesConverter::computeSimulationTime(const string &token) {
    double simulationTime = atof(token.c_str());

    if (simulationTime < 0) throw ERR_NEG_SIM_TIME;

    return simulationTime;
}

// Compute the concentration of the next position
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
    if (nrOfConcentrationsForPosition == 1)
        return computeNormalisedConcentration(totalConcentration, circleIndex);
    else {
        return (totalConcentration != 0) ? (concentration/totalConcentration) : 0;
    }
}

// Compute the concentration from the given string considering the number of concentrations for each position
inline double PolarCsvToInputFilesConverter::computeConcentration(const string &concentration, int circleIndex) {
    return (nrOfConcentrationsForPosition == 1)
                ? computeScaledConcentration(concentration, circleIndex)
                : computeNonScaledConcentration(concentration, circleIndex);
}

// Compute the non scaled concentration from the given string
inline double PolarCsvToInputFilesConverter::computeNonScaledConcentration(const string &concentration, int circleIndex) {
    double amount = atof(concentration.c_str());

    return computeConcentrationWrtArea(amount, circleIndex);
}

// Compute the scaled concentration from the given string by applying
// a logit transformation to it
inline double PolarCsvToInputFilesConverter::computeScaledConcentration(const string &concentration, int circleIndex) {
    double amount = atof(concentration.c_str());

    double scaledConcentration = computeConcentrationWrtArea(amount, circleIndex);

    // Convert all concentrations which are lower than 1 to 1,
    // such that we don't obtain negative values after applying log
    if (scaledConcentration < 1) {
        scaledConcentration = 1;
    }

    return log2(scaledConcentration);
}

// Compute the concentration of a annular sector given the number of species
// and the level at which the annular sector is positioned
inline double PolarCsvToInputFilesConverter::computeConcentrationWrtArea(double amount, int circleIndex) {
    return amount / ((2 * (circleIndex - 1)) + 1);
}

// Compute the normalised concentration by considering the maximum concentration
// and the area of the current annular sector
inline double PolarCsvToInputFilesConverter::computeNormalisedConcentration(double concentration, int circleIndex) {
    return (concentration / maximumConcentration);
}

// Update the maximum value if any of the concentrations from the
// provided string are greater than it
void PolarCsvToInputFilesConverter::updateMaximumConcentration(const string &currentLine, double &maximumConcentration) {
    double simulationTime;

    vector<double> concentrations = splitLineInConcentrations(currentLine, simulationTime);

    for (vector<double>::iterator it = concentrations.begin(); it != concentrations.end(); it++) {
        if ((*it) > maximumConcentration) {
            maximumConcentration = (*it);
        }
    }
}
