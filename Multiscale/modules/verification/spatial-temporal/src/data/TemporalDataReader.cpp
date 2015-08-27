#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/util/FileReader.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/data/TemporalDataReader.hpp"

using namespace multiscale;
using namespace multiscale::verification;


TemporalDataReader::TemporalDataReader() : currentLineNumber(0) {}

SpatialTemporalTrace TemporalDataReader::readTimeSeriesFromFile(const std::string &filePath) {
    this->filePath = filePath;

    // Read the file contents and represent it as a collection of lines
    std::vector<std::string> inputFile = FileReader::readFileLineByLine(filePath, INPUT_FILE_EXTENSION);

    return readTimeSeriesFromFile(inputFile);
}

SpatialTemporalTrace TemporalDataReader::readTimeSeriesFromFile(const std::vector<std::string> &inputFile) {
    SpatialTemporalTrace trace(inputFile.size());

    if (isValidInputFile(inputFile)) {
        readInputFileHeader(inputFile);
        readInputFileContents(inputFile, trace);
    }

    return trace;
}

bool TemporalDataReader::isValidInputFile(const std::vector<std::string> &inputFile) {
    if (inputFile.empty()) {
        MS_throw(
            InvalidInputException,
            ERR_INPUT_FILE_EMPTY_BEGIN +
            filePath +
            ERR_INPUT_FILE_EMPTY_END
        );
    }

    return true;
}

void TemporalDataReader::readInputFileHeader(const std::vector<std::string> &inputFile) {
    // Advance the current line number
    ++currentLineNumber;

    // The first observable variable is always time
    observableVariables = StringManipulator::split(inputFile[0], INPUT_FILE_DELIMITER);

    validateObservableVariables();
    createNumericStateVariableIdsFromObservableVariables();
}

void TemporalDataReader::validateObservableVariables() {
    // Check if there are at least two observable variables in the collection i.e. (time + 1 observable variable)
    if (observableVariables.size() < 2) {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_NR_OBSERVABLE_VARIABLES_BEGIN +
            StringManipulator::toString<std::size_t>(observableVariables.size()) +
            ERR_INVALID_NR_OBSERVABLE_VARIABLES_END
        );
    }

    // Check if all observable variable names are non-empty
    for (const std::string &name : observableVariables) {
        if (name.empty()) {
            MS_throw(
                InvalidInputException,
                ERR_EMPTY_OBSERVABLE_VARIABLE_NAME
            );
        }
    }
}

void TemporalDataReader::createNumericStateVariableIdsFromObservableVariables() {
    numericStateVariableIds.reserve(observableVariables.size());

    for (const std::string &name : observableVariables) {
        numericStateVariableIds.push_back(
            NumericStateVariableId(name)
        );
    }
}

void TemporalDataReader::readInputFileContents(const std::vector<std::string> &inputFile,
                                               SpatialTemporalTrace &trace) {
    std::size_t nrOfLines = inputFile.size();

    // Process the lines of the input file (excluding the first header line)
    for (std::size_t i = 1; i < (nrOfLines - 1); ++i) {
        processLine(inputFile[i], trace);
    }

    // If the last line is non-empty process it
    if (!inputFile[nrOfLines - 1].empty()) {
        processLine(inputFile[nrOfLines - 1], trace);
    }
}

void TemporalDataReader::processLine(const std::string &line, SpatialTemporalTrace &trace) {
    // Advance the current line number
    ++currentLineNumber;

    // Split the line into multiple values
    std::vector<std::string> lineValues = StringManipulator::split(line, INPUT_FILE_DELIMITER);

    // Process the values
    processLineTokens(lineValues, trace);
}

void TemporalDataReader::processLineTokens(const std::vector<std::string> &lineValues,
                                           SpatialTemporalTrace &trace) {
    if (lineValues.size() == observableVariables.size()) {
        createTimePointFromTokens(lineValues, trace);
    } else {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_NR_LINE_TOKENS_BEGIN +
            StringManipulator::toString<unsigned long>(currentLineNumber) +
            ERR_INVALID_NR_LINE_TOKENS_MIDDLE +
            filePath +
            ERR_INVALID_NR_LINE_TOKENS_END
        );
    }
}

void TemporalDataReader::createTimePointFromTokens(const std::vector<std::string> &lineTokens,
                                                   SpatialTemporalTrace &trace) {
    TimePoint timePoint;

    setTimePointValue(lineTokens, timePoint);
    addNumericStateVariablesToTimePoint(lineTokens, timePoint);

    trace.addTimePoint(timePoint);
}

void TemporalDataReader::setTimePointValue(const std::vector<std::string> &lineTokens,
                                           TimePoint &timePoint) {
    double timePointValue = StringManipulator::convert<double>(lineTokens[0]);

    timePoint.setValue(timePointValue);
}

void TemporalDataReader::addNumericStateVariablesToTimePoint(const std::vector<std::string> &lineTokens,
                                                             TimePoint &timePoint) {
    std::size_t nrOfTokens = lineTokens.size();

    for (std::size_t i = 1; i < nrOfTokens; i++) {
        double observableVariableValue = StringManipulator::convert<double>(lineTokens[i]);

        timePoint.addNumericStateVariable(
            numericStateVariableIds[i],
            observableVariableValue
        );
    }
}


// Constants
const std::string TemporalDataReader::INPUT_FILE_EXTENSION = ".csv";

const std::string TemporalDataReader::INPUT_FILE_DELIMITER = ",; \t";

const std::string TemporalDataReader::ERR_INPUT_FILE_EMPTY_BEGIN    = "The spatio-temporal trace could not be created because the provided input file (";
const std::string TemporalDataReader::ERR_INPUT_FILE_EMPTY_END      = ") is empty. Please change.";

const std::string TemporalDataReader::ERR_INVALID_NR_OBSERVABLE_VARIABLES_BEGIN = "The number of observable variables (";
const std::string TemporalDataReader::ERR_INVALID_NR_OBSERVABLE_VARIABLES_END   = ") should be greater or equal to two. Please change.";

const std::string TemporalDataReader::ERR_EMPTY_OBSERVABLE_VARIABLE_NAME    = "The name of one of the observable variables is empty when it should contain at least one character. Please change.";

const std::string TemporalDataReader::ERR_INVALID_NR_LINE_TOKENS_BEGIN  = "The number of tokens on line ";
const std::string TemporalDataReader::ERR_INVALID_NR_LINE_TOKENS_MIDDLE = " of input file ";
const std::string TemporalDataReader::ERR_INVALID_NR_LINE_TOKENS_END    = " is different from the number of observable variables in the header. Please change.";
