#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/statistics/BinomialDistribution.hpp"

#include <boost/math/distributions/binomial.hpp>

using namespace multiscale;


double BinomialDistribution::cdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                 double probability) {
    validateProbability(probability);
    validateNrOfSuccesses(nrOfObservations, nrOfSuccesses);

    return computeCdf(nrOfObservations, nrOfSuccesses, probability);
}

void BinomialDistribution::validateProbability(double probability) {
    if ((probability < 0) || (probability > 1)) {
        MS_throw(
            NumericException,
            ERR_PROBABILITY_VALUE_BEGIN +
            StringManipulator::toString(probability) +
            ERR_PROBABILITY_VALUE_END
        );
    }
}

void BinomialDistribution::validateNrOfSuccesses(unsigned nrOfObservations, unsigned int nrOfSuccesses) {
    if (nrOfSuccesses > nrOfObservations) {
        MS_throw(
            NumericException,
            ERR_NR_OF_SUCCESSES_BEGIN +
            StringManipulator::toString(nrOfSuccesses) +
            ERR_NR_OF_SUCCESSES_MIDDLE +
            StringManipulator::toString(nrOfObservations) +
            ERR_NR_OF_SUCCESSES_END
        );
    }
}

double BinomialDistribution::computeCdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                        double probability) {
    boost::math::binomial binomialDistribution(nrOfObservations, probability);

    return boost::math::cdf(binomialDistribution, nrOfSuccesses);
}


// Constants
const std::string BinomialDistribution::ERR_PROBABILITY_VALUE_BEGIN = "The given probability value (";
const std::string BinomialDistribution::ERR_PROBABILITY_VALUE_END   = ") should be between 0 and 1.";

const std::string BinomialDistribution::ERR_NR_OF_SUCCESSES_BEGIN   = "The given number of successes (";
const std::string BinomialDistribution::ERR_NR_OF_SUCCESSES_MIDDLE  = ") should be less than or equal to the total number of observations (";
const std::string BinomialDistribution::ERR_NR_OF_SUCCESSES_END     = ").";
