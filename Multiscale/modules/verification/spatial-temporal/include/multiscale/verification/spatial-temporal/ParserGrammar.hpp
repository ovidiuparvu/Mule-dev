#ifndef PARSERGRAMMAR_HPP
#define PARSERGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/SynthesizedAttribute.hpp"
#include "multiscale/verification/spatial-temporal/handler/ErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/qi_and_predicate.hpp>

#include <string>


namespace multiscale {

    namespace verification {

    	// Namespace aliases
		namespace phoenix = boost::phoenix;
		namespace qi = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;

		// Create a lazy error handler function
		phoenix::function<ErrorHandler> const handleError = ErrorHandler();


        //! The grammar for parsing (P)BLSTL spatial-temporal logical queries
        template <typename Iterator>
        class ParserGrammar : public qi::grammar<Iterator, ProbabilisticLogicPropertyAttribute(), ascii::space_type> {

            private:

                qi::rule<Iterator, ProbabilisticLogicPropertyAttribute(), ascii::space_type>		probabilisticLogicPropertyRule;			/*!< The rule for parsing a probabilistic logic property */
                qi::rule<Iterator, LogicPropertyAttribute(), ascii::space_type>						logicPropertyRule;						/*!< The rule for parsing a logic property */
                qi::rule<Iterator, PrimaryLogicPropertyAttribute(), ascii::space_type>				primaryLogicPropertyRule;				/*!< The rule for parsing a primary logic property */

                qi::rule<Iterator, DifferenceAttribute(), ascii::space_type>						differenceRule;							/*!< The rule for parsing a difference attribute */
                qi::rule<Iterator, NumericNumericComparisonAttribute(), ascii::space_type>			numericNumericComparisonRule;			/*!< The rule for parsing a numeric numeric comparison */
                qi::rule<Iterator, NumericSpatialNumericComparisonAttribute(), ascii::space_type>	numericSpatialNumericComparisonRule;	/*!< The rule for parsing a numeric spatial numeric comparison */

                qi::rule<Iterator, NotLogicPropertyAttribute(), ascii::space_type>					notLogicPropertyRule;					/*!< The rule for parsing a "not" logic property */
                qi::rule<Iterator, FutureLogicPropertyAttribute(), ascii::space_type>				futureLogicPropertyRule;				/*!< The rule for parsing a "future" logic property */
                qi::rule<Iterator, GlobalLogicPropertyAttribute(), ascii::space_type>				globalLogicPropertyRule;				/*!< The rule for parsing a "global" logic property */
                qi::rule<Iterator, NextLogicPropertyAttribute(), ascii::space_type>					nextLogicPropertyRule;					/*!< The rule for parsing an "next" logic property */
                qi::rule<Iterator, NextKLogicPropertyAttribute(), ascii::space_type>				nextKLogicPropertyRule;					/*!< The rule for parsing an "next K" logic property */
                qi::rule<Iterator, AndLogicPropertyAttribute(), ascii::space_type>					andLogicPropertyRule;					/*!< The rule for parsing an "and" logic property */
                qi::rule<Iterator, OrLogicPropertyAttribute(), ascii::space_type>					orLogicPropertyRule;					/*!< The rule for parsing an "or" logic property */
                qi::rule<Iterator, ImplicationLogicPropertyAttribute(), ascii::space_type>			implicationLogicPropertyRule;			/*!< The rule for parsing an "implication" logic property */
                qi::rule<Iterator, EquivalenceLogicPropertyAttribute(), ascii::space_type>			equivalenceLogicPropertyRule;			/*!< The rule for parsing an "equivalence" logic property */
                qi::rule<Iterator, UntilLogicPropertyAttribute(), ascii::space_type>				untilLogicPropertyRule;					/*!< The rule for parsing an "until" logic property */

