#ifndef NEXTLOGICPROPERTYATTRIBUTE_HPP
#define NEXTLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "next" logic property attribute
        class NextLogicPropertyAttribute {

            public:

                LogicPropertyAttributeType logicProperty;   /*!< The logic property attribute following the
                                                                 "next" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NextLogicPropertyAttribute,
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
