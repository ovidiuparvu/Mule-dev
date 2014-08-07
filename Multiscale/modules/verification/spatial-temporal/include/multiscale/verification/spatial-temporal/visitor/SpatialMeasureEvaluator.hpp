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
                    spatialmeasure::validateSpatialMeasureType(type);

                    return spatialEntity.getSpatialMeasureValue(type);
                }

        };

    };

};


#endif
