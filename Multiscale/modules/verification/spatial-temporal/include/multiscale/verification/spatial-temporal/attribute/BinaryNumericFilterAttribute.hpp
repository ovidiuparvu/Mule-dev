#ifndef BINARYNUMERICFILTERATTRIBUTE_HPP
#define BINARYNUMERICFILTERATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/FilterNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a binary numeric filter attribute
        class BinaryNumericFilterAttribute {

            public:

                BinaryNumericMeasureAttribute
                    binaryNumericMeasure;       /*!< The binary numeric measure */
                FilterNumericMeasureAttributeType
                    firstFilterNumericMeasure;  /*!< The first filter numeric measure */
                FilterNumericMeasureAttributeType
                    secondFilterNumericMeasure; /*!< The second filter numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericFilterAttribute,
    (multiscale::verification::BinaryNumericMeasureAttribute, binaryNumericMeasure)
    (multiscale::verification::FilterNumericMeasureAttributeType, firstFilterNumericMeasure)
    (multiscale::verification::FilterNumericMeasureAttributeType, secondFilterNumericMeasure)
)


#endif
