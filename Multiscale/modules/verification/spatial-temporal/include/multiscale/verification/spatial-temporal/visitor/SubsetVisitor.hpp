#ifndef SUBSETVISITOR_HPP
#define SUBSETVISITOR_HPP

#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Class used to evaluate subsets
        class SubsetVisitor : public boost::static_visitor<TimePoint> {

            private:

                TimePoint
                    &timePoint;                     /*!< The initial timepoint */
                const MultiscaleArchitectureGraph
                    &multiscaleArchitectureGraph;   /*!< The considered multiscale architecture graph */

            public:

                SubsetVisitor(TimePoint &timePoint, const MultiscaleArchitectureGraph &multiscaleArchitectureGraph)
                              : timePoint(timePoint), multiscaleArchitectureGraph(multiscaleArchitectureGraph) {}

                //! Overloading the "()" operator for the SubsetAttribute alternative
                /*!
                 * \param subset    The subset
                 */
                TimePoint operator() (const SubsetAttribute &subset) const {
                    return evaluate(subset.subset, timePoint);
                }

                //! Overloading the "()" operator for the SubsetSpecificAttribute alternative
                /*!
                 * \param subset    The specific subset
                 */
                TimePoint operator() (const SubsetSpecificAttribute &subset) const {
                    TimePoint subsetSpecificTimePoint(timePoint);

                    setTimePointConsideredSpatialEntityType(
                        subsetSpecificTimePoint,
                        subset.subsetSpecificType
                    );

                    return subsetSpecificTimePoint;
                }

                //! Overloading the "()" operator for the FilterSubsetAttribute alternative
                /*!
                 * \param subset    The filter subset
                 */
                TimePoint operator() (const FilterSubsetAttribute &subset) const {
                    TimePoint filterSubsetTimePoint(timePoint);

                    setTimePointConsideredSpatialEntityType(
                        filterSubsetTimePoint,
                        subset.subsetSpecific.subsetSpecificType
                    );

                    return (
                        filterTimePoint(
                            filterSubsetTimePoint,
                            subset.constraint
                        )
                    );
                }

                //! Overloading the "()" operator for the SubsetSubsetOperationAttribute alternative
                /*!
                 * \param subset    The subset subset operation attribute
                 */
                TimePoint operator() (const SubsetSubsetOperationAttribute &subset) const {
                    TimePoint firstSubsetTimePoint(evaluate(subset.firstSubset, timePoint));
                    TimePoint secondSubsetTimePoint(evaluate(subset.secondSubset, timePoint));

                    return (
                        evaluateSubsetOperation(
                            subset.subsetOperation.subsetOperationType,
                            firstSubsetTimePoint,
                            secondSubsetTimePoint
                        )
                    );
                }


            private:

                //! Evaluate the subset considering the given timepoint
                /*!
                 * \param subset    The subset
                 * \param timePoint The given timepoint
                 */
                TimePoint evaluate(const SubsetAttributeType &subset, TimePoint &timePoint) const {
                    return (
                        boost::apply_visitor(
                            SubsetVisitor(
                                timePoint,
                                multiscaleArchitectureGraph
                            ),
                            subset
                        )
                    );
                }

                //! Set the considered spatial entity type for the given timepoint using the specific subset type
                /*!
                 * \param timePoint     The given timepoint
                 * \param subsetType    The specific subset type
                 */
                void setTimePointConsideredSpatialEntityType(TimePoint &timePoint,
                                                             const SubsetSpecificType &subsetType) const {
                    timePoint.setConsideredSpatialEntityType(subsetType);
                }

                //! Filter the given timepoint considering the provided constraint
                /*!
                 * \param timePoint     The given timepoint
                 * \param constraint    The provided constraint
                 */
                TimePoint filterTimePoint(TimePoint &timePoint,
                                          const ConstraintAttributeType &constraint) const;

                //! Evaluate subsetOperation against the given subsets timepoints
                /*!
                 * \param subsetOperation       The considered subset operation
                 * \param firstSubsetTimePoint  The timepoint corresponding to the first subset
                 * \param secondSubsetTimePoint The timepoint corresponding to the second subset
                 */
                TimePoint evaluateSubsetOperation(const SubsetOperationType &subsetOperation,
                                                  const TimePoint &firstSubsetTimePoint,
                                                  const TimePoint &secondSubsetTimePoint) const {
                    TimePoint firstSubsetNonConstTimePoint(firstSubsetTimePoint);

                    switch(subsetOperation) {
                        case SubsetOperationType::Difference:
                            firstSubsetNonConstTimePoint.timePointDifference(secondSubsetTimePoint);
                            break;

                        case SubsetOperationType::Intersection:
                            firstSubsetNonConstTimePoint.timePointIntersection(secondSubsetTimePoint);
                            break;

                        case SubsetOperationType::Union:
                            firstSubsetNonConstTimePoint.timePointUnion(secondSubsetTimePoint);
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    return firstSubsetNonConstTimePoint;
                }

        };

    };

};


// Includes added after class declaration to avoid include circular dependency errors

#include "multiscale/verification/spatial-temporal/visitor/ConstraintVisitor.hpp"


// Methods which depend on the immediately above included classes

inline multiscale::verification::TimePoint
multiscale::verification::SubsetVisitor::filterTimePoint(TimePoint &timePoint,
                                                         const ConstraintAttributeType &constraint) const {
    return (
        boost::apply_visitor(
            ConstraintVisitor(
                timePoint,
                timePoint,
                multiscaleArchitectureGraph
            ),
            constraint
        )
    );
}


#endif
