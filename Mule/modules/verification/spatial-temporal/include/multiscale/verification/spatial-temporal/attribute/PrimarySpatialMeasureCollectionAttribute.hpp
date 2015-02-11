#ifndef PRIMARYSPATIALMEASURECOLLECTIONATTRIBUTE_HPP
#define PRIMARYSPATIALMEASURECOLLECTIONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class used to represent a primary spatial measure collection attribute
        class PrimarySpatialMeasureCollectionAttribute {

            public:

                SpatialMeasureAttribute spatialMeasure; /*!< The spatial measure */
                SubsetAttribute         subset;         /*!< The considered subset */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::PrimarySpatialMeasureCollectionAttribute,
    (multiscale::verification::SpatialMeasureAttribute, spatialMeasure)
    (multiscale::verification::SubsetAttribute, subset)
)


#endif
