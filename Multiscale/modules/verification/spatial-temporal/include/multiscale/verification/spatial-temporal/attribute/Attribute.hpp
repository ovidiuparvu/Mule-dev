#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

/*
 *  TODO: Remove this file
 */

#include "multiscale/verification/spatial-temporal/attribute/AttributeVisitor.hpp"

#include <boost/variant.hpp>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class used to represent an attribute
        class Attribute {

            public:

                virtual ~Attribute() {};

                //! Evaluate the attribute
                virtual bool evaluate() const = 0;

                //! Evaluate the attribute considering the given truth value
                /*!
                 * \param truthValue The given truth value
                 */
                virtual bool evaluateConsideringTruthValue(const bool &truthValue) const {
                    return evaluate();
                }

                //! Evaluate a unary expression
                /*!
                 * \param unaryExpression   The unary expression
                 */
                template <typename T>
                bool evaluateUnaryExpression(const T &unaryExpression) const {
                    return evaluateExpression(unaryExpression);
                }

                //! Evaluate an n-ary expression considering the given evaluation functor
                /*!
                 * \param firstExpression   The first expression
                 * \param nextExpressions   The vector of next expressions
                 * \param evaluator         The functor used to evaluate two expressions
                 */
                template <typename T, typename U, typename V>
                bool evaluateNaryExpression(const T &firstExpression, const std::vector<U> &nextExpressions,
                                            const V &evaluator) const {
                    bool evaluationResult = evaluateExpression(firstExpression);

                    return evaluateNextExpressions(evaluationResult, nextExpressions, evaluator);
                }

                //! Evaluate an n-ary expression
                /*!
                 * \param firstExpression   The first expression
                 * \param nextExpressions   The vector of next expressions
                 */
                template <typename T, typename U>
                bool evaluateNaryExpression(const T &firstExpression, const std::vector<U> &nextExpressions) const {
                    AttributeTruthValue firstExpressionTruthValue = evaluateExpression(firstExpression);

                    return evaluateNextExpressions(firstExpressionTruthValue, nextExpressions);
                }

            private:

                //! Evaluate the given expression
                /*!
                 * \param expression The expression
                 */
                template <typename T>
                bool evaluateExpression(const T &expression) const {
                    return boost::apply_visitor(AttributeVisitor(), expression);
                }

                //! Evaluate the next expressions considering the given evaluation functor and evaluation result
                /*!
                 * \param evaluationResult  The evaluation result
                 * \param nextExpressions   The vector of next expressions
                 * \param evaluator         The functor used to evaluate two expressions
                 */
                template <typename T, typename U>
                bool evaluateNextExpressions(bool evaluationResult, const std::vector<T> &nextExpressions,
                                             const U &evaluator) const {
                    bool nextExpressionEvaluation = false;

                    for (const auto &nextExpression : nextExpressions) {
                        nextExpressionEvaluation = boost::apply_visitor(AttributeVisitor(), nextExpression);
                        evaluationResult = evaluator(evaluationResult, nextExpressionEvaluation);
                    }

                    return evaluationResult;
                }

                //! Evaluate the next expressions
                template <typename T>
                bool evaluateNextExpressions(AttributeTruthValue evaluationResult, const std::vector<T> &nextExpressions) const {
                    for (const auto &nextExpression : nextExpressions) {
                        evaluationResult = boost::apply_visitor(AttributeVisitor(), nextExpression, evaluationResult);
                    }

                    return boost::get<bool>(evaluationResult);
                }

        };

    };

};


#endif
