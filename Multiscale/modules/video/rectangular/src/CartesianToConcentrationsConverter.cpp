#include "multiscale/exception/CartesianToConcentrationsConverterException.hpp"
#include "multiscale/video/rectangular/CartesianToConcentrationsConverter.hpp"
#include "multiscale/video/rectangular/RectangularGnuplotScriptGenerator.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"

#include <iostream>
#include <fstream>
#include <exception>
#include <cassert>
#include <vector>

using namespace multiscale::video;


CartesianToConcentrationsConverter::CartesianToConcentrationsConverter(const string &inputFilepath, const string &outputFilepath) {
    this->inputFilepath.assign(inputFilepath);
    this->outputFilepath.assign(outputFilepath);

    height = 0;
    width = 0;
    simulationTime = 0;
}

CartesianToConcentrationsConverter::~CartesianToConcentrationsConverter() {}

void CartesianToConcentrationsConverter::convert() {
    readInputData();
    outputResults();
}

void CartesianToConcentrationsConverter::readInputData() {
    ifstream fin(inputFilepath, ios_base::in);

    if (!fin.is_open()) {
        MS_throw(CartesianToConcentrationsConverterException, ERR_INPUT_OPEN);
    }

    // Read the header line
    readHeaderLine(fin);

    // Read the concentrations
    readConcentrations(fin);

    // Check if the file contains additional unnecessary data
    // after excluding the line feed character
    fin.get();

    if (fin.peek() != EOF) {
        MS_throw(CartesianToConcentrationsConverterException, ERR_IN_EXTRA_DATA);
    }

    fin.close();
}

void CartesianToConcentrationsConverter::readHeaderLine(ifstream &fin) {
    fin >> height >> width >> simulationTime;

    // Validate the header line
    if (height <= 0) MS_throw(CartesianToConcentrationsConverterException, ERR_NONPOS_DIMENSION);
    if (width <= 0)  MS_throw(CartesianToConcentrationsConverterException, ERR_NONPOS_DIMENSION);
    if (simulationTime < 0) MS_throw(CartesianToConcentrationsConverterException, ERR_NEG_SIM_TIME);
}

void CartesianToConcentrationsConverter::readConcentrations(ifstream &fin) {
    int nrOfConcentrations = height * width;

    concentrations.resize(nrOfConcentrations);

    double tmp = 0;

    // Read all the concentrations and verify if they are
    // non-negative
    for (int i = 0; i < nrOfConcentrations; i++) {
        fin >> tmp;

        if ((tmp < 0) || (tmp > 1)) {
            MS_throw(CartesianToConcentrationsConverterException, ERR_CONC);
        }

        concentrations[i] = tmp;
    }
}

void CartesianToConcentrationsConverter::outputResults() {
    RectangularGnuplotScriptGenerator::generateScript(concentrations, simulationTime, height, width, outputFilepath);
}


// Constants
const string CartesianToConcentrationsConverter::ERR_CONC                = "All concentrations have to be between 0 and 1.";
const string CartesianToConcentrationsConverter::ERR_NONPOS_DIMENSION    = "The dimensions N and M must be positive.";
const string CartesianToConcentrationsConverter::ERR_NEG_SIM_TIME        = "The simulation time must be non-negative.";
const string CartesianToConcentrationsConverter::ERR_INPUT_OPEN          = "The input file could not be opened";
const string CartesianToConcentrationsConverter::ERR_IN_EXTRA_DATA       = "The input file contains more data than required.";

const string CartesianToConcentrationsConverter::OUTPUT_FILE_EXTENSION   = ".out";

const double CartesianToConcentrationsConverter::RADIUS_MIN  = 0.001;
const double CartesianToConcentrationsConverter::RADIUS_MAX  = 0.3;
