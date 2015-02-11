#ifndef NUMERICSTATISTICALMEASUREATTRIBUTE_HPP
#define NUMERICSTATISTICALMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalNumericAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalQuantileNumericAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryStatisticalNumericAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Variant for the numeric statistical measure attribute
        typedef boost::variant<
            UnaryStatisticalNumericAttribute,
            BinaryStatisticalNumericAttribute,
            BinaryStatisticalQuantileNumericAttribute
        > NumericStatisticalMeasureType;


        //! Class for representing a numeric statistical measure attribute
        class NumericStatisticalMeasureAttribute {

            public:

                NumericStatisticalMeasureType   numericStatisticalMeasure;  /*!< The numeric statistical measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericStatisticalMeasureAttribute,
    (multiscale::verification::NumericStatisticalMeasureType, numericStatisticalMeasure)
)


#endif
