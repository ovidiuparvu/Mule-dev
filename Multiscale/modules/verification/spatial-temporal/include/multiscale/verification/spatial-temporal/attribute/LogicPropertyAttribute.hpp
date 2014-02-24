#ifndef LOGICPROPERTYATTRIBUTE_HPP
#define LOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class for representing a logic property attribute
        class LogicPropertyAttribute : public LogicPropertyEvaluator {

            public:

                LogicPropertyAttributeType                 firstLogicProperty;      /*!< The first logic property */
                std::vector<LogicPropertyAttributeType>    nextLogicProperties;     /*!< The next logic properties */

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
    multiscale::verification::LogicPropertyAttribute,
    (multiscale::verification::LogicPropertyAttributeType, firstLogicProperty)
    (std::vector<multiscale::verification::LogicPropertyAttributeType>, nextLogicProperties)
)

#endif
