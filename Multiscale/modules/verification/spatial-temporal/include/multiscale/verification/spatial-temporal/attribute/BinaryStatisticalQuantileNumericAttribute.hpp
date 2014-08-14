#ifndef BINARYSTATISTICALQUANTILENUMERICATTRIBUTE_HPP
#define BINARYSTATISTICALQUANTILENUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalQuantileMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a binary statistical quantile numeric attribute
        class BinaryStatisticalQuantileNumericAttribute {

            public:

                BinaryStatisticalQuantileMeasureAttribute
                    binaryStatisticalQuantileMeasure;   /*!< The binary statistical quantile measure */
                NumericMeasureCollectionAttribute
                    numericMeasureCollection;           /*!< The considered numeric measure collection */
                double
                    parameter;                          /*!< The considered parameter */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryStatisticalQuantileNumericAttribute,
    (multiscale::verification::BinaryStatisticalQuantileMeasureAttribute, binaryStatisticalQuantileMeasure)
    (multiscale::verification::NumericMeasureCollectionAttribute, numericMeasureCollection)
    (double, parameter)
)


#endif
