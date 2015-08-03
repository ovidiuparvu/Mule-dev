#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <string>
#include <vector>


namespace multiscale {

    //! Class for representing a nanoseconds timer
    class Timer {

        private:

            static std::vector<std::chrono::high_resolution_clock::time_point>
                startTimePoints;        /*!< The considered start time points */

        public:

            //! Start the timer
            static void start();

            //! Stop the timer and return the number of elapsed nanoseconds as a floating point number
            static double stop();

        private:

            //! Stop the timer and set the isStartedFlag to false
            static double stopTimer();


            // Constants
            static const std::string ERR_TIMER_STOP_WHEN_NOT_STARTED;

    };


};


#endif
