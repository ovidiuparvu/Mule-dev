#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"

#include "opencv2/highgui/highgui.hpp"

using namespace multiscale::analysis;


RectangularMatFactory::RectangularMatFactory() : MatFactory() {}

RectangularMatFactory::~RectangularMatFactory() {}

Mat RectangularMatFactory::createFromViewerImage(const string &inputFile) {
    Mat image = imread(inputFile, CV_LOAD_IMAGE_GRAYSCALE);

    if (!image.data)
        throw ERR_INPUT_OPEN;

    return image(Rect(ROI_START_X, ROI_START_Y, ROI_WIDTH, ROI_HEIGHT));
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
