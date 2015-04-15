#include "multiscale/verification/spatial-temporal/checking/ApproximateBayesianModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/checking/ApproximateBayesianModelCheckerFactory.hpp"

using namespace multiscale::verification;


ApproximateBayesianModelCheckerFactory::ApproximateBayesianModelCheckerFactory(double alpha, double beta,
                                                                               double varianceThreshold)
                                                                               : alpha(alpha), beta(beta),
                                                                                 varianceThreshold(varianceThreshold) {}

ApproximateBayesianModelCheckerFactory::~ApproximateBayesianModelCheckerFactory() {}

std::shared_ptr<ModelChecker>
ApproximateBayesianModelCheckerFactory::createInstance(const AbstractSyntaxTree &abstractSyntaxTree,
                                                       const MultiscaleArchitectureGraph
                                                           &multiscaleArchitectureGraph) {
    return (
        std::make_shared<ApproximateBayesianModelChecker>(
            abstractSyntaxTree,
            multiscaleArchitectureGraph,
            alpha,
            beta,
            varianceThreshold
        )
    );
}
