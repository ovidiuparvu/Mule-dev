#ifndef NUMERICEVALUATOR_HPP
#define NUMERICEVALUATOR_HPP

#include "multiscale/util/Numeric.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"

#include <cmath>


namespace multiscale {

    namespace verification {

        //! Class for evaluating numeric expressions
        class NumericEvaluator {

            public:

                //! Evaluate the given unary numeric expression
                /*!
                 * \param unaryNumericMeasure   The unary numeric measure type
                 * \param value                 The value for which the unary numeric measure is applied
                 */
                template <typename T>
                static double evaluate(const UnaryNumericMeasureType &unaryNumericMeasure, T value) {
                    switch (unaryNumericMeasure) {
                        case UnaryNumericMeasureType::Abs:
                            return (std::fabs(value));

                        case UnaryNumericMeasureType::Ceil:
                            return (std::ceil(value));

                        case UnaryNumericMeasureType::Floor:
                            return (std::floor(value));

                        case UnaryNumericMeasureType::Round:
                            return (std::round(value));

                        case UnaryNumericMeasureType::Sign:
                            return (multiscale::Numeric::sign(value));

                        case UnaryNumericMeasureType::Sqrt:
                            return (std::sqrt(value));

                        case UnaryNumericMeasureType::Trunc:
                            return (std::trunc(value));
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

                //! Evaluate the given binary numeric expression
                /*!
                 * \param binaryNumericMeasure  The binary numeric measure type
                 * \param firstValue            The first value for which the binary numeric measure is applied
                 * \param secondValue           The second value for which the binary numeric measure is applied
                 */
                template <typename T>
                static double evaluate(const BinaryNumericMeasureType &binaryNumericMeasure, T firstValue, T secondValue) {
                    switch (binaryNumericMeasure) {
                        case BinaryNumericMeasureType::Add:
                            return (firstValue + secondValue);

                        case BinaryNumericMeasureType::Div:
                            return (firstValue / secondValue);

                        case BinaryNumericMeasureType::Log:
                            return (Numeric::log(firstValue, secondValue));

                        case BinaryNumericMeasureType::Mod:
                            return (std::fmod(firstValue, secondValue));

                        case BinaryNumericMeasureType::Multiply:
                            return (firstValue * secondValue);

                        case BinaryNumericMeasureType::Power:
                            return (std::pow(firstValue, secondValue));

                        case BinaryNumericMeasureType::Subtract:
                            return (firstValue - secondValue);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

                //! Evaluate the given unary subset measure expression
                /*!
                 * \param unarySubset   The unary subset measure type
                 * \param timePoint     The considered timePoint
                 */
                static double evaluate(const UnarySubsetMeasureType &unarySubset, const TimePoint &timePoint) {
                    switch (unarySubset) {
                        case UnarySubsetMeasureType::Count:
                            return timePoint.numberOfSpatialEntities();

                        case UnarySubsetMeasureType::Clusteredness:
                            return timePoint.avgClusteredness();

                        case UnarySubsetMeasureType::Density:
                            return timePoint.avgDensity();

                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

                //! Evaluate the given binary subset measure expression
                /*!
                 * \param binarySubset  The binary subset measure type
                 * \param values        The considered values
                 */
                static double evaluate(const BinarySubsetMeasureType &binarySubset, const std::vector<double> &values) {
                    switch (binarySubset) {
                        case BinarySubsetMeasureType::Avg:
                            return Numeric::average(values);

                        case BinarySubsetMeasureType::Geomean:
                            return Numeric::geometricMean(values);

                        case BinarySubsetMeasureType::Harmean:
                            return Numeric::harmonicMean(values);

                        case BinarySubsetMeasureType::Kurt:
                            return Numeric::kurtosis(values);

                        case BinarySubsetMeasureType::Max:
                            return Numeric::maximum(values);

                        case BinarySubsetMeasureType::Median:
                            return Numeric::median(values);

                        case BinarySubsetMeasureType::Min:
                            return Numeric::minimum(values);

                        case BinarySubsetMeasureType::Mode:
                            return Numeric::mode(values);

                        case BinarySubsetMeasureType::Product:
                            return Numeric::product(values);

                        case BinarySubsetMeasureType::Skew:
                            return Numeric::skew(values);

                        case BinarySubsetMeasureType::Stdev:
                            return Numeric::standardDeviation(values);

                        case BinarySubsetMeasureType::Sum:
                            return Numeric::sum(values);

                        case BinarySubsetMeasureType::Var:
                            return Numeric::variance(values);

                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

                //! Evaluate the given ternary subset measure expression
                /*!
                 * \param ternarySubset The ternary subset measure type
                 * \param values        The considered values
                 * \param parameter     The parameter used by the ternary subset measure
                 */
                static double evaluate(const TernarySubsetMeasureType &ternarySubset, const std::vector<double> &values,
                                       double parameter) {
                    switch (ternarySubset) {
                        case TernarySubsetMeasureType::Percentile:
                            return Numeric::percentile(values, parameter);

                        case TernarySubsetMeasureType::Quartile:
                            return Numeric::quartile(values, parameter);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

                //! Evaluate the given quaternary subset measure expression
                /*!
                 * \param quaternarySubset  The quaternary subset measure type
                 * \param values1           The first collection of considered values
                 * \param values2           The second collection of considered values
                 */
                static double evaluate(const QuaternarySubsetMeasureType &quaternarySubset,
                                       const std::vector<double> &values1, const std::vector<double> &values2) {
                    switch (quaternarySubset) {
                        case QuaternarySubsetMeasureType::Covar:
                            return Numeric::covariance(values1, values2);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

        };

    };

};

#endif
