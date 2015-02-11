#ifndef SUBSETSUBSETOPERATIONATTRIBUTE_HPP
#define SUBSETSUBSETOPERATIONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetOperationAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a subset subset operation attribute
        class SubsetSubsetOperationAttribute {

            public:

                SubsetOperationAttribute    subsetOperation;    /*!< The employed subset operation */
                SubsetAttributeType         firstSubset;        /*!< The first considered subset */
                SubsetAttributeType         secondSubset;       /*!< The second considered subset */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SubsetSubsetOperationAttribute,
    (multiscale::verification::SubsetOperationAttribute, subsetOperation)
    (multiscale::verification::SubsetAttributeType, firstSubset)
    (multiscale::verification::SubsetAttributeType, secondSubset)
)


#endif
