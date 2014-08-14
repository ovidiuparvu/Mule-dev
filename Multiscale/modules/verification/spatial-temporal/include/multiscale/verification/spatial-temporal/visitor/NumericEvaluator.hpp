#ifndef NUMERICEVALUATOR_HPP
#define NUMERICEVALUATOR_HPP

#include "multiscale/util/Numeric.hpp"

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

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
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
                            return (secondValue != 0) ? (firstValue / secondValue)
                                                      : 0;

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

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

                //! Evaluate the given unary statistical measure expression
                /*!
                 * \param unaryStatisticalMeasure   The unary statistical measure type
                 * \param values                    The considered collection of values
                 */
                static double evaluate(const UnaryStatisticalMeasureType &unaryStatisticalMeasure,
                                       const std::vector<double> &values) {
                    switch (unaryStatisticalMeasure) {
                        case UnaryStatisticalMeasureType::Avg:
                            return Numeric::average(values);
                            break;

                        case UnaryStatisticalMeasureType::Count:
                            return static_cast<double>(values.size());
                            break;

                        case UnaryStatisticalMeasureType::Geomean:
                            return Numeric::geometricMean(values);
                            break;

                        case UnaryStatisticalMeasureType::Harmean:
                            return Numeric::harmonicMean(values);
                            break;

                        case UnaryStatisticalMeasureType::Kurt:
                            return Numeric::kurtosis(values);
                            break;

                        case UnaryStatisticalMeasureType::Max:
                            return Numeric::maximum(values);
                            break;

                        case UnaryStatisticalMeasureType::Median:
                            return Numeric::median(values);
                            break;

                        case UnaryStatisticalMeasureType::Min:
                            return Numeric::minimum(values);
                            break;

                        case UnaryStatisticalMeasureType::Mode:
                            return Numeric::mode(values);
                            break;

                        case UnaryStatisticalMeasureType::Product:
                            return Numeric::product(values);
                            break;

                        case UnaryStatisticalMeasureType::Skew:
                            return Numeric::skew(values);
                            break;

                        case UnaryStatisticalMeasureType::Stdev:
                            return Numeric::standardDeviation(values);
                            break;

                        case UnaryStatisticalMeasureType::Sum:
                            return Numeric::sum(values);
                            break;

                        case UnaryStatisticalMeasureType::Var:
                            return Numeric::variance(values);
                            break;

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
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
                static double evaluate(const BinaryStatisticalQuantileMeasureType &ternarySubset, const std::vector<double> &values,
                                       double parameter) {
                    switch (ternarySubset) {
                        case BinaryStatisticalQuantileMeasureType::Percentile:
                            return Numeric::percentile(values, parameter);

                        case BinaryStatisticalQuantileMeasureType::Quartile:
                            return Numeric::quartile(values, parameter);

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
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
                static double evaluate(const BinaryStatisticalMeasureType &quaternarySubset,
                                       const std::vector<double> &values1, const std::vector<double> &values2) {
                    switch (quaternarySubset) {
                        case BinaryStatisticalMeasureType::Covar:
                            return Numeric::covariance(values1, values2);

                        default:
                            MS_throw(SpatialTemporalException, multiscale::ERR_UNDEFINED_ENUM_VALUE);
                    }

                    // Line added to avoid "control reaches end of non-void function" warnings
                    return 0.0;
                }

        };

    };

};


#endif
