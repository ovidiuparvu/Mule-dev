#ifndef CARTESIANTOPOLARCONVERTER_HPP
#define CARTESIANTOPOLARCONVERTER_HPP

#include "multiscale/visualisation/circular/AnnularSector.hpp"

#include <string>
#include <vector>


namespace multiscale {

    namespace visualisation {

        //! Converter from the rectangular geometry grid cells to annular sectors
        class CartesianToPolarConverter {

            private:

                std::vector<AnnularSector>
                    annularSectors;             /*!< Resulting annular sectors */
                std::vector<double>
                    concentrations;             /*!< Concentrations received as input */

                unsigned long
                    nrOfConcentricCircles;      /*!< Number of concentric circles */
                unsigned long
                    nrOfSectors;                /*!< Number of sectors */
                double
                    simulationTime;             /*!< Simulation time corresponding to the input data */

                std::string
                    inputFilepath;              /*!< Path to the input file */
                std::string
                    outputFilepath;             /*!< Path to the output file */

            public:

                CartesianToPolarConverter(const std::string &inputFilepath, const std::string &outputFilepath);
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
                void readHeaderLine(std::ifstream &fin);

                //! Read the concentrations
                /*!
                 * \param fin Input file stream
                 */
                void readConcentrations(std::ifstream &fin);

                //! Convert the concentrations to annular sectors
                void transformToAnnularSectors();

                //! Output the results as a plain file
                void outputResultsAsFile();

                //! Output the results as a gnuplot script
                void outputResultsAsScript();

            private:

                // Constants
                static const std::string ERR_CONC;
                static const std::string ERR_NONPOS_DIMENSION;
                static const std::string ERR_NEG_SIM_TIME;
                static const std::string ERR_INPUT_OPEN;
                static const std::string ERR_IN_EXTRA_DATA;

                static const std::string OUTPUT_FILE_EXTENSION;

                static const double RADIUS_MIN;
                static const double RADIUS_MAX;

        };

    };

};


#endif
