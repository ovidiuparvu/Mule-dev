#ifndef TEMPORALNUMERICVISITOR_HPP
#define TEMPORALNUMERICVISITOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericEvaluator.hpp"

#include <boost/variant.hpp>

#include <string>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class for evaluating temporal numeric measures
        class TemporalNumericVisitor : public boost::static_visitor<double> {

            private:

                SpatialTemporalTrace
                    &trace;                         /*!< The considered spatial temporal trace */
                const MultiscaleArchitectureGraph
                    &multiscaleArchitectureGraph;   /*!< The considered multiscale architecture graph */

            public:

                TemporalNumericVisitor(SpatialTemporalTrace &trace,
                                       const MultiscaleArchitectureGraph &multiscaleArchitectureGraph)
                                       : trace(trace), multiscaleArchitectureGraph(multiscaleArchitectureGraph) {}

                //! Overloading the "()" operator for the TemporalNumericMeasureAttribute alternative
                /*!
                 * \param temporalNumericMeasure    The temporal numeric measure
                 */
                double
                operator()(const TemporalNumericMeasureAttribute &temporalNumericMeasure) const {
                    return evaluate(temporalNumericMeasure.temporalNumericMeasure);
                }

                //! Overloading the "()" operator for the real number alternative
                /*!
                 * \param realNumber The real number
                 */
                double
                operator()(double realNumber) const {
                    return realNumber;
                }

                //! Overloading the "()" operator for the NumericStateVariableAttribute alternative
                /*!
                 * \param numericStateVariable  The numeric state variable
                 */
                double
                operator()(const NumericStateVariableAttribute &numericStateVariable) const {
                    // Retrieve a reference to the current time point in the trace
                    TimePoint &currentTimePoint = trace.getTimePointReference(0);

                    // Return the value of the numeric state variable
                    return (
                        NumericStateVariableEvaluator::evaluate(
                            numericStateVariable,
                            currentTimePoint,
                            multiscaleArchitectureGraph
                        )
                    );
                }

                //! Overloading the "()" operator for the NumericStatisticalMeasureAttribute alternative
                /*!
                 * \param numericStatisticalMeasure  The numeric statistical measure attribute
                 */
                double
                operator()(const NumericStatisticalMeasureAttribute &numericStatisticalMeasure) const {
                    return evaluateNumericStatisticalMeasure(
                        numericStatisticalMeasure.numericStatisticalMeasure
                    );
                }

                //! Overloading the "()" operator for the UnaryNumericTemporalAttribute alternative
                /*!
                 * \param unaryNumericTemporalMeasure  The unary numeric temporal measure
                 */
                double
                operator()(const UnaryNumericTemporalAttribute &unaryNumericTemporalMeasure) const {
                    UnaryNumericMeasureType unaryNumericMeasureType =
                        unaryNumericTemporalMeasure.unaryNumericMeasure.unaryNumericMeasureType;

                    double numericMeasure = evaluate(unaryNumericTemporalMeasure.temporalNumericMeasure);

                    return (
                        NumericEvaluator::evaluate(
                            unaryNumericMeasureType,
                            numericMeasure
                        )
                    );
                }

                //! Overloading the "()" operator for the BinaryNumericTemporalAttribute alternative
                /*!
                 * \param binaryNumericTemporalMeasure  The binary numeric temporal measure
                 */
                double
                operator()(const BinaryNumericTemporalAttribute &binaryNumericTemporalMeasure) const {
                    BinaryNumericMeasureType binaryNumericMeasureType =
                        binaryNumericTemporalMeasure.binaryNumericMeasure.binaryNumericMeasureType;

                    double firstNumericMeasure  =
                        evaluate(binaryNumericTemporalMeasure.firstTemporalNumericMeasure);
                    double secondNumericMeasure =
                        evaluate(binaryNumericTemporalMeasure.secondTemporalNumericMeasure);

                    return (
                        NumericEvaluator::evaluate(
                            binaryNumericMeasureType,
                            firstNumericMeasure,
                            secondNumericMeasure
                        )
                    );
                }

                //! Overloading the "()" operator for the UnaryStatisticalNumericAttribute alternative
                /*!
                 * \param unaryStatisticalNumericAttribute  The unary statistical numeric attribute
                 */
                double
                operator()(const UnaryStatisticalNumericAttribute &unaryStatisticalNumericAttribute) const {
                    std::vector<double> numericMeasureValues =
                        evaluateNumericMeasureCollection(
                            unaryStatisticalNumericAttribute.numericMeasureCollection
                        );

                    return (
                        NumericEvaluator::evaluate(
                            unaryStatisticalNumericAttribute.unaryStatisticalMeasure.unaryStatisticalMeasureType,
                            numericMeasureValues
                        )
                    );
                }

                //! Overloading the "()" operator for the BinaryStatisticalNumericAttribute alternative
                /*!
                 * \param binaryStatisticalNumericAttribute  The binary statistical numeric attribute
                 */
                double
                operator()(const BinaryStatisticalNumericAttribute &binaryStatisticalNumericAttribute) const {
                    std::vector<double> firstNumericMeasureValues =
                        evaluateNumericMeasureCollection(
                            binaryStatisticalNumericAttribute.firstNumericMeasureCollection
                        );
                    std::vector<double> secondNumericMeasureValues =
                        evaluateNumericMeasureCollection(
                            binaryStatisticalNumericAttribute.secondNumericMeasureCollection
                        );

                    return (
                        NumericEvaluator::evaluate(
                            binaryStatisticalNumericAttribute.binaryStatisticalMeasure.binaryStatisticalMeasureType,
                            firstNumericMeasureValues,
                            secondNumericMeasureValues
                        )
                    );
                }


                //! Overloading the "()" operator for the BinaryStatisticalQuantileNumericAttribute alternative
                /*!
                 * \param binaryStatisticalQuantileNumericAttribute The binary statistical quantile numeric attribute
                 */
                double
                operator()(const BinaryStatisticalQuantileNumericAttribute
                           &binaryStatisticalQuantileNumericAttribute) const {
                    std::vector<double> numericMeasureValues =
                        evaluateNumericMeasureCollection(
                            binaryStatisticalQuantileNumericAttribute.numericMeasureCollection
                        );

                    return (
                        NumericEvaluator::evaluate(
                            binaryStatisticalQuantileNumericAttribute.binaryStatisticalQuantileMeasure.
                                binaryStatisticalQuantileMeasureType,
                            numericMeasureValues,
                            binaryStatisticalQuantileNumericAttribute.parameter
                        )
                    );
                }


            private:

                //! Evaluate the given temporal numeric measure considering the trace field
                /*!
                 * \param temporalNumericMeasure    The given temporal numeric measure
                 */
                double
                evaluate(const TemporalNumericMeasureType &temporalNumericMeasure) const {
                    return (
                        boost::apply_visitor(
                            TemporalNumericVisitor(
                                trace,
                                multiscaleArchitectureGraph
                            ),
                            temporalNumericMeasure
                        )
                    );
                }

                //! Evaluate the given numeric statistical measure considering the trace field
                /*!
                 * \param numericStatisticalMeasure The given numeric statistical measure
                 */
                double
                evaluateNumericStatisticalMeasure(const NumericStatisticalMeasureType
                                                  &numericStatisticalMeasure) const {
                    return (
                        boost::apply_visitor(
                            TemporalNumericVisitor(
                                trace,
                                multiscaleArchitectureGraph
                            ),
                            numericStatisticalMeasure
                        )
                    );
                }

                //! Evaluate the given numeric measure collection considering the trace field
                /*!
                 * \param numericMeasureCollection  The given numeric measure collection
                 */
                std::vector<double>
                evaluateNumericMeasureCollection(const NumericMeasureCollectionAttribute
                                                 &numericMeasureCollection) const;

        };

    };

};


// NumericMeasureCollectionEvaluator dependent includes

// The NumericVisitor.hpp file is included instead of the NumericMeasureCollectionEvaluator.hpp file
// to avoid include circular dependency issues. Since the NumericVisitor.hpp file includes
// the NumericMeasureCollectionEvaluator.hpp file this is fine.
#include "multiscale/verification/spatial-temporal/visitor/NumericVisitor.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericMeasureCollectionVisitor.hpp"


// Implement the NumericMeasureCollectionVisitor dependent methods

inline std::vector<double>
multiscale::verification::TemporalNumericVisitor::evaluateNumericMeasureCollection(
    const NumericMeasureCollectionAttribute &numericMeasureCollection
) const {
    return (
        boost::apply_visitor(
            NumericMeasureCollectionVisitor(
                trace,
                multiscaleArchitectureGraph
            ),
            numericMeasureCollection.numericMeasureCollection
        )
    );
}


#endif
