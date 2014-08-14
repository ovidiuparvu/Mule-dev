#ifndef BINARYSTATISTICALNUMERICATTRIBUTE_HPP
#define BINARYSTATISTICALNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a binary statistical numeric attribute
        class BinaryStatisticalNumericAttribute {

            public:

                BinaryStatisticalMeasureAttribute
                    binaryStatisticalMeasure;       /*!< The binary statistical subset measure */
                NumericMeasureCollectionAttribute
                    firstNumericMeasureCollection;  /*!< The first considered numeric measure collection */
                NumericMeasureCollectionAttribute
                    secondNumericMeasureCollection; /*!< The second considered numeric measure collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryStatisticalNumericAttribute,
    (multiscale::verification::BinaryStatisticalMeasureAttribute, binaryStatisticalMeasure)
    (multiscale::verification::NumericMeasureCollectionAttribute, firstNumericMeasureCollection)
    (multiscale::verification::NumericMeasureCollectionAttribute, secondNumericMeasureCollection)
)


#endif
