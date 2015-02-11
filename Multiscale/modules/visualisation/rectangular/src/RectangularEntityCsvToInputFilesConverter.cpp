#include "multiscale/exception/FileOpenException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/visualisation/rectangular/RectangularEntityCsvToInputFilesConverter.hpp"
#include "multiscale/util/iterator/NumberIteratorType.hpp"
#include "multiscale/util/iterator/LexicographicNumberIterator.hpp"
#include "multiscale/util/iterator/StandardNumberIterator.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace multiscale::visualisation;
using namespace multiscale;


RectangularEntityCsvToInputFilesConverter::RectangularEntityCsvToInputFilesConverter(
    const std::string &inputFilepath, const std::string &outputFilepath, unsigned int height,
    unsigned int width, unsigned int nrOfEntities, unsigned int maxNrOfEntitiesPerPosition,
    NumberIteratorType numberIteratorType
) {
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
    std::ifstream fin;

    validateMaxNrOfEntitiesPerPosition();
    validateInput(fin);

    initInputFile(fin);
    processInputFile(fin);

    fin.close();
}

void RectangularEntityCsvToInputFilesConverter::initInputFile(std::ifstream &fin) {
    fin.open(inputFilepath, std::ios_base::in);

    if (!fin.is_open()) {
        MS_throw(FileOpenException, ERR_INPUT_OPEN);
    }
}

void RectangularEntityCsvToInputFilesConverter::initOutputFile(std::ofstream &fout, unsigned int index,
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
        MS_throw(InvalidInputException, ERR_MAX_NR_ENTITIES);
    }
}

void RectangularEntityCsvToInputFilesConverter::validateInput(std::ifstream &fin) {
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

void RectangularEntityCsvToInputFilesConverter::validateInputLine(const std::string &currentLine,
                                                                  unsigned int lineNumber) {
    std::vector<std::string> tokens = StringManipulator::split(currentLine, INPUT_FILE_SEPARATOR);

    if (tokens.size() < ((nrOfEntities * 2) + 1)) {
        MS_throw(InvalidInputException, ERR_NR_COORDINATES);
    }

    // Validate simulation time
    validateSimulationTime(tokens[0], lineNumber);

    // Validate coordinates
    for (unsigned int i = 1; i <= nrOfEntities; i++) {
        validateCoordinate(tokens[i], lineNumber, true);
        validateCoordinate(tokens[i + nrOfEntities], lineNumber, false);
    }
}

void RectangularEntityCsvToInputFilesConverter::processInputFile(std::ifstream &fin) {
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

void RectangularEntityCsvToInputFilesConverter::processLine(const std::string &line, unsigned int outputIndex) {
    std::ofstream fout;
    double simulationTime;

    std::vector<double> entitiesGrid = splitLineInCoordinates(line, simulationTime);

    initOutputFile(fout, outputIndex, simulationTime);

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < (width - 1); j++) {
            fout << std::setprecision(OUTPUT_PRECISION)
                 << entitiesGrid[(i * width) + j] << OUTPUT_SEPARATOR;
        }

        fout << std::setprecision(OUTPUT_PRECISION)
             << entitiesGrid[(i * width) + width - 1] << std::endl;
    }

    fout.close();
}

std::vector<double> RectangularEntityCsvToInputFilesConverter::splitLineInCoordinates(const std::string &line,
                                                                                      double &simulationTime) {
    std::vector<double> entitiesGrid(height * width, 0);

    std::vector<std::string> tokens = StringManipulator::split(line, INPUT_FILE_SEPARATOR);
    simulationTime = computeSimulationTime(tokens[0]);

    entitiesIterator->reset();

    while (entitiesIterator->hasNext()) {
        unsigned int entityIndex = entitiesIterator->number();

        unsigned int xCoordinate = computeCoordinate(tokens[entityIndex + nrOfEntities], true);
        unsigned int yCoordinate = computeCoordinate(tokens[entityIndex], false);

        entitiesGrid[(width * (yCoordinate)) + (xCoordinate)] +=
            (static_cast<double>(1) / maxNrOfEntitiesPerPosition);
    }

    validateEntitiesGrid(entitiesGrid);

    return entitiesGrid;
}

