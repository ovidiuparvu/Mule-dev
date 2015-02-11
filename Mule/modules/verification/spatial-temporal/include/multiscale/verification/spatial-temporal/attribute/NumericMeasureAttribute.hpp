#ifndef NUMERICMEASUREATTRIBUTE_HPP
#define NUMERICMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class BinaryNumericNumericAttribute;
        class NumericMeasureAttribute;
        class NumericSpatialMeasureAttribute;
        class PrimaryNumericMeasureAttribute;
        class UnaryNumericNumericAttribute;


        //! Variant for the numeric measure attribute
        typedef boost::variant<
            double,
            NumericStateVariableAttribute,
            boost::recursive_wrapper<NumericSpatialMeasureAttribute>,
            boost::recursive_wrapper<PrimaryNumericMeasureAttribute>,
            boost::recursive_wrapper<UnaryNumericNumericAttribute>,
            boost::recursive_wrapper<BinaryNumericNumericAttribute>,
            boost::recursive_wrapper<NumericMeasureAttribute>
        > NumericMeasureType;


        //! Class for representing a numeric measure attribute
        class NumericMeasureAttribute {

            public:

                NumericMeasureType numericMeasure; /*!< The numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericMeasureAttribute,
    (multiscale::verification::NumericMeasureType, numericMeasure)
)


#endif
