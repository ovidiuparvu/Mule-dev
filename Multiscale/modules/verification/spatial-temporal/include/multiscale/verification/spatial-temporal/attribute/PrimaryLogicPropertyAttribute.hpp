#ifndef PRIMARYLOGICPROPERTYATTRIBUTE_HPP
#define PRIMARYLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/DifferenceAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericNumericComparisonAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/NumericSpatialNumericComparisonAttribute.hpp"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/variant.hpp"


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
            DifferenceAttribute,
            NumericSpatialNumericComparisonAttribute,
            NumericNumericComparisonAttribute,
            boost::recursive_wrapper<NotLogicPropertyAttribute>,
            boost::recursive_wrapper<FutureLogicPropertyAttribute>,
            boost::recursive_wrapper<GlobalLogicPropertyAttribute>,
            boost::recursive_wrapper<NextLogicPropertyAttribute>,
            boost::recursive_wrapper<NextKLogicPropertyAttribute>,
            boost::recursive_wrapper<LogicPropertyAttribute>
        > PrimaryLogicPropertyAttributeType;


        //! Class for representing a primary logic property attribute
        class PrimaryLogicPropertyAttribute {
//        class PrimaryLogicPropertyAttribute : public LogicPropertyEvaluator {

            public:

                PrimaryLogicPropertyAttributeType primaryLogicProperty;    /*!< The primary logic property */

            public:

                //! Evaluate the truth value of the logic property considering the given spatial temporal trace
                /*!
                 * \param trace             The spatial temporal trace
                 * \param lhsLogicProperty  The left hand side logic property
                 */
//                bool evaluate(const SpatialTemporalTrace &trace,
//                              const LogicPropertyAttributeType &lhsLogicProperty) const override {
//                    return true;
//                }

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT (
    multiscale::verification::PrimaryLogicPropertyAttribute,
    (multiscale::verification::PrimaryLogicPropertyAttributeType, primaryLogicProperty)
);

#endif