                qi::rule<Iterator, NumericMeasureAttribute(), ascii::space_type>					numericMeasureRule;						/*!< The rule for parsing a numeric measure */
                qi::rule<Iterator, UnaryNumericNumericAttribute(), ascii::space_type>				unaryNumericNumericRule;				/*!< The rule for parsing a unary numeric numeric attribute */
                qi::rule<Iterator, BinaryNumericNumericAttribute(), ascii::space_type>				binaryNumericNumericRule;				/*!< The rule for parsing a binary numeric numeric attribute */

                qi::rule<Iterator, NumericSpatialAttribute(), ascii::space_type>					numericSpatialRule;						/*!< The rule for parsing a numeric spatial measure */
                qi::rule<Iterator, UnarySubsetAttribute(), ascii::space_type>						unarySubsetRule;						/*!< The rule for parsing a unary subset */
                qi::rule<Iterator, BinarySubsetAttribute(), ascii::space_type>						binarySubsetRule;						/*!< The rule for parsing a binary subset */
                qi::rule<Iterator, TernarySubsetAttribute(), ascii::space_type>						ternarySubsetRule;						/*!< The rule for parsing a ternary subset */
                qi::rule<Iterator, QuaternarySubsetAttribute(), ascii::space_type>					quaternarySubsetRule;					/*!< The rule for parsing a quaternary subset */
                qi::rule<Iterator, UnaryNumericSpatialAttribute(), ascii::space_type>				unaryNumericSpatialRule;				/*!< The rule for parsing a unary numeric spatial attribute */
                qi::rule<Iterator, BinaryNumericSpatialAttribute(), ascii::space_type>				binaryNumericSpatialRule;				/*!< The rule for parsing a binary numeric spatial attribute */

                qi::rule<Iterator, UnarySubsetMeasureAttribute(), ascii::space_type>				unarySubsetMeasureRule;					/*!< The rule for parsing a unary subset measure */
                qi::rule<Iterator, BinarySubsetMeasureAttribute(), ascii::space_type>				binarySubsetMeasureRule;				/*!< The rule for parsing a binary subset measure */
                qi::rule<Iterator, TernarySubsetMeasureAttribute(), ascii::space_type>				ternarySubsetMeasureRule;				/*!< The rule for parsing a ternary subset measure */
                qi::rule<Iterator, QuaternarySubsetMeasureAttribute(), ascii::space_type>			quaternarySubsetMeasureRule;			/*!< The rule for parsing a quaternary subset measure */

                qi::rule<Iterator, UnaryNumericMeasureAttribute(), ascii::space_type>				unaryNumericMeasureRule;				/*!< The rule for parsing a unary numeric measure */
                qi::rule<Iterator, BinaryNumericMeasureAttribute(), ascii::space_type>				binaryNumericMeasureRule;				/*!< The rule for parsing a binary numeric measure */

                qi::rule<Iterator, SubsetAttribute(), ascii::space_type> 							subsetRule;								/*!< The rule for parsing a subset */
                qi::rule<Iterator, FilterSubsetAttribute(), ascii::space_type> 						filterSubsetRule;						/*!< The rule for parsing a subset filter */
                qi::rule<Iterator, SubsetSpecificAttribute(), ascii::space_type> 					subsetSpecificRule;						/*!< The rule for parsing a specific subset */

                qi::rule<Iterator, ConstraintAttribute(), ascii::space_type> 						constraintRule;							/*!< The rule for parsing a constraint */
                qi::rule<Iterator, PrimaryConstraintAttribute(), ascii::space_type> 				primaryConstraintRule;					/*!< The rule for parsing a primary constraint */
                qi::rule<Iterator, NotConstraintAttribute(), ascii::space_type> 					notConstraintRule;						/*!< The rule for parsing a "not" constraint */
                qi::rule<Iterator, UnaryConstraintAttribute(), ascii::space_type> 					unaryConstraintRule;					/*!< The rule for parsing a unary constraint */
                qi::rule<Iterator, AndConstraintAttribute(), ascii::space_type>						andConstraintRule;						/*!< The rule for parsing an "and" constraint */
                qi::rule<Iterator, OrConstraintAttribute(), ascii::space_type> 						orConstraintRule;						/*!< The rule for parsing an "or" constraint */
                qi::rule<Iterator, ImplicationConstraintAttribute(), ascii::space_type>				implicationConstraintRule;				/*!< The rule for parsing an "implication" constraint */
                qi::rule<Iterator, EquivalenceConstraintAttribute(), ascii::space_type>				equivalenceConstraintRule;				/*!< The rule for parsing an "equivalence" constraint */

