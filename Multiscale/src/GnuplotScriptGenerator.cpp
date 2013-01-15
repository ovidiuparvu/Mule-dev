#include "../include/GnuplotScriptGenerator.hpp"
#include "../include/RGBColourGenerator.hpp"
#include "../include/StringManipulator.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace multiscale;
using namespace std;


// Using the annular sectors generate the corresponding gnuplot script in the
// output file
void GnuplotScriptGenerator::generateScript(vector<AnnularSector>& annularSectors,
		                                    string outputFilepath) throw (string) {
	ofstream fout((outputFilepath + GNUPLOT_EXTENSION).c_str(), std::ios_base::trunc);

	assert(fout.is_open());

	generateHeader(fout, outputFilepath);
	generateBody  (annularSectors, fout);
	generateFooter(fout);

	fout.close();
}

// Generate the header of the script
void GnuplotScriptGenerator::generateHeader(ofstream& fout, string outputFilepath) {
	ifstream fin(HEADER_IN);

	assert(fin.is_open());

	string outputFilename = StringManipulator::filenameFromPath(outputFilepath);

	outputHeader(fin, outputFilename, fout);

	fin.close();
}

// Generate the body of the script
void GnuplotScriptGenerator::generateBody(vector<AnnularSector>& annularSectors,
										  ofstream& fout) {
	ifstream fin(CONTENT_IN);

	assert(fin.is_open());

	string contentTemplate = readContentTemplate(fin);

	outputContent(annularSectors, contentTemplate, fout);

	fin.close();
}

// Generate the footer of the script
void GnuplotScriptGenerator::generateFooter(ofstream& fout) {
	ifstream fin(FOOTER_IN);

	assert(fin.is_open());

	outputFooter(fin, fout);

	fin.close();
}

// Output the header of the script
void GnuplotScriptGenerator::outputHeader(ifstream& fin, string outputFilename, ofstream& fout) {
	string line;

	while (getline(fin, line)) {
		fout << StringManipulator::replace(line, REPLACE_HEADER_FILENAME, outputFilename) << endl;
	}

	fout.flush();
}

// Output the content of the script
void GnuplotScriptGenerator::outputContent(vector<AnnularSector>& annularSectors, string& contentTemplate, ofstream& fout) {
	int index = annularSectors.size();

	for (vector<AnnularSector>::iterator it = annularSectors.begin(); it != annularSectors.end(); it++) {
		string content = contentTemplate;

		content = StringManipulator::replace(content, REPLACE_CONTENT_INDEX, StringManipulator::toString(index--));
		content = StringManipulator::replace(content, REPLACE_CONTENT_RADIUS, StringManipulator::toString((*it).getEndingRadius()));
		content = StringManipulator::replace(content, REPLACE_CONTENT_START_ANGLE, StringManipulator::toString((*it).getStartingAngle()));
		content = StringManipulator::replace(content, REPLACE_CONTENT_END_ANGLE, StringManipulator::toString((*it).getEndingAngle()));
		content = StringManipulator::replace(content, REPLACE_CONTENT_CONCENTRATION, StringManipulator::toString((*it).getConcentration()));

		fout << content << endl;
	}

	fout.flush();
}

// Output the footer of the script
void GnuplotScriptGenerator::outputFooter(ifstream& fin, ofstream& fout) {
	string line;

	while (getline(fin, line)) {
		fout << line << endl;
	}

	fout.flush();
}

// Read the template for content and return it as a string
string GnuplotScriptGenerator::readContentTemplate(ifstream& fin) {
	ostringstream stringStream;
	string line;

	while (getline(fin, line)) {
		stringStream << line << endl;
	}

	return stringStream.str();
}
