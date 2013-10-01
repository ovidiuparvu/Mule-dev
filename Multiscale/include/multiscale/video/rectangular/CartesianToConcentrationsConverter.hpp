#ifndef CARTESIANTOCONCENTRATIONSCONVERTER_HPP
#define CARTESIANTOCONCENTRATIONSCONVERTER_HPP

#include <string>
#include <vector>

using namespace std;

const string ERR_CONC                = "All concentrations have to be between 0 and 1.";
const string ERR_NONPOS_DIMENSION    = "The dimensions N and M must be positive.";
const string ERR_NEG_SIM_TIME        = "The simulation time must be non-negative.";
const string ERR_INPUT_OPEN          = "The input file could not be opened";
const string ERR_IN_EXTRA_DATA       = "The input file contains more data than required.";

const string OUTPUT_FILE_EXTENSION   = ".out";

const double RADIUS_MIN  = 0.001;
const double RADIUS_MAX  = 0.3;


namespace multiscale {

    namespace video {

        //! Scale the values of the rectangular geometry grid cells
        class CartesianToConcentrationsConverter {

            private:

                vector<double>  concentrations;     /*!< Concentrations received as input */

                unsigned long   height;             /*!< Height of the grid */
                unsigned long   width;              /*!< Width of the grid */
                double          simulationTime;     /*!< Simulation time */

                string inputFilepath;       /*!< Path to the input file */
                string outputFilepath;      /*!< Path to the output file */

            public:

                CartesianToConcentrationsConverter (const string &inputFilepath, const string &outputFilepath);
                ~CartesianToConcentrationsConverter();

                //! Start the conversion
                void convert();

            private:

                //! Read the input data
                void readInputData();

                //! Read the header line
                /*!
                 * The header line contains values for number of concentric circles,
                 * number of sectors and simulation time
                 *
                 * \param fin Input file stream
                 */
                void readHeaderLine(ifstream &fin);

                //! Read the concentrations
                /*!
                 * \param fin Input file stream
                 */
                void readConcentrations(ifstream &fin);

                //! Output the results
                void outputResults();

        };

    };

};

#endif
