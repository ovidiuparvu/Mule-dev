#ifndef CONSTRAINTEVALUATOR_HPP
#define CONSTRAINTEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/TimePoint.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ComparatorEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/SpatialMeasureEvaluator.hpp"


namespace multiscale {

    namespace verification {

        //! Class for evaluating constraint expressions
        class ConstraintEvaluator {

            public:

                //! Filter the timepoint considering the given constraints
                /*!
                 * \param timePoint         The timepoint which will be filtered
                 * \param spatialMeasure    The type of the spatial measure
                 * \param comparator        The type of the comparator
                 * \param numericMeasure    The value of the numeric measure
                 */
                static void filter(TimePoint &timePoint, const SpatialMeasureType &spatialMeasure,
                                   const ComparatorType &comparator, double numericMeasure) {
                    ConsideredSpatialEntityType type = timePoint.getConsideredSpatialEntityType();

                    switch(type) {
                        case ConsideredSpatialEntityType::All:
                            filterClusters(timePoint, spatialMeasure, comparator, numericMeasure);
                            filterRegions(timePoint, spatialMeasure, comparator, numericMeasure);
                            break;

                        case ConsideredSpatialEntityType::Clusters:
                            filterClusters(timePoint, spatialMeasure, comparator, numericMeasure);
                            break;

                        case ConsideredSpatialEntityType::Regions:
                            filterRegions(timePoint, spatialMeasure, comparator, numericMeasure);
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }
                }

            private:

                //! Filter the clusters considering the given timepoint and constraints
                /*!
                 * \param timePoint         The timepoint which will be filtered
                 * \param spatialMeasure    The type of the spatial measure
                 * \param comparator        The type of the comparator
                 * \param numericMeasure    The value of the numeric measure
                 */
                static void filterClusters(TimePoint &timePoint, const SpatialMeasureType &spatialMeasure,
                                           const ComparatorType &comparator, double numericMeasure) {
                    double spatialMeasureValue = 0;

                    std::set<Cluster> clusters = timePoint.getClusters();
                    std::set<Cluster>::iterator clustersEndIterator = clusters.end();

                    for (std::set<Cluster>::iterator it = clusters.begin(); it != clustersEndIterator; it++) {
                        spatialMeasureValue = SpatialMeasureEvaluator::evaluate(*it, spatialMeasure);

                        if (!ComparatorEvaluator::evaluate(spatialMeasureValue, comparator, numericMeasure)) {
                            timePoint.removeCluster(it);
                        }
                    }
                }

                //! Filter the regions considering the given timepoint and constraints
                /*!
                 * \param timePoint         The timepoint which will be filtered
                 * \param spatialMeasure    The type of the spatial measure
                 * \param comparator        The type of the comparator
                 * \param numericMeasure    The value of the numeric measure
                 */
                static void filterRegions(TimePoint &timePoint, const SpatialMeasureType &spatialMeasure,
                                          const ComparatorType &comparator, double numericMeasure) {
                    double spatialMeasureValue = 0;

                    std::set<Region> regions = timePoint.getRegions();
                    std::set<Region>::iterator regionsEndIterator = regions.end();

                    for (std::set<Region>::iterator it = regions.begin(); it != regionsEndIterator; it++) {
                        spatialMeasureValue = SpatialMeasureEvaluator::evaluate(*it, spatialMeasure);

                        if (!ComparatorEvaluator::evaluate(spatialMeasureValue, comparator, numericMeasure)) {
                            timePoint.removeRegion(it);
                        }
                    }
                }

        };

    };

};

#endif
