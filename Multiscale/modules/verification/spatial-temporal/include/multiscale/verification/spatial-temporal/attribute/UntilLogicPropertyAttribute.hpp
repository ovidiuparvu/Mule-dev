#ifndef UNTILLOGICPROPERTYATTRIBUTE_HPP
#define UNTILLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "until" logic property attribute
        class UntilLogicPropertyAttribute {

            public:

                double                      startTimePoint; /*!< The considered start time point */
                double                      endTimePoint;   /*!< The considered end time point */
                LogicPropertyAttributeType  logicProperty;  /*!< The logic property following the "until" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UntilLogicPropertyAttribute,
    (double, startTimePoint)
    (double, endTimePoint)
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
