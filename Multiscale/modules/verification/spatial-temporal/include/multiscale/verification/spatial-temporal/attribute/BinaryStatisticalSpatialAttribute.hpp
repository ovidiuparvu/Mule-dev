#ifndef BINARYSTATISTICALSPATIALATTRIBUTE_HPP
#define BINARYSTATISTICALSPATIALATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a binary statistical spatial attribute
        class BinaryStatisticalSpatialAttribute {

            public:

                BinaryStatisticalMeasureAttribute
                    binaryStatisticalMeasure;       /*!< The binary statistical subset measure */
                SpatialMeasureCollectionAttribute
                    firstSpatialMeasureCollection;  /*!< The first considered spatial measure collection */
                SpatialMeasureCollectionAttribute
                    secondSpatialMeasureCollection; /*!< The second considered spatial measure collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryStatisticalSpatialAttribute,
    (multiscale::verification::BinaryStatisticalMeasureAttribute, binaryStatisticalMeasure)
    (multiscale::verification::SpatialMeasureCollectionAttribute, firstSpatialMeasureCollection)
    (multiscale::verification::SpatialMeasureCollectionAttribute, secondSpatialMeasureCollection)
)


#endif
