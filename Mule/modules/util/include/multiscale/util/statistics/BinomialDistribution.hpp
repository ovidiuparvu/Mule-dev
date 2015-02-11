#ifndef BINOMIALDISTRIBUTION_HPP
#define BINOMIALDISTRIBUTION_HPP

#include "multiscale/util/statistics/Distribution.hpp"

#include <string>


namespace multiscale {

    //! Class for analysing Binomial distributed data
    class BinomialDistribution : public Distribution {

        public:

            //! Compute the value of the probability distribution/mass function (pdf) for a binomial distribution
            /*!
             * \param nrOfObservations  The total number of observations
             * \param nrOfSuccesses     The number of successes
             * \param probability       The probability p used by the cumulative distribution function
             */
            static double pdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                              double probability);


            //! Compute the value of the cumulative distribution function (cdf) for a binomial distribution
            /*!
             * \param nrOfObservations  The total number of observations
             * \param nrOfSuccesses     The number of successes
             * \param probability       The probability p used by the cumulative distribution function
             */
            static double cdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                              double probability);

        private:

            //! Validate the given input data
            /*!
             * \param nrOfObservations  The total number of observations
             * \param nrOfSuccesses     The number of successes
             * \param probability       The probability p used by the cumulative distribution function
             */
            static void validateInput(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                      double probability);

            //! Check if the number of true observations is less than or equal to the total number of observations
            /*!
             * \param nrOfObservations  The total number of observations
             * \param nrOfSuccesses     The number of successes
             */
            static void validateNrOfSuccesses(unsigned int nrOfObservations, unsigned int nrOfSuccesses);

            //! Compute the value of the probability distribution function for a binomial distribution
            /*!
             * \param nrOfObservations  The total number of observations
             * \param nrOfSuccesses     The number of successes
             * \param probability       The probability p used by the cumulative distribution function
             */
            static double computePdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                     double probability);

            //! Compute the value of the cumulative distribution function for a binomial distribution
            /*!
             * \param nrOfObservations  The total number of observations
             * \param nrOfSuccesses     The number of successes
             * \param probability       The probability p used by the cumulative distribution function
             */
            static double computeCdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                     double probability);


            // Constants
            static const std::string ERR_NR_OF_SUCCESSES_BEGIN;
            static const std::string ERR_NR_OF_SUCCESSES_MIDDLE;
            static const std::string ERR_NR_OF_SUCCESSES_END;

    };

};


#endif
