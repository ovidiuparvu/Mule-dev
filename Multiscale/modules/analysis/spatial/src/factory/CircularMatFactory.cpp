#include "multiscale/analysis/spatial/factory/CircularMatFactory.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/UnimplementedMethodException.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace multiscale::analysis;


CircularMatFactory::CircularMatFactory() : MatFactory() {}

CircularMatFactory::~CircularMatFactory() {}

cv::Mat CircularMatFactory::createFromImageFile(const std::string &inputFilePath) {
    cv::Mat initialImage;
    cv::Mat grayscaleImage;

    // Read the initial image from disk in 32FC3 format
    cv::imread(inputFilePath, CV_LOAD_IMAGE_COLOR).convertTo(initialImage, CV_32FC3);

    // Convert the image to grayscale considering 32-bit floating point precision
    cv::cvtColor(initialImage, grayscaleImage, CV_BGR2GRAY);

    // Check if the input image is valid
    isValidInputImage(grayscaleImage, inputFilePath);

    // Create a circular image which masks out all pixels outside the circle
    cv::Mat circularGrayscaleImage = cv::Mat::zeros(grayscaleImage.size(), CV_32FC1);

    grayscaleImage.copyTo(
        circularGrayscaleImage,
        createCircularMaskFromCentreToEdge(grayscaleImage)
    );

    // Return the resulting circular grayscale image
    return circularGrayscaleImage;
}

void CircularMatFactory::readValuesFromFile(std::ifstream& fin, cv::Mat &image) {
    MS_throw(UnimplementedMethodException, ERR_UNIMPLEMENTED_METHOD);

    // Statement not executed but added to avoid warning messages
    throw UnimplementedMethodException(__FILE__, __LINE__, ERR_UNIMPLEMENTED_METHOD);
}

cv::Mat CircularMatFactory::createCircularMaskFromCentreToEdge(const cv::Mat &image) {
    // Start with a blank mask where all pixels have 0 intensity
    cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);

    // Compute the image centre point
    cv::Point imageCentrePoint((image.cols + 1) / 2, (image.rows + 1) / 2);

    // Compute the radius of the circular mask
    double radius = static_cast<double>(std::min(image.cols, image.rows)) / 2.0;

    // Draw max intensity pixels of the mask
    cv::circle(
        mask, imageCentrePoint, radius,
        cv::Scalar(INTENSITY_MAX, INTENSITY_MAX, INTENSITY_MAX),
        CV_FILLED
    );

    return mask;
}


// Constants
const std::string CircularMatFactory::ERR_UNIMPLEMENTED_METHOD = "The method you called is not implemented.";

const int CircularMatFactory::INTENSITY_MAX = 1;
