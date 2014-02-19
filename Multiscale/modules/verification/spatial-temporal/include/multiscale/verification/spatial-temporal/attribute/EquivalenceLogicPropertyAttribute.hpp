#ifndef EQUIVALENCELOGICPROPERTYATTRIBUTE_HPP
#define EQUIVALENCELOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "equivalence" logic property attribute
        class EquivalenceLogicPropertyAttribute {

            public:

                LogicPropertyAttributeType logicProperty;   /*!< The logical property following the "equivalence" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::EquivalenceLogicPropertyAttribute,
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)

#endif
