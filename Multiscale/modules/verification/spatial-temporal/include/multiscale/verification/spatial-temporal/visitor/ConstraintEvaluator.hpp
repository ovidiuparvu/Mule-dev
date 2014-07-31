#ifndef CONSTRAINTEVALUATOR_HPP
#define CONSTRAINTEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ComparatorEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/FilterNumericVisitor.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SpatialMeasureEvaluator.hpp"


namespace multiscale {

    namespace verification {

        //! Class for evaluating constraint expressions
        class ConstraintEvaluator {

            public:

                //! Filter the timepoint's spatial entities considering the given spatial measure constraint
                /*!
                 * All considered spatial entities which fail to meet the constraints
                 * will be removed from the given timepoint.
                 *
                 * \param timePoint             The timepoint storing the collection of spatial entities which will be filtered
                 * \param spatialMeasure        The type of the spatial measure
                 * \param comparator            The type of the comparator
                 * \param filterNumericMeasure  The filter numeric measure
                 */
                static void evalSpatialMeasureConstraint(TimePoint &timePoint,
                                                         const SpatialMeasureType &spatialMeasure,
                                                         const ComparatorType &comparator,
                                                         const FilterNumericMeasureAttributeType &filterNumericMeasure) {
                    std::bitset<NR_SUBSET_SPECIFIC_TYPES> consideredSpatialEntityTypes = timePoint.getConsideredSpatialEntityTypes();

                    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
                        if (consideredSpatialEntityTypes[i] == true) {
                            SubsetSpecificType subsetSpecificType = subsetspecific::computeSubsetSpecificType(i);

                            filterSpatialEntitiesWrtSpatialMeasure(timePoint, subsetSpecificType, spatialMeasure,
                                                                   comparator, filterNumericMeasure);
                        }
                    }
                }

                //! Filter the timepoint's spatial entities considering the type of each spatial entity
                /*!
                 * \param timePoint             The timepoint storing the collection of spatial entities which will be filtered
                 * \param comparator            The type of the comparator
                 * \param filterNumericMeasure  The filter numeric measure
                 */
                static void evalTypeConstraint(TimePoint &timePoint,
                                               const ComparatorType &comparator,
                                               const FilterNumericMeasureAttributeType &filterNumericMeasure) {
                    std::bitset<NR_SUBSET_SPECIFIC_TYPES> consideredSpatialEntityTypes = timePoint.getConsideredSpatialEntityTypes();

                    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
                        if (consideredSpatialEntityTypes[i] == true) {
                            SubsetSpecificType subsetSpecificType = subsetspecific::computeSubsetSpecificType(i);

                            filterSpatialEntitiesWrtType(timePoint, subsetSpecificType, comparator,
                                                         filterNumericMeasure);
                        }
                    }
                }

            private:

                //! Remove from the timepoint the spatial entities which fail to meet the spatial measure constraint
                /*!
                 * \param timePoint             The timepoint which will be filtered
                 * \param spatialEntityType     The considered spatial entity type
                 * \param spatialMeasure        The type of the spatial measure
                 * \param comparator            The type of the comparator
                 * \param filterNumericMeasure  The filter numeric measure
                 */
                static void filterSpatialEntitiesWrtSpatialMeasure(TimePoint &timePoint,
                                                                   const SubsetSpecificType &spatialEntityType,
                                                                   const SpatialMeasureType &spatialMeasure,
                                                                   const ComparatorType &comparator,
                                                                   const FilterNumericMeasureAttributeType &filterNumericMeasure) {
                    std::list<std::shared_ptr<SpatialEntity>>::iterator beginIt = timePoint.getSpatialEntitiesBeginIterator(spatialEntityType);
                    std::list<std::shared_ptr<SpatialEntity>>::iterator endIt   = timePoint.getSpatialEntitiesEndIterator(spatialEntityType);

                    while (beginIt != endIt) {
                        double spatialMeasureValue          = SpatialMeasureEvaluator::evaluate(*(*beginIt), spatialMeasure);
                        double filterNumericMeasureValue    = evalFilterNumericMeasure(filterNumericMeasure, timePoint, *(*beginIt));

                        if (!ComparatorEvaluator::evaluate(spatialMeasureValue, comparator, filterNumericMeasureValue)) {
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
                 * \param filterNumericMeasure  The filter numeric measure
                 */
                static void filterSpatialEntitiesWrtType(TimePoint &timePoint,
                                                         const SubsetSpecificType &spatialEntityType,
                                                         const ComparatorType &comparator,
                                                         const FilterNumericMeasureAttributeType &filterNumericMeasure) {
                    std::list<std::shared_ptr<SpatialEntity>>::iterator beginIt = timePoint.getSpatialEntitiesBeginIterator(spatialEntityType);
                    std::list<std::shared_ptr<SpatialEntity>>::iterator endIt   = timePoint.getSpatialEntitiesEndIterator(spatialEntityType);

                    while (beginIt != endIt) {
                        double typeValue                    = static_cast<double>((*beginIt)->getType());
                        double filterNumericMeasureValue    = evalFilterNumericMeasure(filterNumericMeasure, timePoint, *(*beginIt));

                        if (!ComparatorEvaluator::evaluate(typeValue, comparator, filterNumericMeasureValue)) {
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
                static double evalFilterNumericMeasure(const FilterNumericMeasureAttributeType &filterNumericMeasure,
                                                       const TimePoint &timePoint, const SpatialEntity &spatialEntity) {
                    return boost::apply_visitor(FilterNumericVisitor(timePoint, spatialEntity), filterNumericMeasure);
                }

        };

    };

};

#endif
