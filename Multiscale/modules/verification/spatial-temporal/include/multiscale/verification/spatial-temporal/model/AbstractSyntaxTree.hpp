#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SynthesizedAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"


namespace multiscale {

    namespace verification {

        //! Class used for representing an abstract syntax tree
        class AbstractSyntaxTree {

            private:

                ProbabilisticLogicPropertyAttribute probabilisticLogicProperty; /*!< The abstract syntax tree represented using a probabilistic logic property attribute */

            public:

                AbstractSyntaxTree(ProbabilisticLogicPropertyAttribute &probabilisticLogicPropertyAttribute);
                ~AbstractSyntaxTree();

                //! Get the type of the comparator used in the probabilistic logical query
                ComparatorType getComparator();

                //! Get the value of the probability used in the probabilistic logical query
                double getProbability();

                //! Evaluate the abstract syntax tree considering the given trace
                /*!
                 * \param spatialTemporalTrace  The given spatial temporal trace
                 */
                bool evaluate(const SpatialTemporalTrace &spatialTemporalTrace);

        };

    };

};

#endif
