#ifndef CARTESIANTOPOLARCONVERTER_HPP_
#define CARTESIANTOPOLARCONVERTER_HPP_

#include "multiscale/video/circular/AnnularSector.hpp"

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

        //! Converter from the rectangular geometry grid cells to annular sectors
        class CartesianToPolarConverter {

            private:

                vector<AnnularSector>   annularSectors;     /*!< Resulting annular sectors */
                vector<double>          concentrations;     /*!< Concentrations received as input */

                unsigned long nrOfConcentricCircles;    /*!< Number of concentric circles */
                unsigned long nrOfSectors;              /*!< Number of sectors */
                double        simulationTime;           /*!< Simulation time corresponding to the input data */

                string inputFilepath;   /*!< Path to the input file */
                string outputFilepath;  /*!< Path to the output file */

            public:

                CartesianToPolarConverter (const string &inputFilepath, const string &outputFilepath);
                ~CartesianToPolarConverter();

                //! Start the conversion
                /*!
                 * \param outputToScript Output to script or to plain file
                 */
                void convert(bool outputToScript);

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

                //! Convert the concentrations to annular sectors
                void transformToAnnularSectors();

                //! Output the results as a plain file
                void outputResultsAsFile();

                //! Output the results as a gnuplot script
                void outputResultsAsScript();

        };

    };

};

#endif
