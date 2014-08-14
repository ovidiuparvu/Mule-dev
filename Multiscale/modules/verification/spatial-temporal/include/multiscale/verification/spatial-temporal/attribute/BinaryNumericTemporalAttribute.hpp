#ifndef BINARYNUMERICTEMPORALATTRIBUTE_HPP
#define BINARYNUMERICTEMPORALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a binary numeric temporal measure attribute
        class BinaryNumericTemporalAttribute {

            public:

                BinaryNumericMeasureAttribute
                    binaryNumericMeasure;           /*!< The binary numeric measure */
                TemporalNumericMeasureType
                    firstTemporalNumericMeasure;    /*!< The first temporal numeric measure */
                TemporalNumericMeasureType
                    secondTemporalNumericMeasure;   /*!< The second temporal numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryNumericTemporalAttribute,
    (multiscale::verification::BinaryNumericMeasureAttribute, binaryNumericMeasure)
    (multiscale::verification::TemporalNumericMeasureType, firstTemporalNumericMeasure)
    (multiscale::verification::TemporalNumericMeasureType, secondTemporalNumericMeasure)
)


#endif
