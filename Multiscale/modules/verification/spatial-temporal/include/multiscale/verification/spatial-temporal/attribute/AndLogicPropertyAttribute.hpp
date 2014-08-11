#ifndef ANDLOGICPROPERTYATTRIBUTE_HPP
#define ANDLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "and" logic property attribute
        class AndLogicPropertyAttribute {

            public:

                LogicPropertyAttributeType logicProperty;   /*!< The logical property following the "and" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::AndLogicPropertyAttribute,
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
