#include "multiscale/verification/spatial-temporal/checking/StatisticalModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/checking/StatisticalModelCheckerFactory.hpp"

using namespace multiscale::verification;


StatisticalModelCheckerFactory::StatisticalModelCheckerFactory(double typeIError,
                                                               double typeIIError)
                                                               : typeIError(typeIError),
                                                                 typeIIError(typeIIError) {}

StatisticalModelCheckerFactory::~StatisticalModelCheckerFactory() {}

std::shared_ptr<ModelChecker>
StatisticalModelCheckerFactory::createInstance(const AbstractSyntaxTree &abstractSyntaxTree,
                                               const TypeSemanticsTable &typeSemanticsTable) {
    return (
        std::make_shared<StatisticalModelChecker>(
            abstractSyntaxTree, typeSemanticsTable, typeIError, typeIIError
        )
    );
}
