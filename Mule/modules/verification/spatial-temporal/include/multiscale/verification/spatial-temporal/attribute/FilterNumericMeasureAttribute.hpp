#ifndef FILTERNUMERICMEASUREATTRIBUTE_HPP
#define FILTERNUMERICMEASUREATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Forward declarations
        class BinaryNumericFilterAttribute;
        class FilterNumericMeasureAttribute;
        class PrimaryNumericMeasureAttribute;
        class UnaryNumericFilterAttribute;


        //! Variant for a filter numeric measure attribute
        typedef boost::variant<
            SpatialMeasureAttribute,
            boost::recursive_wrapper<PrimaryNumericMeasureAttribute>,
            boost::recursive_wrapper<UnaryNumericFilterAttribute>,
            boost::recursive_wrapper<BinaryNumericFilterAttribute>,
            boost::recursive_wrapper<FilterNumericMeasureAttribute>
        > FilterNumericMeasureAttributeType;


        //! Class for representing a filter numeric measure
        class FilterNumericMeasureAttribute {

            public:

                FilterNumericMeasureAttributeType filterNumericMeasure;   /*!< The filter numeric measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::FilterNumericMeasureAttribute,
    (multiscale::verification::FilterNumericMeasureAttributeType, filterNumericMeasure)
)


#endif
