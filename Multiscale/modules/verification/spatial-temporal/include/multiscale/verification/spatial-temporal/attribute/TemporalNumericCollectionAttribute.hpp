#ifndef TEMPORALNUMERICCOLLETIONATTRIBUTE_HPP
#define TEMPORALNUMERICCOLLETIONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class ChangeTemporalNumericCollectionAttribute;
        class HomogeneousHomogeneousTimeseriesMeasureAttribute;
        class TimeseriesMeasureHeterogeneousAttribute;
        class TimeseriesMeasureHomogeneousAttribute;


        //! Variant for the temporal numeric collection attribute
        typedef boost::variant<
            TemporalNumericMeasureCollectionAttribute,
            boost::recursive_wrapper<TimeseriesMeasureHeterogeneousAttribute>,
            boost::recursive_wrapper<TimeseriesMeasureHomogeneousAttribute>,
            boost::recursive_wrapper<HomogeneousHomogeneousTimeseriesMeasureAttribute>
        > TemporalNumericCollectionType;


        //! Class for representing a temporal numeric collection attribute
        class TemporalNumericCollectionAttribute {

            public:

                TemporalNumericCollectionType temporalNumericCollection;  /*!< The temporal numeric collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TemporalNumericCollectionAttribute,
    (multiscale::verification::TemporalNumericCollectionType, temporalNumericCollection)
)


#endif
