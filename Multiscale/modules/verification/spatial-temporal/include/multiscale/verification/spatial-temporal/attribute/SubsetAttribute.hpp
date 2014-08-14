#ifndef SUBSETATTRIBUTE_HPP
#define SUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/FilterSubsetAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class SubsetAttribute;
        class SubsetSubsetOperationAttribute;


        //! Variant for a subset attribute
        typedef boost::variant<
            SubsetSpecificAttribute,
            FilterSubsetAttribute,
            boost::recursive_wrapper<SubsetSubsetOperationAttribute>,
            boost::recursive_wrapper<SubsetAttribute>
        > SubsetAttributeType;


        //! Class for representing a subset attribute
        class SubsetAttribute {

            public:

                SubsetAttributeType subset; /*!< The considered subset */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SubsetAttribute,
    (multiscale::verification::SubsetAttributeType, subset)
)


#endif
