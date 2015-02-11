#include "multiscale/verification/spatial-temporal/checking/ProbabilisticBlackBoxModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/checking/ProbabilisticBlackBoxModelCheckerFactory.hpp"

using namespace multiscale::verification;


ProbabilisticBlackBoxModelCheckerFactory::ProbabilisticBlackBoxModelCheckerFactory() {}

ProbabilisticBlackBoxModelCheckerFactory::~ProbabilisticBlackBoxModelCheckerFactory() {}

std::shared_ptr<ModelChecker>
ProbabilisticBlackBoxModelCheckerFactory::createInstance(const AbstractSyntaxTree &abstractSyntaxTree,
                                                         const TypeSemanticsTable &typeSemanticsTable) {
    return (
        std::make_shared<ProbabilisticBlackBoxModelChecker>(
            abstractSyntaxTree, typeSemanticsTable
        )
    );
}
