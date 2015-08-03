#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/FileCloseException.hpp"
#include "multiscale/exception/FileOpenException.hpp"
#include "multiscale/util/FileReader.hpp"
#include "multiscale/util/Filesystem.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <sstream>

using namespace multiscale;


std::vector<std::string> FileReader::readFileLineByLine(const std::string &filePath,
                                                        const std::string &fileExtension) {
    validateFilePath(filePath, fileExtension);

    return readValidFileLineByLine(filePath);
}

void FileReader::validateFilePath(const std::string &filePath, const std::string &fileExtension) {
    if (!Filesystem::isValidFilePath(filePath, fileExtension)) {
        MS_throw(
            InvalidInputException,
            ERR_INVALID_INPUT_FILE_PATH_BEGIN +
            filePath +
            ERR_INVALID_INPUT_FILE_PATH_MIDDLE +
            fileExtension +
            ERR_INVALID_INPUT_FILE_PATH_END
        );
    }
}

std::vector<std::string> FileReader::readValidFileLineByLine(const std::string &filePath) {
    // Initialise input file stream considering the given valid file path
    std::ifstream fin(filePath, std::ios::in);

    // Read stream contents and split into lines
    std::vector<std::string> lines = readStreamContentsAndSplitLines(filePath, fin);

    // Close the input file stream
    closeInputFileStream(filePath, fin);

    // Return the collection of lines
    return lines;
}

std::vector<std::string> FileReader::readStreamContentsAndSplitLines(const std::string &filePath,
                                                                     std::ifstream &inputFileStream) {
    if (!inputFileStream.is_open()) {
        MS_throw(
            FileOpenException,
            ERR_OPEN_INPUT_FILE_STREAM_BEGIN +
            filePath +
            ERR_OPEN_INPUT_FILE_STREAM_END
        );
    }

    return readOpenStreamContentsAndSplitLines(filePath, inputFileStream);
}

std::vector<std::string> FileReader::readOpenStreamContentsAndSplitLines(const std::string &filePath,
                                                                         std::ifstream &inputFileStream) {
    // Allocate a buffer for reading data from stream
    char *buffer = new char[BUFFER_SIZE + 1];

    // Represent the entire stream contents as a string
    std::string streamContents = readOpenStreamContents(filePath, inputFileStream, buffer);

    // Deallocate buffer
    delete [] buffer;

    // Return contents split by new line character
    return (
        StringManipulator::split(
            streamContents,
            LINE_DELIMITER
        )
    );
}

std::string FileReader::readOpenStreamContents(const std::string &filePath,
                                               std::ifstream &inputFileStream,
                                               char *buffer) {
    std::stringstream stringBuilder;

    // Read input file stream contents
    while (!inputFileStream.eof()) {
        readFromInputFileStream(filePath, inputFileStream, buffer);

        stringBuilder << std::string(buffer, inputFileStream.gcount());
    }

    return stringBuilder.str();
}

void FileReader::readFromInputFileStream(const std::string &filePath,
                                         std::ifstream &inputFileStream,
                                         char *buffer) {
    inputFileStream.read(buffer, BUFFER_SIZE);

    if (inputFileStream.bad()) {
        MS_throw(
            InvalidInputException,
            ERR_READ_DATA_FROM_INPUT_FILE_STREAM_BEGIN +
            filePath +
            ERR_READ_DATA_FROM_INPUT_FILE_STREAM_END
        );
    }
}

void FileReader::closeInputFileStream(const std::string &filePath,
                                      std::ifstream &inputFileStream) {
    inputFileStream.close();

    if (inputFileStream.bad()) {
        MS_throw(
            FileCloseException,
            ERR_CLOSE_INPUT_FILE_STREAM_BEGIN +
            filePath +
            ERR_CLOSE_INPUT_FILE_STREAM_END
        );
    }
}



// Constants
const long int FileReader::BUFFER_SIZE = 1048576;

const std::string FileReader::ERR_INVALID_INPUT_FILE_PATH_BEGIN     = "The provided input file path (";
const std::string FileReader::ERR_INVALID_INPUT_FILE_PATH_MIDDLE    = ") does not point to a file with the required extension (";
const std::string FileReader::ERR_INVALID_INPUT_FILE_PATH_END       = "). Please change.";

const std::string FileReader::ERR_OPEN_INPUT_FILE_STREAM_BEGIN  = "The input file stream pointing to the file path \"";
const std::string FileReader::ERR_OPEN_INPUT_FILE_STREAM_END    = "\" could not be successfully initialized.";

const std::string FileReader::ERR_READ_DATA_FROM_INPUT_FILE_STREAM_BEGIN    = "Cannot read data from the input file stream corresponding to the file \"";
const std::string FileReader::ERR_READ_DATA_FROM_INPUT_FILE_STREAM_END      = "\". Please retry and ensure that the file is not opened/used by any other application.";

const std::string FileReader::ERR_CLOSE_INPUT_FILE_STREAM_BEGIN = "Cannot close the input file stream corresponding to the file \"";
const std::string FileReader::ERR_CLOSE_INPUT_FILE_STREAM_END   = "\".";
