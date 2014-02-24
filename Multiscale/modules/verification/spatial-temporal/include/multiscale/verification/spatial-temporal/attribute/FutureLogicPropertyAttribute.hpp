#ifndef FUTURELOGICPROPERTYATTRIBUTE_HPP
#define FUTURELOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a "future" logic property attribute
        class FutureLogicPropertyAttribute : public LogicPropertyEvaluator {

            public:

                unsigned long               startTimepoint; /*!< The considered start timepoint */
                unsigned long               endTimepoint;   /*!< The considered end timepoint */
                LogicPropertyAttributeType  logicProperty;  /*!< The logic property following the "future" operator */

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
    multiscale::verification::FutureLogicPropertyAttribute,
    (unsigned long, startTimepoint)
    (unsigned long, endTimepoint)
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
)

#endif
