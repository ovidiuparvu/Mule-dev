#ifndef FREQUENCYMODELCHECKER_HPP
#define FREQUENCYMODELCHECKER_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"


namespace multiscale {

    namespace verification {

        //! Class used to run frequency model checking tasks
        class FrequencyModelChecker : public ModelChecker {

            private:

                unsigned int totalNumberOfEvaluations;      /*!< The total number of evaluations */
                unsigned int totalNumberOfTrueEvaluations;  /*!< The total number of times the abstract
                                                                 syntax tree was evaluated to true */

            public:

                FrequencyModelChecker(const AbstractSyntaxTree &abstractSyntaxTree);
                ~FrequencyModelChecker();

                //! Check if more traces are accepted for evaluating the logic property
                bool acceptsMoreTraces() override;

                //! Check if more traces are required for evaluating the logic property
                bool requiresMoreTraces() override;

                //! Check if the given property holds
                bool doesPropertyHold() override;

                //! Output the results
                std::string getDetailedResults() override;

            protected:

                //! Update the model checker results considering that the logic property was evaluated to true for the last trace
                /*!
                 * Increment the total number of true evaluations and the total number of evaluations
                 */
                void updateModelCheckerForTrueEvaluation() override;

                //! Update the model checker results considering that the logic property was evaluated to false for the last trace
                /*!
                 * Increment the total number of evaluations
                 */
                void updateModelCheckerForFalseEvaluation() override;

            private:

                //! Initialisation function
                void initialise();

                //! Convert the resulting probability to a string
                std::string resultToString();

                //! Compute the probability that the logic property holds
                double computeProbabilityThatPropertyHolds();


                // Constants
                static const std::string PROPERTY_HOLDS_WITH_PROBABILITY_LABEL;

        };

    };

};

#endif
