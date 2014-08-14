#ifndef UNARYNUMERICNUMERICATTRIBUTE_HPP
#define UNARYNUMERICNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a unary numeric numeric measure attribute
        class UnaryNumericNumericAttribute {

            public:

                UnaryNumericMeasureAttribute    unaryNumericMeasure;    /*!< The unary numeric measure */
                NumericMeasureType              numericMeasure;         /*!< The considered numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericNumericAttribute,
    (multiscale::verification::UnaryNumericMeasureAttribute, unaryNumericMeasure)
    (multiscale::verification::NumericMeasureType, numericMeasure)
)


#endif
