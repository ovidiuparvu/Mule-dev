#ifndef LOGICPROPERTYVISITOR_HPP
#define LOGICPROPERTYVISITOR_HPP

#include "multiscale/util/ConsolePrinter.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ChangeMeasureEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericVisitor.hpp"
#include "multiscale/verification/spatial-temporal/visitor/TemporalNumericVisitor.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Constants
        static const std::string WRN_LOGIC_PROPERTY_EVAL_FALSE = "The enclosing logic property was evaluated to the default value \"false\".";
        static const std::string WRN_OUTPUT_SEPARATOR          = " ";


        //! Class used to evaluate logic properties
        class LogicPropertyVisitor : public boost::static_visitor<bool> {

            private:

                const SpatialTemporalTrace  &trace;                     /*!< The spatial temporal trace */
                const TypeSemanticsTable    &typeSemanticsTable;        /*!< The type semantics table */

                LogicPropertyAttributeType  evaluationLogicProperty;    /*!< The logic property used only for
                                                                             evaluation purposes */

                bool precedingTruthValue;   /*!< The truth value of the preceding logic property */

            public:

                LogicPropertyVisitor(const SpatialTemporalTrace &trace,
                                     const TypeSemanticsTable &typeSemanticsTable,
                                     bool precedingTruthValue = true)
                                     : trace(trace), typeSemanticsTable(typeSemanticsTable),
                                       precedingTruthValue(precedingTruthValue) {}

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
                 * Remark: Lazy evaluation is performed for efficiency purposes.
                 *
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const OrLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    if (precedingTruthValue == true) {
                        return true;
                    } else {
                        // Not considering precedingTruthValue because it is F (F V X = X where X = T/F)
                        return evaluate(logicProperty.logicProperty, trace);
                    }
                }

                //! Overloading the "()" operator for the AndLogicPropertyAttribute alternative
                /*!
                 * Remark: Lazy evaluation is performed for efficiency purposes.
                 *
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const AndLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    if (precedingTruthValue == false) {
                        return false;
                    } else {
                        // Not considering precedingTruthValue because it is T (T ^ X = X where X = T/F)
                        return evaluate(logicProperty.logicProperty, trace);
                    }
                }

                //! Overloading the "()" operator for the ImplicationLogicPropertyAttribute alternative
                /*!
                 * Remark: Lazy evaluation is performed for efficiency purposes.
                 *
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const ImplicationLogicPropertyAttribute &logicProperty,
                                 const T &lhsLogicProperty) const {
                    if (precedingTruthValue == false) {
                        return true;
                    } else {
                        // Not considering precedingTruthValue because it is T ((T => X) logically equivalent
                        // to (~T V X) = X where X = T/F)
                        return evaluate(logicProperty.logicProperty, trace);
                    }
                }

                //! Overloading the "()" operator for the EquivalenceLogicPropertyAttribute alternative
                /*!
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const EquivalenceLogicPropertyAttribute &logicProperty,
                                 const T &lhsLogicProperty) const {
                    bool logicPropertyTruthValue = evaluate(logicProperty.logicProperty, trace);

                    // p <=> q is logically equivalent to p => q and q => p
                    return (((!precedingTruthValue) || logicPropertyTruthValue) &&
                            ((!logicPropertyTruthValue) || precedingTruthValue));
                }

                //! Overloading the operator "()" for the UntilLogicPropertyAttribute alternative
                /*!
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const UntilLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    try {
                        return evaluateUntilLogicProperty(logicProperty, lhsLogicProperty);
                    } catch (const SpatialTemporalException &ex) {
                        return printExceptionMessage(ex.rawMessage());
                    }
                }

                //! Overloading the "()" operator for the PrimaryLogicPropertyAttribute alternative
                /*!
                 * \param logicProperty     The logic property
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool operator() (const PrimaryLogicPropertyAttribute &logicProperty,
                                 const T &lhsLogicProperty) const {
                    return evaluate(logicProperty.primaryLogicProperty, trace);
                }

                //! Overloading the "()" operator for the TemporalNumericComparisonAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const TemporalNumericComparisonAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    try {
                        return evaluateTemporalNumericComparison(primaryLogicProperty, lhsLogicProperty);
                    } catch (const SpatialTemporalException &ex) {
                        return printExceptionMessage(ex.rawMessage());
                    }
                }

                //! Overloading the "()" operator for the ChangeTemporalNumericMeasureAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const ChangeTemporalNumericMeasureAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    try {
                        return evaluateChangeTemporalNumericMeasure(primaryLogicProperty, lhsLogicProperty);
                    } catch (const SpatialTemporalException &ex) {
                        return printExceptionMessage(ex.rawMessage());
                    }
                }

                //! Overloading the "()" operator for the SimilarityTemporalNumericCollectionAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const SimilarityTemporalNumericCollectionAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    std::vector<double> lhsTemporalNumericCollectionValues =
                        NumericMeasureCollectionEvaluator::evaluateTemporalNumericCollection(
                            trace, typeSemanticsTable,
                            primaryLogicProperty.lhsTemporalNumericCollection
                        );

                    std::vector<double> rhsTemporalNumericCollectionValues =
                        NumericMeasureCollectionEvaluator::evaluateTemporalNumericCollection(
                            trace, typeSemanticsTable,
                            primaryLogicProperty.rhsTemporalNumericCollection
                        );

                    return evaluateSimilarityTemporalNumericCollection(
                        primaryLogicProperty.similarityMeasure.similarityMeasure,
                        lhsTemporalNumericCollectionValues,
                        rhsTemporalNumericCollectionValues,
                        primaryLogicProperty.toleratedSimilarityDifference
                    );
                }

                //! Overloading the "()" operator for the NotLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NotLogicPropertyAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    bool logicPropertyTruthValue = evaluate(primaryLogicProperty.logicProperty, trace);

                    return (!logicPropertyTruthValue);
                }

                //! Overloading the "()" operator for the FutureLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const FutureLogicPropertyAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    try {
                        return evaluateFutureLogicProperty(primaryLogicProperty, lhsLogicProperty);
                    } catch (const SpatialTemporalException &ex) {
                        return printExceptionMessage(ex.rawMessage());
                    }
                }

                //! Overloading the "()" operator for the GlobalLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const GlobalLogicPropertyAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    try {
                        return evaluateGlobalLogicProperty(primaryLogicProperty, lhsLogicProperty);
                    } catch (const SpatialTemporalException &ex) {
                        return printExceptionMessage(ex.rawMessage());
                    }
                }

                //! Overloading the "()" operator for the NextLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NextLogicPropertyAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    try {
                        return evaluateNextLogicProperty(primaryLogicProperty, lhsLogicProperty);
                    } catch (const SpatialTemporalException &ex) {
                        return printExceptionMessage(ex.rawMessage());
                    }
                }

                //! Overloading the "()" operator for the NextKLogicPropertyAttribute alternative
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool operator() (const NextKLogicPropertyAttribute &primaryLogicProperty,
                                 const T &lhsLogicProperty) const {
                    try {
                        return evaluateNextKLogicProperty(primaryLogicProperty, lhsLogicProperty);
                    } catch (const SpatialTemporalException &ex) {
                        return printExceptionMessage(ex.rawMessage());
                    }
                }

            private:

                //! Evaluate the given TemporalNumericComparisonAttribute
                /*!
                 * \param comparisonAttribute   The numeric numeric comparison attribute
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool evaluateTemporalNumericComparison(const TemporalNumericComparisonAttribute &comparisonAttribute,
                                                      const T &lhsLogicProperty) const {
                    double lhsNumericMeasure = evaluateTemporalNumericMeasure(
                                                   comparisonAttribute.lhsTemporalNumericMeasure,
                                                   trace
                                               );
                    double rhsNumericMeasure = evaluateTemporalNumericMeasure(
                                                   comparisonAttribute.rhsTemporalNumericMeasure,
                                                   trace
                                               );

                    return ComparatorEvaluator::evaluate(lhsNumericMeasure,
                                                         comparisonAttribute.comparator.comparatorType,
                                                         rhsNumericMeasure);
                }

                //! Evaluate the given ChangeTemporalNumericMeasureAttribute
                /*!
                 * \param changeAttribute   The change temporal numeric measure attribute
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                template <typename T>
                bool evaluateChangeTemporalNumericMeasure(const ChangeTemporalNumericMeasureAttribute &changeAttribute,
                                                          const T &lhsLogicProperty) const {
                    double lhsNumericMeasure = evaluateChangeLhsTemporalNumericMeasure(changeAttribute);
                    double rhsNumericMeasure = evaluateTemporalNumericMeasure(
                                                   changeAttribute.rhsTemporalNumericMeasure,
                                                   trace
                                               );

                    return ComparatorEvaluator::evaluate(lhsNumericMeasure,
                                                         changeAttribute.comparator.comparatorType,
                                                         rhsNumericMeasure);
                }

                //! Evaluate the left hand side temporal numeric measure of the given ChangeTemporalNumericMeasure
                /*!
                 * \param changeAttribute   The change temporal numeric measure attribute
                 */
                double evaluateChangeLhsTemporalNumericMeasure(const ChangeTemporalNumericMeasureAttribute
                                                               &changeAttribute) const {
                    double lhsTemporalNumericMeasureFirstTimepoint = evaluateTemporalNumericMeasure(
                                                                         changeAttribute.lhsTemporalNumericMeasure,
                                                                         trace,
                                                                         0
                                                                     );
                    double lhsTemporalNumericMeasureSecondTimepoint = evaluateTemporalNumericMeasure(
                                                                          changeAttribute.lhsTemporalNumericMeasure,
                                                                          trace,
                                                                          1
                                                                      );

                    unsigned long timeValueFirstTimepoint  = trace.getTimePoint(0).getValue();
                    unsigned long timeValueSecondTimepoint = trace.getTimePoint(1).getValue();

                    return ChangeMeasureEvaluator::evaluate(changeAttribute.changeMeasure.changeMeasureType,
                                                            lhsTemporalNumericMeasureFirstTimepoint,
                                                            lhsTemporalNumericMeasureSecondTimepoint,
                                                            timeValueFirstTimepoint,
                                                            timeValueSecondTimepoint);
                }

                //! Evaluate the given SimilarityTemporalNumericCollectionAttribute
                /*!
                 * \param similarityMeasureType                 The specific similarity measure type
                 * \param lhsTemporalNumericCollectionValues    The left hand side temporal numeric collection values
                 * \param rhsTemporalNumericCollectionValues    The right hand side temporal numeric collection values
                 * \param toleratedSimilarityDifference         The maximum tolerated similarity difference between
                 *                                              two values
                 */
                bool
                evaluateSimilarityTemporalNumericCollection(const SimilarityMeasureType &similarityMeasureType,
                                                            const std::vector<double>
                                                            &lhsTemporalNumericCollectionValues,
                                                            const std::vector<double>
                                                            &rhsTemporalNumericCollectionValues,
                                                            double toleratedSimilarityDifference) const {
                    if (lhsTemporalNumericCollectionValues.size() < rhsTemporalNumericCollectionValues.size()) {
                        return isLhsSimilarToRhs(lhsTemporalNumericCollectionValues,
                                                 rhsTemporalNumericCollectionValues,
                                                 toleratedSimilarityDifference, similarityMeasureType);
                    } else {
                        return isLhsSimilarToRhs(rhsTemporalNumericCollectionValues,
                                                 lhsTemporalNumericCollectionValues,
                                                 toleratedSimilarityDifference, similarityMeasureType);
                    }
                }

                //! Check if the left- and right-hand side collections of values are similar
                /*!
                 * \param similarityMeasureType                 The specific similarity measure type
                 * \param lhsTemporalNumericCollectionValues    The left hand side temporal numeric collection values
                 * \param rhsTemporalNumericCollectionValues    The right hand side temporal numeric collection values
                 * \param toleratedSimilarityDifference         The maximum tolerated similarity difference between
                 *                                              two values
                 */
                bool
                isLhsSimilarToRhs(const std::vector<double> &lhsTemporalNumericCollectionValues,
                                  const std::vector<double> &rhsTemporalNumericCollectionValues,
                                  double toleratedSimilarityDifference,
                                  const SimilarityMeasureType &similarityMeasureType) const {
                    // Precondition
                    assert(lhsTemporalNumericCollectionValues.size() <= rhsTemporalNumericCollectionValues.size());

                    std::size_t lhsIndex = 0;
                    std::size_t rhsIndex = 0;

                    std::size_t nrOfLhsElements = lhsTemporalNumericCollectionValues.size();
                    std::size_t nrOfRhsElements = rhsTemporalNumericCollectionValues.size();

                    // Incrementally check if the collections of values are similar
                    while ((lhsIndex < nrOfLhsElements) &&
                           ((nrOfLhsElements - lhsIndex) <= (nrOfRhsElements - rhsIndex))) {
                        if (areSimilarValues(lhsTemporalNumericCollectionValues[lhsIndex],
                                             rhsTemporalNumericCollectionValues[rhsIndex],
                                             toleratedSimilarityDifference, similarityMeasureType)) {
                            lhsIndex++;
                        }

                        rhsIndex++;
                    }

                    return (lhsIndex == nrOfLhsElements);
                }

                //! Check if two values are similar considering the given similarity measure type
                /*! Two values are considered similar if their dissimilarity value is smaller or equal to
                 *  toleratedSimilarityDifference.
                 *
                 * \param lhsValue                      The left hand side value
                 * \param rhsValue                      The right hand side value
                 * \param toleratedSimilarityDifference The maximum tolerated similarity difference between
                 *                                      two values
                 * \param similarityMeasureType         The specific similarity measure type
                 */
                bool
                areSimilarValues(double lhsValue, double rhsValue, double toleratedSimilarityDifference,
                                 const SimilarityMeasureType &similarityMeasureType) const {
                    return (
                        Numeric::lessOrEqual(
                            computeDissimilarityValue(lhsValue, rhsValue, similarityMeasureType),
                            toleratedSimilarityDifference
                        )
                    );
                }

                //! Compute the dissimilarity between two values considering the given similarity measure type
                /*!
                 * \param lhsValue                  The left hand side value
                 * \param rhsValue                  The right hand side value
                 * \param similarityMeasureType     The specific similarity measure type
                 */
                double
                computeDissimilarityValue(double lhsValue, double rhsValue,
                                          const SimilarityMeasureType &similarityMeasureType) const {
                    switch (similarityMeasureType) {
                        case SimilarityMeasureType::Opposite:
                            return (std::fabs(lhsValue + rhsValue));
                            break;

                        case SimilarityMeasureType::Similar:
                            return (std::fabs(lhsValue - rhsValue));
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

                //! Evaluate the given UntilLogicPropertyAttribute
                /*!
                 * \param untilLogicProperty    The until logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool evaluateUntilLogicProperty(const UntilLogicPropertyAttribute &untilLogicProperty,
                                                const T &lhsLogicProperty) const {
                    unsigned long startTime = untilLogicProperty.startTimepoint;
                    unsigned long endTime   = untilLogicProperty.endTimepoint;

                    SpatialTemporalTrace traceCopy(trace);

                    for (unsigned long i = startTime; i <= endTime; i = traceCopy.nextTimePointValue()) {
                         traceCopy.setSubTrace(i);

                        if (evaluate(untilLogicProperty.logicProperty, traceCopy)) {
                            return evaluatePrecedingLogicProperties(startTime, i, lhsLogicProperty);
                        }
                    }

                    return false;
                }

                //! Evaluate the given FutureLogicPropertyAttribute
                /*!
                 * \param futureLogicProperty   The future logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool evaluateFutureLogicProperty(const FutureLogicPropertyAttribute &futureLogicProperty,
                                                 const T &lhsLogicProperty) const {
                    unsigned long startTime = futureLogicProperty.startTimepoint;
                    unsigned long endTime   = futureLogicProperty.endTimepoint;

                    SpatialTemporalTrace traceCopy(trace);

                    for (unsigned long i = startTime; i <= endTime; i = traceCopy.nextTimePointValue()) {
                        traceCopy.setSubTrace(i);

                        if (evaluate(futureLogicProperty.logicProperty, traceCopy)) {
                            return true;
                        }
                    }

                    return false;
                }

                //! Evaluate the given GlobalLogicPropertyAttribute
                /*!
                 * \param globalLogicProperty   The global logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool evaluateGlobalLogicProperty(const GlobalLogicPropertyAttribute &globalLogicProperty,
                                                 const T &lhsLogicProperty) const {
                    unsigned long startTime = globalLogicProperty.startTimepoint;
                    unsigned long endTime   = globalLogicProperty.endTimepoint;

                    SpatialTemporalTrace traceCopy(trace);

                    for (unsigned long i = startTime; i <= endTime; i = traceCopy.nextTimePointValue()) {
                        traceCopy.setSubTrace(i);

                        if (!evaluate(globalLogicProperty.logicProperty, traceCopy)) {
                            return false;
                        }
                    }

                    return true;
                }

                //! Evaluate the given NextLogicPropertyAttribute
                /*!
                 * \param nextLogicProperty     The next logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool evaluateNextLogicProperty(const NextLogicPropertyAttribute &nextLogicProperty,
                                               const T &lhsLogicProperty) const {
                    return evaluateNextKLogicProperty(nextLogicProperty.logicProperty, trace, 1);
                }

                //! Evaluate the given NextKLogicPropertyAttribute 
                /*!
                 * \param nextKLogicProperty    The next "k" logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 */
                template <typename T>
                bool evaluateNextKLogicProperty(const NextKLogicPropertyAttribute &nextKLogicProperty,
                                                const T &lhsLogicProperty) const {
                    return evaluateNextKLogicProperty(nextKLogicProperty.logicProperty, trace,
                                                      nextKLogicProperty.nrOfTimepointsAhead);
                }
                
                //! Evaluate the given NextKLogicPropertyAttribute
                /*!
                 * \param logicProperty         The logic property enclosed by the next "k" logic property
                 * \param lhsLogicProperty      The left hand side logic property
                 * \param kValue                The value of "k"
                 */
                template <typename T>
                bool evaluateNextKLogicProperty(const LogicPropertyAttributeType &logicProperty,
                                                const T &lhsLogicProperty, unsigned long kValue) const {
                    SpatialTemporalTrace subTrace(trace.subTrace(kValue));

                    return evaluate(logicProperty, subTrace);
                }

                //! Evaluate the logic property considering the given spatial temporal trace
                /*!
                 * \param logicProperty The logic property
                 * \param trace         The given spatial temporal trace
                 */
                bool evaluate(const LogicPropertyAttributeType &logicProperty,
                              const SpatialTemporalTrace &trace) const {
                    return boost::apply_visitor(LogicPropertyVisitor(trace, typeSemanticsTable),
                                                logicProperty, evaluationLogicProperty);
                }

                //! Evaluate the logic property considering the given spatial temporal trace
                /*!
                 * \param primaryLogicProperty  The primary logic property
                 * \param trace                 The given spatial temporal trace
                 */
                bool evaluate(const PrimaryLogicPropertyAttributeType &primaryLogicProperty,
                              const SpatialTemporalTrace &trace) const {
                    return boost::apply_visitor(
                        LogicPropertyVisitor(trace, typeSemanticsTable),
                        primaryLogicProperty,
                        evaluationLogicProperty
                    );
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
                        LogicPropertyAttributeType precedingEvaluationLogicProperty(
                            constructEvaluationLogicProperty(
                                logicProperty,
                                precedingEvaluationLogicProperties
                            )
                        );

                        truthValue = boost::apply_visitor(LogicPropertyVisitor(trace, typeSemanticsTable, truthValue),
                                                          nextLogicProperty, precedingEvaluationLogicProperty);

                        precedingEvaluationLogicProperties.push_back(nextLogicProperty);
                    }

                    return truthValue;
                }

                //! Construct a new logic property attribute using the evaluation logic properties
                /*!
                 * \param logicProperty             The logic property containing the currently evaluated logic
                 *                                  subproperty
                 * \param evaluationLogicProperties The logic properties preceding the currently evaluated logic
                 *                                  subproperty
                 */
                LogicPropertyAttribute constructEvaluationLogicProperty(const LogicPropertyAttribute &logicProperty,
                                                                        const std::vector<LogicPropertyAttributeType>
                                                                        &evaluationLogicProperties) const {
                    return LogicPropertyAttribute(
                        logicProperty.firstLogicProperty,
                        evaluationLogicProperties
                    );
                }

                //! Evaluate the preceding logic properties considering the interval [startTime, endTime)
                /*!
                 * \param startTime                 The considered start time value
                 * \param endTime                   The considered end time value (exclusive)
                 * \param precedingLogicProperties  The preceding logic properties
                 */
                bool evaluatePrecedingLogicProperties(unsigned long startTime, unsigned long endTime,
                                                      const LogicPropertyAttributeType
                                                      &precedingLogicProperties) const {
                    SpatialTemporalTrace traceCopy(trace);

                    for (unsigned long i = startTime; i < endTime; i = traceCopy.nextTimePointValue()) {
                        traceCopy.setSubTrace(i);

                        if (!evaluate(precedingLogicProperties, traceCopy)) {
                            return false;
                        }
                    }

                    return true;
                }

                //! Evaluate the temporal numeric measure considering the given spatial temporal trace
                /*!
                 * \param temporalNumericMeasure    The given temporal numeric measure
                 * \param trace                     The given spatial temporal trace
                 * \param timePointIndex            The index of the considered starting timepoint from the trace
                 */
                double evaluateTemporalNumericMeasure(const TemporalNumericMeasureType &temporalNumericMeasure,
                                                      const SpatialTemporalTrace &trace,
                                                      unsigned int timePointIndex = 0) const {
                    SpatialTemporalTrace subTrace(trace.subTrace(timePointIndex));

                    return (
                        boost::apply_visitor(TemporalNumericVisitor(subTrace, typeSemanticsTable),
                                             temporalNumericMeasure)
                    );
                }

                //! Print a warning message regarding the exception and return false
                /*!
                 * \param message   The exception message
                 */
                bool printExceptionMessage(const std::string &message) const {
                    std::string detailedMessage = message + WRN_OUTPUT_SEPARATOR + WRN_LOGIC_PROPERTY_EVAL_FALSE;

                    ConsolePrinter::printWarningMessage(detailedMessage);

                    return false;
                }

        };

    };

};


#endif
