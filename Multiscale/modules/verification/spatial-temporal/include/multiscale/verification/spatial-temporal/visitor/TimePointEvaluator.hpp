#ifndef TIMEPOINTEVALUATOR_HPP
#define TIMEPOINTEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/visitor/SpatialMeasureEvaluator.hpp"


namespace multiscale {

    namespace verification {

        //! Class used to evaluate time points
        class TimePointEvaluator {

            public:

                //! Return the spatial measure values for all considered spatial entities in the given time point
                /*!
                 * \param timePoint         The considered time point
                 * \param spatialMeasure    The considered spatial measure
                 */
                static std::vector<double> getSpatialMeasureValues(const TimePoint &timePoint,
                                                                   const SpatialMeasureType &spatialMeasure) {
                    std::vector<double> spatialMeasureValues;

                    std::vector<std::shared_ptr<SpatialEntity>> consideredSpatialEntities = timePoint.getConsideredSpatialEntities();

                    getSpatialMeasureValues(consideredSpatialEntities, spatialMeasureValues, spatialMeasure);

                    return spatialMeasureValues;
                }


            private:

                //! Return the spatial measure values for all considered spatial entities in the given time point
                /*!
                 * \param consideredSpatialEntities The considered spatial entities
                 * \param spatialMeasureValues      The collection of values for the given spatial measure
                 * \param spatialMeasure            The considered spatial measure
                 */
                static void getSpatialMeasureValues(const std::vector<std::shared_ptr<SpatialEntity>> &consideredSpatialEntities,
                                                    std::vector<double> &spatialMeasureValues,
                                                    const SpatialMeasureType &spatialMeasure) {
                    double spatialMeasureValue = 0;

                    for (const auto &spatialEntity : consideredSpatialEntities) {
                        spatialMeasureValue = SpatialMeasureEvaluator::evaluate(*spatialEntity, spatialMeasure);

                        spatialMeasureValues.push_back(spatialMeasureValue);
                    }
                }

        };

    };

};



#endif
