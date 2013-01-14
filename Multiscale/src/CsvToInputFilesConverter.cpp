#include "../include/CsvToInputFilesConverter.hpp"
#include "../include/StringManipulator.hpp"

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

	this->maximumConcentration = numeric_limits<double>::min();
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
	fin.open(inputFilepath.c_str(), ios_base::in);

	assert(fin.is_open());

	string currentLine;

	while (!fin.eof()) {
		getline(fin, currentLine);

		updateMaximumConcentration(currentLine);
	}

	fin.close();
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

	for (int i = 1; i < nrOfConcentricCircles; i++) {
		for (int j = 0; j < nrOfSectors; j++) {
			fout << concentrations[(i - 1) * nrOfSectors + j + 1] << OUTPUT_SEPARATOR;
		}

		fout << endl;
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
	unsigned int sectorIndex = sectorsIterator.number();

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
	double concentration = atof(tokens[(nrOfConcentrationsForPosition * concentrationIndex)].c_str());

	if (concentration < 0) throw ERR_NEG_CONCENTRATION;

	double totalConcentration = concentration;

	// Read the other concentrations if they exist
	for (int i = 1; i < nrOfConcentrationsForPosition; i++) {
		double tmpConcentration = atof(tokens[(nrOfConcentrationsForPosition * concentrationIndex) + i].c_str());

		if (tmpConcentration < 0) throw ERR_NEG_CONCENTRATION;

		totalConcentration += tmpConcentration;
	}

	// Return normalised concentration
	if (nrOfConcentrationsForPosition == 1) {
		return ((concentration * RADIUS_MIN * RADIUS_MIN) /
				(maximumConcentration * circleIndex * circleIndex));
	} else {
		return (((concentration/totalConcentration) * RADIUS_MIN * RADIUS_MIN) /
                 (maximumConcentration * circleIndex * circleIndex));
	}
}

// Update the maximum value if any of the concentrations from the
// provided string are greater than it
void CsvToInputFilesConverter::updateMaximumConcentration(string& currentLine) {
	vector<string> tokens = StringManipulator::split(currentLine, INPUT_FILE_SEPARATOR);

	for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
		double concentration = atof((*it).c_str());

		if (concentration > maximumConcentration) {
			maximumConcentration = concentration;
		}
	}
}
