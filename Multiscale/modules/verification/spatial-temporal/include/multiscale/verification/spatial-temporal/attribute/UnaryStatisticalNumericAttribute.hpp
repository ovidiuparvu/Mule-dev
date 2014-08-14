#ifndef UNARYSTATISTICALNUMERICATTRIBUTE_HPP
#define UNARYSTATISTICALNUMERICATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnaryStatisticalMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a unary statistical numeric attribute
        class UnaryStatisticalNumericAttribute {

            public:

                UnaryStatisticalMeasureAttribute  unaryStatisticalMeasure;   /*!< The unary statistical measure */
                NumericMeasureCollectionAttribute numericMeasureCollection;  /*!< The considered numeric measure
                                                                                  collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryStatisticalNumericAttribute,
    (multiscale::verification::UnaryStatisticalMeasureAttribute, unaryStatisticalMeasure)
    (multiscale::verification::NumericMeasureCollectionAttribute, numericMeasureCollection)
)


#endif
