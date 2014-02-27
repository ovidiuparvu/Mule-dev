#ifndef UNARYSUBSETATTRIBUTE_HPP
#define UNARYSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a unary subset attribute
        class UnarySubsetAttribute {

            public:

                UnarySubsetMeasureAttribute unarySubsetMeasure; /*!< The unary subset measure */
                SubsetAttributeType         subset;             /*!< The considered subset */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnarySubsetAttribute,
    (multiscale::verification::UnarySubsetMeasureAttribute, unarySubsetMeasure)
    (multiscale::verification::SubsetAttributeType, subset)
)

#endif
