#include "multiscale/analysis/spatial/MatFactory.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"

using namespace multiscale;
using namespace analysis;

MatFactory::MatFactory() : rows(0), cols(0), simulationTime(0) {}


MatFactory::~MatFactory() {}


Mat MatFactory::create(const string &inputFile) {
    ifstream fin;

    initInputFile(fin, inputFile);

    unsigned char *data = processConcentrations(fin);

    fin.close();

    return Mat(rows, cols, CV_8UC1, data);
}


void MatFactory::initInputFile(ifstream &fin, const string& inputFile) {
    fin.open(inputFile.c_str(), ios_base::in);

    if (!fin.is_open())
        throw ERR_INPUT_OPEN;

    fin >> rows >> cols >> simulationTime;
}


unsigned char MatFactory::convertToIntensity(double concentration) {
    return NumericRangeManipulator::convertFromRange<double, unsigned char>(0, 1, 0, 255, concentration);
}