double RectangularEntityCsvToInputFilesConverter::computeSimulationTime(const std::string &token) {
    double simulationTime = stod(token);

    if (simulationTime < 0) {
        MS_throw(InvalidInputException, ERR_NEG_SIM_TIME);
    }

    return simulationTime;
}

unsigned int RectangularEntityCsvToInputFilesConverter::computeCoordinate(const std::string &token,
                                                                          bool isOxCoordinate) {
    unsigned int coordinate = stoi(token);

    if (isOxCoordinate) {
        if (coordinate > width) {
            MS_throw(InvalidInputException, ERR_INVALID_OX_COORDINATE);
        }
    } else {
        if (coordinate > height) {
            MS_throw(InvalidInputException, ERR_INVALID_OY_COORDINATE);
        }
    }

    return coordinate;
}

void RectangularEntityCsvToInputFilesConverter::validateSimulationTime(const std::string &token,
                                                                       unsigned int lineNumber) {
    double simulationTime = stod(token);

    if (simulationTime < 0) {
        MS_throw(InvalidInputException,
                 std::string(ERR_INVALID_VALUE_LINE)  +
                 StringManipulator::toString<unsigned int>(lineNumber) +
                 std::string(ERR_INVALID_VALUE_TOKEN) +
                 StringManipulator::toString<double>(simulationTime)
        );
    }
}

void RectangularEntityCsvToInputFilesConverter::validateCoordinate(const std::string & token,
                                                                   unsigned int lineNumber,
                                                                   bool isOxCoordinate) {
    unsigned int coordinate = stoi(token);

    if (((isOxCoordinate) && ((coordinate > width))) ||
        ((!isOxCoordinate) && ((coordinate > height)))) {
        MS_throw(InvalidInputException,
                 std::string(ERR_INVALID_VALUE_LINE)  +
                 StringManipulator::toString<unsigned int>(lineNumber) +
                 std::string(ERR_INVALID_VALUE_TOKEN) +
                 StringManipulator::toString<unsigned int>(coordinate)
        );
    }
}

void RectangularEntityCsvToInputFilesConverter::validateEntitiesGrid(const std::vector<double> &entitiesGrid) {
    for (double gridPosition : entitiesGrid) {
        if ((gridPosition < 0) || (gridPosition > 1)) {
            MS_throw(InvalidInputException, ERR_INVALID_NR_ENTITIES);
        }
    }
}


// Constants
const int         RectangularEntityCsvToInputFilesConverter::OUTPUT_PRECISION        = std::numeric_limits<double>::max_digits10;

const std::string RectangularEntityCsvToInputFilesConverter::OUTPUT_EXTENSION        = ".in";
const std::string RectangularEntityCsvToInputFilesConverter::OUTPUT_SEPARATOR        = " ";
const std::string RectangularEntityCsvToInputFilesConverter::OUTPUT_FILE_SEPARATOR   = "_";
const std::string RectangularEntityCsvToInputFilesConverter::INPUT_FILE_SEPARATOR    = ",";

const std::string RectangularEntityCsvToInputFilesConverter::ERR_INVALID_NR_ENTITIES     = "The number of entities at the given position is invalid.";
const std::string RectangularEntityCsvToInputFilesConverter::ERR_INVALID_OX_COORDINATE   = "The value of the Ox coordinate is invalid.";
const std::string RectangularEntityCsvToInputFilesConverter::ERR_INVALID_OY_COORDINATE   = "The value of the Oy coordinate is invalid.";
const std::string RectangularEntityCsvToInputFilesConverter::ERR_MAX_NR_ENTITIES         = "The maximum number of entities per grid position is equal to zero.";
const std::string RectangularEntityCsvToInputFilesConverter::ERR_NR_COORDINATES          = "The number of coordinates in the input file does not match the values of the input parameters height, width and nrOfEntities.";
const std::string RectangularEntityCsvToInputFilesConverter::ERR_NEG_SIM_TIME            = "The simulation time must be non-negative.";
const std::string RectangularEntityCsvToInputFilesConverter::ERR_INPUT_OPEN              = "The input file could not be opened.";
const std::string RectangularEntityCsvToInputFilesConverter::ERR_INVALID_VALUE_LINE      = "Invalid value on line: ";
const std::string RectangularEntityCsvToInputFilesConverter::ERR_INVALID_VALUE_TOKEN     = ", value: ";
