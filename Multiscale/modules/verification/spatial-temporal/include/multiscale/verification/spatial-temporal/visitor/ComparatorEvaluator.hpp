#ifndef COMPARATOREVALUATOR_HPP
#define COMPARATOREVALUATOR_HPP

#include "multiscale/util/Numeric.hpp"
#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ScaleAndSubsystemEvaluator.hpp"


namespace multiscale {

    namespace verification {

        //! Class for evaluating comparison expressions
        class ComparatorEvaluator {

            public:

                //! Compare two real valued elements considering a given comparator
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

                //! Compare two scales and subsystems considering a given comparator and multiscale architecture graph
                /*!
                 * \param lhsScaleAndSubsystem          The left hand side scale and subsystem
                 * \param comparator                    The comparator type used to compare the elements
                 * \param rhsScaleAndSubsystem          The right hand side scale and subsystem
                 * \param multiscaleArchitectureGraph   The considered multiscale architecture graph which encodes
                 *                                      relations between scales and subsystems
                 */
                static bool evaluate(const std::string &lhsScaleAndSubsystem, const ComparatorType &comparator,
                                     const std::string &rhsScaleAndSubsystem,
                                     const MultiscaleArchitectureGraph &multiscaleArchitectureGraph) {
                    switch (comparator) {
                        case ComparatorType::GreaterThan:
                            return (
                                multiscaleArchitectureGraph.isScaleAndSubsystemSmallerThan(
                                    rhsScaleAndSubsystem,
                                    lhsScaleAndSubsystem
                                )
                            );

                        case ComparatorType::GreaterThanOrEqual:
                            return (
                                multiscaleArchitectureGraph.isScaleAndSubsystemSmallerThan(
                                    rhsScaleAndSubsystem,
                                    lhsScaleAndSubsystem
                                ) || (
                                    ScaleAndSubsystemEvaluator::areEqualScalesAndSubsystems(
                                        lhsScaleAndSubsystem,
                                        rhsScaleAndSubsystem
                                    )
                                )
                            );

                        case ComparatorType::LessThan:
                            return (
                                multiscaleArchitectureGraph.isScaleAndSubsystemSmallerThan(
                                    lhsScaleAndSubsystem,
                                    rhsScaleAndSubsystem
                                )
                            );

                        case ComparatorType::LessThanOrEqual:
                            return (
                                multiscaleArchitectureGraph.isScaleAndSubsystemSmallerThan(
                                    lhsScaleAndSubsystem,
                                    rhsScaleAndSubsystem
                                ) || (
                                    ScaleAndSubsystemEvaluator::areEqualScalesAndSubsystems(
                                        lhsScaleAndSubsystem,
                                        rhsScaleAndSubsystem
                                    )
                                )
                            );

                        case ComparatorType::Equal:
                            return (
                                ScaleAndSubsystemEvaluator::areEqualScalesAndSubsystems(
                                    lhsScaleAndSubsystem,
                                    rhsScaleAndSubsystem
                                )
                            );

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
