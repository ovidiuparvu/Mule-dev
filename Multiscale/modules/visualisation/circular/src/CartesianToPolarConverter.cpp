#include "multiscale/exception/FileOpenException.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/visualisation/circular/CartesianToPolarConverter.hpp"
#include "multiscale/visualisation/circular/PolarGnuplotScriptGenerator.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"

#include <iostream>
#include <fstream>
#include <exception>
#include <cassert>
#include <vector>

using namespace multiscale::visualisation;


CartesianToPolarConverter::CartesianToPolarConverter(const std::string &inputFilepath,
                                                     const std::string &outputFilepath) {
    this->inputFilepath.assign(inputFilepath);
    this->outputFilepath.assign(outputFilepath);

    nrOfSectors = 0;
    nrOfConcentricCircles = 0;
    simulationTime = 0.0;
}

CartesianToPolarConverter::~CartesianToPolarConverter() {}

void CartesianToPolarConverter::convert(bool outputToScript) {
    readInputData();
    transformToAnnularSectors();

    if (outputToScript) {
        outputResultsAsScript();
    } else {
        outputResultsAsFile();
    }
}

void CartesianToPolarConverter::readInputData() {
    std::ifstream fin(inputFilepath, std::ios_base::in);

    if (!fin.is_open()) {
        MS_throw(FileOpenException, ERR_INPUT_OPEN);
    }

    // Read the header line
    readHeaderLine(fin);

    // Read the concentrations
    readConcentrations(fin);

    // Check if the file contains additional unnecessary data
    // after excluding the line feed character
    fin.get();

    if (fin.peek() != EOF) {
        MS_throw(InvalidInputException, ERR_IN_EXTRA_DATA);
    }

    fin.close();
}

void CartesianToPolarConverter::readHeaderLine(std::ifstream &fin) {
    fin >> nrOfConcentricCircles >> nrOfSectors >> simulationTime;

    // Validate the header line
    if (nrOfConcentricCircles <= 0) MS_throw(InvalidInputException, ERR_NONPOS_DIMENSION);
    if (nrOfSectors <= 0)           MS_throw(InvalidInputException, ERR_NONPOS_DIMENSION);
    if (simulationTime < 0)         MS_throw(InvalidInputException, ERR_NEG_SIM_TIME);
}

void CartesianToPolarConverter::readConcentrations(std::ifstream &fin) {
    int nrOfConcentrations = ((nrOfConcentricCircles - 1) * nrOfSectors) + 1;

    concentrations.resize(nrOfConcentrations);

    double tmp = 0;

    // Read all the concentrations and verify if they are
    // non-negative
    for (int i = 0; i < nrOfConcentrations; i++) {
        fin >> tmp;

        if ((tmp < 0) || (tmp > 1)) {
            MS_throw(InvalidInputException, ERR_CONC);
        }

        concentrations[i] = tmp;
    }
}

void CartesianToPolarConverter::transformToAnnularSectors() {
    int nrOfConcentrations = ((nrOfConcentricCircles - 1) * nrOfSectors) + 1;

    annularSectors.resize(nrOfConcentrations);

    // Tranform the cell of the grid to the annular sector corresponding
    // to the circle of radius 0
    (annularSectors.at(0)).initialise(0.0, RADIUS_MIN, 0.0, 360.0, concentrations.at(0));

    // Define the constants
    double angle     = 360.0 / nrOfSectors;
    int    maxRadius = (nrOfConcentricCircles - 1);

    // Transform the rest of the grid to annular sectors
    for (int i = 1; i < nrOfConcentrations; i++) {
        int row = (i - 1) / nrOfSectors;
        int col = (i - 1) % nrOfSectors;

        double startRadius = NumericRangeManipulator::convertFromRange<int, double>(
                                 0, maxRadius, RADIUS_MIN, RADIUS_MAX, row
                             );
        double endRadius   = NumericRangeManipulator::convertFromRange<int, double>(
                                 0, maxRadius, RADIUS_MIN, RADIUS_MAX, row + 1
                             );

        (annularSectors.at(i)).initialise(
            startRadius, endRadius, col * angle, (col + 1) * angle, concentrations.at(i)
        );
    }
}

void CartesianToPolarConverter::outputResultsAsFile() {
    int nrOfAnnularSectors = annularSectors.size();

    std::ofstream fout((outputFilepath.append(OUTPUT_FILE_EXTENSION)), std::ios_base::trunc);

    assert(fout.is_open());

    // Output the information of the annular sectors
    for (int i = 0; i < nrOfAnnularSectors; i++) {
        fout << (annularSectors.at(i)).toString() << std::endl;
    }

    fout.close();
}

void CartesianToPolarConverter::outputResultsAsScript() {
    PolarGnuplotScriptGenerator::generateScript(annularSectors, simulationTime, outputFilepath);
}

// Constants
const std::string CartesianToPolarConverter::ERR_CONC                = "All concentrations have to be between 0 and 1.";
const std::string CartesianToPolarConverter::ERR_NONPOS_DIMENSION    = "The dimensions N and M must be positive.";
const std::string CartesianToPolarConverter::ERR_NEG_SIM_TIME        = "The simulation time must be non-negative.";
const std::string CartesianToPolarConverter::ERR_INPUT_OPEN          = "The input file could not be opened";
const std::string CartesianToPolarConverter::ERR_IN_EXTRA_DATA       = "The input file contains more data than required.";

const std::string CartesianToPolarConverter::OUTPUT_FILE_EXTENSION   = ".out";

const double CartesianToPolarConverter::RADIUS_MIN  = 0.001;
const double CartesianToPolarConverter::RADIUS_MAX  = 0.3;
