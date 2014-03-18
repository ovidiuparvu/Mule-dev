#ifndef MODELCHECKER_HPP
#define MODELCHECKER_HPP

#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"


namespace multiscale {

    namespace verification {

        //! Abstract class representing a generic model checker
        class ModelChecker {

            protected:

                AbstractSyntaxTree abstractSyntaxTree;  /*!< The abstract syntax tree representing
                                                             the logic property which this model checker
                                                             instance evaluates */

            public:

                ModelChecker(const AbstractSyntaxTree &abstractSyntaxTree)
                             : abstractSyntaxTree(abstractSyntaxTree) {}
                virtual ~ModelChecker() {};

                //! Evaluate the abstract syntax tree for the given trace and return the result
                /*!
                 * \param trace The given spatial temporal trace
                 */
                virtual bool evaluate(const SpatialTemporalTrace &trace);

                //! Check if more traces are accepted for evaluating the logic property
                virtual bool acceptsMoreTraces() = 0;

                //! Check if more traces are required for evaluating the logic property
                virtual bool requiresMoreTraces() = 0;

                //! Check if the given property holds
                virtual bool doesPropertyHold() = 0;

                //! Get a detailed report of the results
                virtual std::string getDetailedResults() = 0;

            protected:

                //! Update the model checker results considering that the logic property was evaluated to true for the last trace
                virtual void updateModelCheckerForTrueEvaluation() = 0;

                //! Update the model checker results considering that the logic property was evaluated to false for the last trace
                virtual void updateModelCheckerForFalseEvaluation() = 0;

            private:

                //! Update the model checker results considering that the logic property was evaluated to evaluationResult for the last trace
                /*!
                 * \param evaluationResult  The result of evaluating the logic property considering the last trace
                 */
                void updateModelChecker(bool evaluationResult);

        };

    };

};

#endif
