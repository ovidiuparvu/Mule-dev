#include "multiscale/exception/NumericException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/statistics/Distribution.hpp"

using namespace multiscale;


void Distribution::validateProbability(double probability) {
    if ((probability < 0) || (probability > 1)) {
        MS_throw(
            NumericException,
            ERR_PROBABILITY_VALUE_BEGIN +
            StringManipulator::toString(probability) +
            ERR_PROBABILITY_VALUE_END
        );
    }
}


// Constants
const std::string Distribution::ERR_PROBABILITY_VALUE_BEGIN = "The given probability value (";
const std::string Distribution::ERR_PROBABILITY_VALUE_END   = ") should be between 0 and 1.";
