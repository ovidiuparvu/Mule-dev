#ifndef ORLOGICPROPERTYATTRIBUTE_HPP
#define ORLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "or" logic property attribute
        class OrLogicPropertyAttribute {

            public:

                LogicPropertyAttributeType logicProperty;    /*!< The logical property following the "or" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::OrLogicPropertyAttribute,
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
