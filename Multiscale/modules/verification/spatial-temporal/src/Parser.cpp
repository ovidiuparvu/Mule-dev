#include "multiscale/verification/spatial-temporal/Parser.hpp"
#include "multiscale/verification/spatial-temporal/exception/ParserGrammarExceptionHandler.hpp"
#include "multiscale/verification/spatial-temporal/exception/ParserGrammarExtraInputException.hpp"
#include "multiscale/verification/spatial-temporal/exception/ParserGrammarUnexpectedTokenException.hpp"
#include "multiscale/verification/spatial-temporal/exception/ParserGrammarUnparseableInputException.hpp"

using namespace boost::spirit;
using namespace multiscale::verification;


Parser::Parser(const std::string &logicalQuery) {
    this->logicalQuery = logicalQuery;

    initialise();
}

Parser::~Parser() {}

void Parser::setLogicalQuery(const std::string &logicalQuery) {
	this->logicalQuery = logicalQuery;

	initialise();
}

bool Parser::parse(ProbabilisticLogicPropertyAttribute &parseResult) {
    bool isSuccessfulParse = false;

    try {
    	isSuccessfulParse = parseLogicalQuery(parseResult);
    } catch(const ParserGrammarUnexpectedTokenException &e) {
        ParserGrammarExceptionHandler::handleUnexpectedTokenException(std::string(logicalQueryIterator, logicalQueryEnd),
                                                                      e.getErrorString(), e.getExpectedToken());
    } catch(const ParserGrammarExtraInputException &e) {
        ParserGrammarExceptionHandler::handleExtraInputException(logicalQuery, e.getErrorString());
    } catch(const ParserGrammarUnparseableInputException &e) {
		ParserGrammarExceptionHandler::handleUnparseableInputException(logicalQuery, e.getErrorString());
	}

    return isSuccessfulParse;
}

void Parser::initialise() {
    this->logicalQueryIterator = logicalQuery.begin();
    this->logicalQueryEnd = logicalQuery.end();
}

bool Parser::parseLogicalQuery(ProbabilisticLogicPropertyAttribute &parseResult) {
    bool isSuccesfulParse = phrase_parse(logicalQueryIterator, logicalQueryEnd, grammar, ascii::space, parseResult);

    checkIfErrorCase(isSuccesfulParse);

    return isSuccesfulParse;
}

void Parser::checkIfErrorCase(bool isSuccessfulParse) {
	if (isSuccessfulParse) {
		if (!isStringParsedCompletely()) {
			throw ParserGrammarExtraInputException(std::string(logicalQueryIterator, logicalQueryEnd));
		}
	} else {
		throw ParserGrammarUnparseableInputException(std::string(logicalQueryIterator, logicalQueryEnd));
	}
}

bool Parser::isStringParsedCompletely() {
    return (logicalQueryIterator == logicalQueryEnd);
}
