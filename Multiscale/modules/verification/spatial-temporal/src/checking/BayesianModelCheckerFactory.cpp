#include "multiscale/verification/spatial-temporal/checking/BayesianModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/checking/BayesianModelCheckerFactory.hpp"

using namespace multiscale::verification;


BayesianModelCheckerFactory::BayesianModelCheckerFactory(double alpha, double beta,
                                                         double bayesFactorThreshold)
                                                         : alpha(alpha), beta(beta),
                                                           bayesFactorThreshold(bayesFactorThreshold) {}

BayesianModelCheckerFactory::~BayesianModelCheckerFactory() {}

std::shared_ptr<ModelChecker>
BayesianModelCheckerFactory::createInstance(const AbstractSyntaxTree &abstractSyntaxTree,
                                            const MultiscaleArchitectureGraph &multiscaleArchitectureGraph) {
    return (
        std::make_shared<BayesianModelChecker>(
            abstractSyntaxTree,
            multiscaleArchitectureGraph,
            alpha,
            beta,
            bayesFactorThreshold
        )
    );
}
