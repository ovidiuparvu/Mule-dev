#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"

#include "opencv2/highgui/highgui.hpp"

using namespace multiscale::analysis;


RectangularMatFactory::RectangularMatFactory() : MatFactory() {}

RectangularMatFactory::~RectangularMatFactory() {}

Mat RectangularMatFactory::createFromViewerImage(const string &inputFile) {
    Mat image = imread(inputFile, CV_LOAD_IMAGE_GRAYSCALE);

    isValidViewerImage(image);

    return image(Rect(ROI_START_X, ROI_START_Y, ROI_WIDTH, ROI_HEIGHT));
}

double RectangularMatFactory::maxColourBarIntensityFromViewerImage(const string &inputFile) {
    Mat image = imread(inputFile, CV_LOAD_IMAGE_GRAYSCALE);

    isValidViewerImage(image);

    return (double)image.at<uchar>(Point(COLOURBAR_MAX_X, COLOURBAR_MAX_Y));
}

unsigned char *RectangularMatFactory::processConcentrations(ifstream& fin) {
    unsigned char *data = new unsigned char[rows*cols];
    int nrOfConcentrations = rows * cols;
    double concentration = 0;

    for (int i = 0; i < nrOfConcentrations; i++) {
        fin >> concentration;

        if ((concentration < 0) || (concentration > 1))
            throw ERR_CONC;

        data[i] = convertToIntensity(concentration);
    }

    return data;
}

bool RectangularMatFactory::isValidViewerImage(const Mat &image) {
    if (!image.data)
        throw ERR_INPUT_OPEN;

    if ((image.cols != INPUT_IMG_WIDTH) || (image.rows != INPUT_IMG_HEIGHT))
        throw ERR_IMG_RESOLUTION;

    return true;
}
