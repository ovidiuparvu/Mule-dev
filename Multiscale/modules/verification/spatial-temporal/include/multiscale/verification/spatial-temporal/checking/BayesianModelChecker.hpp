#ifndef BAYESIANMODELCHECKER_HPP
#define BAYESIANMODELCHECKER_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"

#include <string>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing the model checking result
        enum class BayesianModelCheckingResult : int {
            TRUE                    ,   /*!< The logic property was evaluated to true */
            FALSE                   ,   /*!< The logic property was evaluated to false */
            MORE_TRACES_REQUIRED        /*!< More traces are required to determine the truth value of the logic property */
        };


        //! Class used to run Bayesian model checking tasks
        /*!
         *  The implementation of this class is (partially) based on the algorithms
         *  described in the following paper:
         *  S. K. Jha, E. M. Clarke, C. J. Langmead, A. Legay, A. Platzer, and P. Zuliani,
         *  ‘A Bayesian Approach to Model Checking Biological Systems’, in Computational
         *  Methods in Systems Biology, P. Degano and R. Gorrieri, Eds. Springer Berlin
         *  Heidelberg, 2009, pp. 218–234.
         *
         *  In our implementation the variables in the original paper (right hand side of the assignments)
         *  have been given the following new names (left hand side of assignments):
         *
         *  probability                     \f$ = \theta            \f$
         *  alpha                           \f$ = \alpha            \f$
         *  beta                            \f$ = \beta             \f$
         *  bayesFactor                     \f$ = \mathcal{B}_{n}   \f$
         *  bayesFactorThreshold            \f$ = T                 \f$
         *  totalNumberOfEvaluations        \f$ = n                 \f$
         *  totalNumberOfTrueEvaluations    \f$ = x                 \f$
         */
        class BayesianModelChecker : public ModelChecker {

            private:

                double probability;                 /*!< The probability specified by the user for the
                                                         logic property to be evaluated */

                double alpha;                       /*!< The shape parameter \f$ \alpha \f$ for the beta distribution prior */
                double beta;                        /*!< The shape parameter \f$ \beta \f$ for the beta distribution prior */

                double bayesFactorThreshold;        /*!< The Bayes factor threshold */
                double bayesFactorThresholdInverse; /*!< The Bayes factor threshold to the power "-1" */

                BayesianModelCheckingResult modelCheckingResult; /*!< The result of the model checking task */

            public:

                BayesianModelChecker(const AbstractSyntaxTree &abstractSyntaxTree,
                                     double alpha, double beta, double bayesFactorThreshold);
                ~BayesianModelChecker();

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

            private:

                //! Validate the input parameters \f$ \alpha \f$, \f$ \beta \f$ and the Bayes factor threshold
                /*! \f$ \alpha \f$ and \f$ \beta \f$ should be greater than zero, and Bayes factor threshold should be greater than 1
                 *
                 * \param alpha                 The shape parameter \f$ \alpha \f$ for the beta distribution
                 * \param beta                  The shape parameter \f$ \beta \f$ for the beta distribution
                 * \param bayesFactorThreshold  The Bayes factor threshold
                 */
                void validateInput(double alpha, double beta, double bayesFactorThreshold);

                //! Validate the shape parameters \f$ \alpha \f$ and \f$ \beta \f$
                /*! \f$ \alpha \f$ and \f$ \beta \f$ should be greater than zero
                 *
                 * \param alpha The shape parameter \f$ \alpha \f$ for the beta distribution
                 * \param beta  The shape parameter \f$ \beta \f$ for the beta distribution
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

                //! Update the initialised model checking task result
                void updateInitialisedModelCheckingResult();

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

                //! Compute the value of the Bayes factor
                /*!
                 * According to the original paper the Bayes factor can be computed as follows:
                 *  \f$ \mathcal{B} = \frac{1}{(F_{x + \alpha, n - x + \beta)}(\theta)} - 1\f$
                 */
                double computeBayesFactorValue();

                //! Check if the given probability holds considering the obtained answer and probability comparator (i.e. <=, >=)
                /*! For queries of type :
                 *      a) P >= \theta [\phi] the isNullHypothesisTrue flag value is returned
                 *      b) P <= \theta [\phi] the !(isNullHypothesisTrue) flag value is returned
                 *
                 * \param isNullHypothesisTrue  Flag indicating if the null hypothesis is true considering a P >= [\phi] query
                 */
                bool doesPropertyHoldConsideringProbabilityComparator(bool isNullHypothesisTrue);


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
                static const std::string MSG_OUTPUT_RESULT_END;

                static const std::string MSG_OUTPUT_SEPARATOR;

        };

    };

};

#endif
