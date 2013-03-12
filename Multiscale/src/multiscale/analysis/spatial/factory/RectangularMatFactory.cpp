#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"

using namespace multiscale::analysis;


RectangularMatFactory::RectangularMatFactory() : MatFactory() {}


RectangularMatFactory::~RectangularMatFactory() {}


unsigned char *RectangularMatFactory::processConcentrations(ifstream& fin) {
    unsigned char *data = new unsigned char[rows*cols];
    int nrOfConcentrations = rows * cols;
    double concentration = 0;

    for (int i = 0; i < nrOfConcentrations; i++) {
        fin >> concentration;

        data[i] = convertToIntensity(concentration);
    }

    return data;
}
