#ifndef UNARYSTATISTICALSPATIALATTRIBUTE_HPP
#define UNARYSTATISTICALSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnaryStatisticalMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a unary statistical spatial attribute
        class UnaryStatisticalSpatialAttribute {

            public:

                UnaryStatisticalMeasureAttribute  unaryStatisticalMeasure;   /*!< The unary statistical measure */
                SpatialMeasureCollectionAttribute spatialMeasureCollection;  /*!< The considered spatial measure
                                                                                  collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryStatisticalSpatialAttribute,
    (multiscale::verification::UnaryStatisticalMeasureAttribute, unaryStatisticalMeasure)
    (multiscale::verification::SpatialMeasureCollectionAttribute, spatialMeasureCollection)
)


#endif
