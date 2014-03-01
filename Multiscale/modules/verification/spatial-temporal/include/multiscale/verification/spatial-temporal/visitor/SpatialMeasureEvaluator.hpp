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
                            break;

                        case SpatialMeasureType::Density:
                            return spatialEntity.getDensity();
                            break;

                        case SpatialMeasureType::Area:
                            return spatialEntity.getArea();
                            break;

                        case SpatialMeasureType::Perimeter:
                            return spatialEntity.getPerimeter();
                            break;

                        case SpatialMeasureType::DistanceFromOrigin:
                            return spatialEntity.getDistanceFromOrigin();
                            break;

                        case SpatialMeasureType::Angle:
                            return spatialEntity.getAngle();
                            break;

                        case SpatialMeasureType::TriangleMeasure:
                            return spatialEntity.getTriangleMeasure();
                            break;

                        case SpatialMeasureType::RectangleMeasure:
                            return spatialEntity.getRectangleMeasure();
                            break;

                        case SpatialMeasureType::CircleMeasure:
                            return spatialEntity.getCircleMeasure();
                            break;

                        case SpatialMeasureType::CentroidX:
                            return spatialEntity.getCentroidX();
                            break;

                        case SpatialMeasureType::CentroidY:
                            return spatialEntity.getCentroidY();
                            break;
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

        };

    };

};

#endif
