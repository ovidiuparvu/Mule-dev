#ifndef BAYESIANMODELCHECKER_HPP
#define BAYESIANMODELCHECKER_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"

#include <string>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing the model checking result
        enum class BayesianModelCheckingResult : unsigned int {
            TRUE                    = 0,    /*!< The logic property was evaluated to true */
            FALSE                      ,    /*!< The logic property was evaluated to false */
            MORE_TRACES_REQUIRED            /*!< More traces are required to determine the truth value of the
                                                 logic property */
        };


        //! Class used to run Bayesian model checking tasks
        /*!
         *  The implementation of this class is (partially) based on the algorithms
         *  described in the following paper:
         *
         *  S. K. Jha, E. M. Clarke, C. J. Langmead, A. Legay, A. Platzer, and P. Zuliani,
         *  ‘A Bayesian Approach to Model Checking Biological Systems’, in Computational
         *  Methods in Systems Biology, P. Degano and R. Gorrieri, Eds. Springer Berlin
         *  Heidelberg, 2009, pp. 218–234.
         *
         *  In our implementation the variables in the original paper (right hand side of the assignments)
         *  have been given the following new names (left hand side of assignments):
         *
         *  probability                     \f$ = \theta            \f$
         *
         *  alpha                           \f$ = \alpha            \f$
         *
         *  beta                            \f$ = \beta             \f$
         *
         *  bayesFactor                     \f$ = \mathcal{B}_{n}   \f$
         *
         *  bayesFactorThreshold            \f$ = T                 \f$
         *
         *  totalNumberOfEvaluations        \f$ = n                 \f$
         *
         *  totalNumberOfTrueEvaluations    \f$ = x                 \f$
         */
        class BayesianModelChecker : public ModelChecker {

            private:

                double probability;                 /*!< The probability specified by the user for the
                                                         logic property to be evaluated */

                double alpha;                       /*!< The shape parameter \f$ \alpha \f$ for the Beta distribution prior */
                double beta;                        /*!< The shape parameter \f$ \beta \f$ for the Beta distribution prior */

                double bayesFactorThreshold;        /*!< The Bayes factor threshold */
                double bayesFactorThresholdInverse; /*!< The Bayes factor threshold to the power "-1" */

                double typeIErrorUpperBound;        /*!< The type I error upper bound */

                BayesianModelCheckingResult modelCheckingResult; /*!< The result of the model checking task */

            public:

                BayesianModelChecker(const AbstractSyntaxTree &abstractSyntaxTree,
                                     const TypeSemanticsTable &typeSemanticsTable,
                                     double alpha, double beta, double bayesFactorThreshold);
                ~BayesianModelChecker();

                //! Check if more traces are accepted for evaluating the logic property
                bool acceptsMoreTraces() override;

                //! Check if more traces are required for evaluating the logic property
                bool requiresMoreTraces() override;

                //! Check if the given property holds
                bool doesPropertyHold() override;

                //! Get the detailed description of the results
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

            private:

                //! Validate the input parameters \f$ \alpha \f$, \f$ \beta \f$ and the Bayes factor threshold
                /*! \f$ \alpha \f$ and \f$ \beta \f$ should be greater than zero, and Bayes factor threshold should be greater than 1
                 *
                 * \param alpha                 The shape parameter \f$ \alpha \f$ for the Beta distribution
                 * \param beta                  The shape parameter \f$ \beta \f$ for the Beta distribution
                 * \param bayesFactorThreshold  The Bayes factor threshold
                 */
                void validateInput(double alpha, double beta, double bayesFactorThreshold);

                //! Validate the shape parameters \f$ \alpha \f$ and \f$ \beta \f$
                /*! \f$ \alpha \f$ and \f$ \beta \f$ should be greater than zero
                 *
                 * \param alpha The shape parameter \f$ \alpha \f$ for the Beta distribution
                 * \param beta  The shape parameter \f$ \beta \f$ for the Beta distribution
                 */
                void validateShapeParameters(double alpha, double beta);

                //! Check if the given shape parameter value is valid
                /*! The shape parameter values should be greater than zero
                 *
                 * \param shapeParameter    The given shape parameter
                 */
                bool isValidShapeParameter(double shapeParameter);

                //! Validate the Bayes factor threshold
                /*! The Bayes factor threshold should be greater than 1
                 *
                 * \param bayesFactorThreshold  The Bayes factor threshold
                 */
                void validateBayesFactorThreshold(double bayesFactorThreshold);

                //! Initialisation of some of the class members
                void initialise();

                //! Update the result of the model checking task
                void updateModelCheckingResult();

                //! Update the result of the model checking task considering the given Bayes factor value
                /*!
                 * \param bayesFactor   The given Bayes factor value
                 */
                void updateModelCheckingResult(double bayesFactor);

                //! Update the result of the model checking task considering that enough traces have been provided
                /*!
                 * \param bayesFactor   The given Bayes factor value
                 */
                void updateModelCheckingResultEnoughTraces(double bayesFactor);

                //! Update the result of the model checking task considering that not enough traces have been provided
                void updateModelCheckingResultNotEnoughTraces();

                //! Update the value of the type I error upper bound
                void updateTypeIErrorUpperBound();

                //! Compute the value of the indicator function \f$ I_{\mathcal{B}(n, x) < 1/T}(x) \f$
                /*!
                 * \param nrOfSuccesses The number of successful observations/trials
                 */
                bool indicatorFunction(unsigned int nrOfSuccesses);

                //! Compute the maximum value of the probability distribution function for the Binomial distribution
                /*! The maximum value is reached when p = \f$ \theta \f$ or p = \f$ \frac{2k}{n} \f$
                 *
                 * \param nrOfSuccesses The number of successful observations/trials
                 */
                double computeMaximumBinomialPDF(unsigned int nrOfSuccesses);

                //! Compute the value of the probability distribution function for the Binomial distribution
                /*!
                 * \param nrOfSuccesses The number of successful observations/trials
                 * \param probability   The probability of success
                 */
                double computeBinomialPDF(unsigned int nrOfSuccesses, double probability);

                //! Compute the value of the Bayes factor
                /*!
                 * According to the original paper the Bayes factor can be computed as follows:
                 *  \f$ \mathcal{B} = \frac{1}{(F_{x + \alpha, n - x + \beta)}(\theta)} - 1\f$
                 *
                 *  \param nrOfObservations The total number of observations
                 *  \param nrOfSuccesses    The total number of successes
                 */
                double computeBayesFactorValue(unsigned int nrOfObservations, unsigned int nrOfSuccesses);

                //! Check if the given property holds considering the obtained model checking result
                bool doesPropertyHoldConsideringResult();

                //! Check if the given property holds considering the obtained answer and probability comparator (i.e. <=, >=)
                /*! For queries of type :
                 *      a) \f$ P >= \theta [\phi] \f$ the isNullHypothesisTrue flag value is returned
                 *      b) \f$ P <= \theta [\phi] \f$ the !(isNullHypothesisTrue) flag value is returned
                 *
                 * \param isNullHypothesisTrue  Flag indicating if the null hypothesis is true considering a \f$ P >= [\phi] \f$ query
                 */
                bool doesPropertyHoldConsideringProbabilityComparator(bool isNullHypothesisTrue);

                //! Get the detailed description of the updated results
                std::string getDetailedUpdatedResults();


                // Constants
                static const std::string ERR_UNEXPECTED_MODEL_CHECKING_RESULT;

                static const std::string ERR_SHAPE_PARAMETERS_BEGIN;
                static const std::string ERR_SHAPE_PARAMETERS_MIDDLE;
                static const std::string ERR_SHAPE_PARAMETERS_END;

                static const std::string ERR_BAYES_FACTOR_THRESHOLD_BEGIN;
                static const std::string ERR_BAYES_FACTOR_THRESHOLD_END;

                static const std::string MSG_OUTPUT_MORE_TRACES_REQUIRED;

                static const std::string MSG_OUTPUT_RESULT_BEGIN;
                static const std::string MSG_OUTPUT_RESULT_MIDDLE1;
                static const std::string MSG_OUTPUT_RESULT_MIDDLE2;
                static const std::string MSG_OUTPUT_RESULT_MIDDLE3;
                static const std::string MSG_OUTPUT_RESULT_END;

                static const std::string MSG_OUTPUT_SEPARATOR;

        };

    };

};


#endif
