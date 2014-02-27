#ifndef BINARYSUBSETATTRIBUTE_HPP
#define BINARYSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a binary subset attribute
        class BinarySubsetAttribute {

            public:

                BinarySubsetMeasureAttribute    binarySubsetMeasure;    /*!< The binary subset measure */
                SubsetAttributeType             subset;                 /*!< The considered subset */
                SpatialMeasureAttribute         spatialMeasure;         /*!< The considered spatial measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinarySubsetAttribute,
    (multiscale::verification::BinarySubsetMeasureAttribute, binarySubsetMeasure)
    (multiscale::verification::SubsetAttributeType, subset)
    (multiscale::verification::SpatialMeasureAttribute, spatialMeasure)
)

#endif
