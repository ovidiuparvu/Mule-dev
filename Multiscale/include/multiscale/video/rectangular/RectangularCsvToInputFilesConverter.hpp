#ifndef RECTANGULARCSVTOINPUTFILESCONVERTER_HPP_
#define RECTANGULARCSVTOINPUTFILESCONVERTER_HPP_

#include "multiscale/util/NumberIterator.hpp"
#include "multiscale/util/iterator/NumberIteratorType.hpp"

#include <string>
#include <vector>

#define OUTPUT_EXTENSION        ".in"
#define OUTPUT_SEPARATOR        " "
#define OUTPUT_FILE_SEPARATOR   "_"
#define INPUT_FILE_SEPARATOR    ","

#define ERR_NEG_CONCENTRATION           "All concentrations must be non-negative.";
#define ERR_NR_CONCENTRATIONS           "The number of concentrations in the input file does not match the values of the input parameters nr-concentric-circles and nr-sectors.";
#define ERR_INVALID_CONCENTRATION_LINE  "Invalid concentration on line: "
#define ERR_INVALID_CONCENTRATION_TOKEN ", concentration: "

using namespace std;

namespace multiscale {

    namespace video {

        class RectangularCsvToInputFilesConverter {

            private:

                string inputFilepath;
                string outputFilepath;

                unsigned int height;
                unsigned int width;
                unsigned int nrOfConcentrationsForPosition;

                unsigned int concentrationsIndex;

                double maximumConcentration;

                NumberIterator* circlesIterator;
                NumberIterator* sectorsIterator;

            public:

                RectangularCsvToInputFilesConverter (string inputFilepath,
                                                     string outputFilepath,
                                                     unsigned int height,
                                                     unsigned int width,
                                                     unsigned int nrOfConcentrationsForPosition,
                                                     NumberIteratorType numberIteratorType);
                ~RectangularCsvToInputFilesConverter();

                void convert();

            private:

                void            initInputFile                   (ifstream& fin);
                void            initMaximumConcentration        (ifstream& fin);
                void            initOutputFile                  (ofstream& fout, unsigned int index);
                void            initIterators                   (NumberIteratorType& numberIteratorType);
                void            validateInput                   (ifstream& fin);
                void            validateInputLine               (string& line, unsigned int lineNumber);
                void            processLine                     (string& line, unsigned int outputIndex);
                vector<double>  splitLineInConcentrations       (string line);
                void            splitLineInConcentrations       (vector<double>& concentrations,
                                                                 vector<string>& tokens);
                double          computeNextPositionConcentration(int concentrationIndex,
                                                                 vector<string>& tokens);
                double          computeScaledConcentration      (string concentration);
                double          computeConcentrationWrtArea     (double amount);
                double          computeNormalisedConcentration  (double concentration);
                void            updateMaximumConcentration      (string& line,
                                                                 double& maximumConcentration);

        };

    };

};

#endif