                qi::rule<Iterator, ComparatorAttribute(), ascii::space_type> 						spatialMeasureRule;						/*!< The rule for parsing a spatial measure */

                qi::rule<Iterator, ComparatorAttribute(), ascii::space_type> 						comparatorRule;							/*!< The rule for parsing a comparator */

                qi::rule<Iterator, NumericStateVariableAttribute(), ascii::space_type> 				numericStateVariableRule;				/*!< The rule for parsing a numeric state variable */
                qi::rule<Iterator, StateVariableAttribute(), ascii::space_type> 					stateVariableRule;						/*!< The rule for parsing a state variable */
                qi::rule<Iterator, std::string(), ascii::space_type> 								stateVariableNameRule; 					/*!< The rule for parsing the name of a state variable without escaping white space */

            public:

                ParserGrammar() : ParserGrammar::base_type(probabilisticLogicPropertyRule) {
                	// Rules definitions

                	constraintRule
                		=	primaryConstraintRule
                		    >>  *(
                		            (orConstraintRule)
                		        |   (andConstraintRule)
                		        |   (implicationConstraintRule)
                		        |   (equivalenceConstraintRule)
                                );

                	orConstraintRule
                		=	('V' > constraintRule);

                	andConstraintRule
                		=	('^' > constraintRule);

                	implicationConstraintRule
                		=	("=>" > constraintRule);

                	equivalenceConstraintRule
                		=	("<=>" > constraintRule);

                	primaryConstraintRule
						=	notConstraintRule
						// TODO: Update
//						|	numericStateVariableRule
						| 	('(' > constraintRule > ')');

                	notConstraintRule
                		=	('~' > constraintRule);

                	numericStateVariableRule
                		=   stateVariableRule;

                	stateVariableRule
                		=	stringRule;

                	stateVariableNameRule
                		=	+(qi::char_ - "[]");

                	// Assign a name to the rules
					constraintRule.name("constraintRule");
					orConstraintRule.name("orConstraintRule");
					andConstraintRule.name("andConstraintRule");
					implicationConstraintRule.name("implicationConstraintRule");
					equivalenceConstraintRule.name("equivalenceConstraintRule");
					primaryConstraintRule.name("primaryConstraintRule");
					notConstraintRule.name("notConstraintRule");
					numericStateVariableRule.name("numericStateVariableRule");
					stateVariableRule.name("stateVariableRule");
					stateVariableNameRule.name("stateVariableNameRule");

					// Debugging and reporting support
					debug(constraintRule);
					debug(orConstraintRule);
					debug(andConstraintRule);
					debug(implicationConstraintRule);
					debug(equivalenceConstraintRule);
					debug(primaryConstraintRule);
					debug(notConstraintRule);
					debug(numericStateVariableRule);
					debug(stateVariableRule);
					debug(stateVariableNameRule);

                	// Error handling routines
                	qi::on_error<qi::fail>(orConstraintRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                	qi::on_error<qi::fail>(andConstraintRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                	qi::on_error<qi::fail>(implicationConstraintRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                	qi::on_error<qi::fail>(equivalenceConstraintRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                	qi::on_error<qi::fail>(primaryConstraintRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                	qi::on_error<qi::fail>(notConstraintRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                }

        };

    };

};

#endif
