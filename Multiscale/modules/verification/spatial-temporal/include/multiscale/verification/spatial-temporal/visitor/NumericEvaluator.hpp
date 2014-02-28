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

                    // Line added to avoid warnings "control reaches end of non-void function"
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

                    // Line added to avoid warnings "control reaches end of non-void function"
                    return 0.0;
                }

        };

    };

};

#endif
