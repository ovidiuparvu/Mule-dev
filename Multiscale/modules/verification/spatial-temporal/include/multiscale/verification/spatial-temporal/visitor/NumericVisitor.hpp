#ifndef NUMERICVISITOR_HPP
#define NUMERICVISITOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ComparatorEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericStateVariableEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/TimePointEvaluator.hpp"

#include <boost/variant.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for evaluating numeric measures
        class NumericVisitor : public boost::static_visitor<double> {

            private:

                TimePoint
                    &timePoint;                     /*!< The considered timepoint */
                const MultiscaleArchitectureGraph
                    &multiscaleArchitectureGraph;   /*!< The considered multiscale architecture graph */

            public:

                NumericVisitor(TimePoint &timePoint,
                               const MultiscaleArchitectureGraph &multiscaleArchitectureGraph)
                               : timePoint(timePoint), multiscaleArchitectureGraph(multiscaleArchitectureGraph) {}

                //! Overloading the "()" operator for the NumericMeasureAttribute alternative
                /*!
                 * \param numericMeasure  The numeric measure
                 */
                double
                operator()(const NumericMeasureAttribute &numericMeasure) const {
                    return evaluate(numericMeasure.numericMeasure);
                }

                //! Overloading the "()" operator for the PrimaryNumericMeasureAttribute alternative
                /*!
                 * \param primaryNumericMeasure The primary numeric measure
                 */
                double
                operator()(const PrimaryNumericMeasureAttribute &primaryNumericMeasure) const {
                    return evaluatePrimaryNumericMeasure(primaryNumericMeasure.primaryNumericMeasure);
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
                    // Return the value of the numeric state variable
                    return (
                        NumericStateVariableEvaluator::evaluate(
                            numericStateVariable,
                            timePoint,
                            multiscaleArchitectureGraph
                        )
                    );
                }

                //! Overloading the "()" operator for the NumericSpatialAttribute alternative
                /*!
                 * \param numericSpatialMeasure  The numeric spatial measure attribute
                 */
                double
                operator()(const NumericSpatialMeasureAttribute &numericSpatialMeasure) const {
                    return evaluateNumericSpatialMeasure(numericSpatialMeasure.numericSpatialMeasure);
                }

                //! Overloading the "()" operator for the UnaryNumericNumericAttribute alternative
                /*!
                 * \param unaryNumericNumericMeasure  The unary numeric numeric measure
                 */
                double
                operator()(const UnaryNumericNumericAttribute &unaryNumericNumericMeasure) const {
                    UnaryNumericMeasureType unaryNumericMeasureType
                        = unaryNumericNumericMeasure.unaryNumericMeasure.unaryNumericMeasureType;

                    double numericMeasure = evaluate(unaryNumericNumericMeasure.numericMeasure);

                    return (
                        NumericEvaluator::evaluate(
                            unaryNumericMeasureType,
                            numericMeasure
                        )
                    );
                }

                //! Overloading the "()" operator for the BinaryNumericNumericAttribute alternative
                /*!
                 * \param binaryNumericNumericMeasure  The binary numeric numeric measure
                 */
                double
                operator()(const BinaryNumericNumericAttribute &binaryNumericNumericMeasure) const {
                    BinaryNumericMeasureType binaryNumericMeasureType
                        = binaryNumericNumericMeasure.binaryNumericMeasure.binaryNumericMeasureType;

                    double firstNumericMeasure  = evaluate(binaryNumericNumericMeasure.firstNumericMeasure);
                    double secondNumericMeasure = evaluate(binaryNumericNumericMeasure.secondNumericMeasure);

                    return (
                        NumericEvaluator::evaluate(
                            binaryNumericMeasureType,
                            firstNumericMeasure,
                            secondNumericMeasure
                        )
                    );
                }

                //! Overloading the "()" operator for the UnaryStatisticalSpatialAttribute alternative
                /*!
                 * \param unaryStatisticalSpatialAttribute  The unary statistical spatial attribute
                 */
                double
                operator()(const UnaryStatisticalSpatialAttribute &unaryStatisticalSpatialAttribute) const;

                //! Overloading the "()" operator for the BinaryStatisticalSpatialAttribute alternative
                /*!
                 * \param binaryStatisticalSpatialAttribute  The binary statistical spatial attribute
                 */
                double
                operator()(const BinaryStatisticalSpatialAttribute &binaryStatisticalSpatialAttribute) const;


                //! Overloading the "()" operator for the BinaryStatisticalQuantileSpatialAttribute alternative
                /*!
                 * \param binaryStatisticalQuantileSpatialAttribute The binary statistical quantile spatial attribute
                 */
                double
                operator()(const BinaryStatisticalQuantileSpatialAttribute
                           &binaryStatisticalQuantileSpatialAttribute) const;


            private:

                //! Evaluate the given numeric measure considering the timePoint field
                /*!
                 * \param numericMeasure    The given numeric measure
                 */
                double
                evaluate(const NumericMeasureType &numericMeasure) const {
                    return (
                        boost::apply_visitor(
                            NumericVisitor(
                                timePoint,
                                multiscaleArchitectureGraph
                            ),
                            numericMeasure
                        )
                    );
                }

                //! Evaluate the given primary numeric measure considering the timePoint field
                /*!
                 * \param primaryNumericMeasure The given primary numeric measure
                 */
                double
                evaluatePrimaryNumericMeasure(const PrimaryNumericMeasureAttributeType &primaryNumericMeasure) const {
                    return (
                        boost::apply_visitor(
                            NumericVisitor(
                                timePoint,
                                multiscaleArchitectureGraph
                            ),
                            primaryNumericMeasure
                        )
                    );
                }

                //! Evaluate the given numeric spatial measure considering the timePoint field
                /*!
                 * \param numericSpatialMeasure The given numeric spatial measure
                 */
                double
                evaluateNumericSpatialMeasure(const NumericSpatialMeasureType &numericSpatialMeasure) const {
                    return (
                        boost::apply_visitor(
                            NumericVisitor(
                                timePoint,
                                multiscaleArchitectureGraph
                            ),
                            numericSpatialMeasure
                        )
                    );
                }

        };

    };

};


