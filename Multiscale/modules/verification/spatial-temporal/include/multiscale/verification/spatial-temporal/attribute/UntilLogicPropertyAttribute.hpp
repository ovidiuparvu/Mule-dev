#ifndef UNTILLOGICPROPERTYATTRIBUTE_HPP
#define UNTILLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing an "until" logic property attribute
        class UntilLogicPropertyAttribute : public LogicPropertyEvaluator {

            public:

                unsigned long               startTimepoint; /*!< The considered start timepoint */
                unsigned long               endTimepoint;   /*!< The considered end timepoint */
                LogicPropertyAttributeType  logicProperty;  /*!< The logic property following the "until" operator */

            public:

                //! Evaluate the truth value of the logic property considering the given spatial temporal trace
                /*!
                 * \param trace             The spatial temporal trace
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                bool evaluate(const SpatialTemporalTrace &trace,
                              const LogicPropertyAttributeType &lhsLogicProperty) const override {
                    return true;
                }

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UntilLogicPropertyAttribute,
    (unsigned long, startTimepoint)
    (unsigned long, endTimepoint)
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)

#endif
