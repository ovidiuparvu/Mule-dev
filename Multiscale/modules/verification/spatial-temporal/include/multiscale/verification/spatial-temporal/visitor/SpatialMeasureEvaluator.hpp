#ifndef SPATIALMEASUREEVALUATOR_HPP
#define SPATIALMEASUREEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialEntity.hpp"


namespace multiscale {

    namespace verification {

        //! Class for evaluating spatial measures
        class SpatialMeasureEvaluator {

            public:

                //! Return the value of the spatial measure for the given spatial entity
                /*!
                 * \param spatialEntity The given spatial entity
                 * \param type          The type of the spatial measure
                 */
                static double evaluate(const SpatialEntity &spatialEntity, const SpatialMeasureType &type) {
                    switch(type) {
                        case SpatialMeasureType::Clusteredness:
                            return spatialEntity.getClusteredness();

                        case SpatialMeasureType::Density:
                            return spatialEntity.getDensity();

                        case SpatialMeasureType::Area:
                            return spatialEntity.getArea();

                        case SpatialMeasureType::Perimeter:
                            return spatialEntity.getPerimeter();

                        case SpatialMeasureType::DistanceFromOrigin:
                            return spatialEntity.getDistanceFromOrigin();

                        case SpatialMeasureType::Angle:
                            return spatialEntity.getAngle();

                        case SpatialMeasureType::TriangleMeasure:
                            return spatialEntity.getTriangleMeasure();

                        case SpatialMeasureType::RectangleMeasure:
                            return spatialEntity.getRectangleMeasure();

                        case SpatialMeasureType::CircleMeasure:
                            return spatialEntity.getCircleMeasure();

                        case SpatialMeasureType::CentroidX:
                            return spatialEntity.getCentroidX();

                        case SpatialMeasureType::CentroidY:
                            return spatialEntity.getCentroidY();

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

        };

    };

};

#endif
