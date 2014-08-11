#ifndef FILTERSUBSETATTRIBUTE_HPP
#define FILTERSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ConstraintAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a filter subset attribute
        class FilterSubsetAttribute {

            public:

                SubsetSpecificAttribute     subsetSpecific;    /*!< The specific subset to consider */
                ConstraintAttributeType     constraint;        /*!< The constraint */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::FilterSubsetAttribute,
    (multiscale::verification::SubsetSpecificAttribute, subsetSpecific)
    (multiscale::verification::ConstraintAttributeType, constraint)
)


#endif
