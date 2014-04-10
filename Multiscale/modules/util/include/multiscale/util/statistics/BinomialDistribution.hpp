#ifndef BINOMIALDISTRIBUTION_HPP
#define BINOMIALDISTRIBUTION_HPP

#include <string>


namespace multiscale {

    //! Class for computing measures considering binomial distributions
    class BinomialDistribution {

        public:

            //! Compute the value of the cumulative distribution function for a binomial distribution
            /*!
             * \param nrOfObservations  The total number of observations
             * \param nrOfSuccesses     The number of successes
             * \param probability       The probability p used by the cumulative distribution function
             */
            static double cdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                              double probability);

        private:

            //! Check if the value of the probability is valid
            /*!
             * \param probability The value of the probability
             */
            static void validateProbability(double probability);

            //! Check if the number of true observations is less than or equal to the total number of observations
            /*!
             * \param nrOfObservations  The total number of observations
             * \param nrOfSuccesses     The number of successes
             */
            static void validateNrOfSuccesses(unsigned int nrOfObservations, unsigned int nrOfSuccesses);

            //! Compute the value of the cumulative distribution function for a binomial distribution
            /*!
             * \param nrOfObservations  The total number of observations
             * \param nrOfSuccesses     The number of successes
             * \param probability       The probability p used by the cumulative distribution function
             */
            static double computeCdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                     double probability);


            // Constants
            static const std::string ERR_PROBABILITY_VALUE_BEGIN;
            static const std::string ERR_PROBABILITY_VALUE_END;

            static const std::string ERR_NR_OF_SUCCESSES_BEGIN;
            static const std::string ERR_NR_OF_SUCCESSES_MIDDLE;
            static const std::string ERR_NR_OF_SUCCESSES_END;

    };

};

#endif
