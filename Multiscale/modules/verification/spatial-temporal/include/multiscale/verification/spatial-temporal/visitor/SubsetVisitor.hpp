#ifndef SUBSETVISITOR_HPP
#define SUBSETVISITOR_HPP

#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Class used to evaluate subsets
        class SubsetVisitor : public boost::static_visitor<TimePoint> {

            private:

                TimePoint timePoint;    /*!< The initial timepoint */

            public:

                SubsetVisitor(const TimePoint &timePoint) {
                    this->timePoint = timePoint;
                }

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

                    setTimePointConsideredSpatialEntityType(subsetSpecificTimePoint, subset.subsetSpecificType);

                    return subsetSpecificTimePoint;
                }

                //! Overloading the "()" operator for the FilterSubsetAttribute alternative
                /*!
                 * \param subset    The filter subset
                 */
                TimePoint operator() (const FilterSubsetAttribute &subset) const {
                    TimePoint subsetSpecificTimePoint(timePoint);

                    setTimePointConsideredSpatialEntityType(subsetSpecificTimePoint,
                                                            subset.subsetSpecific.subsetSpecificType);

                    return filterTimePoint(subsetSpecificTimePoint, subset.constraint);
                }


            private:

                //! Evaluate the subset considering the given timepoint
                /*!
                 * \param subset    The subset
                 * \param timePoint The given timepoint
                 */
                TimePoint evaluate(const SubsetAttributeType &subset, const TimePoint &timePoint) const {
                    return boost::apply_visitor(SubsetVisitor(timePoint), subset);
                }

                //! Set the considered spatial entity type for the given timepoint using the specific subset type
                /*!
                 * \param timePoint     The given timepoint
                 * \param subsetType    The specific subset type
                 */
                void setTimePointConsideredSpatialEntityType(TimePoint &timePoint,
                                                             const SubsetSpecificType &subsetType) const {
                    switch(subsetType) {
                        case SubsetSpecificType::Clusters:
                            timePoint.setConsideredSpatialEntityType(ConsideredSpatialEntityType::Clusters);
                            break;

                        case SubsetSpecificType::Regions:
                            timePoint.setConsideredSpatialEntityType(ConsideredSpatialEntityType::Regions);
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }
                }

                //! Filter the given timepoint considering the provided constraint
                /*!
                 * \param timePoint     The given timepoint
                 * \param constraint    The provided constraint
                 */
                TimePoint filterTimePoint(const TimePoint &timePoint, const ConstraintAttributeType &constraint) const {
                    return boost::apply_visitor(ConstraintVisitor(timePoint, timePoint), constraint);
                }

        };

    };

};

#endif
