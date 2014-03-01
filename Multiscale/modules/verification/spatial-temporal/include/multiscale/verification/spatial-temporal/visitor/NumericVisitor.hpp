#ifndef NUMERICVISITOR_HPP
#define NUMERICVISITOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/visitor/ComparatorEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/visitor/NumericEvaluator.hpp"

#include <boost/variant.hpp>
#include <string>


namespace multiscale {

    namespace verification {

        //! Class for evaluating numeric measures
        class NumericVisitor : public boost::static_visitor<double> {

            private:

                TimePoint timePoint;  /*!< The considered timepoint */

            public:

                NumericVisitor(const TimePoint &timePoint) {
                    this->timePoint = timePoint;
                }

                //! Overloading the "()" operator for the NumericMeasureAttribute alternative
                /*!
                 * \param numericMeasure  The numeric measure
                 */
                double operator()(const NumericMeasureAttribute &numericMeasure) const {
                    return evaluate(numericMeasure);
                }

                //! Overloading the "()" operator for the real number alternative
                /*!
                 * \param realNumber The real number
                 */
                double operator()(double realNumber) const {
                    return realNumber;
                }

                //! Overloading the "()" operator for the NumericStateVariableAttribute alternative
                /*!
                 * \param numericStateVariable  The numeric state variable
                 */
                double operator()(const NumericStateVariableAttribute &numericStateVariable) const {
                    std::string name = numericStateVariable.stateVariable.name;

                    return timePoint.getNumericStateVariable(name);
                }

                //! Overloading the "()" operator for the NumericSpatialAttribute alternative
                /*!
                 * \param numericSpatialMeasure  The numeric spatial measure attribute
                 */
                double operator()(const NumericSpatialAttribute &numericSpatialMeasure) const {
                    // TODO: Implement
                    return 1.1;
                }

                //! Overloading the "()" operator for the UnaryNumericNumericAttribute alternative
                /*!
                 * \param unaryNumericNumericMeasure  The unary numeric numeric measure
                 */
                double operator()(const UnaryNumericNumericAttribute &unaryNumericNumericMeasure) const {
                    UnaryNumericMeasureType unaryNumericMeasureType = unaryNumericNumericMeasure.
                                                                      unaryNumericMeasure.
                                                                      unaryNumericMeasureType;

                    double numericMeasure = evaluate(unaryNumericNumericMeasure.numericMeasure);

                    return NumericEvaluator::evaluate(unaryNumericMeasureType, numericMeasure);
                }

                //! Overloading the "()" operator for the BinaryNumericNumericAttribute alternative
                /*!
                 * \param binaryNumericNumericMeasure  The binary numeric numeric measure
                 */
                double operator()(const BinaryNumericNumericAttribute &binaryNumericNumericMeasure) const {
                    BinaryNumericMeasureType binaryNumericMeasureType = binaryNumericNumericMeasure.
                                                                        binaryNumericMeasure.
                                                                        binaryNumericMeasureType;

                    double firstNumericMeasure  = evaluate(binaryNumericNumericMeasure.firstNumericMeasure);
                    double secondNumericMeasure = evaluate(binaryNumericNumericMeasure.secondNumericMeasure);

                    return NumericEvaluator::evaluate(binaryNumericMeasureType, firstNumericMeasure, secondNumericMeasure);
                }

                //! Overloading the "()" operator for the UnarySubsetAttribute alternative
                /*!
                 * \param unarySubset  The unary subset
                 */
                double operator()(const UnarySubsetAttribute &unarySubset) const {
                    // TODO: Implement
                    return 1.0;
                }

                //! Overloading the "()" operator for the BinarySubsetAttribute alternative
                /*!
                 * \param binarySubset  The binary subset
                 */
                double operator()(const BinarySubsetAttribute &binarySubset) const {
                    // TODO: Implement
                    return 1.0;
                }

                //! Overloading the "()" operator for the TernarySubsetAttribute alternative
                /*!
                 * \param ternarySubset  The ternary subset
                 */
                double operator()(const TernarySubsetAttribute &ternarySubset) const {
                    // TODO: Implement
                    return 1.0;
                }

                //! Overloading the "()" operator for the QuaternarySubsetAttribute alternative
                /*!
                 * \param quaternarySubset  The quaternary subset
                 */
                double operator()(const QuaternarySubsetAttribute &quaternarySubset) const {
                    // TODO: Implement
                    return 1.0;
                }

            private:

                //! Evaluate the given numeric measure considering the timePoint field
                /*!
                 * \param numericMeasure    Evaluate the given numeric measure
                 */
                double evaluate(const NumericMeasureAttributeType &numericMeasure) const {
                    return boost::apply_visitor(NumericVisitor(timePoint), numericMeasure);
                }

        };

    };

};


// NumericVisitor dependent includes

#include "multiscale/verification/spatial-temporal/visitor/ConstraintVisitor.hpp"


#endif
