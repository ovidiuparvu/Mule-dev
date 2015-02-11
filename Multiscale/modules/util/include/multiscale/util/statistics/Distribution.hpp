#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

#include <string>


namespace multiscale {

    // Parent class for representing a statistical distribution
    class Distribution {

        protected:

            //! Check if the value of the probability is valid
            /*!
             * \param probability The value of the probability
             */
            static void validateProbability(double probability);

        private:

            // Constants
            static const std::string ERR_PROBABILITY_VALUE_BEGIN;
            static const std::string ERR_PROBABILITY_VALUE_END;

    };

};


#endif
