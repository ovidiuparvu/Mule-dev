#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/statistics/BinomialDistribution.hpp"

#include <boost/math/distributions/binomial.hpp>

using namespace multiscale;


double BinomialDistribution::pdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                 double probability) {
    validateInput(nrOfObservations, nrOfSuccesses, probability);

    return computePdf(nrOfObservations, nrOfSuccesses, probability);
}

double BinomialDistribution::cdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                 double probability) {
    validateInput(nrOfObservations, nrOfSuccesses, probability);

    return computeCdf(nrOfObservations, nrOfSuccesses, probability);
}

void BinomialDistribution::validateInput(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                         double probability) {
    validateProbability(probability);
    validateNrOfSuccesses(nrOfObservations, nrOfSuccesses);
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

double BinomialDistribution::computePdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                        double probability) {
    boost::math::binomial binomialDistribution(nrOfObservations, probability);

    return boost::math::pdf(binomialDistribution, nrOfSuccesses);
}

double BinomialDistribution::computeCdf(unsigned int nrOfObservations, unsigned int nrOfSuccesses,
                                        double probability) {
    boost::math::binomial binomialDistribution(nrOfObservations, probability);

    return boost::math::cdf(binomialDistribution, nrOfSuccesses);
}


// Constants
const std::string BinomialDistribution::ERR_NR_OF_SUCCESSES_BEGIN   = "The given number of successes (";
const std::string BinomialDistribution::ERR_NR_OF_SUCCESSES_MIDDLE  = ") should be less than or equal to the total number of observations (";
const std::string BinomialDistribution::ERR_NR_OF_SUCCESSES_END     = ").";
