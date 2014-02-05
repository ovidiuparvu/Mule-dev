#ifndef PARSERGRAMMAR_HPP
#define PARSERGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/SynthesizedAttribute.hpp"
#include "multiscale/verification/spatial-temporal/exception/ParserGrammarUnexpectedTokenException.hpp"
#include "multiscale/verification/spatial-temporal/handler/ErrorHandler.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/qi_and_predicate.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


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
        class ParserGrammar : public qi::grammar<Iterator, SubsetAttribute(), ascii::space_type> {

            private:

                //qi::rule<Iterator, LogicPropertyAttribute(), ascii::space_type> logicalPropertyRule;		/*!< The rule for parsing a logical property*/

                qi::rule<Iterator, SubsetAttribute(), ascii::space_type> 				subsetRule;					/*!< The rule for parsing a subset */
                qi::rule<Iterator, FilterSubsetAttribute(), ascii::space_type> 			filterSubsetRule;			/*!< The rule for parsing a subset filter */
                qi::rule<Iterator, SubsetSpecificAttribute(), ascii::space_type> 		subsetSpecificRule;			/*!< The rule for parsing a specific subset */
                qi::rule<Iterator, std::string(), ascii::space_type> 					subsetSpecificNameRule;		/*!< The rule for parsing a specific subset name */
                qi::rule<Iterator, ConstraintAttribute(), ascii::space_type> 			constraintRule;				/*!< The rule for parsing a constraint */
                qi::rule<Iterator, NotConstraintAttribute(), ascii::space_type> 		notConstraintRule;			/*!< The rule for parsing a "not" constraint */
                qi::rule<Iterator, OrConstraintAttribute(), ascii::space_type> 			orConstraintRule;			/*!< The rule for parsing an "or" constraint */
                qi::rule<Iterator, NumericStateVariableAttribute(), ascii::space_type> 	numericStateVariableRule;	/*!< The rule for parsing a numeric state variable */
                qi::rule<Iterator, StateVariableAttribute(), ascii::space_type> 		stateVariableRule;			/*!< The rule for parsing a state variable */
                qi::rule<Iterator, std::string(), ascii::space_type> 					stringRule; 				/*!< The rule for parsing a string without escaping white space */

            public:

                ParserGrammar() : ParserGrammar::base_type(subsetRule) {
                	// Rules definitions

                	subsetRule
                		=	subsetSpecificRule
                		|	filterSubsetRule;

                	filterSubsetRule
                		=	qi::lit("filter")
                			> '('
                			> subsetSpecificRule
                			> ','
                			> constraintRule
                			> ')';

                	subsetSpecificRule
                		=	subsetSpecificNameRule;

                	subsetSpecificNameRule
                		=	ascii::string("clusters")
                		|	ascii::string("regions");

                	constraintRule
                		=	notConstraintRule
                		|	orConstraintRule
                			>> &qi::lit("V")
                		|	numericStateVariableRule
                		|	'('
                			> constraintRule
                			> ')';

                	notConstraintRule
                		=	"~"
                			> constraintRule;

                	orConstraintRule
                		=	constraintRule
                			>	"V"
                			>	constraintRule;

                	numericStateVariableRule
                		=   stateVariableRule;

                	stateVariableRule
                		=	stringRule;

                	stringRule
                		=	+(qi::char_("a-zA-UW-Z_"));

                	// Assign a name to the rules
					subsetRule.name("subsetRule");
					filterSubsetRule.name("filterSubsetRule");
					subsetSpecificRule.name("subsetSpecificRule");
					subsetSpecificNameRule.name("subsetSpecificNameRule");
					constraintRule.name("constraintRule");
					notConstraintRule.name("notConstraintRule");
					orConstraintRule.name("orConstraintRule");
					numericStateVariableRule.name("numericStateVariableRule");
					stateVariableRule.name("stateVariableRule");
					stringRule.name("stringRule");

					// Debugging and reporting support
					debug(subsetRule);
					debug(filterSubsetRule);
					debug(subsetSpecificRule);
					debug(subsetSpecificNameRule);
					debug(constraintRule);
					debug(notConstraintRule);
					debug(orConstraintRule);
					debug(numericStateVariableRule);
					debug(stateVariableRule);
					debug(stringRule);

                	// Error handling routines
                	qi::on_error<qi::fail>(filterSubsetRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                	qi::on_error<qi::fail>(constraintRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                	qi::on_error<qi::fail>(notConstraintRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                	qi::on_error<qi::fail>(orConstraintRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                }

        };

    };

};

#endif
