#ifndef LOGICPROPERTYVISITOR_HPP
#define LOGICPROPERTYVISITOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericVisitor.hpp"


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
                    unsigned long startTime = logicProperty.startTimepoint;
                    unsigned long endTime   = logicProperty.endTimepoint;

                    for (unsigned long i = startTime; i <= endTime; i++) {
                        SpatialTemporalTrace subTrace = SpatialTemporalTrace::subTrace(trace, i, endTime);

                        if (evaluate(logicProperty.logicProperty, subTrace)) {
                            return evaluatePrecedingLogicProperties(i, startTime, endTime, lhsLogicProperty);
                        }
                    }

                    return false;
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
                    if (trace.length() > 1) {
                        double lhsNumericMeasureOne = evaluateNumericMeasure(primaryLogicProperty.lhsNumericMeasure, trace, 1);
                        double lhsNumericMeasureTwo = evaluateNumericMeasure(primaryLogicProperty.lhsNumericMeasure, trace, 0);
                        double rhsNumericMeasure    = evaluateNumericMeasure(primaryLogicProperty.rhsNumericMeasure, trace, 0);

                        return ComparatorEvaluator::evaluate(lhsNumericMeasureOne - lhsNumericMeasureTwo,
                                                             primaryLogicProperty.comparator.comparatorType,
                                                             rhsNumericMeasure);
                    }

                    return true;
                }

                //! Overloading the "()" operator for the NumericSpatialNumericComparisonAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NumericSpatialNumericComparisonAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    double lhsNumericMeasure = evaluateNumericMeasure(primaryLogicProperty.numericMeasure, trace);
                    double rhsNumericMeasure = evaluateNumericSpatialMeasure(primaryLogicProperty.numericSpatialMeasure, trace);

                    return ComparatorEvaluator::evaluate(lhsNumericMeasure,
                                                         primaryLogicProperty.comparator.comparatorType,
                                                         rhsNumericMeasure);
                }

                //! Overloading the "()" operator for the NumericNumericComparisonAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NumericNumericComparisonAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    double numericStateVariable = evaluateNumericMeasure(primaryLogicProperty.numericStateVariable, trace);
                    double numericMeasure       = evaluateNumericMeasure(primaryLogicProperty.numericMeasure, trace);

                    return ComparatorEvaluator::evaluate(numericStateVariable,
                                                         primaryLogicProperty.comparator.comparatorType,
                                                         numericMeasure);
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
                    unsigned long startTime = primaryLogicProperty.startTimepoint;
                    unsigned long endTime   = primaryLogicProperty.endTimepoint;

                    for (unsigned long i = startTime; i <= endTime; i++) {
                        SpatialTemporalTrace subTrace = SpatialTemporalTrace::subTrace(trace, startTime, endTime);

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
                    unsigned long startTime = primaryLogicProperty.startTimepoint;
                    unsigned long endTime   = primaryLogicProperty.endTimepoint;

                    for (unsigned long i = startTime; i <= endTime; i++) {
                        SpatialTemporalTrace subTrace = SpatialTemporalTrace::subTrace(trace, startTime, endTime);

                        if (!evaluate(primaryLogicProperty.logicProperty, subTrace)) {
                            return false;
                        }
                    }

                    return true;
                }

                //! Overloading the "()" operator for the NextLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NextLogicPropertyAttribute &primaryLogicProperty, const T &lhsLogicProperty) const {
                    SpatialTemporalTrace subTrace = SpatialTemporalTrace::subTrace(trace, 1);

                    return evaluate(primaryLogicProperty.logicProperty, subTrace);
                }

                //! Overloading the "()" operator for the NextKLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NextKLogicPropertyAttribute &primaryLogicProperty, const T &lhsLogicProperty) const {
                    SpatialTemporalTrace subTrace = SpatialTemporalTrace::subTrace(trace, primaryLogicProperty.nrOfTimepointsAhead);

                    return evaluate(primaryLogicProperty.logicProperty, subTrace);
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
                /*!
                 * \param logicProperty             The logic property containing the currently evaluated logic subproperty
                 * \param evaluationLogicProperties The logic properties preceding the currently evaluated logic subproperty
                 */
                LogicPropertyAttribute constructEvaluationLogicProperty(const LogicPropertyAttribute &logicProperty,
                                                                        const std::vector<LogicPropertyAttributeType> evaluationLogicProperties) const {
                    return LogicPropertyAttribute(logicProperty.firstLogicProperty, evaluationLogicProperties);
                }

                //! Evaluate the preceding logic properties
                /*!
                 * \param stopIndex                 All indices before this index are used as subtrace start index
                 * \param startTime                 The considered start time value
                 * \param endTime                   The considered end time value
                 * \param precedingLogicProperties  The preceding logic properties
                 */
                bool evaluatePrecedingLogicProperties(unsigned long stopIndex, unsigned long startTime, unsigned long endTime,
                                                     const LogicPropertyAttributeType &precedingLogicProperties) const {
                    for (unsigned long j = startTime; j < stopIndex; j++) {
                        SpatialTemporalTrace subTrace = SpatialTemporalTrace::subTrace(trace, j, endTime);

                        if (!evaluate(precedingLogicProperties, subTrace)) {
                            return false;
                        }
                    }

                    return true;
                }

                //! Evaluate the numeric measure considering the given spatial temporal trace
                /*!
                 * \param numericMeasure    The given numeric measure
                 * \param trace             The given spatial temporal trace
                 * \param timePointIndex    The index of the considered timepoint from the trace
                 */
                double evaluateNumericMeasure(const NumericMeasureAttributeType &numericMeasure, const SpatialTemporalTrace &trace,
                                              unsigned int timePointIndex = 0) const {
                    SpatialTemporalTrace nonConstTrace = SpatialTemporalTrace(trace);
                    TimePoint timePoint = nonConstTrace.getTimePoint(timePointIndex);

                    return boost::apply_visitor(NumericVisitor(timePoint), numericMeasure);
                }

                //! Evaluate the numeric spatial measure considering the given spatial temporal trace
                /*!
                 * \param numericMeasure    The given numeric measure
                 * \param trace             The given spatial temporal trace
                 * \param timePointIndex    The index of the considered timepoint from the trace
                 */
                double evaluateNumericSpatialMeasure(const NumericSpatialAttributeType &numericSpatialMeasure, const SpatialTemporalTrace &trace,
                                                     unsigned int timePointIndex = 0) const {
                    SpatialTemporalTrace nonConstTrace = SpatialTemporalTrace(trace);
                    TimePoint timePoint = nonConstTrace.getTimePoint(timePointIndex);

                    return boost::apply_visitor(NumericVisitor(timePoint), numericSpatialMeasure);
                }

        };

    };

};

#endif
