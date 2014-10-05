#include "multiscale/analysis/spatial/factory/CircularMatFactory.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/UnimplementedMethodException.hpp"

#include "opencv2/highgui/highgui.hpp"

using namespace multiscale::analysis;


CircularMatFactory::CircularMatFactory() : MatFactory() {}

CircularMatFactory::~CircularMatFactory() {}

cv::Mat CircularMatFactory::createFromViewerImage(const std::string &inputFile) {
    cv::Mat image = cv::imread(inputFile, CV_LOAD_IMAGE_GRAYSCALE);

    isValidViewerImage(image);

    cv::Mat croppedImage = image(
                            cv::Rect(
                                ROI_START_X - ROI_RADIUS,
                                ROI_START_Y - ROI_RADIUS,
                                2 * ROI_RADIUS, 2 * ROI_RADIUS
                            )
                       );
    cv::Mat circularImage = cv::Mat::zeros(croppedImage.size(), CV_8UC1);

    croppedImage.copyTo(circularImage, createCircularMask(ROI_RADIUS, ROI_RADIUS, ROI_RADIUS - 1, croppedImage));

    return circularImage;
}

double CircularMatFactory::maxColourBarIntensityFromViewerImage(const std::string &inputFile) {
    cv::Mat image = cv::imread(inputFile, CV_LOAD_IMAGE_GRAYSCALE);

    isValidViewerImage(image);

    return (double)image.at<uchar>(cv::Point(COLOURBAR_MAX_X, COLOURBAR_MAX_Y));
}

unsigned char * CircularMatFactory::processConcentrations(std::ifstream& fin) {
    MS_throw(UnimplementedMethodException, ERR_UNIMPLEMENTED_METHOD);

    // Statement not executed but added to overcome warning message
    throw UnimplementedMethodException(__FILE__, __LINE__, ERR_UNIMPLEMENTED_METHOD);
}

cv::Mat CircularMatFactory::createCircularMask(unsigned int originX, unsigned int originY,
                                               unsigned int radius, const cv::Mat &image) {
    cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);

    cv::circle(mask, cv::Point(originX, originY), radius, cv::Scalar(INTENSITY_MAX, INTENSITY_MAX, INTENSITY_MAX),
               CV_FILLED);

    return mask;
}

bool CircularMatFactory::isValidViewerImage(const cv::Mat &image) {
    if (!image.data) {
        MS_throw(InvalidInputException, ERR_INPUT_OPEN);
    }

    if ((image.cols != INPUT_IMG_WIDTH) || (image.rows != INPUT_IMG_HEIGHT)) {
        MS_throw(InvalidInputException, ERR_IMG_RESOLUTION);
    }

    return true;
}


// Constants
const std::string CircularMatFactory::ERR_UNIMPLEMENTED_METHOD = "The method you called is not implemented.";

const int CircularMatFactory::INTENSITY_MAX     = 255;

const int CircularMatFactory::ROI_START_X       = 1024;
const int CircularMatFactory::ROI_START_Y       = 786;
const int CircularMatFactory::ROI_RADIUS        = 615;

const int CircularMatFactory::INPUT_IMG_WIDTH   = 2048;
const int CircularMatFactory::INPUT_IMG_HEIGHT  = 1572;

const int CircularMatFactory::COLOURBAR_MAX_X   = 1775;
const int CircularMatFactory::COLOURBAR_MAX_Y   = 56;
