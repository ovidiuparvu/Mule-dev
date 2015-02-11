#include "multiscale/exception/NumericException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/statistics/BetaDistribution.hpp"

#include <boost/math/distributions/beta.hpp>

using namespace multiscale;


double BetaDistribution::cdf(double alpha, double beta, double probability) {
    validateShapeParameters(alpha, beta);
    validateProbability(probability);

    return computeCdf(alpha, beta, probability);
}

void BetaDistribution::validateShapeParameters(double alpha, double beta) {
    if (!((isValidShapeParameter(alpha)) && (isValidShapeParameter(beta)))) {
        MS_throw(
            NumericException,
            ERR_SHAPE_PARAMETERS_BEGIN  + StringManipulator::toString(alpha)  +
            ERR_SHAPE_PARAMETERS_MIDDLE + StringManipulator::toString(beta) +
            ERR_SHAPE_PARAMETERS_END
        );
    }
}

bool BetaDistribution::isValidShapeParameter(double shapeParameter) {
    return (shapeParameter > 0);
}

double BetaDistribution::computeCdf(double alpha, double beta, double probability) {
    boost::math::beta_distribution<> betaDistribution(alpha, beta);

    return boost::math::cdf(betaDistribution, probability);
}


// Constants
const std::string BetaDistribution::ERR_SHAPE_PARAMETERS_BEGIN  = "The provided Beta distribution shape parameters alpha and beta (";
const std::string BetaDistribution::ERR_SHAPE_PARAMETERS_MIDDLE = ", ";
const std::string BetaDistribution::ERR_SHAPE_PARAMETERS_END    = ") should be greater than zero. Please change.";
