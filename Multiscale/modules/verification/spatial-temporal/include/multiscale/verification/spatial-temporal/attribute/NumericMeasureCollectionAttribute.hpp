#ifndef NUMERICMEASURECOLLECTIONATTRIBUTE_HPP
#define NUMERICMEASURECOLLECTIONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureCollectionAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Variant for the numeric measure collection attribute
        typedef boost::variant<
            SpatialMeasureCollectionAttribute,
            TemporalNumericCollectionAttribute
        > NumericMeasureCollectionType;


        //! Class for representing a numeric measure collection attribute
        class NumericMeasureCollectionAttribute {

            public:

                NumericMeasureCollectionType numericMeasureCollection;  /*!< The numeric measure collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::NumericMeasureCollectionAttribute,
    (multiscale::verification::NumericMeasureCollectionType, numericMeasureCollection)
)


#endif
