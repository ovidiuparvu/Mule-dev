#ifndef APPROXIMATEPROBABILISTICMODELCHECKER_HPP
#define APPROXIMATEPROBABILISTICMODELCHECKER_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"

#include <string>


namespace multiscale {

    namespace verification {

        //! Class used to run approximate probabilistic model checking tasks
        /*!
         *  The implementation of this class is based on the algorithm described in
         *  the following paper:
         *
         *  T. Hérault, R. Lassaigne, F. Magniette, and S. Peyronnet,
         *  ‘Approximate Probabilistic Model Checking’, in Verification, Model Checking,
         *  and Abstract Interpretation, B. Steffen and G. Levi, Eds. Springer Berlin
         *  Heidelberg, 2004, pp. 73–84.
         */
        class ApproximateProbabilisticModelChecker : public ModelChecker {

            private:

                double probability;                 /*!< The probability specified by the user for the
                                                         logic property to be evaluated */

                double delta;                       /*!< The upper bound on the probability for the computed probability to
                                                         deviate from the true probability */
                double epsilon;                     /*!< The considered deviation from the true probability */

                unsigned int nrOfRequiredTraces;    /*!< The number of required traces */

            public:

                ApproximateProbabilisticModelChecker(const AbstractSyntaxTree &abstractSyntaxTree,
                                                     const MultiscaleArchitectureGraph &multiscaleArchitectureGraph,
                                                     double delta, double epsilon);
                ~ApproximateProbabilisticModelChecker();

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

                //! Validate the input parameters delta and epsilon
                /*!
                 *  Precondition: \f$ 0 < \delta, \epsilon < 1 \f$
                 *
                 * \param delta     The upper bound on the probability to deviate from the true probability
                 * \param epsilon   The considered amount by which the probability deviates from the true probability
                 */
                void validateInput(double delta, double epsilon);

                //! Check if the given value is between zero and one (exclusive)
                /*!
                 * \param value The given value
                 */
                bool isBetweenZeroAndOne(double value);

                //! Initialisation of some of the class members
                void initialize();

                //! Initialize the number of required traces
                /*!
                 *  Precondition: The class members delta and epsilon are correctly initialized.
                 */
                void initializeNumberOfRequiredTraces();

                //! Check if the given property holds considering the probability comparator (i.e. <=, >=)
                /*! For queries of type :
                 *      a) \f$ P >= \theta [\phi] \f$ result = \f$ (nr_true_traces/nr_traces) - \epsilon >= \theta \f$
                 *      b)\f$  P <= \theta [\phi] \f$ result = \f$ (nr_true_traces/nr_traces) + \epsilon <= \theta \f$
                 */
                bool doesPropertyHoldConsideringProbabilityComparator();


                // Constants
                static const std::string ERR_INVALID_INPUT_BEGIN;
                static const std::string ERR_INVALID_INPUT_MIDDLE;
                static const std::string ERR_INVALID_INPUT_END;

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
