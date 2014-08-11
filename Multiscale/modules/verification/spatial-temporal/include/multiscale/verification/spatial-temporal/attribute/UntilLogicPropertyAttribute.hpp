#ifndef UNTILLOGICPROPERTYATTRIBUTE_HPP
#define UNTILLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "until" logic property attribute
        class UntilLogicPropertyAttribute {

            public:

                unsigned long               startTimepoint; /*!< The considered start timepoint */
                unsigned long               endTimepoint;   /*!< The considered end timepoint */
                LogicPropertyAttributeType  logicProperty;  /*!< The logic property following the "until" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UntilLogicPropertyAttribute,
    (unsigned long, startTimepoint)
    (unsigned long, endTimepoint)
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
