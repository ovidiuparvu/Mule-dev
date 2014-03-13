#include "multiscale/verification/spatial-temporal/exception/ParserGrammarExceptionHandler.hpp"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

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

void ParserGrammarExceptionHandler::handleProbabilityException(const string &initialString,
                                                               const string &errorString,
                                                               const string &expectedToken) {
    stringstream strStream;

    unsigned errorPositionIndex = initialString.length() - errorString.length();

    strStream   << getIntroductoryErrorMessage()
                << "Please change the value of the following invalid probability \""
                << initialString.substr(errorPositionIndex, expectedToken.length())
                << "\" such that it is in the interval [0, 1]. "
                << "You can find the error starting position emphasised by \">>>\" and \"<<<\" below (character "
                << (errorPositionIndex + 1)
                << "):" << endl
                << initialString.substr(0, errorPositionIndex) + ">>>" +
                   initialString.at(errorPositionIndex) + "<<<" + errorString.substr(1);

    MS_throw(InvalidInputException, strStream.str());
}

void ParserGrammarExceptionHandler::handleUnparseableInputException(const string &initialString, const string &errorString) {
    stringstream strStream;

    unsigned correctlyParsedStringLength = initialString.length() - errorString.length();
    string correctlyParsedString = initialString.substr(0, correctlyParsedStringLength);

    strStream   << getIntroductoryErrorMessage()
                << "Please rewrite the unparseable part \""
                << errorString
                << "\" of the query. "
                << "You can find the unparseable input emphasised by \">>>\" and \"<<<\" below (character "
                << (correctlyParsedString.length() + 1)
                << "): " << endl
                << correctlyParsedString + ">>>" + trimRight(errorString) + "<<<";

    MS_throw(InvalidInputException, strStream.str());
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
                << "You can find the extra input emphasised by \">>>\" and \"<<<\" below (character "
                << (correctlyParsedString.length() + 1)
                << "): " << endl
                << correctlyParsedString + ">>>" + trimRight(extraInput) + "<<<";

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
                << "You can find the error starting position emphasised by \">>>\" and \"<<<\" below (character "
                << (errorPositionIndex + 1)
                << "):" << endl
                << initialString.substr(0, errorPositionIndex) + ">>>" +
                   initialString.at(errorPositionIndex) + "<<<" + errorString.substr(1);

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

string ParserGrammarExceptionHandler::trimRight(const string &inputString) {
    string trimmedString = inputString;

    trimmedString.erase(
        std::find_if(
            trimmedString.rbegin(),
            trimmedString.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base()
        , trimmedString.end()
   );

   return trimmedString;
}

string ParserGrammarExceptionHandler::getIntroductoryErrorMessage() {
    stringstream strStream;

    strStream   << endl
                << "You have to consider the syntax rules specified by the grammar of the language "
                << "when writing logical queries." << endl << endl;

    return strStream.str();
}
