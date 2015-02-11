#ifndef UNARYNUMERICTEMPORALATTRIBUTE_HPP
#define UNARYNUMERICTEMPORALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a unary numeric temporal measure attribute
        class UnaryNumericTemporalAttribute {

            public:

                UnaryNumericMeasureAttribute
                    unaryNumericMeasure;    /*!< The unary numeric measure */
                TemporalNumericMeasureType
                    temporalNumericMeasure; /*!< The considered temporal numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericTemporalAttribute,
    (multiscale::verification::UnaryNumericMeasureAttribute, unaryNumericMeasure)
    (multiscale::verification::TemporalNumericMeasureType, temporalNumericMeasure)
)


#endif
