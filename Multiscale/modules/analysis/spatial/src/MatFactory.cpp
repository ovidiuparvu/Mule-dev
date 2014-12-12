#include "multiscale/analysis/spatial/MatFactory.hpp"
#include "multiscale/exception/FileOpenException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"

using namespace multiscale;
using namespace analysis;


MatFactory::MatFactory() : rows(0), cols(0), simulationTime(0) {}

MatFactory::~MatFactory() {}

cv::Mat MatFactory::createFromTextFile(const std::string &inputFilePath) {
    std::ifstream fin;

    // Initialise the input file stream
    initInputFile(fin, inputFilePath);

    // Read the values from the input file
    void *data = readValuesFromFile(fin);

    // Close the input file stream
    closeInputFileStream(fin, inputFilePath);

    // Return the Mat object containing the given data
    return (
        cv::Mat(rows, cols, CV_32FC1, data)
    );
}

void MatFactory::initInputFile(std::ifstream &fin, const std::string& inputFilePath) {
    fin.open(inputFilePath, std::ios_base::in);

    // Check if the file was successfully opened
    if (!fin.is_open()) {
        MS_throw(
            FileOpenException,
            ERR_OPEN_INPUT_FILE_BEGIN +
            inputFilePath +
            ERR_OPEN_INPUT_FILE_END
        );
    }

    // Read the number of rows, columns, respectively the corresponding simulation time
    fin >> rows >> cols >> simulationTime;
}

void MatFactory::closeInputFileStream(std::ifstream &fin, const std::string &inputFilePath) {
    // Check if the file contains additional unnecessary data
    // after excluding the cv::line feed character
    fin.get();

    if (fin.peek() != EOF) {
        MS_throw(
            InvalidInputException,
            ERR_INPUT_FILE_EXTRA_DATA_BEGIN +
            inputFilePath +
            ERR_INPUT_FILE_EXTRA_DATA_END
        );
    }

    fin.close();
}

bool MatFactory::isValidInputImage(const cv::Mat &image, const std::string &imageFilePath) {
    if (!image.data) {
        MS_throw(
            InvalidInputException,
            ERR_OPEN_INPUT_FILE_BEGIN +
            imageFilePath +
            ERR_OPEN_INPUT_FILE_END
        );
    }

    return true;
}


// Constants
const std::string MatFactory::ERR_OPEN_INPUT_FILE_BEGIN = "The input file (";
const std::string MatFactory::ERR_OPEN_INPUT_FILE_END   = ") could not be opened.";

const std::string MatFactory::ERR_INPUT_FILE_EXTRA_DATA_BEGIN   = "The input file (";
const std::string MatFactory::ERR_INPUT_FILE_EXTRA_DATA_END     = ") contains more data than required. Please change.";

const std::string MatFactory::ERR_INVALID_IMAGE_FILE_BEGIN  = "The provided image input file (";
const std::string MatFactory::ERR_INVALID_IMAGE_FILE_END    = ") is invalid. Please change.";
