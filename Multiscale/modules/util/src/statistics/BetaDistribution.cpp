#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/statistics/BetaDistribution.hpp"

using namespace multiscale;


double BetaDistribution::cdf(double alpha, double beta, double probability) {
    // TODO: Implement
}

void BetaDistribution::validateShapeParameters(double alpha, double beta) {
    if (!((isValidShapeParameter(alpha)) && (isValidShapeParameter(beta)))) {
        MS_throw(
            InvalidInputException,
            ERR_SHAPE_PARAMETERS_BEGIN  + StringManipulator::toString(alpha)  +
            ERR_SHAPE_PARAMETERS_MIDDLE + StringManipulator::toString(beta) +
            ERR_SHAPE_PARAMETERS_END
        );
    }
}

bool BetaDistribution::isValidShapeParameter(double shapeParameter) {
    return (shapeParameter > 0);
}


// Constants
const std::string BetaDistribution::ERR_SHAPE_PARAMETERS_BEGIN  = "The provided beta distribution shape parameters alpha and beta (";
const std::string BetaDistribution::ERR_SHAPE_PARAMETERS_MIDDLE = ", ";
const std::string BetaDistribution::ERR_SHAPE_PARAMETERS_END    = ") should be greater than zero. Please change.";
