#ifndef COMPARATOREVALUATOR_HPP
#define COMPARATOREVALUATOR_HPP

#include "multiscale/util/Numeric.hpp"
#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"


namespace multiscale {

    namespace verification {

        //! Class for evaluating comparison expressions
        class ComparatorEvaluator {

            public:

                //! Compare two elements using a ComparatorType comparator
                /*!
                 *  \param lhsElement   The element which is on the left hand side of the comparator
                 *  \param comparator   The comparator type used to compare the elements
                 *  \param rhsElement   The element which is on the right hand side of the comparator
                 */
                template <typename T>
                static bool evaluate(T lhsElement, const ComparatorType &comparator, T rhsElement) {
                    switch (comparator) {
                        case ComparatorType::GreaterThan:
                            return (lhsElement > rhsElement);

                        case ComparatorType::GreaterThanOrEqual:
                            return (Numeric::greaterOrEqual(lhsElement, rhsElement));

                        case ComparatorType::LessThan:
                            return (lhsElement < rhsElement);

                        case ComparatorType::LessThanOrEqual:
                            return (Numeric::lessOrEqual(lhsElement, rhsElement));

                        case ComparatorType::Equal:
                            return (Numeric::almostEqual(lhsElement, rhsElement));

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return true;
                }

        };

    };

};


#endif
