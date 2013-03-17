#ifndef CARTESIANTOCONCENTRATIONSCONVERTER_HPP_
#define CARTESIANTOCONCENTRATIONSCONVERTER_HPP_

#include <string>
#include <vector>

using namespace std;

#define ERR_CONC                "All concentrations have to be between 0 and 1."
#define ERR_NONPOS_DIMENSION    "The dimensions N and M must be positive."
#define ERR_NEG_SIM_TIME        "The simulation time must be non-negative."
#define ERR_INPUT_OPEN          "The input file could not be opened"
#define ERR_IN_EXTRA_DATA       "The input file contains more data than required."

#define OUTPUT_FILE_EXTENSION   ".out"

#define RADIUS_MIN              0.001
#define RADIUS_MAX              0.3


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
                void readInputData() throw (string);

                //! Read the header line
                /*!
                 * The header line contains values for number of concentric circles,
                 * number of sectors and simulation time
                 *
                 * \param fin Input file stream
                 */
                void readHeaderLine(ifstream &fin) throw (string);

                //! Read the concentrations
                /*!
                 * \param fin Input file stream
                 */
                void readConcentrations(ifstream &fin) throw (string);

                //! Output the results
                void outputResults();

        };

    };

};

#endif
