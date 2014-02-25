#ifndef LOGICPROPERTYATTRIBUTE_HPP
#define LOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class for representing a logic property attribute
        class LogicPropertyAttribute {
//        class LogicPropertyAttribute : public LogicPropertyEvaluator {

            public:

                LogicPropertyAttributeType              firstLogicProperty;         /*!< The first logic property */
                std::vector<LogicPropertyAttributeType> nextLogicProperties;        /*!< The next logic properties */

                LogicPropertyAttributeType              evaluationLogicProperty;    /*!< The logic property used only for
                                                                                         evaluation purposes */
                std::vector<LogicPropertyAttributeType> evaluationLogicProperties;  /*!< The logic property used only for
                                                                                         evaluation purposes */

            public:

                //! Evaluate the truth value of a logic property considering the spatial temporal trace and logic property
                /*!
                 * \param trace             The spatial temporal trace
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                bool evaluate(const SpatialTemporalTrace &trace) const {
                    bool firstLogicPropertyTruthValue = evaluateFirstLogicProperty(trace);

                    return evaluateNextLogicProperties(firstLogicPropertyTruthValue, trace);
                }

                //! Evaluate the first logic property considering the given spatial temporal trace
                /*!
                 * \param trace The given spatial temporal trace
                 */
                bool evaluateFirstLogicProperty(const SpatialTemporalTrace &trace) const {
                    return boost::apply_visitor(LogicPropertyVisitor(trace),firstLogicProperty, evaluationLogicProperty);
                }

                //! Evaluate the next logic properties considering the given spatial temporal trace and truth value
                /*!
                 * \param truthValue    The given truth value
                 * \param trace         The given spatial temporal trace
                 */
                bool evaluateNextLogicProperties(bool truthValue, const SpatialTemporalTrace &trace) const {
                    for (const auto &nextLogicProperty : nextLogicProperties) {
                        firstLogicPropertyTruthValue = bool::
                    }
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
