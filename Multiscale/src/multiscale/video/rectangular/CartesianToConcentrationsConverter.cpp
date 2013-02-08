#include "multiscale/video/rectangular/CartesianToConcentrationsConverter.hpp"
#include "multiscale/video/rectangular/RectangularGnuplotScriptGenerator.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"

#include <iostream>
#include <fstream>
#include <exception>
#include <cassert>
#include <vector>

using namespace multiscale::video;


// Constructor for the class
CartesianToConcentrationsConverter::CartesianToConcentrationsConverter(string inputFilepath, string outputFilepath) {
    this->inputFilepath.assign(inputFilepath);
    this->outputFilepath.assign(outputFilepath);

    height = 0;
    width = 0;
}

// Destructor for the class
CartesianToConcentrationsConverter::~CartesianToConcentrationsConverter() {
    // Do nothing
}

// Convert the cell from the grid to scaled concentrations
void CartesianToConcentrationsConverter::convert() {
    readInputData();
    outputResults();
}

// Read the input data
void CartesianToConcentrationsConverter::readInputData() throw (string) {
    ifstream fin(inputFilepath.c_str());

    assert(fin.is_open());

    // Read the header line
    readHeaderLine(fin);

    // Read the concentrations
    readConcentrations(fin);

    // Check if the file contains additional unnecessary data
    // after excluding the line feed character
    fin.get();

    if (fin.peek() != EOF) throw string(ERR_IN_EXTRA_DATA);

    fin.close();
}

// Read the header line from the input file
void CartesianToConcentrationsConverter::readHeaderLine(ifstream& fin) throw (string) {
    fin >> height >> width;

    // Validate the header line
    if (height < 0) throw string(ERR_NEG_DIMENSION);
    if (width < 0)  throw string(ERR_NEG_DIMENSION);
}

// Read the concentrations from the input file
void CartesianToConcentrationsConverter::readConcentrations(ifstream& fin) throw (string) {
    int nrOfConcentrations = height * width;

    concentrations.resize(nrOfConcentrations);

    double tmp = 0;

    // Read all the concentrations and verify if they are
    // non-negative
    for (int i = 0; i < nrOfConcentrations; i++) {
        fin >> tmp;

        if ((tmp < 0) || (tmp > 1)) throw string(ERR_CONC);

        concentrations[i] = tmp;
    }
}

// Output the results as a gnuplot script
void CartesianToConcentrationsConverter::outputResults() {
    RectangularGnuplotScriptGenerator::generateScript(concentrations, height, width, outputFilepath);
}
