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

                //! Evaluate the abstract syntax tree for the given trace
                /*!
                 * \param trace The given spatial temporal trace
                 */
                void evaluate(const SpatialTemporalTrace &trace) override;

                //! Check if more traces are accepted for evaluating the logic property
                bool acceptsMoreTraces() override;

                //! Check if more traces are required for evaluating the logic property
                bool requiresMoreTraces() override;

                //! Output the results
                void outputResults() override;

            private:

                //! Initialisation function
                void initialise();

                //! Convert the result to a string
                std::string resultToString();

        };

    };

};

#endif
