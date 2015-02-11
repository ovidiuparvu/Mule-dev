#ifndef CIRCULARMATFACTORY_HPP
#define CIRCULARMATFACTORY_HPP

#include "multiscale/analysis/spatial/factory/MatFactory.hpp"


namespace multiscale {

    namespace analysis {

        //! Class for creating a Mat object considering a circular grid
        class CircularMatFactory : public MatFactory {

            public:

                CircularMatFactory();
                ~CircularMatFactory();

                //! Create a Mat object from the provided image file
                /*! Create a Mat instance from the given image file
                 *
                 *  \param inputFilePath    The path to the image file
                 */
                cv::Mat createFromImageFile(const std::string &inputFilePath) override;

            protected:

                //! Read the values from the input file
                /*!
                 * REMARK: This method is not implemented and throws an error when called.
                 *
                 * \param fin   Input file stream from which the values are read
                 * \param image The image to which the values are written
                 */
                void readValuesFromFile(std::ifstream& fin, cv::Mat &image) override;

            private:

                //! Create a circular mask with origin at image centre and tangent to at least two image edges
                /*! Create a mask with 255 intensity pixels inside the circle with origin at image centre and
                 *  the radius equal to the minimum distance from the image centre to one of the image edges.
                 *  All the other pixels have intensity zero.
                 *
                 * \param image The original image
                 */
                cv::Mat createCircularMaskFromCentreToEdge(const cv::Mat &image);

            private:

                // Constants
                static const std::string ERR_UNIMPLEMENTED_METHOD;

                static const int INTENSITY_MAX;

        };

    };

};


#endif
