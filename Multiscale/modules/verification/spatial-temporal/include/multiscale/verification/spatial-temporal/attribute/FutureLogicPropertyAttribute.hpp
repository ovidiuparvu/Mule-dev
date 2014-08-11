#ifndef FUTURELOGICPROPERTYATTRIBUTE_HPP
#define FUTURELOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "future" logic property attribute
        class FutureLogicPropertyAttribute {

            public:

                unsigned long               startTimepoint; /*!< The considered start timepoint */
                unsigned long               endTimepoint;   /*!< The considered end timepoint */
                LogicPropertyAttributeType  logicProperty;  /*!< The logic property following the "future" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::FutureLogicPropertyAttribute,
    (unsigned long, startTimepoint)
    (unsigned long, endTimepoint)
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
