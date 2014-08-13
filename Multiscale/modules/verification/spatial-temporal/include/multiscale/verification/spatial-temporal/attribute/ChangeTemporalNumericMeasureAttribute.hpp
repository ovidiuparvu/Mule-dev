#ifndef CHANGETEMPORALNUMERICMEASUREATTRIBUTE_HPP
#define CHANGETEMPORALNUMERICMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ChangeMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a change temporal numeric measure attribute
        class ChangeTemporalNumericMeasureAttribute {

            public:

                ChangeMeasureAttribute         changeMeasure;       /*!< The change measure */
                NumericMeasureAttributeType    lhsNumericMeasure;   /*!< The left hand side numeric measure */
                ComparatorAttribute            comparator;          /*!< The comparator */
                NumericMeasureAttributeType    rhsNumericMeasure;   /*!< The right hand side numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ChangeTemporalNumericMeasureAttribute,
    (multiscale::verification::ChangeMeasureAttribute, changeMeasure)
    (multiscale::verification::NumericMeasureAttributeType, lhsNumericMeasure)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::NumericMeasureAttributeType, rhsNumericMeasure)
)


#endif
