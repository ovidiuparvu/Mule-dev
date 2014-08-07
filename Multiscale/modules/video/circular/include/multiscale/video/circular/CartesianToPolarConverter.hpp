#ifndef CARTESIANTOPOLARCONVERTER_HPP
#define CARTESIANTOPOLARCONVERTER_HPP

#include "multiscale/video/circular/AnnularSector.hpp"

#include <string>
#include <vector>

using namespace std;


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
