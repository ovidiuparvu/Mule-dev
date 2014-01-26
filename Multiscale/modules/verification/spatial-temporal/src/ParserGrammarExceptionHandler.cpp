#include "multiscale/verification/spatial-temporal/ParserGrammarExceptionHandler.hpp"

using namespace multiscale::verification;


void ParserGrammarExceptionHandler::handleUnexpectedTokenException(const string &initialString,
                                                                   const string &errorString,
                                                                   const string &expectedToken) {
    string errorMessage;

    if (errorString.length() == 0) {
        errorMessage = handleExpectedTokenAtEndOfString(initialString, expectedToken);
    } else {
        errorMessage = handleUnexpectedTokenInString(initialString, errorString, expectedToken);
    }

    MS_throw(InvalidInputException, errorMessage);
}

void ParserGrammarExceptionHandler::handleExtraInputException(const string &initialString, const string &extraInput) {
    stringstream strStream;

    unsigned correctlyParsedStringLength = initialString.length() - extraInput.length();
    string correctlyParsedString = initialString.substr(0, correctlyParsedStringLength);

    strStream   << getIntroductoryErrorMessage()
                << "Please remove the additional tokens \""
                << extraInput
                << "\" following the syntactically correct query \""
                << correctlyParsedString << "\". "
                << "You can find the extra input emphasized by \">>>\" and \"<<<\" below (column "
                << (correctlyParsedString.length() + 1)
                << "): " << endl
                << correctlyParsedString + ">>>" + extraInput + "<<<";


    MS_throw(InvalidInputException, strStream.str());
}

string ParserGrammarExceptionHandler::handleUnexpectedTokenInString(const string &initialString,
                                                                    const string &errorString,
                                                                    const string &expectedToken) {
    stringstream strStream;

    unsigned errorPositionIndex = initialString.length() - errorString.length();

    strStream   << getIntroductoryErrorMessage()
                << "The following error token \""
                << initialString.substr(errorPositionIndex, expectedToken.length())
                << "\" was encountered "
                << "instead of the expected token \""
                << expectedToken
                << "\". "
                << "You can find the error starting position emphasized by \">>>\" and \"<<<\" below (column "
                << (errorPositionIndex + 1)
                << "):" << endl
                << initialString.substr(0, errorPositionIndex) + ">>>" +
                initialString.at(errorPositionIndex) + "<<<" + errorString;

    return strStream.str();
}

string ParserGrammarExceptionHandler::handleExpectedTokenAtEndOfString(const string &initialString,
                                                                       const string &expectedToken) {
    stringstream strStream;

    strStream   << getIntroductoryErrorMessage()
                << "The token \""
                << expectedToken
                << "\" was expected after the provided input query and was not found. "
                << "The input query is displayed below: " << endl
                << initialString;

    return strStream.str();
}

string ParserGrammarExceptionHandler::getIntroductoryErrorMessage() {
    stringstream strStream;

    strStream   << endl
                << "You have to consider the syntax rules specified by the grammar of the language "
                << "when writing logical queries." << endl << endl;

    return strStream.str();
}
