#include "multiscale/exception/AlgorithmException.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/util/Timer.hpp"

using namespace multiscale;


// Define class member fields
std::chrono::high_resolution_clock::time_point multiscale::Timer::startTimepoint;
std::chrono::high_resolution_clock::time_point multiscale::Timer::stopTimepoint;

bool multiscale::Timer::isStartedFlag = false;


// Define class member functions
void Timer::start() {
    if (isStartedFlag) {
        MS_throw(
            AlgorithmException,
            ERR_TIMER_ALREADY_STARTED
        );
    }

    startTimer();
}

double Timer::stop() {
    if (!isStartedFlag) {
        MS_throw(
            AlgorithmException,
            ERR_TIMER_STOP_WHEN_NOT_STARTED
        );
    }

    return stopTimer();
}

void Timer::startTimer() {
    startTimepoint = std::chrono::high_resolution_clock::now();

    isStartedFlag = true;
}

double Timer::stopTimer() {
    stopTimepoint = std::chrono::high_resolution_clock::now();

    isStartedFlag = false;

    std::chrono::duration<double> duration = (stopTimepoint - startTimepoint);

    return (
        duration.count()
    );
}


// Constants
const std::string multiscale::Timer::ERR_TIMER_ALREADY_STARTED          = "You cannot start a timer which was previously started and not stopped. Please change.";
const std::string multiscale::Timer::ERR_TIMER_STOP_WHEN_NOT_STARTED    = "You cannot stop a timer which was not previously started. Please change.";
