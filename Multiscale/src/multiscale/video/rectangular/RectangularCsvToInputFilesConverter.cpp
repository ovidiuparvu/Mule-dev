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

// Constructor for the class
RectangularCsvToInputFilesConverter::RectangularCsvToInputFilesConverter(string inputFilepath,
                                                                         string outputFilepath,
                                                                         unsigned int height,
                                                                         unsigned int width,
                                                                         unsigned int nrOfConcentrationsForPosition,
                                                                         NumberIteratorType numberIteratorType) {
    this->inputFilepath                 = inputFilepath;
    this->outputFilepath                = outputFilepath;

    this->height                        = height;
    this->width                         = width;
    this->nrOfConcentrationsForPosition = nrOfConcentrationsForPosition;

    this->concentrationsIndex           = 0;
    this->selectedConcentrationIndex    = 1;
    this->maximumConcentration          = 1;

    initIterators(numberIteratorType);
}

// Destructor for the class
RectangularCsvToInputFilesConverter::~RectangularCsvToInputFilesConverter() {
    delete circlesIterator;
    delete sectorsIterator;
}

// Convert the ".csv" file to input files
void RectangularCsvToInputFilesConverter::convert() {
    ifstream fin;

    validateInput(fin);

    initMaximumConcentration(fin);
    initInputFile(fin);
    processInputFile(fin);

    fin.close();
}

// Initialise the input file
void RectangularCsvToInputFilesConverter::initInputFile(ifstream& fin) {
    fin.open(inputFilepath.c_str(), ios_base::in);

    if (!fin.is_open()) throw ERR_INPUT_OPEN;
}

// Initialise the maximum concentration value
void RectangularCsvToInputFilesConverter::initMaximumConcentration(ifstream& fin) {
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
void RectangularCsvToInputFilesConverter::initOutputFile(ofstream& fout, unsigned int index, double& simulationTime) {
    fout.open(
                (
                    (outputFilepath + OUTPUT_FILE_SEPARATOR) +
                    StringManipulator::toString(index) +
                    OUTPUT_EXTENSION
                ).c_str(),
                ios_base::trunc
            );

    assert(fout.is_open());

    fout << height << OUTPUT_SEPARATOR
         << width  << OUTPUT_SEPARATOR
         << simulationTime << endl;
}

// Initialise the iterators
void RectangularCsvToInputFilesConverter::initIterators(NumberIteratorType& numberIteratorType) {
    switch (numberIteratorType) {
    case multiscale::STANDARD:
        circlesIterator = new StandardNumberIterator(height);
        sectorsIterator = new StandardNumberIterator(width);
        break;

    case multiscale::LEXICOGRAPHIC:
        circlesIterator = new LexicographicNumberIterator(height);
        sectorsIterator = new LexicographicNumberIterator(width);
        break;

    default:
        break;
    }
}

// Validate the input file
void RectangularCsvToInputFilesConverter::validateInput(ifstream& fin) {
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
void RectangularCsvToInputFilesConverter::validateInputLine(string& currentLine, unsigned int lineNumber) {
    vector<string> tokens = StringManipulator::split(currentLine, INPUT_FILE_SEPARATOR);

    if (tokens.size() < ((height * width * nrOfConcentrationsForPosition) + 1))
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
void RectangularCsvToInputFilesConverter::processInputFile(ifstream& fin) {
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
void RectangularCsvToInputFilesConverter::processLine(string& line, unsigned int outputIndex) {
    ofstream fout;
    double simulationTime;

    vector<double> concentrations = splitLineInConcentrations(line, simulationTime);

    initOutputFile(fout, outputIndex, simulationTime);

    for (unsigned int i = 0; i < height; i++) {
        for (int j = 0; j < (width - 1); j++) {
            fout << concentrations[(i * width) + j] << OUTPUT_SEPARATOR;
        }

        fout << concentrations[(i * width) + width - 1] << endl;
    }
}

// Split the line in concentrations and simulation time
vector<double> RectangularCsvToInputFilesConverter::splitLineInConcentrations(string line, double& simulationTime) {
    vector<double> concentrations(height * width);

    vector<string> tokens = StringManipulator::split(line, INPUT_FILE_SEPARATOR);

    simulationTime = computeSimulationTime(tokens[0]);
    concentrationsIndex = 1;

    circlesIterator->reset();

    while (circlesIterator->hasNext()) {
        unsigned int rowIndex = circlesIterator->number();

        sectorsIterator->reset();

        splitLineInConcentrations(concentrations, tokens, rowIndex);
    }

    return concentrations;
}

// Split the line into concentrations
void RectangularCsvToInputFilesConverter::splitLineInConcentrations(vector<double>& concentrations,
                                                                    vector<string>& tokens,
                                                                    unsigned int rowIndex) {
    while (sectorsIterator->hasNext()) {
        unsigned int sectorIndex = sectorsIterator->number();

        double concentration = computeNextPositionConcentration(concentrationsIndex,
                                                                tokens);

        concentrations[((rowIndex - 1) * width) + sectorIndex - 1] = concentration;

        concentrationsIndex++;
    }
}

// Compute the simulation time from the given string and verify if it is valid
double RectangularCsvToInputFilesConverter::computeSimulationTime(string token) {
    double simulationTime = atof(token.c_str());

    if (simulationTime < 0) throw ERR_NEG_SIM_TIME;

    return simulationTime;
}

// Compute the concentration of the next position
double RectangularCsvToInputFilesConverter::computeNextPositionConcentration(int concentrationIndex,
                                                                             vector<string>& tokens) {
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
    if (nrOfConcentrationsForPosition == 1)
        return computeNormalisedConcentration(totalConcentration);
    else {
        return (totalConcentration != 0) ? (concentration/totalConcentration) : 0;
    }
}

// Compute the concentration from the given string considering the number of concentrations for each position
double RectangularCsvToInputFilesConverter::computeConcentration(string concentration) {
    return (nrOfConcentrationsForPosition == 1)
                ? computeScaledConcentration(concentration)
                : computeNonScaledConcentration(concentration);
}

// Compute the non scaled concentration from the given string
double RectangularCsvToInputFilesConverter::computeNonScaledConcentration(string concentration) {
    return atof(concentration.c_str());
}

// Compute the scaled concentration from the given string by applying
// a logit transformation to it
double RectangularCsvToInputFilesConverter::computeScaledConcentration(string concentration) {
    double scaledConcentration = atof(concentration.c_str());

    // Convert all concentrations which are lower than 1 to 1,
    // such that we don't obtain negative values after applying log
    if (scaledConcentration < 1) {
        scaledConcentration = 1;
    }

    return log2(scaledConcentration);
}

// Compute the normalised concentration by considering the maximum concentration
// and the area of the current annular sector
double RectangularCsvToInputFilesConverter::computeNormalisedConcentration(double concentration) {
    return (concentration / maximumConcentration);
}

// Update the maximum value if any of the concentrations from the
// provided string are greater than it
void RectangularCsvToInputFilesConverter::updateMaximumConcentration(string& currentLine, double& maximumConcentration) {
    double simulationTime;

    vector<double> concentrations = splitLineInConcentrations(currentLine, simulationTime);

    for (vector<double>::iterator it = concentrations.begin(); it != concentrations.end(); it++) {
        if ((*it) > maximumConcentration) {
            maximumConcentration = (*it);
        }
    }
}
