#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"
#include "multiscale/verification/spatial-temporal/model/MultiscaleArchitectureGraph.hpp"


namespace multiscale {

    namespace verification {

        //! Class used for representing an abstract syntax tree
        class AbstractSyntaxTree {

            private:

                bool
                    isInitialized;                      /*!< Flag for indicating if the abstract syntax tree
                                                             was initialized */
                ProbabilisticLogicPropertyAttribute
                    probabilisticLogicProperty;         /*!< The abstract syntax tree represented using a
                                                             probabilistic logic property attribute */

            public:

                AbstractSyntaxTree();
                ~AbstractSyntaxTree();

                //! Initialize the abstract syntax tree using the given probabilistic logic property attribute
                /*!
                 * \param probabilisticLogicPropertyAttribute   The probabilistic logic property attribute
                 */
                void initializeTree(const ProbabilisticLogicPropertyAttribute &probabilisticLogicPropertyAttribute);

                //! Get the type of the comparator used in the probabilistic logical query
                ComparatorType getComparator();

                //! Get the value of the probability used in the probabilistic logical query
                double getProbability();

                //! Evaluate the abstract syntax tree considering the given trace and multiscale architecture graph
                /*!
                 * \param spatialTemporalTrace          The given spatial temporal trace
                 * \param multiscaleArchitectureGraph   The considered multiscale architecture graph
                 */
                bool evaluate(SpatialTemporalTrace &spatialTemporalTrace,
                              const MultiscaleArchitectureGraph &multiscaleArchitectureGraph);

            private:

                // Constants
                static const std::string ERR_ABSTRACT_SYNTAX_TREE_NOT_INITIALIZED;

        };

    };

};


#endif
