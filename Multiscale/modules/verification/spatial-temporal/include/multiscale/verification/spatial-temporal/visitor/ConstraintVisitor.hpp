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

                TimePoint                   &initialTimePoint;     /*!< A copy of the initial timepoint */
                TimePoint                   &constraintTimePoint;  /*!< The currently obtained constraint timepoint */
                const TypeSemanticsTable    &typeSemanticsTable;   /*!< The considered type semantics table */

            public:

                ConstraintVisitor(TimePoint &initialTimePoint, TimePoint &constraintTimePoint,
                                  const TypeSemanticsTable &typeSemanticsTable)
                                  : initialTimePoint(initialTimePoint), constraintTimePoint(constraintTimePoint),
                                    typeSemanticsTable(typeSemanticsTable) {}

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
                    // Apply the first constraint to the timepoint
                    TimePoint timePoint(
                        evaluate(constraint.firstConstraint, initialTimePoint)
                    );

                    // Apply the remaining constraints to the timepoint
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

                //! Overloading the "()" operator for the UnaryTypeConstraintAttribute alternative
                /*!
                 * \param primaryConstraint The primary constraint
                 */
                TimePoint operator() (const UnaryTypeConstraintAttribute &primaryConstraint) const {
                    ComparatorType comparatorType = primaryConstraint.comparator.comparatorType;

                    return evaluateUnaryTypeConstraint(comparatorType, primaryConstraint.semanticType,
                                                       constraintTimePoint);
                }

                //! Overloading the "()" operator for the UnarySpatialConstraintAttribute alternative
                /*!
                 * \param primaryConstraint The primary constraint
                 */
                TimePoint operator() (const UnarySpatialConstraintAttribute &primaryConstraint) const {
                    ComparatorType comparatorType = primaryConstraint.comparator.comparatorType;

                    return evaluateUnarySpatialConstraint(primaryConstraint.spatialMeasure.spatialMeasureType,
                                                          comparatorType, primaryConstraint.filterNumericMeasure,
                                                          constraintTimePoint);
                }

            private:

                //! Evaluate the constraint considering the given timepoint
                /*!
                 * \param constraint    The given constraint
                 * \param timePoint     The given timepoint
                 */
                TimePoint evaluate(const ConstraintAttributeType &constraint, TimePoint &timePoint) const {
                    return (
                        boost::apply_visitor(
                            ConstraintVisitor(initialTimePoint, timePoint, typeSemanticsTable),
                            constraint
                        )
                    );
                }

                //! Evaluate the primary constraint considering the given timepoints
                /*!
                 * \param primaryConstraint The given primary constraint
                 * \param timePoint         The given timepoint
                 */
                TimePoint evaluate(const PrimaryConstraintAttributeType &primaryConstraint,
                                   TimePoint &timePoint) const {
                    return (
                        boost::apply_visitor(
                            ConstraintVisitor(initialTimePoint, timePoint, typeSemanticsTable),
                            primaryConstraint
                        )
                    );
                }

                //! Evaluate the next constraints
                /*!
                 * Evaluate the next constraints considering the given constraint and timepoints
                 *
                 * \param constraint    The given constraint
                 * \param timePoint     The resulting timepoint after applying the first constraint to the
                 *                      initial timepoint
                 */
                TimePoint evaluateNextConstraints(const ConstraintAttribute &constraint,
                                                  const TimePoint &timePoint) const {
                    TimePoint constrainedTimePoint(timePoint);

                    for (const auto &nextConstraint : constraint.nextConstraints) {
                        constrainedTimePoint = boost::apply_visitor(
                                                   ConstraintVisitor(
                                                       initialTimePoint,
                                                       constrainedTimePoint,
                                                       typeSemanticsTable
                                                   ),
                                                   nextConstraint
                                               );
                    }

                    return constrainedTimePoint;
                }

                //! Evaluate the unary type constraint
                /*! Evaluate the unary type constraint considering the given spatial measure, comparator,
                 *  semantic type and timepoint
                 *
                 * \param comparator    The comparator type
                 * \param semanticType  The semantic type
                 * \param timePoint     The considered timepoint
                 */
                TimePoint evaluateUnaryTypeConstraint(const ComparatorType &comparator,
                                                      const SemanticTypeAttribute &semanticType,
                                                      TimePoint &timePoint) const {
                    TimePoint unaryConstraintTimePoint(timePoint);

                    evaluateTypeConstraint(unaryConstraintTimePoint, comparator, semanticType);

                    return unaryConstraintTimePoint;
                }

                //! Filter the timepoint's spatial entities considering the type of each spatial entity
                /*!
                 * \param timePoint     The timepoint storing the collection of spatial entities which
                 *                      will be filtered
                 * \param comparator    The type of the comparator
                 * \param semanticType  The semantic type
                 */
                void evaluateTypeConstraint(TimePoint &timePoint, const ComparatorType &comparator,
                                            const SemanticTypeAttribute &semanticType) const {
                    std::bitset<NR_SUBSET_SPECIFIC_TYPES> consideredSpatialEntityTypes
                        = timePoint.getConsideredSpatialEntityTypes();

                    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
                        if (consideredSpatialEntityTypes[i] == true) {
                            SubsetSpecificType subsetSpecificType = subsetspecific::computeSubsetSpecificType(i);

                            filterSpatialEntitiesWrtType(timePoint, subsetSpecificType, comparator,
                                                         semanticType);
                        }
                    }
                }

                //! Evaluate the unary spatial constraint
                /*! Evaluate the unary spatial constraint considering the given spatial measure, comparator,
                 *  numeric measure and timepoint
                 *
                 * \param spatialMeasure        The spatial measure type
                 * \param comparator            The comparator type
                 * \param filterNumericMeasure  The filter numeric measure
                 * \param timePoint             The considered timepoint
                 */
                TimePoint evaluateUnarySpatialConstraint(const SpatialMeasureType &spatialMeasure,
                                                         const ComparatorType &comparator,
                                                         const FilterNumericMeasureAttributeType &filterNumericMeasure,
                                                         TimePoint &timePoint) const {
                    TimePoint unaryConstraintTimePoint(timePoint);

                    evaluateSpatialMeasureConstraint(unaryConstraintTimePoint, spatialMeasure,
                                                     comparator, filterNumericMeasure);

                    return unaryConstraintTimePoint;
                }

                //! Evaluate the numeric measure considering the given timepoint
                /*!
                 * \param numericMeasure    The numeric measure
                 * \param timePoint         The given timepoint
                 */
                double evaluateNumericMeasure(const NumericMeasureType &numericMeasure,
                                              TimePoint &timePoint) const {
                    return (
                        boost::apply_visitor(
                            NumericVisitor(timePoint, typeSemanticsTable),
                            numericMeasure
                        )
                    );
                }

                //! Filter the timepoint's spatial entities considering the given spatial measure constraint
                /*!
                 * All considered spatial entities which fail to meet the constraints
                 * will be removed from the given timepoint.
                 *
                 * \param timePoint             The timepoint storing the collection of spatial entities which
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

                            filterSpatialEntitiesWrtSpatialMeasure(timePoint, subsetSpecificType, spatialMeasure,
                                                                   comparator, filterNumericMeasure);
                        }
                    }
                }

                //! Remove from the timepoint the spatial entities which fail to meet the spatial measure constraint
                /*!
                 * \param timePoint             The timepoint which will be filtered
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

                //! Remove from the timepoint the spatial entities which fail to meet the type constraint
                /*!
                 * \param timePoint             The timepoint which will be filtered
                 * \param spatialEntityType     The considered spatial entity type
                 * \param comparator            The type of the comparator
                 * \param semanticType          The semantic type
                 */
                void filterSpatialEntitiesWrtType(
                    TimePoint &timePoint, const SubsetSpecificType &spatialEntityType,
                    const ComparatorType &comparator, const SemanticTypeAttribute &semanticType
                ) const {
                    // Obtain the right hand side semantic type
                    std::string rhsSemanticType = semanticType.semanticType;

                    // Validate the semantic type
                    SemanticTypeEvaluator::validate(rhsSemanticType, typeSemanticsTable);

                    // Filter the spatial entities with respect to the semantic type
                    return (
                        filterSpatialEntitiesWrtType(
                            timePoint,
                            spatialEntityType,
                            comparator,
                            rhsSemanticType
                        )
                    );
                }

                //! Remove from the timepoint the spatial entities which fail to meet the type constraint
                /*! The assumption for this method is that the provided semantic type exists in the
                 *  type semantics table.
                 *
                 * \param timePoint             The timepoint which will be filtered
                 * \param spatialEntityType     The considered spatial entity type
                 * \param comparator            The type of the comparator
                 * \param semanticType          The semantic type
                 */
                void filterSpatialEntitiesWrtType(
                    TimePoint &timePoint, const SubsetSpecificType &spatialEntityType,
                    const ComparatorType &comparator, const std::string &semanticType
                ) const {
                    if (comparator == ComparatorType::Equal) {
                        filterSpatialEntitiesWrtTypeConsideringEqualComparator(
                            timePoint, spatialEntityType, semanticType
                        );
                    } else {
                        filterSpatialEntitiesWrtTypeConsideringNonEqualComparator(
                            timePoint, spatialEntityType, comparator, semanticType
                        );
                    }
                }

                //! Remove from the timepoint the spatial entities which fail to meet the type constraint
                /*! The assumption for this method is that the considered comparator is "=".
                 *
                 * In this case the type semantics table is NOT used.
                 *
                 * \param timePoint             The timepoint which will be filtered
                 * \param spatialEntityType     The considered spatial entity type
                 * \param rhsSemanticType       The semantic type on the right of the comparator
                 */
                void filterSpatialEntitiesWrtTypeConsideringEqualComparator(
                    TimePoint &timePoint, const SubsetSpecificType &spatialEntityType,
                    const std::string &rhsSemanticType
                ) const {
                    auto beginIt = timePoint.getSpatialEntitiesBeginIterator(spatialEntityType);
                    auto endIt   = timePoint.getSpatialEntitiesEndIterator(spatialEntityType);

                    // Filter spatial entities considering their type
                    while (beginIt != endIt) {
                        std::string lhsTypeValue = ((*beginIt)->getSemanticType());

                        if (lhsTypeValue.compare(rhsSemanticType) != 0) {
                            beginIt = timePoint.removeSpatialEntity(beginIt, spatialEntityType);
                        } else {
                            beginIt++;
                        }
                    }
                }

                //! Remove from the timepoint the spatial entities which fail to meet the type constraint
                /*! The assumption for this method is that the considered comparator is different from "=".
                 *
                 * In this case the type semantics table is used.
                 *
                 * \param timePoint             The timepoint which will be filtered
                 * \param spatialEntityType     The considered spatial entity type
                 * \param comparator            The type of the comparator
                 * \param rhsSemanticType       The semantic type on the right of the comparator
                 */
                void filterSpatialEntitiesWrtTypeConsideringNonEqualComparator(
                    TimePoint &timePoint, const SubsetSpecificType &spatialEntityType,
                    const ComparatorType &comparator, const std::string &rhsSemanticType
                ) const {
                    // Obtain the type value for the right hand side semantic criteria values
                    double rhsTypeValue = translateSemanticTypeToAbstractNaturalNumber(rhsSemanticType);

                    auto beginIt = timePoint.getSpatialEntitiesBeginIterator(spatialEntityType);
                    auto endIt   = timePoint.getSpatialEntitiesEndIterator(spatialEntityType);

                    // Filter spatial entities considering their type
                    while (beginIt != endIt) {
                        double lhsTypeValue
                            = translateSemanticTypeToAbstractNaturalNumber((*beginIt)->getSemanticType());

                        if (!ComparatorEvaluator::evaluate(lhsTypeValue, comparator, rhsTypeValue)) {
                            beginIt = timePoint.removeSpatialEntity(beginIt, spatialEntityType);
                        } else {
                            beginIt++;
                        }
                    }
                }

                //! Evaluate the filter numeric measure considering the provided timepoint and spatial entity
                /*!
                 * \param filterNumericMeasure  The filter numeric measure
                 * \param timePoint             The considered timepoint
                 * \param spatialEntity         The considered spatial entity
                 */
                double evaluateFilterNumericMeasure(const FilterNumericMeasureAttributeType &filterNumericMeasure,
                                                    TimePoint &timePoint,
                                                    const SpatialEntity &spatialEntity) const {
                    return (
                        boost::apply_visitor(
                            FilterNumericVisitor(timePoint, spatialEntity, typeSemanticsTable),
                            filterNumericMeasure
                        )
                    );
                }

                //! Translate the given semantic type to an abstract natural number
                /*! The type semantics table is used to compute the natural number corresponding
                 *  to the semantic type.
                 *
                 * \param semanticType  The considered semantic type
                 */
                double translateSemanticTypeToAbstractNaturalNumber(const std::string &semanticType) const {
                    return (
                        static_cast<double>(
                            typeSemanticsTable.getTypeOfSemanticCriteriaValues(semanticType)
                        )
                    );
                }

        };

    };

};


#endif
