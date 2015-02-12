#include "multiscale/visualisation/rectangular/RectangularGnuplotScriptGenerator.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>


using namespace multiscale::visualisation;


void RectangularGnuplotScriptGenerator::generateScript(const std::vector<double> &concentrations,
                                                       double simulationTime,
                                                       unsigned long height,
                                                       unsigned long width,
                                                       const std::string &outputFilepath) {
    std::ofstream fout((outputFilepath + GNUPLOT_EXTENSION), std::ios_base::trunc);

    assert(fout.is_open());

    generateHeader(fout, outputFilepath, simulationTime, height, width);
    generateBody  (concentrations, height, width, fout);
    generateFooter(fout);

    fout.close();
}

void RectangularGnuplotScriptGenerator::generateHeader(std::ofstream &fout, const std::string &outputFilepath,
                                                       double simulationTime, unsigned long height,
                                                       unsigned long width) {
    std::ifstream fin(HEADER_IN);

    assert(fin.is_open());

    std::string outputFilename = StringManipulator::filenameFromPath(outputFilepath);

    outputHeader(fin, outputFilename, simulationTime, height, width, fout);

    fin.close();
}

void RectangularGnuplotScriptGenerator::generateBody(const std::vector<double> &concentrations,
                                                     unsigned long height, unsigned long width,
                                                     std::ofstream &fout) {
    std::ifstream fin(CONTENT_IN);

    assert(fin.is_open());

    outputContent(concentrations, height, width, fout);

    fin.close();
}

void RectangularGnuplotScriptGenerator::generateFooter(std::ofstream &fout) {
    std::ifstream fin(FOOTER_IN);

    assert(fin.is_open());

    outputFooter(fin, fout);

    fin.close();
}

void RectangularGnuplotScriptGenerator::outputHeader(std::ifstream &fin,
                                                     const std::string &outputFilename,
                                                     double simulationTime,
                                                     unsigned long height, unsigned long width,
                                                     std::ofstream &fout) {
    std::string line;

    while (getline(fin, line)) {
        line = StringManipulator::replace(
                   line,
                   REPLACE_HEADER_FILENAME,
                   outputFilename
               );
        line = StringManipulator::replace(
                   line,
                   REPLACE_HEADER_HEIGHT,
                   StringManipulator::toString<double>(height - REPLACE_DIMENSION_EXTRA)
               );
        line = StringManipulator::replace(
                   line,
                   REPLACE_HEADER_WIDTH,
                   StringManipulator::toString<double>(width - REPLACE_DIMENSION_EXTRA)
               );
        line = StringManipulator::replace(
                   line,
                   REPLACE_HEADER_SIM_TIME,
                   StringManipulator::toString<double>(simulationTime)
               );

        fout << line << std::endl;
    }

    fout.flush();
}

void RectangularGnuplotScriptGenerator::outputContent(const std::vector<double> &concentrations,
                                                      unsigned long height, unsigned long width,
                                                      std::ofstream &fout) {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < (width - 1); j++) {
            fout << std::setprecision(OUTPUT_PRECISION)
                 << concentrations[(i * width) + j] << OUTPUT_SEPARATOR;
        }

        fout << std::setprecision(OUTPUT_PRECISION)
             << concentrations[(i * width) + width - 1] << std::endl;
    }

    fout.flush();
}

void RectangularGnuplotScriptGenerator::outputFooter(std::ifstream &fin, std::ofstream &fout) {
    std::string line;

    while (getline(fin, line)) {
        fout << line << std::endl;
    }

    fout.flush();
}


// Constants
const std::string RectangularGnuplotScriptGenerator::HEADER_IN   = "/usr/local/share/mule/config/visualisation/rectangular/header.in";
const std::string RectangularGnuplotScriptGenerator::CONTENT_IN  = "/usr/local/share/mule/config/visualisation/rectangular/content.in";
const std::string RectangularGnuplotScriptGenerator::FOOTER_IN   = "/usr/local/share/mule/config/visualisation/rectangular/footer.in";

const std::string RectangularGnuplotScriptGenerator::REPLACE_HEADER_FILENAME    = "OUTPUT_FILENAME";
const std::string RectangularGnuplotScriptGenerator::REPLACE_HEADER_HEIGHT      = "OUTPUT_DIMENSION1";
const std::string RectangularGnuplotScriptGenerator::REPLACE_HEADER_WIDTH       = "OUTPUT_DIMENSION2";
const std::string RectangularGnuplotScriptGenerator::REPLACE_HEADER_SIM_TIME    = "OUTPUT_SIM_TIME";

const double RectangularGnuplotScriptGenerator::REPLACE_DIMENSION_EXTRA = 0.5;

const int         RectangularGnuplotScriptGenerator::OUTPUT_PRECISION    = std::numeric_limits<double>::max_digits10;

const std::string RectangularGnuplotScriptGenerator::OUTPUT_SEPARATOR    = " ";

const std::string RectangularGnuplotScriptGenerator::GNUPLOT_EXTENSION   = ".plt";
