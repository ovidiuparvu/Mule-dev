#ifndef ANDCONSTRAINTATTRIBUTE_HPP
#define ANDCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "and" constraint attribute
        class AndConstraintAttribute {

        public:

            ConstraintAttributeType constraint; /*!< The constraint following the "and" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::AndConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)


#endif
