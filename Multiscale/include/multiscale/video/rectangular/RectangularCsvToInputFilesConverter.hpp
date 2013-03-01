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

#define ERR_NEG_CONCENTRATION               "All concentrations must be non-negative.";
#define ERR_SELECTED_CONCENTRATION_INDEX    "The selected concentration index (0-based indexing) should be smaller than the number of concentrations."
#define ERR_NR_CONCENTRATIONS               "The number of concentrations in the input file does not match the values of the input parameters height and width.";
#define ERR_NEG_SIM_TIME                    "The simulation time must be non-negative."
#define ERR_INPUT_OPEN                      "The input file could not be opened."
#define ERR_INVALID_VALUE_LINE              "Invalid value on line: "
#define ERR_INVALID_VALUE_TOKEN             ", value: "

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

                unsigned int selectedConcentrationIndex;

                double maximumConcentration;

                NumberIterator* circlesIterator;
                NumberIterator* sectorsIterator;

            public:

                RectangularCsvToInputFilesConverter (const string &inputFilepath,
                                                     const string &outputFilepath,
                                                     unsigned int height,
                                                     unsigned int width,
                                                     unsigned int nrOfConcentrationsForPosition,
                                                     unsigned int selectedConcentrationIndex,
                                                     NumberIteratorType numberIteratorType);
                ~RectangularCsvToInputFilesConverter();

                void convert();

            private:

                void            initInputFile                       (ifstream &fin);
                void            initMaximumConcentration            (ifstream &fin);
                void            initOutputFile                      (ofstream &fout, unsigned int index,
                                                                     double &simulationTime);
                void            initIterators                       (const NumberIteratorType &numberIteratorType);
                void            validateSelectedConcentrationIndex  ();
                void            validateInput                       (ifstream &fin);
                void            validateInputLine                   (const string &line, unsigned int lineNumber);
                void            processInputFile                    (ifstream &fin);
                void            processLine                         (const string &line, unsigned int outputIndex);
                vector<double>  splitLineInConcentrations           (const string &line, double &simulationTime);
                void            splitLineInConcentrations           (vector<double> &concentrations,
                                                                     vector<string> &tokens,
                                                                     unsigned int rowIndex);
                double          computeSimulationTime               (const string &token);
                double          computeNextPositionConcentration    (int concentrationIndex,
                                                                     vector<string> &tokens);
                double          computeConcentration                (const string &concentration);
                double          computeNonScaledConcentration       (const string &concentration);
                double          computeScaledConcentration          (const string &concentration);
                double          computeNormalisedConcentration      (double concentration);
                void            updateMaximumConcentration          (const string &line,
                                                                     double &maximumConcentration);

        };

    };

};

#endif
