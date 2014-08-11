#ifndef EQUIVALENCECONSTRAINTATTRIBUTE_HPP
#define EQUIVALENCECONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "equivalence" constraint attribute
        class EquivalenceConstraintAttribute {

            public:

                ConstraintAttributeType constraint; /*!< The constraint following the "equivalence" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::EquivalenceConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)


#endif
