#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/util/Filesystem.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/data/TemporalDataReader.hpp"

using namespace multiscale;
using namespace multiscale::verification;


TemporalDataReader::TemporalDataReader() : currentLineNumber(0) {}

SpatialTemporalTrace TemporalDataReader::readTimeseriesFromFile(const std::string &filePath) {
    if (Filesystem::isValidFilePath(filePath, INPUT_FILE_EXTENSION)) {
        this->filePath = filePath;
        this->currentLineNumber = 0;

        return readFromValidInputFile();
    } else {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_INPUT_FILE_PATH_BEGIN +
            filePath +
            ERR_INVALID_INPUT_FILE_PATH_END
        );
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return SpatialTemporalTrace();
}

SpatialTemporalTrace TemporalDataReader::readFromValidInputFile() {
    SpatialTemporalTrace trace;

    std::ifstream fin(filePath, std::ifstream::in);

    readFromValidOpenedInputFile(fin, trace);

    fin.close();

    return trace;
}

void TemporalDataReader::readFromValidOpenedInputFile(std::ifstream &fin, SpatialTemporalTrace &trace) {
    if (fin.is_open()) {
        readInputFileHeader(fin, trace);
        readInputFileContents(fin, trace);
    } else {
        MS_throw(
            InvalidInputException,
            ERR_OPEN_INPUT_FILE_BEGIN +
            filePath +
            ERR_OPEN_INPUT_FILE_END
        );
    }
}

void TemporalDataReader::readInputFileHeader(std::ifstream &fin, SpatialTemporalTrace &trace) {
    std::string headerRow;

    getline(fin, headerRow);

    // Advance the current line number
    currentLineNumber++;

    // The first observable variable is always time
    observableVariables = StringManipulator::split(headerRow, INPUT_FILE_DELIMITER);

    validateObservableVariables();
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
    for (auto name : observableVariables) {
        if (name.empty()) {
            MS_throw(
                InvalidInputException,
                ERR_EMPTY_OBSERVABLE_VARIABLE_NAME
            );
        }
    }
}

void TemporalDataReader::readInputFileContents(std::ifstream &fin, SpatialTemporalTrace &trace) {
    std::string              line;
    std::vector<std::string> lineValues;

    while (!fin.eof()) {
        getline(fin, line);

        // Consider processing the line only if it has content
        if (!line.empty()) {
            // Advance the current line number
            currentLineNumber++;

            lineValues = StringManipulator::split(line, INPUT_FILE_DELIMITER);

            processLineTokens(lineValues, trace);
        }
    }
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
    unsigned long timePointValue = StringManipulator::convert<unsigned long>(lineTokens[0]);

    timePoint.setValue(timePointValue);
}

void TemporalDataReader::addNumericStateVariablesToTimePoint(const std::vector<std::string> &lineTokens,
                                                             TimePoint &timePoint) {
    std::size_t nrOfTokens = lineTokens.size();

    for (std::size_t i = 1; i < nrOfTokens; i++) {
        double observableVariableValue = StringManipulator::convert<double>(lineTokens[i]);

        timePoint.addNumericStateVariable(
            NumericStateVariableId(observableVariables[i]),
            observableVariableValue
        );
    }
}


// Constants
const std::string TemporalDataReader::INPUT_FILE_EXTENSION = ".csv";

const std::string TemporalDataReader::INPUT_FILE_DELIMITER = ",";

const std::string TemporalDataReader::ERR_INVALID_INPUT_FILE_PATH_BEGIN = "The provided input file path (";
const std::string TemporalDataReader::ERR_INVALID_INPUT_FILE_PATH_END   = ") does not point to a file with the required extension. Please change.";

const std::string TemporalDataReader::ERR_OPEN_INPUT_FILE_BEGIN = "The provided input file (";
const std::string TemporalDataReader::ERR_OPEN_INPUT_FILE_END   = ") could not be opened. Please make sure it is available and not currently used by another process.";

const std::string TemporalDataReader::ERR_INVALID_NR_OBSERVABLE_VARIABLES_BEGIN = "The number of observable variables (";
const std::string TemporalDataReader::ERR_INVALID_NR_OBSERVABLE_VARIABLES_END   = ") should be greater or equal to two. Please change.";

const std::string TemporalDataReader::ERR_EMPTY_OBSERVABLE_VARIABLE_NAME    = "The name of one of the observable variables is empty when it should contain at least one character. Please change.";

const std::string TemporalDataReader::ERR_INVALID_NR_LINE_TOKENS_BEGIN  = "The number of tokens on line ";
const std::string TemporalDataReader::ERR_INVALID_NR_LINE_TOKENS_MIDDLE = " of input file ";
const std::string TemporalDataReader::ERR_INVALID_NR_LINE_TOKENS_END    = " is different from the number of observable variables in the header. Please change.";
