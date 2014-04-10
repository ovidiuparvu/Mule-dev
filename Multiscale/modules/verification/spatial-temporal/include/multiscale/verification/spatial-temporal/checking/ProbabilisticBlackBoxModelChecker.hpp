#ifndef PROBABILISTICBLACKBOXMODELCHECKER_HPP
#define PROBABILISTICBLACKBOXMODELCHECKER_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"


namespace multiscale {

    namespace verification {

        //! Class used to run probabilistic black-box model checking tasks
        class ProbabilisticBlackBoxModelChecker : public ModelChecker {

            public:

                ProbabilisticBlackBoxModelChecker(const AbstractSyntaxTree &abstractSyntaxTree);
                ~ProbabilisticBlackBoxModelChecker();

                //! Check if more traces are accepted for evaluating the logic property
                bool acceptsMoreTraces() override;

                //! Check if more traces are required for evaluating the logic property
                bool requiresMoreTraces() override;

                //! Check if the given property holds
                bool doesPropertyHold() override;

                //! Output the results
                std::string getDetailedResults() override;

            protected:

                //! Update the results of the derived model checker type considering that the logic property was evaluated to true for the last trace
                /*!
                 * Do not do anything
                 */
                void updateDerivedModelCheckerForTrueEvaluation() override;

                //! Update the results of the derived model checker type considering that the logic property was evaluated to false for the last trace
                /*!
                 * Do not do anything
                 */
                void updateDerivedModelCheckerForFalseEvaluation() override;

        };

    };

};

#endif
