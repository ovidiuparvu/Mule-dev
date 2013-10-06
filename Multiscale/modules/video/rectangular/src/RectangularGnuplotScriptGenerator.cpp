#include "multiscale/video/rectangular/RectangularGnuplotScriptGenerator.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace multiscale::video;
using namespace std;


void RectangularGnuplotScriptGenerator::generateScript(const vector<double> &concentrations,
                                                       double simulationTime,
                                                       unsigned long height,
                                                       unsigned long width,
                                                       const string &outputFilepath) {
    ofstream fout((outputFilepath + GNUPLOT_EXTENSION), std::ios_base::trunc);

    assert(fout.is_open());

    generateHeader(fout, outputFilepath, simulationTime, height, width);
    generateBody  (concentrations, height, width, fout);
    generateFooter(fout);

    fout.close();
}

void RectangularGnuplotScriptGenerator::generateHeader(ofstream &fout, const string &outputFilepath,
                                                       double simulationTime, unsigned long height,
                                                       unsigned long width) {
    ifstream fin(HEADER_IN);

    assert(fin.is_open());

    string outputFilename = StringManipulator::filenameFromPath(outputFilepath);

    outputHeader(fin, outputFilename, simulationTime, height, width, fout);

    fin.close();
}

void RectangularGnuplotScriptGenerator::generateBody(const vector<double> &concentrations, unsigned long height,
                                                     unsigned long width, ofstream &fout) {
    ifstream fin(CONTENT_IN);

    assert(fin.is_open());

    outputContent(concentrations, height, width, fout);

    fin.close();
}

void RectangularGnuplotScriptGenerator::generateFooter(ofstream &fout) {
    ifstream fin(FOOTER_IN);

    assert(fin.is_open());

    outputFooter(fin, fout);

    fin.close();
}

void RectangularGnuplotScriptGenerator::outputHeader(ifstream &fin, const string &outputFilename, double simulationTime,
                                                     unsigned long height, unsigned long width, ofstream &fout) {
    string line;

    while (getline(fin, line)) {
        line = StringManipulator::replace(line, REPLACE_HEADER_FILENAME, outputFilename);
        line = StringManipulator::replace(line, REPLACE_HEADER_HEIGHT, StringManipulator::toString<double>(height - REPLACE_DIMENSION_EXTRA));
        line = StringManipulator::replace(line, REPLACE_HEADER_WIDTH, StringManipulator::toString<double>(width - REPLACE_DIMENSION_EXTRA));
        line = StringManipulator::replace(line, REPLACE_HEADER_SIM_TIME, StringManipulator::toString<double>(simulationTime));

        fout << line << endl;
    }

    fout.flush();
}

void RectangularGnuplotScriptGenerator::outputContent(const vector<double> &concentrations, unsigned long height,
                                                      unsigned long width, ofstream &fout) {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < (width - 1); j++) {
            fout << concentrations[(i * width) + j] << OUTPUT_SEPARATOR;
        }

        fout << concentrations[(i * width) + width - 1] << endl;
    }

    fout.flush();
}

void RectangularGnuplotScriptGenerator::outputFooter(ifstream &fin, ofstream &fout) {
    string line;

    while (getline(fin, line)) {
        fout << line << endl;
    }

    fout.flush();
}


// Constants
const string RectangularGnuplotScriptGenerator::HEADER_IN       = "/home/ovidiu/Repositories/git/multiscale/Multiscale/config/video/rectangular/header.in";
const string RectangularGnuplotScriptGenerator::CONTENT_IN      = "/home/ovidiu/Repositories/git/multiscale/Multiscale/config/video/rectangular/content.in";
const string RectangularGnuplotScriptGenerator::FOOTER_IN       = "/home/ovidiu/Repositories/git/multiscale/Multiscale/config/video/rectangular/footer.in";

const string RectangularGnuplotScriptGenerator::REPLACE_HEADER_FILENAME    = "OUTPUT_FILENAME";
const string RectangularGnuplotScriptGenerator::REPLACE_HEADER_HEIGHT      = "OUTPUT_DIMENSION1";
const string RectangularGnuplotScriptGenerator::REPLACE_HEADER_WIDTH       = "OUTPUT_DIMENSION2";
const string RectangularGnuplotScriptGenerator::REPLACE_HEADER_SIM_TIME    = "OUTPUT_SIM_TIME";

const double RectangularGnuplotScriptGenerator::REPLACE_DIMENSION_EXTRA = 0.5;

const string RectangularGnuplotScriptGenerator::OUTPUT_SEPARATOR    = " ";

const string RectangularGnuplotScriptGenerator::GNUPLOT_EXTENSION   = ".plt";
