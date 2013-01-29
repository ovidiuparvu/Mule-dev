#include "multiscale/video/circular/CartesianToPolarConverter.hpp"
#include "multiscale/video/circular/GnuplotScriptGenerator.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"

#include <iostream>
#include <fstream>
#include <exception>
#include <cassert>
#include <vector>

using namespace multiscale::video;


// Constructor for the class
CartesianToPolarConverter::CartesianToPolarConverter(string inputFilepath, string outputFilepath) {
	this->inputFilepath.assign(inputFilepath);
	this->outputFilepath.assign(outputFilepath);

	nrOfSectors = 0;
	nrOfConcentricCircles = 0;
}

// Destructor for the class
CartesianToPolarConverter::~CartesianToPolarConverter() {
	// Do nothing
}

// Convert the cell from the grid to annular sectors
void CartesianToPolarConverter::convert(bool outputToScript) {
	readInputData();
	transformToAnnularSectors();

	if (outputToScript) {
		outputResultsAsScript();
	} else {
		outputResultsAsFile();
	}
}

// Read the input data
void CartesianToPolarConverter::readInputData() throw (string) {
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
void CartesianToPolarConverter::readHeaderLine(ifstream& fin) throw (string) {
	fin >> nrOfConcentricCircles >> nrOfSectors;

	// Validate the header line
	if (nrOfConcentricCircles < 0) throw string(ERR_NEG_DIMENSION);
	if (nrOfSectors < 0)           throw string(ERR_NEG_DIMENSION);
}

// Read the concentrations from the input file
void CartesianToPolarConverter::readConcentrations(ifstream& fin) throw (string) {
	int nrOfConcentrations = ((nrOfConcentricCircles - 1) * nrOfSectors) + 1;

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

// Transform the cells of the grid into annular sectors
void CartesianToPolarConverter::transformToAnnularSectors() {
	int nrOfConcentrations = ((nrOfConcentricCircles - 1) * nrOfSectors) + 1;

	annularSectors.resize(nrOfConcentrations);

	// Tranform the cell of the grid to the annular sector corresponding
	// to the circle of radius 0
	(annularSectors.at(0)).initialise(0.0, RADIUS_MIN, 0.0, 360.0, concentrations.at(0));

	// Define the constants
	double angle     = 360 / nrOfSectors;
	int    maxRadius = (nrOfConcentricCircles - 1);

	// Transform the rest of the grid to annular sectors
	for (int i = 1; i < nrOfConcentrations; i++) {
		int row = (i - 1) / nrOfSectors;
		int col = (i - 1) % nrOfSectors;

		double startRadius = NumericRangeManipulator::convertFromRange<int, double>(0, maxRadius, RADIUS_MIN, RADIUS_MAX, row);
		double endRadius   = NumericRangeManipulator::convertFromRange<int, double>(0, maxRadius, RADIUS_MIN, RADIUS_MAX, row + 1);

		(annularSectors.at(i)).initialise(startRadius, endRadius, col * angle, (col + 1) * angle, concentrations.at(i));
	}
}

// Output the results as a text file
void CartesianToPolarConverter::outputResultsAsFile() {
	int nrOfAnnularSectors = annularSectors.size();

	ofstream fout((outputFilepath.append(OUTPUT_FILE_EXTENSION)).c_str(), ios_base::trunc);

	assert(fout.is_open());

	// Output the information of the annular sectors
	for (int i = 0; i < nrOfAnnularSectors; i++) {
		fout << (annularSectors.at(i)).toString() << endl;
	}

	fout.close();
}

// Output the results as a gnuplot script
void CartesianToPolarConverter::outputResultsAsScript() {
	GnuplotScriptGenerator::generateScript(annularSectors, outputFilepath);
}
