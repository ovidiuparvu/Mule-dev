#ifndef CIRCULARMATFACTORY_HPP_
#define CIRCULARMATFACTORY_HPP_

#include "multiscale/analysis/spatial/MatFactory.hpp"

using namespace cv;
using namespace std;

#define ERR_UNIMPLEMENTED_METHOD    "The method you called is not implemented."

#define INTENSITY_MAX   255

#define ROI_START_X     1024
#define ROI_START_Y     786
#define ROI_RADIUS      615


namespace multiscale {

    namespace analysis {

        //! Class for creating a Mat object considering a circular grid
        class CircularMatFactory : public MatFactory {

            public:

                CircularMatFactory();
                ~CircularMatFactory();

                //! Create a Mat object from the image file obtained from the CircularGeometryViewer
                /*!
                 * Create the Mat instance from the given image file
                 *
                 *  \param inputFile The path to the image file
                 */
                Mat createFromViewerImage(const string &inputFile);

            protected:

                //! Process the concentrations from the input file
                /*!
                 * REMARK: This method is not implemented and throws an error when called.
                 *
                 * \param fin Input file stream from which the concentrations are read
                 */
                unsigned char *processConcentrations(ifstream& fin);

            private:

                //! Create a mask with 255 intensity pixels inside the circle with origin at (originX, originY) and the given radius
                /*!
                 * All the other pixels have intensity zero.
                 *
                 * The original image is provided only for getting the size correctly
                 *
                 * \param originX The x coordinate for the origin
                 * \param originY The y coordinate for the origin
                 * \param radius The size of the radius
                 * \param image The original image
                 */
                Mat createCircularMask(unsigned int originX, unsigned int originY,
                                       unsigned int radius, const Mat &image);

        };

    };

};

#endif
