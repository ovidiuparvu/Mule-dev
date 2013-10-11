#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"
#include "multiscale/exception/InvalidInputException.hpp"

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

        if ((concentration < 0) || (concentration > 1)) {
            MS_throw(InvalidInputException, ERR_CONC);
        }

        data[i] = convertToIntensity(concentration);
    }

    return data;
}

bool RectangularMatFactory::isValidViewerImage(const Mat &image) {
    if (!image.data) {
        MS_throw(InvalidInputException, ERR_INPUT_OPEN);
    }

    if ((image.cols != INPUT_IMG_WIDTH) || (image.rows != INPUT_IMG_HEIGHT)) {
        MS_throw(InvalidInputException, ERR_IMG_RESOLUTION);
    }

    return true;
}


// Constants
const string RectangularMatFactory::ERR_CONC   = "All concentrations have to be between 0 and 1.";

const int RectangularMatFactory::ROI_START_X       = 321;
const int RectangularMatFactory::ROI_START_Y       = 318;
const int RectangularMatFactory::ROI_WIDTH         = 1407;
const int RectangularMatFactory::ROI_HEIGHT        = 1358;

const int RectangularMatFactory::INPUT_IMG_WIDTH   = 2048;
const int RectangularMatFactory::INPUT_IMG_HEIGHT  = 2048;

const int RectangularMatFactory::COLOURBAR_MAX_X   = 1799;
const int RectangularMatFactory::COLOURBAR_MAX_Y   = 320;
