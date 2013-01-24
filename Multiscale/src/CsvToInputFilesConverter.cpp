#include "../include/CsvToInputFilesConverter.hpp"
#include "../include/StringManipulator.hpp"

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <limits>

using namespace multiscale;
using namespace std;

// Constructor for the class
CsvToInputFilesConverter::CsvToInputFilesConverter(string inputFilepath,
												   string outputFilepath,
												   unsigned int nrOfConcentricCircles,
												   unsigned int nrOfSectors,
												   unsigned int nrOfConcentrationsForPosition) :
												   circlesIterator(nrOfConcentricCircles),
												   sectorsIterator(nrOfSectors) {
	this->inputFilepath					= inputFilepath;
	this->outputFilepath 				= outputFilepath;

	this->nrOfConcentricCircles 		= nrOfConcentricCircles;
	this->nrOfSectors 					= nrOfSectors;
	this->nrOfConcentrationsForPosition = nrOfConcentrationsForPosition;

	this->concentrationsIndex  = 0;
	this->maximumConcentration = 1;
}

// Destructor for the class
CsvToInputFilesConverter::~CsvToInputFilesConverter() {
	// Do nothing
}

// Convert the ".csv" file to input files
void CsvToInputFilesConverter::convert() {
	ifstream fin;

	initMaximumConcentration(fin);
	initInputFile(fin);

	string currentLine;

	unsigned int index = 1;

	while (!fin.eof()) {
		getline(fin, currentLine);

		// Consider processing the line only if it has content
		if (!currentLine.empty()) {
			processLine(currentLine, index++);
		}
	}

	fin.close();
}

// Initialise the input file
void CsvToInputFilesConverter::initInputFile(ifstream& fin) {
	fin.open(inputFilepath.c_str(), ios_base::in);

	assert(fin.is_open());
}

// Initialise the maximum concentration value
void CsvToInputFilesConverter::initMaximumConcentration(ifstream& fin) {
	double maximumConcentration = numeric_limits<double>::min();
	string currentLine;

	fin.open(inputFilepath.c_str(), ios_base::in);

	assert(fin.is_open());

	while (!fin.eof()) {
		getline(fin, currentLine);

		// Consider processing the line only if it has content
		if (!currentLine.empty()) {
			updateMaximumConcentration(currentLine, maximumConcentration);
		}
	}

	fin.close();

	this->maximumConcentration = maximumConcentration;
}

// Initialise the output file
void CsvToInputFilesConverter::initOutputFile(ofstream& fout, unsigned int index) {
	fout.open(((outputFilepath + OUTPUT_FILE_SEPARATOR) +
		        StringManipulator::toString(index) +
		        OUTPUT_EXTENSION).c_str(),
	            ios_base::trunc);

	assert(fout.is_open());

	fout << nrOfConcentricCircles << OUTPUT_SEPARATOR << nrOfSectors << endl;
}

// Process the current line
void CsvToInputFilesConverter::processLine(string line, unsigned int outputIndex) {
	ofstream fout;

	initOutputFile(fout, outputIndex);

	vector<double> concentrations = splitLineInConcentrations(line);

	fout << concentrations[0] << endl;

	for (unsigned int i = 1; i < nrOfConcentricCircles; i++) {
		for (int j = 0; j < (nrOfSectors - 1); j++) {
			fout << concentrations[(i - 1) * nrOfSectors + j + 1] << OUTPUT_SEPARATOR;
		}

		fout << concentrations[i * nrOfSectors] << endl;
	}
}

// Split the line in concentrations
vector<double> CsvToInputFilesConverter::splitLineInConcentrations(string line) {
	vector<double> concentrations((nrOfSectors * (nrOfConcentricCircles - 1)) + 1);

	vector<string> tokens = StringManipulator::split(line, INPUT_FILE_SEPARATOR);

	concentrationsIndex = 0;

	circlesIterator.reset();

	while (circlesIterator.hasNext()) {
		unsigned int circleIndex = circlesIterator.number();

		sectorsIterator.reset();

		if (circleIndex == 1) {
			splitFirstLineInConcentrations(concentrations, tokens, circleIndex);
		} else {
			splitOtherLinesInConcentrations(concentrations, tokens, circleIndex);
		}
	}

	return concentrations;
}

