#include "multiscale/analysis/spatial/MatFactory.hpp"
#include "multiscale/exception/MatFactoryException.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"

using namespace multiscale;
using namespace analysis;


MatFactory::MatFactory() : rows(0), cols(0), simulationTime(0) {}

MatFactory::~MatFactory() {}

Mat MatFactory::create(const string &inputFile) {
    ifstream fin;

    initInputFile(fin, inputFile);

    unsigned char *data = processConcentrations(fin);

    // Check if the file contains additional unnecessary data
    // after excluding the line feed character
    fin.get();

    if (fin.peek() != EOF) {
        MS_throw(MatFactoryException, ERR_IN_EXTRA_DATA);
    }

    fin.close();

    return Mat(rows, cols, CV_8UC1, data);
}

void MatFactory::initInputFile(ifstream &fin, const string& inputFile) {
    fin.open(inputFile, ios_base::in);

    if (!fin.is_open()) {
        MS_throw(MatFactoryException, ERR_INPUT_OPEN);
    }

    fin >> rows >> cols >> simulationTime;
}

unsigned char MatFactory::convertToIntensity(double concentration) {
    return NumericRangeManipulator::convertFromRange<double, unsigned char>(0, 1, 0, 255, concentration);
}


// Constants
const string MatFactory::ERR_INPUT_OPEN      = "The input file could not be opened.";
const string MatFactory::ERR_IMG_RESOLUTION  = "The resolution of the input image is not the expected one.";
const string MatFactory::ERR_IN_EXTRA_DATA   = "The input file contains more data than required.";
