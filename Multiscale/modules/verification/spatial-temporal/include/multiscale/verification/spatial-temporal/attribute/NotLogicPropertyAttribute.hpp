#ifndef NOTLOGICPROPERTYATTRIBUTE_HPP
#define NOTLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "not" logic property attribute
        class NotLogicPropertyAttribute {

            public:

                LogicPropertyAttributeType logicProperty;    /*!< The logic property following the "not" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NotLogicPropertyAttribute,
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
