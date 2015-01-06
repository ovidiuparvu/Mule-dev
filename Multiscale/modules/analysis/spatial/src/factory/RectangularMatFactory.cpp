#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/Numeric.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace multiscale;
using namespace multiscale::analysis;


RectangularMatFactory::RectangularMatFactory() : MatFactory() {}

RectangularMatFactory::~RectangularMatFactory() {}

cv::Mat RectangularMatFactory::createFromImageFile(const std::string &inputFilePath) {
    cv::Mat initialImage;
    cv::Mat grayscaleImage;

    // Read the initial image from disk in 32FC3 format
    cv::imread(inputFilePath, CV_LOAD_IMAGE_COLOR).convertTo(initialImage, CV_32FC3);

    // Convert the image to grayscale considering 32-bit floating point precision
    cv::cvtColor(initialImage, grayscaleImage, CV_BGR2GRAY);

    // Check if the image is valid
    isValidInputImage(grayscaleImage, inputFilePath);

    // Return the grayscale image
    return grayscaleImage;
}

void RectangularMatFactory::readValuesFromFile(std::ifstream &fin, cv::Mat &image) {
    float value;

    // Read the values from the input file stream
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            readNextValueFromFile(fin, value);
            validateValue(value);

            // Scale up the value to the interval [0, 255]
            image.at<float>(i, j) = (value * 255.0);
        }
    }
}

void RectangularMatFactory::validateValue(float value) {
    if ((value < 0) || (value > 1)) {
        MS_throw(InvalidInputException, ERR_INVALID_VALUE);
    }
}


// Constants
const std::string RectangularMatFactory::ERR_INVALID_VALUE = "All values have to be between 0 and 1.";
