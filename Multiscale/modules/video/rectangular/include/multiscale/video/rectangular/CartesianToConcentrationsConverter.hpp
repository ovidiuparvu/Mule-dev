#ifndef CARTESIANTOCONCENTRATIONSCONVERTER_HPP
#define CARTESIANTOCONCENTRATIONSCONVERTER_HPP

#include <string>
#include <vector>

using namespace std;


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

            private:

                // Constants
                static const string ERR_CONC;
                static const string ERR_NONPOS_DIMENSION;
                static const string ERR_NEG_SIM_TIME;
                static const string ERR_INPUT_OPEN;
                static const string ERR_IN_EXTRA_DATA;

                static const string OUTPUT_FILE_EXTENSION;

                static const double RADIUS_MIN;
                static const double RADIUS_MAX;


        };

    };

};


#endif
