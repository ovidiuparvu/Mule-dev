#ifndef CHANGETEMPORALNUMERICMEASUREATTRIBUTE_HPP
#define CHANGETEMPORALNUMERICMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ChangeMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a change temporal numeric measure attribute
        class ChangeTemporalNumericMeasureAttribute {

            public:

                ChangeMeasureAttribute
                    changeMeasure;              /*!< The change measure */
                TemporalNumericMeasureType
                    lhsTemporalNumericMeasure;  /*!< The left hand side temporal numeric measure */
                ComparatorAttribute
                    comparator;                 /*!< The comparator */
                TemporalNumericMeasureType
                    rhsTemporalNumericMeasure;  /*!< The right hand side temporal numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ChangeTemporalNumericMeasureAttribute,
    (multiscale::verification::ChangeMeasureAttribute, changeMeasure)
    (multiscale::verification::TemporalNumericMeasureType, lhsTemporalNumericMeasure)
    (multiscale::verification::ComparatorAttribute, comparator)
    (multiscale::verification::TemporalNumericMeasureType, rhsTemporalNumericMeasure)
)


#endif
