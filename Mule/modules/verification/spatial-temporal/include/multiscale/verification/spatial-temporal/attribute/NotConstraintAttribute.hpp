#ifndef NOTCONSTRAINTATTRIBUTE_HPP
#define NOTCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "not" constraint attribute
        class NotConstraintAttribute {

            public:

                ConstraintAttributeType constraint;    /*!< The constraint which will be negated */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NotConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)


#endif
