#ifndef FUTURELOGICPROPERTYATTRIBUTE_HPP
#define FUTURELOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "future" logic property attribute
        class FutureLogicPropertyAttribute {

            public:

                double                      startTimePoint; /*!< The considered start time point */
                double                      endTimePoint;   /*!< The considered end time point */
                LogicPropertyAttributeType  logicProperty;  /*!< The logic property following the "future" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::FutureLogicPropertyAttribute,
    (double, startTimePoint)
    (double, endTimePoint)
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)


#endif
