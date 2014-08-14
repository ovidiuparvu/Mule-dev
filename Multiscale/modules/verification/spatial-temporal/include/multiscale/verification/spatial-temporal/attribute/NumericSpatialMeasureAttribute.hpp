#ifndef NUMERICSPATIALATTRIBUTE_HPP
#define NUMERICSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalQuantileSpatialAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalSpatialAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryStatisticalSpatialAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class NumericSpatialMeasureAttribute;


        //! Variant for a numeric spatial measure attribute
        typedef boost::variant<
            UnaryStatisticalSpatialAttribute,
            BinaryStatisticalSpatialAttribute,
            BinaryStatisticalQuantileSpatialAttribute,
            boost::recursive_wrapper<NumericSpatialMeasureAttribute>
        > NumericSpatialMeasureAttributeType;


        //! Class for representing a numeric spatial measure attribute
        class NumericSpatialMeasureAttribute {

            public:

                NumericSpatialMeasureAttributeType numericSpatialMeasure;  /*!< The numeric spatial measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericSpatialMeasureAttribute,
    (multiscale::verification::NumericSpatialMeasureAttributeType, numericSpatialMeasure)
)


#endif
