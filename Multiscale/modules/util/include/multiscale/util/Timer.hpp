#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <string>


namespace multiscale {

    //! Class for representing a timer
    class Timer {

        private:

            static std::chrono::high_resolution_clock::time_point
                startTimepoint;         /*!< The considered start time point */
            static std::chrono::high_resolution_clock::time_point
                stopTimepoint;          /*!< The considered stop time point */

            static bool isStartedFlag;  /*! Flag indicating if the timer was started */

        public:

            //! Start the timer
            static void start();

            //! Stop the timer and return the number of elapsed seconds as a floating point number
            static double stop();

        private:

            //! Start the timer and set the isStartedFlag to true
            static void startTimer();

            //! Stop the timer and set the isStartedFlag to false
            static double stopTimer();


            // Constants
            static const std::string ERR_TIMER_ALREADY_STARTED;
            static const std::string ERR_TIMER_STOP_WHEN_NOT_STARTED;

    };


};


#endif
