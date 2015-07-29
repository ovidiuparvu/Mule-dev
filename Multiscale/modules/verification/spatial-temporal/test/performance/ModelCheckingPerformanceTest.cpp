#include "ModelCheckingPerformanceTest.hpp"
#include "multiscale/util/Timer.hpp"

using namespace multiscale;
using namespace multiscaletest;


double ModelCheckingPerformanceTest::RunPerformanceTest() {
    Timer::start();

    RunTest();
    ValidateTestResults();

    return (
        Timer::stop()
    );
}
