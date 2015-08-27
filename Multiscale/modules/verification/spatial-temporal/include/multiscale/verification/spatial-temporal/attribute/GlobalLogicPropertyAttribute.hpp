#ifndef GLOBALLOGICPROPERTYATTRIBUTE_HPP
#define GLOBALLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "globally" logic property attribute
        class GlobalLogicPropertyAttribute {

            public:

                double                      startTimePoint; /*!< The considered start time point */
                double                      endTimePoint;   /*!< The considered end time point */
                LogicPropertyAttributeType  logicProperty;  /*!< The logic property following the
                                                                 "globally" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::GlobalLogicPropertyAttribute,
    (double, startTimePoint)
    (double, endTimePoint)
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
