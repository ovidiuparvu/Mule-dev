#ifndef RECTANGULARMATFACTORY_HPP
#define RECTANGULARMATFACTORY_HPP

#include "multiscale/analysis/spatial/factory/MatFactory.hpp"


namespace multiscale {

    namespace analysis {

        //! Class for creating a cv::Mat object considering a rectangular grid
        class RectangularMatFactory : public MatFactory {

            public:

                RectangularMatFactory();
                ~RectangularMatFactory();

                //! Create a Mat object from the provided image file
                /*! Create a Mat instance from the given image file
                 *
                 *  \param inputFilePath    The path to the image file
                 */
                cv::Mat createFromImageFile(const std::string &inputFilePath) override;

            protected:

                //! Read the values from the given input file
                /*!
                 * Read the values from the input file and return them as an array which can be used
                 * afterwards to create a cv::Mat object. Each floating point value is in the interval
                 * [0, 255].
                 *
                 * REMARK: The constructor of cv::Mat does not copy the data. Therefore, DO NOT
                 *         deallocate the data in this class.
                 *
                 * \param fin Input file stream from which the concentrations are read
                 */
                float *readValuesFromFile(std::ifstream& fin) override;

            private:

                // Constants
                static const std::string ERR_INVALID_VALUE;

        };

    };

};


#endif
