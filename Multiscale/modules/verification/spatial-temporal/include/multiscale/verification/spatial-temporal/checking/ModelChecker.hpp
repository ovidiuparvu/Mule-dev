#ifndef MODELCHECKER_HPP
#define MODELCHECKER_HPP

#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/model/MultiscaleArchitectureGraph.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"


namespace multiscale {

    namespace verification {

        //! Abstract class representing a generic model checker
        class ModelChecker {

            protected:

                AbstractSyntaxTree abstractSyntaxTree;      /*!< The abstract syntax tree representing
                                                                 the logic property which this model checker
                                                                 instance evaluates */

                MultiscaleArchitectureGraph
                    multiscaleArchitectureGraph;            /*!< The multiscale architecture graph encoding the
                                                                 hierarchical organization of scales and subsystems */

                unsigned int totalNumberOfEvaluations;      /*!< The total number of evaluations */
                unsigned int totalNumberOfTrueEvaluations;  /*!< The total number of times the abstract
                                                                 syntax tree was evaluated to true */

                double       nullHypothesisPValue;          /*!< The p-value for the null hypothesis to hold */
                double       alternativeHypothesisPValue;   /*!< The p-value for the alternative hypothesis to hold */

                bool         arePValuesUpdatedFlag;         /*!< Flag indicating if the p-values were updated */

            public:

                ModelChecker(const AbstractSyntaxTree &abstractSyntaxTree,
                             const MultiscaleArchitectureGraph &multiscaleArchitectureGraph)
                             : abstractSyntaxTree(abstractSyntaxTree),
                               multiscaleArchitectureGraph(multiscaleArchitectureGraph),
                               totalNumberOfEvaluations(0),
                               totalNumberOfTrueEvaluations(0),
                               nullHypothesisPValue(1),
                               alternativeHypothesisPValue(1),
                               arePValuesUpdatedFlag(false) {}
                virtual ~ModelChecker() {};

                //! Evaluate the abstract syntax tree for the given trace and return the result
                /*!
                 * \param trace The given spatial temporal trace
                 */
                bool evaluate(const SpatialTemporalTrace &trace);

                //! Check if more traces are accepted for evaluating the logic property
                virtual bool acceptsMoreTraces() = 0;

                //! Check if more traces are required for evaluating the logic property
                virtual bool requiresMoreTraces() = 0;

                //! Check if the given property holds
                virtual bool doesPropertyHold() = 0;

                //! Get a detailed report of the results
                virtual std::string getDetailedResults() = 0;

            protected:

                //! Update the results of the derived model checker type considering that the logic property was evaluated to true for the last trace
                virtual void updateDerivedModelCheckerForTrueEvaluation() = 0;

                //! Update the results of the derived model checker type considering that the logic property was evaluated to false for the last trace
                virtual void updateDerivedModelCheckerForFalseEvaluation() = 0;

                //! Update the p-values for the null and alternative hypothesis
                /*!
                 * The method for updating the p-values is based on considering that each trace
                 * is represented by a Bernoulli variable which can be either true or false with
                 * respect to the given logic property.
                 *
                 * The probability distribution of a sum of n Bernoulli variables (where n = number of traces)
                 * is a binomial distribution. Using the cumulative distribution function the p-values of the
                 * hypotheses can be computed.
                 *
                 * More details are given in the following paper:
                 * H. L. S. Younes, ‘Probabilistic Verification for “Black-Box” Systems’,
                 * in Computer Aided Verification, K. Etessami and S. K. Rajamani, Eds. Springer
                 * Berlin Heidelberg, 2005, pp. 253–265.
                 */
                void updateHypothesesPValues();

                //! Check if the property holds considering the given p-values
                bool doesPropertyHoldUsingPValues();

                //! Get the detailed results when deciding if the property holds based on p-values
                std::string getDetailedResultsUsingPValues();

                //! Check if the comparator used by the probabilistic logic property is greater than or equal to
                bool isGreaterThanOrEqualToComparator();

            private:

                //! Update the model checker results considering that the logic property was evaluated to evaluationResult for the last trace
                /*!
                 * \param evaluationResult  The result of evaluating the logic property considering the last trace
                 */
                void updateModelChecker(bool evaluationResult);

                //! Update the model checker results considering that the logic property was evaluated to evaluationResult for the last trace
                /*!
                 * \param evaluationResult  The result of evaluating the logic property considering the last trace
                 */
                void updateModelCheckerForEvaluationResult(bool evaluationResult);

                //! Update the results of the model checker considering that the logic property was evaluated to true for the last trace
                void updateModelCheckerForTrueEvaluation();

                //! Update the results of the model checker considering that the logic property was evaluated to false for the last trace
                void updateModelCheckerForFalseEvaluation();

                //! Update the p-values for the null and alternative hypothesis considering the comparator contained by the probabilistic logic property
                void updateHypothesesPValuesConsideringComparator();

                //! Update the p-values considering that the probabilistic logic property is of the form \f$ P >[=] \theta [\phi] \f$
                /*!
                 * \f$ p-value_{H_{0}} = 1 - F(d - 1; n, \theta) \f$
                 * \f$ p-value_{H_{1}} = F(d; n, \theta) \f$
                 * where d = number of true evaluations, n = number of evaluations and \f$ \theta\f$ = probability specified in the logic property
                 */
                void updateHypothesesPValuesForGreaterThan();

                //! Update the p-values considering that the probabilistic logic property is of the form \f$ P <[=] \theta [\phi] \f$
                /*!
                 * \f$ p-value_{H_{0}} = 1 - F(d' - 1; n, \theta) \f$
                 * \f$ p-value_{H_{1}} = F(d'; n, \theta) \f$
                 * where \f$ d' = n - d \f$, d = number of true evaluations, n = number of evaluations and \f$ \theta\f$ = probability specified in the logic property
                 */
                void updateHypothesesPValuesForLessThan();

                //! Update the null and alternative hypotheses p-values
                /*!
                 * \param nrOfEvaluations   The number of evaluations
                 * \param nrOfSuccesses     The number of true evaluations
                 * \param probability       The probability specified in the logic property
                 */
                void updateNullAndAlternativeHypothesesPValues(unsigned int nrOfEvaluations,
                                                               unsigned int nrOfSuccesses,
                                                               double probability);

                //! Update the null hypothesis p-value
                /*!
                 * \param nrOfEvaluations   The number of evaluations
                 * \param nrOfSuccesses     The number of true evaluations
                 * \param probability       The probability specified in the logic property
                 */
                void updateNullHypothesisPValue(unsigned int nrOfEvaluations, unsigned int nrOfSuccesses,
                                                double probability);

                //! Update the alternative hypothesis p-value
                /*!
                 * \param nrOfEvaluations   The number of evaluations
                 * \param nrOfSuccesses     The number of true evaluations
                 * \param probability       The probability specified in the logic property
                 */
                void updateAlternativeHypothesisPValue(unsigned int nrOfEvaluations,
                                                       unsigned int nrOfSuccesses,
                                                       double probability);


                // Constants
                static const std::string MSG_OUTPUT_P_VALUE_BEGIN;
                static const std::string MSG_OUTPUT_P_VALUE_MIDDLE1;
                static const std::string MSG_OUTPUT_P_VALUE_MIDDLE2;
                static const std::string MSG_OUTPUT_P_VALUE_END;

        };

    };

};


#endif
