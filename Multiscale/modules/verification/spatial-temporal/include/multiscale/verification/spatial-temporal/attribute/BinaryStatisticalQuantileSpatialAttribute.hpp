#ifndef BINARYSTATISTICALQUANTILESPATIALATTRIBUTE_HPP
#define BINARYSTATISTICALQUANTILESPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalQuantileMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a binary statistical quantile spatial attribute
        class BinaryStatisticalQuantileSpatialAttribute {

            public:

                BinaryStatisticalQuantileMeasureAttribute
                    binaryStatisticalQuantileMeasure;   /*!< The binary statistical quantile measure */
                SpatialMeasureCollectionAttribute
                    spatialMeasureCollection;           /*!< The considered spatial measure collection */
                double
                    parameter;                          /*!< The considered parameter */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryStatisticalQuantileSpatialAttribute,
    (multiscale::verification::BinaryStatisticalQuantileMeasureAttribute, binaryStatisticalQuantileMeasure)
    (multiscale::verification::SpatialMeasureCollectionAttribute, spatialMeasureCollection)
    (double, parameter)
)


#endif
