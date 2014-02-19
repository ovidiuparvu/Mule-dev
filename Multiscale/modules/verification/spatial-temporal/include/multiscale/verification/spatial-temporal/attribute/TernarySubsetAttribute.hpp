#ifndef TERNARYSUBSETATTRIBUTE_HPP
#define TERNARYSUBSETATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/TernarySubsetMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a ternary subset attribute
        class TernarySubsetAttribute {

            public:

                TernarySubsetMeasureAttribute   ternarySubsetMeasure;   /*!< The ternary subset measure */
                SubsetAttributeType             subset;                 /*!< The considered subset */
                SpatialMeasureAttribute         spatialMeasure;         /*!< The considered spatial measure */
                double                          parameter;              /*!< The considered parameter */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TernarySubsetAttribute,
    (multiscale::verification::TernarySubsetMeasureAttribute, ternarySubsetMeasure)
    (multiscale::verification::SubsetAttributeType, subset)
    (multiscale::verification::SpatialMeasureAttribute, spatialMeasure)
    (double, parameter)
)

#endif