// NumericVisitor dependent includes added here to avoid include circular dependency issues

#include "multiscale/verification/spatial-temporal/visitor/ConstraintVisitor.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericMeasureCollectionVisitor.hpp"

// Implement NumericVisitor methods which are dependent on the ConstraintVisitor and
// NumericMeasureCollectionEvaluator classes

inline double
multiscale::verification::NumericVisitor::operator()(const UnaryStatisticalSpatialAttribute
                                                     &unaryStatisticalSpatialAttribute) const {
    std::vector<double> spatialMeasureValues =
        NumericMeasureCollectionEvaluator::evaluateSpatialMeasureCollection(
            timePoint,
            multiscaleArchitectureGraph,
            unaryStatisticalSpatialAttribute.spatialMeasureCollection
        );

    return (
        NumericEvaluator::evaluate(
            unaryStatisticalSpatialAttribute.unaryStatisticalMeasure.unaryStatisticalMeasureType,
            spatialMeasureValues
        )
    );
}

inline double
multiscale::verification::NumericVisitor::operator()(const BinaryStatisticalSpatialAttribute
                                                     &binaryStatisticalSpatialAttribute) const {
    std::vector<double> firstSpatialMeasureValues =
        NumericMeasureCollectionEvaluator::evaluateSpatialMeasureCollection(
            timePoint,
            multiscaleArchitectureGraph,
            binaryStatisticalSpatialAttribute.firstSpatialMeasureCollection
        );
    std::vector<double> secondSpatialMeasureValues =
        NumericMeasureCollectionEvaluator::evaluateSpatialMeasureCollection(
            timePoint,
            multiscaleArchitectureGraph,
            binaryStatisticalSpatialAttribute.secondSpatialMeasureCollection
        );

    return (
        NumericEvaluator::evaluate(
            binaryStatisticalSpatialAttribute.binaryStatisticalMeasure.binaryStatisticalMeasureType,
            firstSpatialMeasureValues,
            secondSpatialMeasureValues
        )
    );
}

inline double
multiscale::verification::NumericVisitor::operator()(const BinaryStatisticalQuantileSpatialAttribute
                                                     &binaryStatisticalQuantileSpatialAttribute) const {
    std::vector<double> spatialMeasureValues =
        NumericMeasureCollectionEvaluator::evaluateSpatialMeasureCollection(
            timePoint,
            multiscaleArchitectureGraph,
            binaryStatisticalQuantileSpatialAttribute.spatialMeasureCollection
        );

    return (
        NumericEvaluator::evaluate(
            binaryStatisticalQuantileSpatialAttribute.binaryStatisticalQuantileMeasure.
                binaryStatisticalQuantileMeasureType,
            spatialMeasureValues,
            binaryStatisticalQuantileSpatialAttribute.parameter
        )
    );
}


#endif
