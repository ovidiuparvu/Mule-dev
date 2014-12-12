#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"
#include "multiscale/exception/InvalidInputException.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

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

float *RectangularMatFactory::readValuesFromFile(std::ifstream &fin) {
    float value = 0;

    // Create an array of floats
    float *data = new float[rows * cols];

    // Compute the number of expected values
    std::size_t nrOfValues = rows * cols;

    // Read the values from the input file stream
    for (std::size_t i = 0; i < nrOfValues; i++) {
        fin >> value;

        if ((value < 0) || (value > 1)) {
            MS_throw(InvalidInputException, ERR_INVALID_VALUE);
        }

        // Scale up the value to the interval [0, 255]
        data[i] = (value * 255);
    }

    // Return the values read from the input file stream
    return data;
}


// Constants
const std::string RectangularMatFactory::ERR_INVALID_VALUE = "All values have to be between 0 and 1.";
