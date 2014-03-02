#ifndef SPATIALENTITYEVALUATOR_HPP
#define SPATIALENTITYEVALUATOR_HPP

namespace multiscale {

    namespace verification {

        //! Class used to evaluate spatial entities
        class SpatialEntityEvaluator {

            public:

                //! Evaluate the numeric spatial measure for the given spatial entity
                /*!
                 * \param spatialEntity     The spatial entity
                 * \param spatialMeasure    The considered spatial measure
                 */
                static double evaluate(const SpatialEntity &spatialEntity, const SpatialMeasureType &spatialMeasure) {
                    switch(spatialMeasure) {
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
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

        };

    };

};



#endif
