#ifndef HOMOGENEOUSHOMOGENEOUSTIMESERIESMEASUREATTRIBUTE_HPP
#define HOMOGENEOUSHOMOGENEOUSTIMESERIESMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/HomogeneousTimeseriesMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/HomogeneousTimeseriesComponentAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Class for representing a homogeneous homogeneous timeseries measure attribute
        class HomogeneousHomogeneousTimeseriesMeasureAttribute {

            public:

                HomogeneousTimeseriesMeasureAttribute
                    homogeneousTimeseriesMeasure;   /*!< The homogeneous timeseries measure */
                HomogeneousTimeseriesComponentAttribute
                    homogeneousTimeseriesComponent; /*!< The homogeneous timeseries component */
                TemporalNumericCollectionAttribute
                    temporalNumericCollection;      /*!< The temporal numeric collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::HomogeneousHomogeneousTimeseriesMeasureAttribute,
    (multiscale::verification::HomogeneousTimeseriesMeasureAttribute, homogeneousTimeseriesMeasure)
    (multiscale::verification::HomogeneousTimeseriesComponentAttribute, homogeneousTimeseriesComponent)
    (multiscale::verification::TemporalNumericCollectionAttribute, temporalNumericCollection)
)


#endif
