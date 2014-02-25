#ifndef NOTLOGICPROPERTYATTRIBUTE_HPP
#define NOTLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "not" logic property attribute
        class NotLogicPropertyAttribute {
//        class NotLogicPropertyAttribute : public LogicPropertyEvaluator {

            public:

                LogicPropertyAttributeType logicProperty;    /*!< The logic property following the "not" operator */

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
    multiscale::verification::NotLogicPropertyAttribute,
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)

#endif
