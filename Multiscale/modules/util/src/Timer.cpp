#include "multiscale/exception/AlgorithmException.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/util/Timer.hpp"

using namespace multiscale;


// Define class member fields
std::vector<std::chrono::high_resolution_clock::time_point> multiscale::Timer::startTimePoints;


// Define class member functions
void Timer::start() {
    startTimePoints.push_back(
        std::chrono::high_resolution_clock::now()
    );

}

double Timer::stop() {
    if (startTimePoints.empty()) {
        MS_throw(
            AlgorithmException,
            ERR_TIMER_STOP_WHEN_NOT_STARTED
        );
    }

    return stopTimer();
}

double Timer::stopTimer() {
    std::chrono::high_resolution_clock::time_point stopTimePoint
        = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point startTimePoint
        = startTimePoints.back();

    startTimePoints.pop_back();

    std::chrono::duration<double, std::nano> duration = (stopTimePoint - startTimePoint);

    return (duration.count());
}


// Constants
const std::string multiscale::Timer::ERR_TIMER_STOP_WHEN_NOT_STARTED    = "You cannot stop a timer which was not previously started. Please change.";
