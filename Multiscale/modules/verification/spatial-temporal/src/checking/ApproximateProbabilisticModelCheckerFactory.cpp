#include "multiscale/verification/spatial-temporal/checking/ApproximateProbabilisticModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/checking/ApproximateProbabilisticModelCheckerFactory.hpp"

using namespace multiscale::verification;


ApproximateProbabilisticModelCheckerFactory::ApproximateProbabilisticModelCheckerFactory(double delta, double epsilon)
                                                                                        : delta(delta),
                                                                                          epsilon(epsilon) {}

ApproximateProbabilisticModelCheckerFactory::~ApproximateProbabilisticModelCheckerFactory() {}

std::shared_ptr<ModelChecker>
ApproximateProbabilisticModelCheckerFactory::createInstance(const AbstractSyntaxTree &abstractSyntaxTree,
                                                            const TypeSemanticsTable &typeSemanticsTable) {
    return (
        std::make_shared<ApproximateProbabilisticModelChecker>(
            abstractSyntaxTree, typeSemanticsTable, delta, epsilon
        )
    );
}
