#ifndef IMPLICATIONCONSTRAINTATTRIBUTE_HPP
#define IMPLICATIONCONSTRAINTATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "implication" constraint attribute
        class ImplicationConstraintAttribute {

            public:

                ConstraintAttributeType constraint; /*!< The constraint following the "implication" operator */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ImplicationConstraintAttribute,
    (multiscale::verification::ConstraintAttributeType, constraint)
)


#endif
