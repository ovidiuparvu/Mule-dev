#ifndef ANDLOGICPROPERTYATTRIBUTE_HPP
#define ANDLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "and" logic property attribute
        class AndLogicPropertyAttribute {
//        class AndLogicPropertyAttribute : public LogicPropertyEvaluator {

            public:

                LogicPropertyAttributeType logicProperty;   /*!< The logical property following the "and" operator */

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


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::AndLogicPropertyAttribute,
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)

#endif
