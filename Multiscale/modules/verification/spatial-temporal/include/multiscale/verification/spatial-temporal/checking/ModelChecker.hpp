#ifndef MODELCHECKER_HPP
#define MODELCHECKER_HPP

#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"


namespace multiscale {

    namespace verification {

        //! Abstract class representing a generic model checker
        class ModelChecker {

            private:

                AbstractSyntaxTree abstractSyntaxTree;  /*!< The abstract syntax tree representing
                                                             the logic property which this model checker
                                                             instance evaluates */

            public:

                ModelChecker(const AbstractSyntaxTree &abstractSyntaxTree)
                             : abstractSyntaxTree(abstractSyntaxTree) {}
                virtual ~ModelChecker();

                //! Evaluate the abstract syntax tree for the given trace
                /*!
                 * \param trace The given spatial temporal trace
                 */
                virtual void evaluate(const SpatialTemporalTrace &trace) = 0;

                //! Check if more traces are accepted for evaluating the logic property
                virtual bool acceptsMoreTraces() = 0;

                //! Check if more traces are required for evaluating the logic property
                virtual bool requiresMoreTraces() = 0;

                //! Check if the given property holds
                virtual bool doesPropertyHold() = 0;

                //! Get a detailed report of the results
                virtual std::string getDetailedResults() = 0;

        };

    };

};

#endif
