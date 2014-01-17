#include "multiscale/analysis/spatial/factory/CircularMatFactory.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/UnimplementedMethodException.hpp"

#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace multiscale::analysis;

CircularMatFactory::CircularMatFactory() : MatFactory() {}

CircularMatFactory::~CircularMatFactory() {}

Mat CircularMatFactory::createFromViewerImage(const string &inputFile) {
    Mat image = imread(inputFile, CV_LOAD_IMAGE_GRAYSCALE);

    isValidViewerImage(image);

    Mat croppedImage = image(
                            Rect(
                                ROI_START_X - ROI_RADIUS,
                                ROI_START_Y - ROI_RADIUS,
                                2 * ROI_RADIUS, 2 * ROI_RADIUS
                            )
                       );
    Mat circularImage = Mat::zeros(croppedImage.size(), CV_8UC1);

    croppedImage.copyTo(circularImage, createCircularMask(ROI_RADIUS, ROI_RADIUS, ROI_RADIUS - 1, croppedImage));

    return circularImage;
}

double CircularMatFactory::maxColourBarIntensityFromViewerImage(const string &inputFile) {
    Mat image = imread(inputFile, CV_LOAD_IMAGE_GRAYSCALE);

    isValidViewerImage(image);

    return (double)image.at<uchar>(Point(COLOURBAR_MAX_X, COLOURBAR_MAX_Y));
}

unsigned char * CircularMatFactory::processConcentrations(ifstream& fin) {
    MS_throw(UnimplementedMethodException, ERR_UNIMPLEMENTED_METHOD);

    // Statement not executed but added to overcome warning message
    throw UnimplementedMethodException(__FILE__, __LINE__, ERR_UNIMPLEMENTED_METHOD);
}

Mat CircularMatFactory::createCircularMask(unsigned int originX, unsigned int originY,
                                           unsigned int radius, const Mat &image) {
    Mat mask = Mat::zeros(image.size(), CV_8UC1);

    circle(mask, Point(originX, originY), radius, Scalar(INTENSITY_MAX, INTENSITY_MAX, INTENSITY_MAX), CV_FILLED);

    return mask;
}

bool CircularMatFactory::isValidViewerImage(const Mat &image) {
    if (!image.data) {
        MS_throw(InvalidInputException, ERR_INPUT_OPEN);
    }

    if ((image.cols != INPUT_IMG_WIDTH) || (image.rows != INPUT_IMG_HEIGHT)) {
        MS_throw(InvalidInputException, ERR_IMG_RESOLUTION);
    }

    return true;
}


// Constants
const string CircularMatFactory::ERR_UNIMPLEMENTED_METHOD = "The method you called is not implemented.";

const int CircularMatFactory::INTENSITY_MAX     = 255;

const int CircularMatFactory::ROI_START_X       = 1024;
const int CircularMatFactory::ROI_START_Y       = 786;
const int CircularMatFactory::ROI_RADIUS        = 615;

const int CircularMatFactory::INPUT_IMG_WIDTH   = 2048;
const int CircularMatFactory::INPUT_IMG_HEIGHT  = 1572;

const int CircularMatFactory::COLOURBAR_MAX_X   = 1775;
const int CircularMatFactory::COLOURBAR_MAX_Y   = 56;