// Split the first line into concentrations
void CsvToInputFilesConverter::splitFirstLineInConcentrations(vector<double>& concentrations,
		                                                      vector<string>& tokens,
		 	 	 	 	 	 	 	 	 	 	 	 	 	  unsigned int circleIndex) {
	unsigned int sectorIndex = 1;

	double concentration = computeNextPositionConcentration(circleIndex,
															concentrationsIndex,
															tokens);

	concentrations[((circleIndex - 1) * nrOfSectors) + (sectorIndex - 1)] = concentration;

	concentrationsIndex++;
}

// Split the first line into concentrations
void CsvToInputFilesConverter::splitOtherLinesInConcentrations(vector<double>& concentrations,
		                                                      vector<string>& tokens,
		 	 	 	 	 	 	 	 	 	 	 	 	 	  unsigned int circleIndex) {
	while (sectorsIterator.hasNext()) {
		unsigned int sectorIndex = sectorsIterator.number();

		double concentration = computeNextPositionConcentration(circleIndex,
																concentrationsIndex,
																tokens);

		concentrations[((circleIndex - 2) * nrOfSectors) + sectorIndex] = concentration;

		concentrationsIndex++;
	}
}

// Compute the concentration of the next position
double CsvToInputFilesConverter::computeNextPositionConcentration(unsigned int circleIndex,
        														  int concentrationIndex,
        														  vector<string>& tokens) {
	// Read the first concentration
	double concentration = computeScaledConcentration(
							   tokens[(nrOfConcentrationsForPosition * concentrationIndex)],
							   circleIndex
						   );

	double totalConcentration = concentration;

	// Read the other concentrations if they exist
	for (unsigned int i = 1; i < nrOfConcentrationsForPosition; i++) {
		double tmpConcentration = computeScaledConcentration(
				                      tokens[(nrOfConcentrationsForPosition * concentrationIndex) + i],
				                      circleIndex
				                  );

		totalConcentration += tmpConcentration;
	}

	// Return normalised concentration
	return (nrOfConcentrationsForPosition == 1) ?
		computeNormalisedConcentration(concentration, circleIndex) :
		computeNormalisedConcentration((concentration/totalConcentration), circleIndex);
}

// Compute the scaled concentration from the given string by applying
// a logit transformation to it
double CsvToInputFilesConverter::computeScaledConcentration(string concentration, int circleIndex) {
	double amount = atof(concentration.c_str());

	double scaledConcentration = computeConcentrationWrtArea(amount, circleIndex);

	// Convert all concentrations which are lower than 1 to 1,
	// such that we don't obtain negative values after applying log
	if (scaledConcentration < 1) {
		scaledConcentration = 1;
	}

	return log2(scaledConcentration);
}

// Compute the concentration of a annular sector given the number of species
// and the level at which the annular sector is positioned
double CsvToInputFilesConverter::computeConcentrationWrtArea(double amount, int circleIndex) {
	return amount / ((2 * (circleIndex - 1)) + 1);
}

// Compute the normalised concentration by considering the maximum concentration
// and the area of the current annular sector
double CsvToInputFilesConverter::computeNormalisedConcentration(double concentration, int circleIndex) {
	return (concentration / maximumConcentration);
}

// Update the maximum value if any of the concentrations from the
// provided string are greater than it
void CsvToInputFilesConverter::updateMaximumConcentration(string& currentLine, double& maximumConcentration) {
	vector<double> concentrations = splitLineInConcentrations(currentLine);

	for (vector<double>::iterator it = concentrations.begin(); it != concentrations.end(); it++) {
		if ((*it) > maximumConcentration) {
			maximumConcentration = (*it);
		}
	}
}
