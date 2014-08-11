#ifndef PRIMARYNUMERICMEASUREATTRIBUTE_HPP
#define PRIMARYNUMERICMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class PrimaryNumericMeasureAttribute;
        class NumericSpatialMeasureAttribute;


        //! Variant for the primary numeric measure attribute
        typedef boost::variant<
            double,
            NumericStateVariableAttribute,
            boost::recursive_wrapper<NumericSpatialMeasureAttribute>,
            boost::recursive_wrapper<PrimaryNumericMeasureAttribute>
        > PrimaryNumericMeasureAttributeType;


        //! Class for representing a primary numeric measure attribute
        class PrimaryNumericMeasureAttribute {

            public:

                PrimaryNumericMeasureAttributeType primaryNumericMeasure; /*!< The primary numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::PrimaryNumericMeasureAttribute,
    (multiscale::verification::PrimaryNumericMeasureAttributeType, primaryNumericMeasure)
)


#endif
