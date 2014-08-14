#ifndef TEMPORALNUMERICMEASUREATTRIBUTE_HPP
#define TEMPORALNUMERICMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericStatisticalMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class BinaryNumericTemporalAttribute;
        class TemporalNumericMeasureAttribute;
        class UnaryNumericTemporalAttribute;


        //! Variant for the temporal numeric measure attribute
        typedef boost::variant<
            double,
            NumericStateVariableAttribute,
            NumericStatisticalMeasureAttribute,
            boost::recursive_wrapper<UnaryNumericTemporalAttribute>,
            boost::recursive_wrapper<BinaryNumericTemporalAttribute>,
            boost::recursive_wrapper<TemporalNumericMeasureAttribute>
        > TemporalNumericMeasureType;


        //! Class for representing a temporal numeric measure attribute
        class TemporalNumericMeasureAttribute {

            public:

                TemporalNumericMeasureType temporalNumericMeasure;  /*!< The temporal numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TemporalNumericMeasureAttribute,
    (multiscale::verification::TemporalNumericMeasureType, temporalNumericMeasure)
)


#endif
