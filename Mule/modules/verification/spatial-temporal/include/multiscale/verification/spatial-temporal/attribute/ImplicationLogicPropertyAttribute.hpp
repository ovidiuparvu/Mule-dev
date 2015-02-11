#ifndef IMPLICATIONLOGICPROPERTYATTRIBUTE_HPP
#define IMPLICATIONLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "implication" logic property attribute
        class ImplicationLogicPropertyAttribute {

            public:

                LogicPropertyAttributeType logicProperty;   /*!< The logical property following the
                                                                 "implication" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ImplicationLogicPropertyAttribute,
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
