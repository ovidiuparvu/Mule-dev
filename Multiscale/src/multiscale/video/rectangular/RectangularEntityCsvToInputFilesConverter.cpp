#include "multiscale/exception/RectangularEntityCsvToInputFilesConverterException.hpp"
#include "multiscale/video/rectangular/RectangularEntityCsvToInputFilesConverter.hpp"
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


RectangularEntityCsvToInputFilesConverter::RectangularEntityCsvToInputFilesConverter(const string &inputFilepath,
                                                                                     const string &outputFilepath,
                                                                                     unsigned int height,
                                                                                     unsigned int width,
                                                                                     unsigned int nrOfEntities,
                                                                                     unsigned int maxNrOfEntitiesPerPosition,
                                                                                     NumberIteratorType numberIteratorType) {
    this->inputFilepath  = inputFilepath;
    this->outputFilepath = outputFilepath;

    this->height       = height;
    this->width        = width;
    this->nrOfEntities = nrOfEntities;

    this->maxNrOfEntitiesPerPosition = maxNrOfEntitiesPerPosition;

    initIterators(numberIteratorType);
}

RectangularEntityCsvToInputFilesConverter::~RectangularEntityCsvToInputFilesConverter() {
    delete entitiesIterator;
}

void RectangularEntityCsvToInputFilesConverter::convert() {
    ifstream fin;

    validateMaxNrOfEntitiesPerPosition();
    validateInput(fin);

    initInputFile(fin);
    processInputFile(fin);

    fin.close();
}

void RectangularEntityCsvToInputFilesConverter::initInputFile(ifstream &fin) {
    fin.open(inputFilepath, ios_base::in);

    if (!fin.is_open()) {
        MS_throw(RectangularEntityCsvToInputFilesConverterException, ERR_INPUT_OPEN);
    }
}

