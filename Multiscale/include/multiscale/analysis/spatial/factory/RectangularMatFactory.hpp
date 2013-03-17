#ifndef RECTANGULARMATFACTORY_HPP_
#define RECTANGULARMATFACTORY_HPP_

#include "multiscale/analysis/spatial/MatFactory.hpp"

using namespace std;


namespace multiscale {

    namespace analysis {

        //! Class for creating a Mat object considering a rectangular grid
        class RectangularMatFactory : public MatFactory {

            public:

                RectangularMatFactory();
                ~RectangularMatFactory();

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
