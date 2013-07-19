#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <fstream>

using namespace cv;
using namespace std;

#define ERR_OUTPUT_WITHOUT_DETECT   "Unable to output results if the detect method was not called previously."
#define ERR_OUTPUT_FILE             "Unable to create output file."
#define ERR_INVALID_IMAGE           "The input image is invalid."

#define OUTPUT_EXTENSION    ".out"
#define IMG_EXTENSION       ".png"

#define WIN_OUTPUT_IMAGE    "Output image"

#define KEY_ESC     27
#define KEY_SAVE    115


namespace multiscale {

    namespace analysis {

        class Detector {

            protected:

                Mat image;                      /*!< Input image */
                string outputFilepath;          /*!< Path of the output file */
                bool debugMode;                 /*!< Flag for indicating if debug mode is set */

                Mat outputImage;                /*!< Image for displaying the results */

                bool detectMethodCalled;                /*!< Flag for indicating if the detect method was called */
                bool detectorSpecificFieldsInitialised; /*!< Flag for indicating if the parameters were */

            public:

                Detector(bool debugMode = false);
                virtual ~Detector();

                //! Run the detection procedure on the given image
                /*!
                 * \param inputImage The input image
                 */
                void detect(const Mat &inputImage);

                //! Output the results to the given file
                /*!
                 * \param outputFilepath Path to the output file
                 */
                void outputResults(const string &outputFilepath);

            protected:

                //! Initialisation function for the class
                void initialise();

                //! Initialisation of the detector specific values in case they were not set
                void initialiseDetectorSpecificFieldsIfNotSet();

                //! Initialisation of the detector specific values
                virtual void initialiseDetectorSpecificFields() = 0;

                //! Initialisation of the image dependent values
                virtual void initialiseImageDependentFields() = 0;

                //! Check if the image is valid
                /*!
                 * Check if the number of dimensions = 2,  if the
                 * number of rows and number of columns is greater than one
                 * and if the image is of type CV_8UC1
                 *
                 * \param inputImage The input image
                 */
                bool isValidInputImage(const Mat& inputImage);

                //! Run the detection procedure
                void detect();

                //! Run the detection procedure when in debug mode
                void detectInDebugMode();

                //! Run the detection procedure when in release mode (i.e. non-debug mode)
                void detectInReleaseMode();

                //! Display the results in a window
                void displayResultsInWindow();

                //! Output the results to file(s)
                void outputResultsToFile();

                //! Output the results to an image
                virtual void outputResultsToImage() = 0;

                //! Store the image with the output results on disk
                void storeOutputImageOnDisk();

                //! Output the results to a file
                void outputResultsToCsvFile();

                //! Output the results to a file using the provided output file stream
                /*!
                 * \param fout Output file stream
                 */
                virtual void outputResultsToCsvFile(ofstream &fout) = 0;

                //! Process the input image and detect objects/entities of interest
                virtual void processImageAndDetect() = 0;

                //! Clear the results from the previous detection
                virtual void clearPreviousDetectionResults() = 0;

                //! Create the trackbars which allow the user to change the values of the parameters
                void createTrackbars();

                //! Create the window in which the trackbars are placed
                void createTrackbarsWindow();

                //! Create the trackbars specific to the used detector
                virtual void createDetectorSpecificTrackbars() = 0;

                //! Process the request of the user by pressing the key
                /*!
                 * \param pressedKey Key pressed by the user, if a key was pressed, or "-1", otherwise
                 */
                void processPressedKeyRequest(char &pressedKey);

                //! Display an image in a particular window
                /*!
                 * \param image The image
                 * \param windowName The name of the window
                 */
                void displayImage(const Mat &image, const string &windowName);

                //! Print error message, because the detect method was not called before calling the output method
                void printOutputErrorMessage();

        };

    };

};

#endif
