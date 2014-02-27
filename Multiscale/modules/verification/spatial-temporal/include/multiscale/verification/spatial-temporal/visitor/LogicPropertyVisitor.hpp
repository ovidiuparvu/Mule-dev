#ifndef LOGICPROPERTYVISITOR_HPP
#define LOGICPROPERTYVISITOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include <boost/variant.hpp>
#include <iostream> // TODO: Remove


namespace multiscale {

    namespace verification {

        //! Class used to evaluate logic properties
        class LogicPropertyVisitor : public boost::static_visitor<bool> {

            private:

                SpatialTemporalTrace        trace;                      /*!< The spatial temporal trace */
                LogicPropertyAttributeType  evaluationLogicProperty;    /*!< The logic property used only for
                                                                             evaluation purposes */

                bool precedingTruthValue;   /*!< The truth value of the preceding logic property */

            public:

                //! Constructor with parameters for the class
                /*!
                 * \param trace                 The spatial temporal trace
                 * \param previousTruthValue    The truth value of the preceding logic property
                 */
                LogicPropertyVisitor(const SpatialTemporalTrace &trace, bool precedingTruthValue = true) {
                    this->trace = trace;
                    this->precedingTruthValue = precedingTruthValue;
                }

                //! Overloading the "()" operator for the Nil alternative
                /*!
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const Nil &logicProperty, const T &lhsLogicProperty) const {
                    return true;
                }

                //! Overloading the "()" operator for the LogicPropertyAttribute alternative
                /*!
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const LogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    bool firstLogicPropertyTruthValue = evaluate(logicProperty.firstLogicProperty, trace);

                    return evaluateNextLogicProperties(logicProperty, firstLogicPropertyTruthValue);
                }

                //! Overloading the "()" operator for the OrLogicPropertyAttribute alternative
                /*!
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const OrLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    bool logicPropertyTruthValue = evaluate(logicProperty.logicProperty, trace);

                    return (precedingTruthValue || logicPropertyTruthValue);
                }

                //! Overloading the "()" operator for the AndLogicPropertyAttribute alternative
                /*!
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const AndLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    bool logicPropertyTruthValue = evaluate(logicProperty.logicProperty, trace);

                    return (precedingTruthValue && logicPropertyTruthValue);
                }

                //! Overloading the "()" operator for the ImplicationLogicPropertyAttribute alternative
                /*!
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const ImplicationLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    bool logicPropertyTruthValue = evaluate(logicProperty.logicProperty, trace);

                    return ((!precedingTruthValue) || logicPropertyTruthValue);
                }

                //! Overloading the "()" operator for the EquivalenceLogicPropertyAttribute alternative
                /*!
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const EquivalenceLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    bool logicPropertyTruthValue = evaluate(logicProperty.logicProperty, trace);

                    return (((!precedingTruthValue) || logicPropertyTruthValue) &&
                            ((!logicPropertyTruthValue) || precedingTruthValue));
                }

                //! Overloading the operator ()
                template <typename T>
                bool operator() (const UntilLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    // TODO: Implement
                    return true;
                }

                //! Overloading the "()" operator for the PrimaryLogicPropertyAttribute alternative
                /*!
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const PrimaryLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    return evaluate(logicProperty.primaryLogicProperty, trace);
                }

                //! Overloading the "()" operator for the DifferenceAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const DifferenceAttribute &primaryLogicProperty, const T &lhsLogicProperty) const {
                    // TODO: Implement
                    return false;
                }

                //! Overloading the "()" operator for the NumericSpatialNumericComparisonAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NumericSpatialNumericComparisonAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    // TODO: Implement
                    std::cout << "NumericSpatialNumericComparisonAttribute" << std::endl;

                    return true;
                }

                //! Overloading the "()" operator for the NumericNumericComparisonAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NumericNumericComparisonAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    // TODO: Implement
                    std::cout << "NumericNumericComparisonAttribute" << std::endl;

                    return true;
                }

                //! Overloading the "()" operator for the NotLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NotLogicPropertyAttribute &primaryLogicProperty, const T &lhsLogicProperty) const {
                    bool logicPropertyTruthValue = evaluate(primaryLogicProperty.logicProperty, trace);

                    return (!logicPropertyTruthValue);
                }

                //! Overloading the "()" operator for the FutureLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const FutureLogicPropertyAttribute &primaryLogicProperty, const T &lhsLogicProperty) const {
                    unsigned long futurePropertyStart   = primaryLogicProperty.startTimepoint;
                    unsigned long futurePropertyEnd     = primaryLogicProperty.endTimepoint;

                    for (unsigned long i = futurePropertyStart; i <= futurePropertyEnd; i++) {
                        SpatialTemporalTrace subTrace = SpatialTemporalTrace::subTrace(trace, futurePropertyStart, futurePropertyEnd);

                        if (evaluate(primaryLogicProperty.logicProperty, subTrace)) {
                            return true;
                        }
                    }

                    return false;
                }

                //! Overloading the "()" operator for the GlobalLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const GlobalLogicPropertyAttribute &primaryLogicProperty, const T &lhsLogicProperty) const {
                    // TODO: Implement
                    std::cout << "GlobalLogicPropertyAttribute" << std::endl;

                    return true;
                }

                //! Overloading the "()" operator for the NextLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NextLogicPropertyAttribute &primaryLogicProperty, const T &lhsLogicProperty) const {
                    // TODO: Implement
                    std::cout << "NextLogicPropertyAttribute" << std::endl;

                    return true;
                }

                //! Overloading the "()" operator for the NextKLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NextKLogicPropertyAttribute &primaryLogicProperty, const T &lhsLogicProperty) const {
                    // TODO: Implement
                    std::cout << "NextKLogicPropertyAttribute" << std::endl;

                    return true;
                }

            private:

                //! Evaluate the logic property considering the given spatial temporal trace
                /*!
                 * \param logicProperty The logic property
                 * \param trace         The given spatial temporal trace
                 */
                bool evaluate(const LogicPropertyAttributeType &logicProperty, const SpatialTemporalTrace &trace) const {
                    return boost::apply_visitor(LogicPropertyVisitor(trace), logicProperty, evaluationLogicProperty);
                }

