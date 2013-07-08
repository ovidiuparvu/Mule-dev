#include "multiscale/analysis/spatial/factory/CircularMatFactory.hpp"

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

unsigned char * CircularMatFactory::processConcentrations(ifstream& fin) {
    throw ERR_UNIMPLEMENTED_METHOD;
}

Mat CircularMatFactory::createCircularMask(unsigned int originX, unsigned int originY,
                                           unsigned int radius, const Mat &image) {
    Mat mask = Mat::zeros(image.size(), CV_8UC1);

    circle(mask, Point(originX, originY), radius, Scalar(INTENSITY_MAX, INTENSITY_MAX, INTENSITY_MAX), CV_FILLED);

    return mask;
}

bool CircularMatFactory::isValidViewerImage(const Mat &image) {
    if (!image.data)
        throw ERR_INPUT_OPEN;

    if ((image.cols != INPUT_IMG_WIDTH) || (image.rows != INPUT_IMG_HEIGHT))
        throw ERR_IMG_RESOLUTION;

    return true;
}
