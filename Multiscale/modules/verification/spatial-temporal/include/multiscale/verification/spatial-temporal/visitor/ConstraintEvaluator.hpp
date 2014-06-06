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

                //! Filter the timepoint considering the given constraints
                /*!
                 * \param timePoint             The timepoint which will be filtered
                 * \param spatialMeasure        The type of the spatial measure
                 * \param comparator            The type of the comparator
                 * \param filterNumericMeasure  The filter numeric measure
                 */
                static void filter(TimePoint &timePoint,
                                   const SpatialMeasureType &spatialMeasure,
                                   const ComparatorType &comparator,
                                   const FilterNumericMeasureAttributeType &filterNumericMeasure) {
                    ConsideredSpatialEntityType type = timePoint.getConsideredSpatialEntityType();

                    switch(type) {
                        case ConsideredSpatialEntityType::All:
                            filterClusters(timePoint, spatialMeasure, comparator, filterNumericMeasure);
                            filterRegions(timePoint, spatialMeasure, comparator, filterNumericMeasure);
                            break;

                        case ConsideredSpatialEntityType::Clusters:
                            filterClusters(timePoint, spatialMeasure, comparator, filterNumericMeasure);
                            break;

                        case ConsideredSpatialEntityType::Regions:
                            filterRegions(timePoint, spatialMeasure, comparator, filterNumericMeasure);
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }
                }

            private:

                //! Filter the clusters considering the given timepoint and constraints
                /*!
                 * \param timePoint             The timepoint which will be filtered
                 * \param spatialMeasure        The type of the spatial measure
                 * \param comparator            The type of the comparator
                 * \param filterNumericMeasure  The filter numeric measure
                 */
                static void filterClusters(TimePoint &timePoint,
                                           const SpatialMeasureType &spatialMeasure,
                                           const ComparatorType &comparator,
                                           const FilterNumericMeasureAttributeType &filterNumericMeasure) {
                    double spatialMeasureValue          = 0;
                    double filterNumericMeasureValue    = 0;

                    auto it = timePoint.getClustersBeginIterator();

                    while (it != timePoint.getClustersEndIterator()) {
                        spatialMeasureValue         = SpatialMeasureEvaluator::evaluate(*it, spatialMeasure);
                        filterNumericMeasureValue   = evaluate(filterNumericMeasure, timePoint, *it);

                        if (!ComparatorEvaluator::evaluate(spatialMeasureValue, comparator, filterNumericMeasureValue)) {
                            timePoint.removeSpatialEntity(it);
                        } else {
                            it++;
                        }
                    }
                }

                //! Filter the regions considering the given timepoint and constraints
                /*!
                 * \param timePoint             The timepoint which will be filtered
                 * \param spatialMeasure        The type of the spatial measure
                 * \param comparator            The type of the comparator
                 * \param filterNumericMeasure  The filter numeric measure
                 */
                static void filterRegions(TimePoint &timePoint,
                                          const SpatialMeasureType &spatialMeasure,
                                          const ComparatorType &comparator,
                                          const FilterNumericMeasureAttributeType &filterNumericMeasure) {
                    double spatialMeasureValue          = 0;
                    double filterNumericMeasureValue    = 0;

                    auto it = timePoint.getRegionsBeginIterator();

                    while (it != timePoint.getRegionsEndIterator()) {
                        spatialMeasureValue         = SpatialMeasureEvaluator::evaluate(*it, spatialMeasure);
                        filterNumericMeasureValue   = evaluate(filterNumericMeasure, timePoint, *it);

                        if (!ComparatorEvaluator::evaluate(spatialMeasureValue, comparator, filterNumericMeasureValue)) {
                            timePoint.removeSpatialEntity(it);
                        } else {
                            it++;
                        }
                    }
                }

                //! Evaluate the filter numeric measure considering the provided timepoint and spatial entity
                /*!
                 * \param filterNumericMeasure  The filter numeric measure
                 * \param timePoint             The considered timepoint
                 * \param spatialEntity         The considered spatial entity
                 */
                static double evaluate(const FilterNumericMeasureAttributeType &filterNumericMeasure,
                                       const TimePoint &timePoint, const SpatialEntity &spatialEntity) {
                    return boost::apply_visitor(FilterNumericVisitor(timePoint, spatialEntity), filterNumericMeasure);
                }

        };

    };

};

#endif
