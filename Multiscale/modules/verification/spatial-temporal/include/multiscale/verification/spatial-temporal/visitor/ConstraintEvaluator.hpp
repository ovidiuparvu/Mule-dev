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
                            filterSpatialEntities<Cluster>(timePoint, spatialMeasure, comparator, filterNumericMeasure);
                            filterSpatialEntities<Region>(timePoint, spatialMeasure, comparator, filterNumericMeasure);
                            break;

                        case ConsideredSpatialEntityType::Clusters:
                            filterSpatialEntities<Cluster>(timePoint, spatialMeasure, comparator, filterNumericMeasure);
                            break;

                        case ConsideredSpatialEntityType::Regions:
                            filterSpatialEntities<Region>(timePoint, spatialMeasure, comparator, filterNumericMeasure);
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
                template <typename T>
                static void filterSpatialEntities(TimePoint &timePoint,
                                                  const SpatialMeasureType &spatialMeasure,
                                                  const ComparatorType &comparator,
                                                  const FilterNumericMeasureAttributeType &filterNumericMeasure) {
                    typename std::list<T>::iterator beginIt;
                    typename std::list<T>::iterator endIt;

                    getBeginIterator(timePoint, beginIt);
                    getEndIterator(timePoint, endIt);

                    while (beginIt != endIt) {
                        double spatialMeasureValue         = SpatialMeasureEvaluator::evaluate(*beginIt, spatialMeasure);
                        double filterNumericMeasureValue   = evaluate(filterNumericMeasure, timePoint, *beginIt);

                        if (!ComparatorEvaluator::evaluate(spatialMeasureValue, comparator, filterNumericMeasureValue)) {
                            timePoint.removeSpatialEntity(beginIt);
                        } else {
                            beginIt++;
                        }
                    }
                }

                //! Get the clusters begin iterator
                /*!
                 * \param timePoint     The considered timepoint
                 * \param beginIterator The iterator pointing at the beginning of the clusters collection
                 */
                static void getBeginIterator(TimePoint &timePoint, std::list<Cluster>::iterator &beginIterator) {
                    beginIterator = timePoint.getClustersBeginIterator();
                }

                //! Get the regions begin iterator
                /*!
                 * \param timePoint     The considered timepoint
                 * \param beginIterator The iterator pointing at the beginning of the regions collection
                 */
                static void getBeginIterator(TimePoint &timePoint, std::list<Region>::iterator &beginIterator) {
                    beginIterator = timePoint.getRegionsBeginIterator();
                }

                //! Get the clusters end iterator
                /*!
                 * \param timePoint     The considered timepoint
                 * \param endIterator   The iterator pointing at the end of the clusters collection
                 */
                static void getEndIterator(TimePoint &timePoint, std::list<Cluster>::iterator &endIterator) {
                    endIterator = timePoint.getClustersEndIterator();
                }

                //! Get the regions end iterator
                /*!
                 * \param timePoint     The considered timepoint
                 * \param endIterator   The iterator pointing at the end of the regions collection
                 */
                static void getEndIterator(TimePoint &timePoint, std::list<Region>::iterator &endIterator) {
                    endIterator = timePoint.getRegionsEndIterator();
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
