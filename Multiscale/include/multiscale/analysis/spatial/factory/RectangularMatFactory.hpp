#ifndef RECTANGULARMATFACTORY_HPP_
#define RECTANGULARMATFACTORY_HPP_

#include "multiscale/analysis/spatial/MatFactory.hpp"

using namespace std;

#define ERR_CONC    "All concentrations have to be between 0 and 1."

#define ROI_START_X 320
#define ROI_START_Y 318
#define ROI_WIDTH   1408
#define ROI_HEIGHT  1358


namespace multiscale {

    namespace analysis {

        //! Class for creating a Mat object considering a rectangular grid
        class RectangularMatFactory : public MatFactory {

            public:

                RectangularMatFactory();
                ~RectangularMatFactory();

                //! Create a Mat object from the image file obtained from the RectangularGeometryViewer
                /*!
                 * Create the Mat instance from the given image file
                 *
                 *  \param inputFile The path to the image file
                 */
                Mat createFromViewerImage(const string &inputFile);

            protected:

                //! Process the concentrations from the input file
                /*!
                 * Read the concentrations from the input file and return them as an array which can be used
                 * afterwards to create a Mat object from them
                 *
                 * REMARK: The constructor of Mat does not copy the data. Therefore, DO NOT
                 *         deallocate it in this class.
                 *
                 * \param fin Input file stream from which the concentrations are read
                 */
                unsigned char *processConcentrations(ifstream& fin);

        };

    };

};

#endif
