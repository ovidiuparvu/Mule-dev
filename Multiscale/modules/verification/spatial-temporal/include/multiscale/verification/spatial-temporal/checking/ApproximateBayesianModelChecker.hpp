#ifndef APPROXIMATEBAYESIANMODELCHECKER_HPP
#define APPROXIMATEBAYESIANMODELCHECKER_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"

#include <string>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing the model checking result
        enum class ApproximateBayesianModelCheckingResult : unsigned int {
            TRUE                    = 0,    /*!< The logic property was evaluated to true */
            FALSE                      ,    /*!< The logic property was evaluated to false */
            MORE_TRACES_REQUIRED            /*!< More traces are required to determine the truth value of
                                                 the logic property */
        };


        //! Class used to run approximate Bayesian model checking tasks
        /*!
         *  The implementation of this class is (partially) based on the algorithms
         *  described in the following paper:
         *
         *  C. Langmead, ‘Generalized Queries and Bayesian Statistical Model Checking in Dynamic
         *  Bayesian Networks: Application to Personalized Medicine’, Computer Science Department,
         *  Aug. 2009.
         *
         *  In our implementation the variables in the original paper (right hand side of the assignments)
         *  have been given the following new names (left hand side of assignments):
         *
         *  probability                     \f$ = p                 \f$
         *
         *  alpha                           \f$ = \alpha            \f$
         *
         *  beta                            \f$ = \beta             \f$
         *
         *  mean                            \f$ = \hat{\rho}        \f$
         *
         *  variance                        \f$ = \hat{\nu}         \f$
         *
         *  varianceThreshold               \f$ = T                 \f$
         *
         *  totalNumberOfEvaluations        \f$ = n                 \f$
         *
         *  totalNumberOfTrueEvaluations    \f$ = k                 \f$
         */
        class ApproximateBayesianModelChecker : public ModelChecker {

            private:

                double probability;            /*!< The probability specified by the user for the
                                                                                     logic property to be evaluated */

                double alpha;                  /*!< The shape parameter \f$ \alpha \f$ for the Beta distribution prior */
                double beta;                   /*!< The shape parameter \f$ \beta \f$ for the Beta distribution prior */

                double mean;                   /*!< The value of the mean */
                double variance;               /*!< The value of the variance */

                double varianceThreshold;      /*!< The variance threshold */

                ApproximateBayesianModelCheckingResult  modelCheckingResult;    /*!< The result of the model checking task */

            public:

                ApproximateBayesianModelChecker(const AbstractSyntaxTree &abstractSyntaxTree,
                                                const TypeSemanticsTable &typeSemanticsTable,
                                                double alpha, double beta, double varianceThreshold);
                ~ApproximateBayesianModelChecker();

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

                //! Validate the input parameters \f$ \alpha \f$, \f$ \beta \f$ and the variance threshold
                /*! \f$ \alpha \f$, \f$ \beta \f$ and variance threshold should be greater than zero
                 *
                 * \param alpha                 The shape parameter \f$ \alpha \f$ for the Beta distribution
                 * \param beta                  The shape parameter \f$ \beta \f$ for the Beta distribution
                 * \param varianceThreshold     The variance threshold
                 */
                void validateInput(double alpha, double beta, double varianceThreshold);

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

                //! Validate the variance threshold
                /*! The variance threshold should be greater than 0
                 *
                 * \param varianceThreshold  The variance threshold
                 */
                void validateVarianceThreshold(double varianceThreshold);

                //! Initialisation of some of the class members
                void initialise();

                //! Update the result of the model checking task
                void updateModelCheckingResult();

                //! Update the value of the mean and variance estimates
                void updateMeanAndVariance();

                //! Update the value of the mean estimate
                void updateMean();

                //! Update the value of the variance estimate
                void updateVariance();

                //! Update the result of the model checking task considering the given variance value
                /*!
                 * \param variance  The given variance value
                 */
                void updateModelCheckingResult(double variance);

                //! Update the result of the model checking task considering that enough traces have been provided
                /*!
                 * \param variance  The given variance value
                 */
                void updateModelCheckingResultEnoughTraces(double variance);

                //! Check if the result of the model checking task is true considering the probabilistic comparator (i.e. <=, >=)
                /*!
                 *  For queries of type :
                 *      a) \f$ P >= \theta [\phi] \f$ the result is \f$ (mean >= \theta) \f$
                 *      b) \f$ P <= \theta [\phi] \f$ the result is \f$ (mean <= \theta) \f$
                 *
                 * \param variance  The given variance value
                 */
                bool isModelCheckingResultTrueConsideringComparator(double variance);

                //! Update the result of the model checking task considering that not enough traces have been provided
                void updateModelCheckingResultNotEnoughTraces();

                //! Check if the given property holds considering the obtained model checking result
                bool doesPropertyHoldConsideringResult();

                //! Get the detailed description of the updated results
                std::string getDetailedUpdatedResults();


                // Constants
                static const std::string ERR_UNEXPECTED_MODEL_CHECKING_RESULT;

                static const std::string ERR_SHAPE_PARAMETERS_BEGIN;
                static const std::string ERR_SHAPE_PARAMETERS_MIDDLE;
                static const std::string ERR_SHAPE_PARAMETERS_END;

                static const std::string ERR_VARIANCE_THRESHOLD_BEGIN;
                static const std::string ERR_VARIANCE_THRESHOLD_END;

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
