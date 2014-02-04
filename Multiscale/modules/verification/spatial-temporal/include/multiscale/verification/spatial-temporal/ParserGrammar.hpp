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
        class ParserGrammar : public qi::grammar<Iterator, NumericStateVariableAttribute(), ascii::space_type> {

            private:

                //qi::rule<Iterator, LogicPropertyAttribute(), ascii::space_type>
                //	logicalPropertyRule;		/*!< The rule for parsing a logical property*/
                qi::rule<Iterator, NumericStateVariableAttribute(), ascii::space_type> numericStateVariableRule;	/*!< The rule for parsing a numeric state variable */
                qi::rule<Iterator, StateVariableAttribute(), ascii::space_type> stateVariableRule;			/*!< The rule for parsing a state variable */
                qi::rule<Iterator, std::string(), ascii::space_type> stringRule; /*!< The rule for parsing a string without escaping white space */

            public:

                ParserGrammar() : ParserGrammar::base_type(numericStateVariableRule) {
                	using qi::int_;
                	using qi::lit;
                	using qi::double_;
                	using qi::lexeme;
                	using ascii::char_;

                	numericStateVariableRule
                		=   stateVariableRule;

                	stateVariableRule
                		= stringRule;

                	stringRule
                		=	lexeme[ +(char_) ];

                	// Error handling routine
                	qi::on_error<qi::fail>(numericStateVariableRule, multiscale::verification::handleError(qi::_4, qi::_3, qi::_2));
                }

        };

    };

};

#endif
