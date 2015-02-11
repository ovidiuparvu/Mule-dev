#ifndef SPATIALMEASURECOLLECTIONATTRIBUTE_HPP
#define SPATIALMEASURECOLLECTIONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/PrimarySpatialMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class UnaryNumericSpatialAttribute;
        class BinaryNumericSpatialAttribute;


        // Variant for representing a spatial measure collection type
        typedef boost::variant<
            PrimarySpatialMeasureCollectionAttribute,
            boost::recursive_wrapper<UnaryNumericSpatialAttribute>,
            boost::recursive_wrapper<BinaryNumericSpatialAttribute>
        > SpatialMeasureCollectionType;


        //! Class used to represent a spatial measure collection
        class SpatialMeasureCollectionAttribute {

            public:

                SpatialMeasureCollectionType spatialMeasureCollection; /*!< The spatial measure collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SpatialMeasureCollectionAttribute,
    (multiscale::verification::SpatialMeasureCollectionType, spatialMeasureCollection)
)


#endif
