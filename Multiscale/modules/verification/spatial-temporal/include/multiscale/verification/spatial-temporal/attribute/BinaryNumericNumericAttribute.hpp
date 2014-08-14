#ifndef BINARYNUMERICNUMERICATTRIBUTE_HPP
#define BINARYNUMERICNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a binary numeric numeric measure attribute
        class BinaryNumericNumericAttribute {

            public:

                BinaryNumericMeasureAttribute   binaryNumericMeasure;   /*!< The binary numeric measure */
                NumericMeasureType              firstNumericMeasure;    /*!< The first numeric measure */
                NumericMeasureType              secondNumericMeasure;   /*!< The second numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericNumericAttribute,
    (multiscale::verification::BinaryNumericMeasureAttribute, binaryNumericMeasure)
    (multiscale::verification::NumericMeasureType, firstNumericMeasure)
    (multiscale::verification::NumericMeasureType, secondNumericMeasure)
)


#endif