                //! Evaluate the logic property considering the given spatial temporal trace
                /*!
                 * \param logicProperty The logic property
                 * \param trace         The given spatial temporal trace
                 */
                bool evaluate(const PrimaryLogicPropertyAttributeType &logicProperty, const SpatialTemporalTrace &trace) const {
                    return boost::apply_visitor(LogicPropertyVisitor(trace), logicProperty, evaluationLogicProperty);
                }

                //! Evaluate the next logic properties
                /*!
                 * Evaluate the next logic properties considering the given logic property,
                 * spatial temporal trace and truth value
                 *
                 * \param logicProperty The given logic property
                 * \param truthValue    The given truth value
                 * \param trace         The given spatial temporal trace
                 */
                bool evaluateNextLogicProperties(const LogicPropertyAttribute &logicProperty, bool truthValue) const {
                    std::vector<LogicPropertyAttributeType> precedingEvaluationLogicProperties;

                    for (const auto &nextLogicProperty : logicProperty.nextLogicProperties) {
                        LogicPropertyAttributeType precedingEvaluationLogicProperty = constructEvaluationLogicProperty(logicProperty, precedingEvaluationLogicProperties);

                        truthValue = boost::apply_visitor(LogicPropertyVisitor(trace, truthValue), nextLogicProperty,
                                                          precedingEvaluationLogicProperty);

                        precedingEvaluationLogicProperties.push_back(nextLogicProperty);
                    }

                    return truthValue;
                }

                //! Construct a new logic property attribute using the evaluation logic properties
                LogicPropertyAttribute constructEvaluationLogicProperty(const LogicPropertyAttribute &logicProperty,
                                                                        const std::vector<LogicPropertyAttributeType> evaluationLogicProperties) const {
                    return LogicPropertyAttribute(logicProperty.firstLogicProperty, evaluationLogicProperties);
                }

        };

    };

};

#endif