void RectangularEntityCsvToInputFilesConverter::initOutputFile(ofstream &fout, unsigned int index, double &simulationTime) {
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

void RectangularEntityCsvToInputFilesConverter::initIterators(const NumberIteratorType &numberIteratorType) {
    switch (numberIteratorType) {
    case multiscale::STANDARD:
        entitiesIterator = new StandardNumberIterator(nrOfEntities);
        break;

    case multiscale::LEXICOGRAPHIC:
        entitiesIterator = new LexicographicNumberIterator(nrOfEntities);
        break;

    default:
        entitiesIterator = nullptr;
        break;
    }
}

void RectangularEntityCsvToInputFilesConverter::validateMaxNrOfEntitiesPerPosition() {
    if (maxNrOfEntitiesPerPosition == 0) {
        MS_throw(RectangularEntityCsvToInputFilesConverterException, ERR_MAX_NR_ENTITIES);
    }
}

void RectangularEntityCsvToInputFilesConverter::validateInput(ifstream &fin) {
    unsigned int lineNumber = 0;
    string currentLine;

    fin.open(inputFilepath, ios_base::in);

    if (!fin.is_open()) {
        MS_throw(RectangularEntityCsvToInputFilesConverterException, ERR_INPUT_OPEN);
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

void RectangularEntityCsvToInputFilesConverter::validateInputLine(const string &currentLine, unsigned int lineNumber) {
    vector<string> tokens = StringManipulator::split(currentLine, INPUT_FILE_SEPARATOR);

    if (tokens.size() < ((nrOfEntities * 2) + 1)) {
        MS_throw(RectangularEntityCsvToInputFilesConverterException, ERR_NR_COORDINATES);
    }

    // Validate simulation time
    validateSimulationTime(tokens[0], lineNumber);

    // Validate coordinates
    for (unsigned int i = 1; i <= nrOfEntities; i++) {
        validateCoordinate(tokens[i], lineNumber, true);
        validateCoordinate(tokens[i + nrOfEntities], lineNumber, false);
    }
}

void RectangularEntityCsvToInputFilesConverter::processInputFile(ifstream &fin) {
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

void RectangularEntityCsvToInputFilesConverter::processLine(const string &line, unsigned int outputIndex) {
    ofstream fout;
    double simulationTime;

    vector<double> entitiesGrid = splitLineInCoordinates(line, simulationTime);

    initOutputFile(fout, outputIndex, simulationTime);

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < (width - 1); j++) {
            fout << entitiesGrid[(i * width) + j] << OUTPUT_SEPARATOR;
        }

        fout << entitiesGrid[(i * width) + width - 1] << endl;
    }

    fout.close();
}

vector<double> RectangularEntityCsvToInputFilesConverter::splitLineInCoordinates(const string &line, double &simulationTime) {
    vector<double> entitiesGrid(height * width, 0);

    vector<string> tokens = StringManipulator::split(line, INPUT_FILE_SEPARATOR);
    simulationTime = computeSimulationTime(tokens[0]);

    entitiesIterator->reset();

    while (entitiesIterator->hasNext()) {
        unsigned int entityIndex = entitiesIterator->number();

        unsigned int xCoordinate = computeCoordinate(tokens[entityIndex + nrOfEntities], true);
        unsigned int yCoordinate = computeCoordinate(tokens[entityIndex], false);

        entitiesGrid[(width * (yCoordinate - 1)) + (xCoordinate - 1)] += (static_cast<double>(1) / maxNrOfEntitiesPerPosition);
    }

    validateEntitiesGrid(entitiesGrid);

    return entitiesGrid;
}

inline double RectangularEntityCsvToInputFilesConverter::computeSimulationTime(const string &token) {
    double simulationTime = stod(token);

    if (simulationTime < 0) {
        MS_throw(RectangularEntityCsvToInputFilesConverterException, ERR_NEG_SIM_TIME);
    }

    return simulationTime;
}

inline unsigned int RectangularEntityCsvToInputFilesConverter::computeCoordinate(const string &token, bool isOxCoordinate) {
    unsigned int coordinate = stoi(token);

    if (isOxCoordinate) {
        if (coordinate > width) {
            MS_throw(RectangularEntityCsvToInputFilesConverterException, ERR_INVALID_OX_COORDINATE);
        }
    } else {
        if (coordinate > height) {
            MS_throw(RectangularEntityCsvToInputFilesConverterException, ERR_INVALID_OY_COORDINATE);
        }
    }

    return coordinate;
}

inline void RectangularEntityCsvToInputFilesConverter::validateSimulationTime(const string &token, unsigned int lineNumber) {
    double simulationTime = stod(token);

    if (simulationTime < 0) {
        MS_throw(RectangularEntityCsvToInputFilesConverterException,
                 string(ERR_INVALID_VALUE_LINE)  +
                 StringManipulator::toString<unsigned int>(lineNumber) +
                 string(ERR_INVALID_VALUE_TOKEN) +
                 StringManipulator::toString<double>(simulationTime)
        );
    }
}

inline void RectangularEntityCsvToInputFilesConverter::validateCoordinate(const string & token, unsigned int lineNumber, bool isOxCoordinate) {
    unsigned int coordinate = stoi(token);

    if (((isOxCoordinate) && (coordinate > width)) || ((!isOxCoordinate) && (coordinate > height))) {
        MS_throw(RectangularEntityCsvToInputFilesConverterException,
                 string(ERR_INVALID_VALUE_LINE)  +
                 StringManipulator::toString<unsigned int>(lineNumber) +
                 string(ERR_INVALID_VALUE_TOKEN) +
                 StringManipulator::toString<unsigned int>(coordinate)
        );
    }
}

inline void RectangularEntityCsvToInputFilesConverter::validateEntitiesGrid(const vector<double> &entitiesGrid) {
    for (double gridPosition : entitiesGrid) {
        if ((gridPosition < 0) || (gridPosition > 1)) {
            MS_throw(RectangularEntityCsvToInputFilesConverterException, ERR_INVALID_NR_ENTITIES);
        }
    }
}
