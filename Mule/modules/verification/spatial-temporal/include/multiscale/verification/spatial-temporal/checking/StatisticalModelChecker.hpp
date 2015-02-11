#ifndef STATISTICALMODELCHECKER_HPP
#define STATISTICALMODELCHECKER_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"

#include <string>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing the model checking result
        enum class StatisticalModelCheckingResult : int {
            TRUE                    = 0,    /*!< The logic property was evaluated to true */
            FALSE                      ,    /*!< The logic property was evaluated to false */
            UNDECIDED                  ,    /*!< The truth value of the logic property is undecided */
            MORE_TRACES_REQUIRED            /*!< More traces are required to determine the truth value of
                                                 the logic property */
        };


        //! Class used to run statistical model checking tasks
        /*!
         *  The implementation of this class is (partially) based on the algorithms
         *  described in the following paper:
         *
         *  C. H. Koh, S. K. Palaniappan, P. S. Thiagarajan, and L. Wong,
         *  ‘Improved statistical model checking methods for pathway analysis’,
         *  BMC Bioinformatics, vol. 13, no. Suppl 17, p. S15, Dec. 2012.
         *
         *  In our implementation the variables in the original paper (right hand side of the assignments)
         *  have been given the following new names (left hand side of assignments):
         *
         *  probability                     \f$ = \theta \f$
         *
         *  indifference                    \f$ = \delta \f$
         *
         *  typeIError                      \f$ = \alpha \f$
         *
         *  typeIIError                     \f$ = \beta  \f$
         *
         *  minTypesError                   \f$ = \gamma \f$
         *
         *  totalNumberOfEvaluations        \f$ = n      \f$
         *
         *  totalNumberOfTrueEvaluations    \f$ = d      \f$
         */
        class StatisticalModelChecker : public ModelChecker {

            private:

                double probability;                 /*!< The probability specified by the user for the
                                                         logic property to be evaluated */

                double indifferenceIntervalHalf;    /*!< Half of the size of the indifference interval */

                double typeIError;                  /*!< The probability of type I errors to occur */
                double typeIIError;                 /*!< The probability of type II errors to occur */

                double minTypesError;               /*!< The minimum probability of type I and type II errors to occur */

                double a1FromPaper;                 /*!< The variable A1 (from the original paper) */
                double b1FromPaper;                 /*!< The variable B1 (from the original paper) */
                double a2FromPaper;                 /*!< The variable A2 (from the original paper) */
                double b2FromPaper;                 /*!< The variable B2 (from the original paper) */

                StatisticalModelCheckingResult modelCheckingResult; /*!< The result of the model checking task */

            public:

                StatisticalModelChecker(const AbstractSyntaxTree &abstractSyntaxTree,
                                        const TypeSemanticsTable &typeSemanticsTable,
                                        double typeIError, double typeIIError);
                ~StatisticalModelChecker();

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

                //! Validate the probability of type I and type II errors to occur
                /*! The probability of type I and type II errors to occur should be greater than zero and less than one
                 *
                 * \param typeIError    The probability of a type I error to occur
                 * \param typeIIError   The probability of a type II error to occur
                 */
                void validateTypesErrors(double typeIError, double typeIIError);

                //! Initialisation of some of the class members
                void initialise();

                //! Compute the value of the indifference interval half considering the given probability
                /*! indifferenceIntervalHalf = max(0, min(probability, 1 - probability) - eps)
                 *
                 * \param probability The value of the probability
                 */
                double computeIndifferenceIntervalHalf(double probability);

                //! Check if the given type I/II error probability is valid
                /*! The probability of the type I/II error to occur should be greater than zero and less than one
                 *
                 * \param typeError   The probability of a type I/II error to occur
                 */
                bool isValidTypeError(double typeError);

                //! Update the result of the model checking task
                void updateModelCheckingResult();

                //! Update the result of the model checking task which was already initialised
                /*!
                 * The name and semantics of the local variables a1, b1, a2, b2, f, fPrime, n, d
                 * correspond to the name and semantics of the variables used in the original paper.
                 */
                void updateInitialisedModelCheckingResult();

                //! Update the result of the model checking task considering the given values
                /*!
                 * \param f         The value of f  (from the original paper)
                 * \param fPrime    The value of f' (from the original paper)
                 */
                void updateModelCheckingResult(double f, double fPrime);

                //! Update the result of the model checking task considering the given values when enough traces have been provided
                /*!
                 * \param f         The value of f  (from the original paper)
                 * \param fPrime    The value of f' (from the original paper)
                 */
                void updateModelCheckingResultEnoughTraces(double f, double fPrime);

                //! Update the result of the model checking task when not enough traces were provided
                void updateModelCheckingResultNotEnoughTraces();

                //! Compute the value of f (from original paper)
                double computeFValue();

                //! Compute the value of the first term of f (from original paper)
                /*!
                 * If the value inside the logarithm is equal to zero than the
                 * returned value is equal to LOGARITHM_ZERO_VALUE. Otherwise
                 * the value of the logarithm is computed and returned.
                 */
                double computeFValueFirstTerm();

                //! Compute the value of the second term of f (from original paper)
                /*!
                 * If the value inside the logarithm is equal to zero than the
                 * returned value is equal to LOGARITHM_ZERO_VALUE. Otherwise
                 * the value of the logarithm is computed and returned.
                 */
                double computeFValueSecondTerm();

                //! Compute the value of f' (from original paper)
                double computeFPrimeValue();

                //! Compute the value of the first term of f' (from original paper)
                /*!
                 * If the value inside the logarithm is equal to zero than the
                 * returned value is equal to LOGARITHM_ZERO_VALUE. Otherwise
                 * the value of the logarithm is computed and returned.
                 */
                double computeFPrimeValueFirstTerm();

                //! Compute the value of the second term of f' (from original paper)
                /*!
                 * If the value inside the logarithm is equal to zero than the
                 * returned value is equal to LOGARITHM_ZERO_VALUE. Otherwise
                 * the value of the logarithm is computed and returned.
                 */
                double computeFPrimeValueSecondTerm();

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
                static const std::string  ERR_UNEXPECTED_MODEL_CHECKING_RESULT;

                static const std::string  ERR_TYPES_ERROR_VALUES_BEGIN;
                static const std::string  ERR_TYPES_ERROR_VALUES_MIDDLE;
                static const std::string  ERR_TYPES_ERROR_VALUES_END;

                static const std::string  MSG_OUTPUT_MORE_TRACES_REQUIRED;

                static const std::string  MSG_OUTPUT_RESULT_BEGIN;
                static const std::string  MSG_OUTPUT_RESULT_MIDDLE;
                static const std::string  MSG_OUTPUT_RESULT_END;

                static const std::string  MSG_OUTPUT_SEPARATOR;

                static const unsigned int INDIFFERENCE_INTERVAL_HALF_K;

                static const double       LOGARITHM_ZERO_VALUE;          /*!< The value obtained when computing log(0) */

        };

    };

};


#endif
