#ifndef CONSTRAINTVISITOR_HPP
#define CONSTRAINTVISITOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ComparatorEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/FilterNumericVisitor.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SpatialMeasureEvaluator.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Class used to evaluate constraints
        class ConstraintVisitor : public boost::static_visitor<TimePoint> {

            private:

                TimePoint
                    &initialTimePoint;              /*!< A copy of the initial time point */
                TimePoint
                    &constraintTimePoint;           /*!< The currently obtained constraint time point */
                const MultiscaleArchitectureGraph
                    &multiscaleArchitectureGraph;   /*!< The considered multiscale architecture graph */

            public:

                ConstraintVisitor(TimePoint &initialTimePoint, TimePoint &constraintTimePoint,
                                  const MultiscaleArchitectureGraph &multiscaleArchitectureGraph)
                                  : initialTimePoint(initialTimePoint), constraintTimePoint(constraintTimePoint),
                                    multiscaleArchitectureGraph(multiscaleArchitectureGraph) {}

                //! Overloading the "()" operator for the Nil alternative
                /*!
                 * \param constraint     The constraint
                 */
                TimePoint operator() (const Nil &constraint) const {
                    return initialTimePoint;
                }

                //! Overloading the "()" operator for the ConstraintAttribute alternative
                /*!
                 * \param constraint     The constraint
                 */
                TimePoint operator() (const ConstraintAttribute &constraint) const {
                    // Apply the first constraint to the time point
                    TimePoint timePoint(
                        evaluate(constraint.firstConstraint, initialTimePoint)
                    );

                    // Apply the remaining constraints to the time point
                    return evaluateNextConstraints(constraint, timePoint);
                }

                //! Overloading the "()" operator for the OrConstraintAttribute alternative
                /*!
                 * \param constraint     The constraint
                 */
                TimePoint operator() (const OrConstraintAttribute &constraint) const {
                    TimePoint timePoint(evaluate(constraint.constraint, initialTimePoint));

                    timePoint.timePointUnion(constraintTimePoint);

                    return timePoint;
                }

                //! Overloading the "()" operator for the AndConstraintAttribute alternative
                /*!
                 * \param constraint     The constraint
                 */
                TimePoint operator() (const AndConstraintAttribute &constraint) const {
                    TimePoint timePoint(evaluate(constraint.constraint, initialTimePoint));

                    timePoint.timePointIntersection(constraintTimePoint);

                    return timePoint;
                }

                //! Overloading the "()" operator for the ImplicationConstraintAttribute alternative
                /*!
                 * \param constraint     The constraint
                 */
                TimePoint operator() (const ImplicationConstraintAttribute &constraint) const {
                    TimePoint timePoint(evaluate(constraint.constraint, initialTimePoint));
                    TimePoint initialTimePointCopy(initialTimePoint);

                    // (p => q)
                    initialTimePointCopy.timePointDifference(constraintTimePoint);
                    initialTimePointCopy.timePointUnion(timePoint);

                    return initialTimePointCopy;
                }

                //! Overloading the "()" operator for the EquivalenceConstraintAttribute alternative
                /*!
                 * \param constraint     The constraint
                 */
                TimePoint operator() (const EquivalenceConstraintAttribute &constraint) const {
                    TimePoint timePoint(evaluate(constraint.constraint, initialTimePoint));
                    TimePoint forwardImplicationTimePoint(initialTimePoint);
                    TimePoint reverseImplicationTimePoint(initialTimePoint);

                    // (p => q)
                    forwardImplicationTimePoint.timePointDifference(constraintTimePoint);
                    forwardImplicationTimePoint.timePointUnion(timePoint);

                    // (q => p)
                    reverseImplicationTimePoint.timePointDifference(timePoint);
                    reverseImplicationTimePoint.timePointUnion(constraintTimePoint);

                    // (p => q) ^ (q => p)
                    forwardImplicationTimePoint.timePointIntersection(reverseImplicationTimePoint);

                    return forwardImplicationTimePoint;
                }

                //! Overloading the "()" operator for the PrimaryConstraintAttribute alternative
                /*!
                 * \param primaryConstraint The primary constraint
                 */
                TimePoint operator() (const PrimaryConstraintAttribute &primaryConstraint) const {
                    return evaluate(primaryConstraint.primaryConstraint, constraintTimePoint);
                }

                //! Overloading the "()" operator for the NotConstraintAttribute alternative
                /*!
                 * \param primaryConstraint The primary constraint
                 */
                TimePoint operator() (const NotConstraintAttribute &primaryConstraint) const {
                    TimePoint constrainedTimePoint(evaluate(primaryConstraint.constraint, constraintTimePoint));
                    TimePoint notTimePoint(initialTimePoint);

                    notTimePoint.timePointDifference(constrainedTimePoint);

                    return notTimePoint;
                }

                //! Overloading the "()" operator for the UnaryScaleAndSubsystemConstraintAttribute alternative
                /*!
                 * \param primaryConstraint The primary constraint
                 */
                TimePoint operator() (const UnaryScaleAndSubsystemConstraintAttribute &primaryConstraint) const {
                    ComparatorType comparatorType = primaryConstraint.comparator.comparatorType;

                    return (
                        evaluateUnaryScaleAndSubsystemConstraint(
                            comparatorType,
                            primaryConstraint.scaleAndSubsystem,
                            constraintTimePoint
                        )
                   );
                }

                //! Overloading the "()" operator for the UnarySpatialConstraintAttribute alternative
                /*!
                 * \param primaryConstraint The primary constraint
                 */
                TimePoint operator() (const UnarySpatialConstraintAttribute &primaryConstraint) const {
                    ComparatorType comparatorType = primaryConstraint.comparator.comparatorType;

                    return (
                        evaluateUnarySpatialConstraint(
                            primaryConstraint.spatialMeasure.spatialMeasureType,
                            comparatorType,
                            primaryConstraint.filterNumericMeasure,
                            constraintTimePoint
                        )
                    );
                }

            private:

                //! Evaluate the constraint considering the given time point
                /*!
                 * \param constraint    The given constraint
                 * \param timePoint     The given time point
                 */
                TimePoint evaluate(const ConstraintAttributeType &constraint, TimePoint &timePoint) const {
                    return (
                        boost::apply_visitor(
                            ConstraintVisitor(
                                initialTimePoint,
                                timePoint,
                                multiscaleArchitectureGraph
                            ),
                            constraint
                        )
                    );
                }

                //! Evaluate the primary constraint considering the given time points
                /*!
                 * \param primaryConstraint The given primary constraint
                 * \param timePoint         The given time point
                 */
                TimePoint evaluate(const PrimaryConstraintAttributeType &primaryConstraint,
                                   TimePoint &timePoint) const {
                    return (
                        boost::apply_visitor(
                            ConstraintVisitor(
                                initialTimePoint,
                                timePoint,
                                multiscaleArchitectureGraph
                            ),
                            primaryConstraint
                        )
                    );
                }

                //! Evaluate the next constraints
                /*!
                 * Evaluate the next constraints considering the given constraint and time points
                 *
                 * \param constraint    The given constraint
                 * \param timePoint     The resulting time point after applying the first constraint to the
                 *                      initial time point
                 */
                TimePoint evaluateNextConstraints(const ConstraintAttribute &constraint,
                                                  const TimePoint &timePoint) const {
                    TimePoint constrainedTimePoint(timePoint);

                    for (const auto &nextConstraint : constraint.nextConstraints) {
                        constrainedTimePoint = boost::apply_visitor(
                                                   ConstraintVisitor(
                                                       initialTimePoint,
                                                       constrainedTimePoint,
                                                       multiscaleArchitectureGraph
                                                   ),
                                                   nextConstraint
                                               );
                    }

                    return constrainedTimePoint;
                }

                //! Evaluate the unary scale and subsystem constraint
                /*! Evaluate the unary scale and subsystem constraint considering the given spatial measure,
                 *  comparator, scale and subsystem and time point
                 *
                 * \param comparator        The comparator type
                 * \param scaleAndSubsystem The scale and subsystem
                 * \param timePoint         The considered time point
                 */
                TimePoint evaluateUnaryScaleAndSubsystemConstraint(
                    const ComparatorType &comparator,
                    const ScaleAndSubsystemAttribute &scaleAndSubsystem,
                    TimePoint &timePoint
                ) const {
                    TimePoint unaryConstraintTimePoint(timePoint);

                    evaluateScaleAndSubsystemConstraint(
                        unaryConstraintTimePoint,
                        comparator,
                        scaleAndSubsystem
                    );

                    return unaryConstraintTimePoint;
                }

                //! Filter the time point's spatial entities considering the scale and subsystem of each spatial entity
                /*!
                 * \param timePoint         The time point storing the collection of spatial entities which
                 *                          will be filtered
                 * \param comparator        The type of the comparator
                 * \param scaleAndSubsystem The scale and subsystem
                 */
                void evaluateScaleAndSubsystemConstraint(TimePoint &timePoint, const ComparatorType &comparator,
                                                         const ScaleAndSubsystemAttribute &scaleAndSubsystem) const {
                    std::bitset<NR_SUBSET_SPECIFIC_TYPES> consideredSpatialEntityTypes
                        = timePoint.getConsideredSpatialEntityTypes();

                    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
                        if (consideredSpatialEntityTypes[i] == true) {
                            SubsetSpecificType subsetSpecificType = subsetspecific::computeSubsetSpecificType(i);

                            filterSpatialEntitiesWrtScaleAndSubsystem(
                                timePoint,
                                subsetSpecificType,
                                comparator,
                                scaleAndSubsystem
                            );
                        }
                    }
                }

                //! Evaluate the unary spatial constraint
                /*! Evaluate the unary spatial constraint considering the given spatial measure, comparator,
                 *  numeric measure and time point
                 *
                 * \param spatialMeasure        The spatial measure type
                 * \param comparator            The comparator type
                 * \param filterNumericMeasure  The filter numeric measure
                 * \param timePoint             The considered time point
                 */
                TimePoint evaluateUnarySpatialConstraint(const SpatialMeasureType &spatialMeasure,
                                                         const ComparatorType &comparator,
                                                         const FilterNumericMeasureAttributeType &filterNumericMeasure,
                                                         TimePoint &timePoint) const {
                    TimePoint unaryConstraintTimePoint(timePoint);

                    evaluateSpatialMeasureConstraint(
                        unaryConstraintTimePoint,
                        spatialMeasure,
                        comparator,
                        filterNumericMeasure
                    );

                    return unaryConstraintTimePoint;
                }

                //! Evaluate the numeric measure considering the given time point
                /*!
                 * \param numericMeasure    The numeric measure
                 * \param timePoint         The given time point
                 */
                double evaluateNumericMeasure(const NumericMeasureType &numericMeasure,
                                              TimePoint &timePoint) const {
                    return (
                        boost::apply_visitor(
                            NumericVisitor(
                                timePoint,
                                multiscaleArchitectureGraph
                            ),
                            numericMeasure
                        )
                    );
                }

                //! Filter the time point's spatial entities considering the given spatial measure constraint
                /*!
                 * All considered spatial entities which fail to meet the constraints
                 * will be removed from the given time point.
                 *
                 * \param timePoint             The time point storing the collection of spatial entities which
                 *                              will be filtered
                 * \param spatialMeasure        The type of the spatial measure
                 * \param comparator            The type of the comparator
                 * \param filterNumericMeasure  The filter numeric measure
                 */
                void evaluateSpatialMeasureConstraint(TimePoint &timePoint,
                                                      const SpatialMeasureType &spatialMeasure,
                                                      const ComparatorType &comparator,
                                                      const FilterNumericMeasureAttributeType
                                                      &filterNumericMeasure) const {
                    std::bitset<NR_SUBSET_SPECIFIC_TYPES> consideredSpatialEntityTypes
                        = timePoint.getConsideredSpatialEntityTypes();

                    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
                        if (consideredSpatialEntityTypes[i] == true) {
                            SubsetSpecificType subsetSpecificType = subsetspecific::computeSubsetSpecificType(i);

                            filterSpatialEntitiesWrtSpatialMeasure(
                                timePoint,
                                subsetSpecificType,
                                spatialMeasure,
                                comparator,
                                filterNumericMeasure
                            );
                        }
                    }
                }

                //! Remove from the time point the spatial entities which fail to meet the spatial measure constraint
                /*!
                 * \param timePoint             The time point which will be filtered
                 * \param spatialEntityType     The considered spatial entity type
                 * \param spatialMeasure        The type of the spatial measure
                 * \param comparator            The type of the comparator
                 * \param filterNumericMeasure  The filter numeric measure
                 */
                void filterSpatialEntitiesWrtSpatialMeasure(TimePoint &timePoint,
                                                            const SubsetSpecificType &spatialEntityType,
                                                            const SpatialMeasureType &spatialMeasure,
                                                            const ComparatorType &comparator,
                                                            const FilterNumericMeasureAttributeType
                                                            &filterNumericMeasure) const {
                    auto beginIt = timePoint.getSpatialEntitiesBeginIterator(spatialEntityType);
                    auto endIt   = timePoint.getSpatialEntitiesEndIterator(spatialEntityType);

                    while (beginIt != endIt) {
                        double spatialMeasureValue
                            = SpatialMeasureEvaluator::evaluate(*(*beginIt), spatialMeasure);
                        double filterNumericMeasureValue
                            = evaluateFilterNumericMeasure(filterNumericMeasure, timePoint, *(*beginIt));

                        if (!ComparatorEvaluator::evaluate(
                                spatialMeasureValue, comparator, filterNumericMeasureValue
                            )
                        ) {
                            beginIt = timePoint.removeSpatialEntity(beginIt, spatialEntityType);
                        } else {
                            beginIt++;
                        }
                    }
                }

                //! Remove from time point the spatial entities which fail to meet the scale and subsystem constraint
                /*!
                 * \param timePoint             The time point which will be filtered
                 * \param subsetSpecificType    The considered subset specific type
                 * \param comparator            The type of the comparator
                 * \param scaleAndSubsystem     The scaleAndSubsystem type
                 */
                void filterSpatialEntitiesWrtScaleAndSubsystem(
                    TimePoint &timePoint, const SubsetSpecificType &subsetSpecificType,
                    const ComparatorType &comparator, const ScaleAndSubsystemAttribute &scaleAndSubsystem
                ) const {
                    // Obtain the right hand side scale and subsystem
                    std::string rhsScaleAndSubsystem = scaleAndSubsystem.scaleAndSubsystem;

                    // Validate the scale and subsystem
                    ScaleAndSubsystemEvaluator::validateScaleAndSubsystem(
                        rhsScaleAndSubsystem,
                        multiscaleArchitectureGraph
                    );

                    // Filter the spatial entities with respect to the scale and subsystem
                    return (
                        filterSpatialEntitiesWrtScaleAndSubsystem(
                            timePoint,
                            subsetSpecificType,
                            comparator,
                            rhsScaleAndSubsystem
                        )
                    );
                }

                //! Remove from time point the spatial entities which fail to meet the scale and subsystem constraint
                /*! The assumption for this method is that the provided scale and subsystem exists in the
                 *  multiscale architecture graph.
                 *
                 * \param timePoint             The time point which will be filtered
                 * \param spatialEntityType     The considered spatial entity type
                 * \param comparator            The type of the comparator
                 * \param scaleAndSubsystem     The scale and subsystem
                 */
                void filterSpatialEntitiesWrtScaleAndSubsystem(
                    TimePoint &timePoint, const SubsetSpecificType &spatialEntityType,
                    const ComparatorType &comparator, const std::string &scaleAndSubsystem
                ) const {
                    if (comparator == ComparatorType::Equal) {
                        filterSpatialEntitiesWrtScaleAndSubsystemConsideringEqualComparator(
                            timePoint,
                            spatialEntityType,
                            scaleAndSubsystem
                        );
                    } else {
                        filterSpatialEntitiesWrtScaleAndSubsystemConsideringNonEqualComparator(
                            timePoint,
                            spatialEntityType,
                            comparator,
                            scaleAndSubsystem
                        );
                    }
                }

                //! Remove from time point the spatial entities which fail to meet the scale and subsystem constraint
                /*! The assumption for this method is that the considered comparator is "=".
                 *
                 * In this case the multiscale architecture graph is NOT used.
                 *
                 * \param timePoint             The time point which will be filtered
                 * \param spatialEntityType     The considered spatial entity type
                 * \param rhsScaleAndSubsystem  The scale and subsystem on the right hand side of the comparator
                 */
                void filterSpatialEntitiesWrtScaleAndSubsystemConsideringEqualComparator(
                    TimePoint &timePoint, const SubsetSpecificType &spatialEntityType,
                    const std::string &rhsScaleAndSubsystem
                ) const {
                    auto beginIt = timePoint.getSpatialEntitiesBeginIterator(spatialEntityType);
                    auto endIt   = timePoint.getSpatialEntitiesEndIterator(spatialEntityType);

                    // Filter spatial entities considering their type
                    while (beginIt != endIt) {
                        std::string lhsScaleAndSubsystem = ((*beginIt)->getScaleAndSubsystem());

                        if (lhsScaleAndSubsystem.compare(rhsScaleAndSubsystem) != 0) {
                            beginIt = timePoint.removeSpatialEntity(beginIt, spatialEntityType);
                        } else {
                            beginIt++;
                        }
                    }
                }

                //! Remove from time point the spatial entities which fail to meet the scale and subsystem constraint
                /*! The assumption for this method is that the considered comparator is different from "=".
                 *
                 * In this case the multiscale architecture graph is used.
                 *
                 * \param timePoint             The time point which will be filtered
                 * \param spatialEntityType     The considered spatial entity type
                 * \param comparator            The type of the comparator
                 * \param rhsScaleAndSubsystem  The scale and subsystem on the right hand side of the comparator
                 */
                void filterSpatialEntitiesWrtScaleAndSubsystemConsideringNonEqualComparator(
                    TimePoint &timePoint, const SubsetSpecificType &spatialEntityType,
                    const ComparatorType &comparator, const std::string &rhsScaleAndSubsystem
                ) const {
                    auto beginIt = timePoint.getSpatialEntitiesBeginIterator(spatialEntityType);
                    auto endIt   = timePoint.getSpatialEntitiesEndIterator(spatialEntityType);

                    // Filter spatial entities considering their scale and subsystem
                    while (beginIt != endIt) {
                        std::string lhsScaleAndSubsystem = ((*beginIt)->getScaleAndSubsystem());

                        if (
                            !ComparatorEvaluator::evaluate(
                                lhsScaleAndSubsystem,
                                comparator,
                                rhsScaleAndSubsystem,
                                multiscaleArchitectureGraph
                            )
                        ) {
                            beginIt = timePoint.removeSpatialEntity(beginIt, spatialEntityType);
                        } else {
                            beginIt++;
                        }
                    }
                }

                //! Evaluate the filter numeric measure considering the provided time point and spatial entity
                /*!
                 * \param filterNumericMeasure  The filter numeric measure
                 * \param timePoint             The considered time point
                 * \param spatialEntity         The considered spatial entity
                 */
                double evaluateFilterNumericMeasure(const FilterNumericMeasureAttributeType &filterNumericMeasure,
                                                    TimePoint &timePoint,
                                                    const SpatialEntity &spatialEntity) const {
                    return (
                        boost::apply_visitor(
                            FilterNumericVisitor(
                                timePoint,
                                spatialEntity,
                                multiscaleArchitectureGraph
                            ),
                            filterNumericMeasure
                        )
                    );
                }

        };

    };

};


#endif
