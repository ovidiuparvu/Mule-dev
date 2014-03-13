#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/IOException.hpp"
#include "multiscale/util/Filesystem.hpp"
#include "multiscale/verification/spatial-temporal/data/LogicPropertyDataReader.hpp"

using namespace multiscale::verification;


std::vector<std::string> LogicPropertyDataReader::readLogicQueriesFromFile(const std::string &inputFilepath) {
    if (!Filesystem::isValidFilePath(inputFilepath)) {
        MS_throw(InvalidInputException, ERR_INVALID_INPUT_PATH);
    }

    return readLogicQueriesFromValidFilepath(inputFilepath);
}

std::vector<std::string> LogicPropertyDataReader::readLogicQueriesFromValidFilepath(const std::string &inputFilepath) {
    std::ifstream fin(inputFilepath, std::ifstream::in);

    if (!fin.is_open()) {
        MS_throw(IOException, ERR_OPEN_INPUT_FILE);
    }

    std::vector<std::string> logicQueries = readLogicQueriesFromOpenStream(fin);

    fin.close();

    return logicQueries;
}

std::vector<std::string> LogicPropertyDataReader::readLogicQueriesFromOpenStream(std::ifstream &fin) {
    std::vector<std::string> logicQueries;
    std::string currentLine;

    while (getline(fin, currentLine)) {
        processLineFromInputFile(currentLine, logicQueries);
    }

    createNewLogicProperty(logicQueries);

    return logicQueries;
}

void LogicPropertyDataReader::processLineFromInputFile(const std::string &line,
                                                    std::vector<std::string> &logicQueries) {
    if (line.size() > 0) {
        if (line[0] == CHAR_START_LOGIC_QUERY) {
            createNewLogicProperty(logicQueries);
            appendLineUsingStringBuilder(line);
        } else if (line[0] == CHAR_START_COMMENT) {
            // Ignore
        } else {
            appendLineUsingStringBuilder(line);
        }
    }
}

void LogicPropertyDataReader::createNewLogicProperty(std::vector<std::string> &logicQueries) {
    std::string stringBuilderContent;

    stringBuilderContent = stringBuilder.str();

    if (stringBuilderContent.size() > 0) {
        logicQueries.push_back(stringBuilderContent);
    }

    removeStringBuilderContents();
}

void LogicPropertyDataReader::appendLineUsingStringBuilder(const std::string &line) {
    stringBuilder << line << std::endl;
}

void LogicPropertyDataReader::removeStringBuilderContents() {
    stringBuilder.str(std::string());
}


// Constants
const std::string LogicPropertyDataReader::ERR_INVALID_INPUT_PATH  = "The path to the file containing the logic queries is invalid. Please change.";
const std::string LogicPropertyDataReader::ERR_OPEN_INPUT_FILE     = "The file containing the logic queries could not be opened. Please make sure it is not used by another process.";

const char LogicPropertyDataReader::CHAR_START_LOGIC_QUERY = 'P';
const char LogicPropertyDataReader::CHAR_START_COMMENT     = '#';
