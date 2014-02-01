#include "multiscale/verification/spatial-temporal/Parser.hpp"
#include "multiscale/verification/spatial-temporal/exception/ParserGrammarExceptionHandler.hpp"

using namespace boost::spirit;
using namespace multiscale::verification;
using namespace std;


Parser::Parser(const string &logicalQuery) {
    this->logicalQuery = logicalQuery;

    initialise();
}

Parser::~Parser() {}

bool Parser::parse(string &parseResult) {
    bool isSuccessfulParse = false;

    try {
        parseLogicalQuery(parseResult);
    } catch(const ParserGrammarUnexpectedTokenException &e) {
        ParserGrammarExceptionHandler::handleUnexpectedTokenException(string(logicalQueryIterator, logicalQueryEnd),
                                                                      e.getErrorString(), e.getExpectedToken());
    } catch(const ParserGrammarExtraInputException &e) {
        ParserGrammarExceptionHandler::handleExtraInputException(logicalQuery, e.getErrorString());
    }

    return isSuccessfulParse;
}

void Parser::initialise() {
    this->logicalQueryIterator = logicalQuery.begin();
    this->logicalQueryEnd = logicalQuery.end();
}

bool Parser::parseLogicalQuery(string &parseResult) {
    bool isSuccesfulParse = phrase_parse(logicalQueryIterator, logicalQueryEnd, grammar, ascii::space, parseResult);

    if ((isSuccesfulParse) && (!isStringParsedCompletely())) {
        throw ParserGrammarExtraInputException(string(logicalQueryIterator, logicalQueryEnd));
    }

    return isSuccesfulParse;
}

bool Parser::isStringParsedCompletely() {
    return (logicalQueryIterator == logicalQueryEnd);
}
