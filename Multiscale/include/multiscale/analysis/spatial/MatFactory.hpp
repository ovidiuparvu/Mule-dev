#ifndef MATFACTORY_HPP_
#define MATFACTORY_HPP_

#include "opencv2/core/core.hpp"
#include <fstream>

using namespace cv;
using namespace std;

#define ERR_INPUT_OPEN  "The input file could not be opened."


namespace multiscale {

    namespace analysis {

        //! Class for creating a Mat object
        class MatFactory {

            protected:

                int     rows;
                int     cols;
                double  simulationTime;

            public:

                MatFactory();
                virtual ~MatFactory();

                //! Create a Mat object from the input file
                /*!
                 * Create the Mat instance from the values given in the input file
                 *
                 * FORMAT OF INPUT FILE:
                 *  - 1st line contains two positive integers and a real value: nr_rows, nr_cols and simulation_time
                 *  - 2nd - (nr_rows + 1)th lines contain the concentrations of the positions in the grid
                 *
                 *  \param inputFile The path to the input file
                 */
                Mat create(const string &inputFile);

            protected:

                //! Initialise the input file
                /*!
                 * Initialise the input file. Open an input file stream to the given input file path.
                 *
                 * \param fin An input stream for reading data from the input file
                 * \param inputFile The path to the input file
                 */
                void initInputFile(ifstream &fin, const string &inputFile);

                //! Process concentrations from file
                /*!
                 * Process the concentrations from the file. This method will be implemented only by subclasses
                 * of this abstract class
                 */
                virtual unsigned char *processConcentrations(ifstream &fin) = 0;

                //! Convert concentration to intensity
                /*!
                 * Convert the concentration (real value between 0 and 1) to intensity (integer value between 0 and 255)
                 *
                 * \param concentration A value between 0 and 1
                 */
                unsigned char convertToIntensity(double concentration);

        };

    };

};

#endif
