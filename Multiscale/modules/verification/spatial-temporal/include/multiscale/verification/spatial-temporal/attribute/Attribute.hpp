#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/AttributeVisitor.hpp"

#include <boost/variant.hpp>
#include <list>


namespace multiscale {

	namespace verification {

		class Attribute {

			public:

				virtual ~Attribute() {};

				//! Evaluate the attribute considering the given truth value
				virtual bool evaluate(bool truthValue) const = 0;

				//! Evaluate a unary expression
				template <typename T>
				bool evaluateUnaryExpression(const T &unaryExpression) const {
					return boost::apply_visitor(AttributeVisitor(), unaryExpression);
				}

				//! Evaluate a n-ary expression
				template <typename T, typename U, typename V>
				bool evaluateNaryExpression(const T &firstExpression, const std::list<U> &nextExpressions,
											const V &evaluator) const {
					bool evaluationResult = evaluateFirstExpression(firstExpression);

					return evaluateNextExpressions(evaluationResult, nextExpressions, evaluator);
				}

				//! Evaluate a n-ary expression considering the given truth value
				template <typename T, typename U>
				bool evaluateNaryExpression(bool firstExpressionTruthValue, const std::list<T> &nextExpressions) const {
					return evaluateNextExpressions(firstExpressionTruthValue, nextExpressions);
				}

			private:

				//! Evaluate the first expression
				template <typename T>
				bool evaluateFirstExpression(const T &firstExpression) const {
					return boost::apply_visitor(AttributeVisitor(), firstExpression);
				}

				//! Evaluate the next expressions
				template <typename T, typename U>
				bool evaluateNextExpressions(bool evaluationResult, const std::list<T> &nextExpressions,
											 const U &evaluator) const {
					bool nextExpressionEvaluation = false;

					for (const auto &nextExpression : nextExpressions) {
						nextExpressionEvaluation = boost::apply_visitor(AttributeVisitor(), nextExpression);
						evaluationResult = evaluator(evaluationResult, nextExpressionEvaluation);
					}

					return evaluationResult;
				}

				//! Evaluate the next expressions
				template <typename T, typename U>
				bool evaluateNextExpressions(bool evaluationResult, const std::list<T> &nextExpressions) const {
					for (const auto &nextExpression : nextExpressions) {
						evaluationResult = boost::apply_visitor(AttributeVisitor(), nextExpression, evaluationResult);
					}

					return evaluationResult;
				}

		};

	};

};


#endif
