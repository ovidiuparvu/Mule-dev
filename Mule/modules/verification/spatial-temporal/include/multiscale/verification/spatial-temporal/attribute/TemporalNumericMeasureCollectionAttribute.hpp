#ifndef TEMPORALNUMERICMEASURECOLLECTIONATTRIBUTE_HPP
#define TEMPORALNUMERICMEASURECOLLECTIONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing temporal numeric measure collection attributes
        class TemporalNumericMeasureCollectionAttribute {

            public:

                unsigned long       startTimepoint; /*!< The considered start timepoint */
                unsigned long       endTimepoint;   /*!< The considered end timepoint */

                NumericMeasureType  numericMeasure; /*!< The numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TemporalNumericMeasureCollectionAttribute,
    (unsigned long, startTimepoint)
    (unsigned long, endTimepoint)
    (multiscale::verification::NumericMeasureType, numericMeasure)
)


#endif
