#ifndef NUMERICMEASUREATTRIBUTE_HPP
#define NUMERICMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class BinaryNumericNumericAttribute;
        class NumericMeasureAttribute;
        class NumericSpatialAttribute;
        class UnaryNumericNumericAttribute;


        //! Variant for the numeric measure attribute
        typedef boost::variant<
            double,
            multiscale::verification::NumericStateVariableAttribute,
            boost::recursive_wrapper<multiscale::verification::NumericSpatialAttribute>,
            boost::recursive_wrapper<multiscale::verification::UnaryNumericNumericAttribute>,
            boost::recursive_wrapper<multiscale::verification::BinaryNumericNumericAttribute>,
            boost::recursive_wrapper<multiscale::verification::NumericMeasureAttribute>
        > NumericMeasureAttributeType;


        //! Class for representing a numeric measure attribute
        class NumericMeasureAttribute {

            public:

                NumericMeasureAttributeType numericMeasure; /*!< The numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericMeasureAttribute,
    (multiscale::verification::NumericMeasureAttributeType, numericMeasure)
)

#endif
