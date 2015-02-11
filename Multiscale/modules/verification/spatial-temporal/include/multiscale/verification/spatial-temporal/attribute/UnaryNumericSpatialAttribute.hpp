#ifndef UNARYNUMERICSPATIALATTRIBUTE_HPP
#define UNARYNUMERICSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureCollectionAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a unary numeric spatial measure collection attribute
        class UnaryNumericSpatialAttribute {

            public:

                UnaryNumericMeasureAttribute        unaryNumericMeasure;        /*!< The unary numeric measure */
                SpatialMeasureCollectionAttribute   spatialMeasureCollection;   /*!< The considered spatial measure
                                                                                     collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericSpatialAttribute,
    (multiscale::verification::UnaryNumericMeasureAttribute, unaryNumericMeasure)
    (multiscale::verification::SpatialMeasureCollectionAttribute, spatialMeasureCollection)
)


#endif
