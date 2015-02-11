#ifndef NEXTKLOGICPROPERTYATTRIBUTE_HPP
#define NEXTKLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "next K" logic property attribute
        class NextKLogicPropertyAttribute {

            public:

                unsigned long               nrOfTimepointsAhead;    /*!< The number of timepoints ahead "K" */
                LogicPropertyAttributeType  logicProperty;          /*!< The logic property following the
                                                                         "next" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NextKLogicPropertyAttribute,
    (unsigned long, nrOfTimepointsAhead)
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
