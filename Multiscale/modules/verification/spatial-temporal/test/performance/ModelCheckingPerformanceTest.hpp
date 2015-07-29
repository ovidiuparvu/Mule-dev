#ifndef MODELCHECKINGPERFORMANCETEST_HPP
#define MODELCHECKINGPERFORMANCETEST_HPP

#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/util/Timer.hpp"


namespace multiscaletest {

    //! Class for representing a model checking performance unit test
    class ModelCheckingPerformanceTest : public MultiscaleTest {

        protected:

            //! Run the model checking performance test
            double RunPerformanceTest();

    };

}


#endif
