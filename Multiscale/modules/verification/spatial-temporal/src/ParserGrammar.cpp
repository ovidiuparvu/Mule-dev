#include "multiscale/verification/spatial-temporal/ParserGrammar.hpp"

using namespace multiscale::verification;


ParserGrammar::ParserGrammar() : ParserGrammar::base_type(numericStateVariableRule) {
	numericStateVariableRule
		=   stateVariableRule;

	stateVariableRule
		=	+char_

	// Error handling routine
	qi::on_error<qi::fail>(numericStateVariableRule, multiscale::verification::handleError(_4, _3, _2));
}
