#ifndef GLOBALLOGICPROPERTYATTRIBUTE_HPP
#define GLOBALLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "globally" logic property attribute
        class GlobalLogicPropertyAttribute {

            public:

                unsigned long               startTimepoint; /*!< The considered start timepoint */
                unsigned long               endTimepoint;   /*!< The considered end timepoint */
                LogicPropertyAttributeType  logicProperty;  /*!< The logic property following the
                                                                 "globally" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::GlobalLogicPropertyAttribute,
    (unsigned long, startTimepoint)
    (unsigned long, endTimepoint)
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
