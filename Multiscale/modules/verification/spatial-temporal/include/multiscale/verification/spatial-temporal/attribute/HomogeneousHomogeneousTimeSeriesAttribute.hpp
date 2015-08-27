#ifndef HOMOGENEOUSHOMOGENEOUSTIMESERIESATTRIBUTE_HPP
#define HOMOGENEOUSHOMOGENEOUSTIMESERIESATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/HomogeneousTimeSeriesMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/HomogeneousTimeSeriesComponentAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Class for representing a homogeneous homogeneous time series attribute
        class HomogeneousHomogeneousTimeSeriesAttribute {

            public:

                HomogeneousTimeSeriesMeasureAttribute
                    homogeneousTimeSeriesMeasure;       /*!< The homogeneous time series measure */
                HomogeneousTimeSeriesComponentAttribute
                    homogeneousTimeSeriesComponent;     /*!< The homogeneous time series component */
                TemporalNumericMeasureCollectionAttribute
                    temporalNumericMeasureCollection;   /*!< The temporal numeric measure collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::HomogeneousHomogeneousTimeSeriesAttribute,
    (multiscale::verification::HomogeneousTimeSeriesMeasureAttribute, homogeneousTimeSeriesMeasure)
    (multiscale::verification::HomogeneousTimeSeriesComponentAttribute, homogeneousTimeSeriesComponent)
    (multiscale::verification::TemporalNumericMeasureCollectionAttribute, temporalNumericMeasureCollection)
)


#endif
