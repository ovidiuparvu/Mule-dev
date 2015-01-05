#ifndef BINARYNUMERICSPATIALATTRIBUTE_HPP
#define BINARYNUMERICSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureCollectionAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a binary numeric spatial measure collection attribute
        class BinaryNumericSpatialAttribute {

            public:

                BinaryNumericMeasureAttribute       binaryNumericMeasure;           /*!< The binary numeric measure */
                SpatialMeasureCollectionAttribute   firstSpatialMeasureCollection;  /*!< The first considered spatial
                                                                                         measure collection */
                SpatialMeasureCollectionAttribute   secondSpatialMeasureCollection; /*!< The second considered spatial
                                                                                         measure collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericSpatialAttribute,
    (multiscale::verification::BinaryNumericMeasureAttribute, binaryNumericMeasure)
    (multiscale::verification::SpatialMeasureCollectionAttribute, firstSpatialMeasureCollection)
    (multiscale::verification::SpatialMeasureCollectionAttribute, secondSpatialMeasureCollection)
)


#endif
