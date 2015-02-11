#ifndef CARTESIANTOCONCENTRATIONSCONVERTER_HPP
#define CARTESIANTOCONCENTRATIONSCONVERTER_HPP

#include <string>
#include <vector>


namespace multiscale {

    namespace visualisation {

        //! Scale the values of the rectangular geometry grid cells
        class CartesianToConcentrationsConverter {

            private:

                std::vector<double> concentrations; /*!< Concentrations received as input */

                unsigned long   height;             /*!< Height of the grid */
                unsigned long   width;              /*!< Width of the grid */
                double          simulationTime;     /*!< Simulation time */

                std::string inputFilepath;          /*!< Path to the input file */
                std::string outputFilepath;         /*!< Path to the output file */

            public:

                CartesianToConcentrationsConverter(const std::string &inputFilepath,
                                                   const std::string &outputFilepath);
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
                void readHeaderLine(std::ifstream &fin);

                //! Read the concentrations
                /*!
                 * \param fin Input file stream
                 */
                void readConcentrations(std::ifstream &fin);

                //! Output the results
                void outputResults();

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
