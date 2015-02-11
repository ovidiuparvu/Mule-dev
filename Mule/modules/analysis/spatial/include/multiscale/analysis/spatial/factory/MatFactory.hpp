#ifndef MATFACTORY_HPP
#define MATFACTORY_HPP

#include "opencv2/core/core.hpp"

#include <fstream>


namespace multiscale {

    namespace analysis {

        //! Class for creating a cv::Mat object
        class MatFactory {

            protected:

                unsigned int    rows;           /*!< Number of rows in the Mat object */
                unsigned int    cols;           /*!< Number of columns in the Mat object */
                double          simulationTime; /*!< Simulation time read from the input file */

            public:

                MatFactory();
                virtual ~MatFactory();

                //! Create a cv::Mat object from the input file
                /*!
                 * Create the cv::Mat instance from the values given in the input file
                 *
                 * FORMAT OF INPUT FILE:
                 *  - 1st line contains two positive integers and a real value:
                 *        nr_rows, nr_cols and simulation_time
                 *  - 2nd - (nr_rows + 1)th lines contain the values of the positions in the grid
                 *
                 *  \param inputFilePath    The path to the input file
                 */
                cv::Mat createFromTextFile(const std::string &inputFilePath);

                //! Create a Mat object from the provided image file
                /*! Create a Mat instance from the given image file
                 *
                 *  \param inputFile The path to the image file
                 */
                virtual cv::Mat createFromImageFile(const std::string &inputFile) = 0;

            protected:

                //! Initialise the input file
                /*!
                 * Initialise the input file. Open an input file stream to the given input file path.
                 *
                 * \param fin           An input stream for reading data from the input file
                 * \param inputFilePath The path to the input file
                 */
                void initInputFile(std::ifstream &fin, const std::string &inputFilePath);

                //! Read image values from the given file
                /*!
                 * Read the image values (in [0, 1]) from the given file.
                 *
                 * \param fin   The input file stream from which the values are read
                 * \param image The image to which the values are written
                 */
                virtual void readValuesFromFile(std::ifstream &fin, cv::Mat &image) = 0;

                //! Read the next image value from the provided input file stream
                /*!
                 * \param fin       The input file stream from which the values are read
                 * \param nextValue The next image value read from the file
                 */
                void readNextValueFromFile(std::ifstream &fin, float &nextValue);

                //! Close the input file stream
                /*! If the file contains more data than expected throw an exception.
                 *
                 * \param fin           The input file stream
                 * \param inputFilePath The path to the input file from which the data is read
                 */
                void closeInputFileStream(std::ifstream &fin, const std::string &inputFilePath);

                //! Check if the provided image represented as a Mat object is valid
                /*!
                 * \param image         The image represented as a Mat object
                 * \param imageFilePath The path to the file from which the image was read
                 */
                bool isValidInputImage(const cv::Mat &image, const std::string &imageFilePath);

            protected:

                // Constants
                static const int         INPUT_VALUE_PRECISION;

                static const std::string ERR_OPEN_INPUT_FILE_BEGIN;
                static const std::string ERR_OPEN_INPUT_FILE_END;

                static const std::string ERR_INPUT_FILE_EXTRA_DATA_BEGIN;
                static const std::string ERR_INPUT_FILE_EXTRA_DATA_END;

                static const std::string ERR_INVALID_IMAGE_FILE_BEGIN;
                static const std::string ERR_INVALID_IMAGE_FILE_END;

        };

    };

};


#endif
