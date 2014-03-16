#include "multiscale/verification/spatial-temporal/checking/FrequencyModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/checking/FrequencyModelCheckerFactory.hpp"

using namespace multiscale::verification;


FrequencyModelCheckerFactory::FrequencyModelCheckerFactory() {}

FrequencyModelCheckerFactory::~FrequencyModelCheckerFactory() {}

std::shared_ptr<ModelChecker> FrequencyModelCheckerFactory::createInstance
    (const AbstractSyntaxTree &abstractSyntaxTree) {
    return std::make_shared<FrequencyModelChecker>(abstractSyntaxTree);
}
