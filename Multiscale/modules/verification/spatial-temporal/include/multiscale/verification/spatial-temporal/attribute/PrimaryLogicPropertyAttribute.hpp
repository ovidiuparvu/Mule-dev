#ifndef PRIMARYLOGICPROPERTYATTRIBUTE_HPP
#define PRIMARYLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ChangeTemporalNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SimilarityTemporalNumericCollectionAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericComparisonAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class FutureLogicPropertyAttribute;
        class GlobalLogicPropertyAttribute;
        class LogicPropertyAttribute;
        class NextKLogicPropertyAttribute;
        class NextLogicPropertyAttribute;
        class NotLogicPropertyAttribute;


        //! Variant for representing a primary logic property type
        typedef boost::variant<
            TemporalNumericComparisonAttribute,
            ChangeTemporalNumericMeasureAttribute,
            SimilarityTemporalNumericCollectionAttribute,
            boost::recursive_wrapper<NotLogicPropertyAttribute>,
            boost::recursive_wrapper<FutureLogicPropertyAttribute>,
            boost::recursive_wrapper<GlobalLogicPropertyAttribute>,
            boost::recursive_wrapper<NextLogicPropertyAttribute>,
            boost::recursive_wrapper<NextKLogicPropertyAttribute>,
            boost::recursive_wrapper<LogicPropertyAttribute>
        > PrimaryLogicPropertyAttributeType;


        //! Class for representing a primary logic property attribute
        class PrimaryLogicPropertyAttribute {

            public:

                PrimaryLogicPropertyAttributeType primaryLogicProperty;    /*!< The primary logic property */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT (
    multiscale::verification::PrimaryLogicPropertyAttribute,
    (multiscale::verification::PrimaryLogicPropertyAttributeType, primaryLogicProperty)
);


#endif
