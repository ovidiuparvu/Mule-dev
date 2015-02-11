#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/exception/ParserGrammarExceptionHandler.hpp"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace multiscale;
using namespace multiscale::verification;


void ParserGrammarExceptionHandler::handleUnexpectedTokenException(const std::string &initialString,
                                                                   const std::string &errorString,
                                                                   const std::string &expectedToken) {
    std::string errorMessage;

    if (errorString.length() == 0) {
        errorMessage = handleExpectedTokenAtEndOfString(initialString, expectedToken);
    } else {
        errorMessage = handleUnexpectedTokenInString(initialString, errorString, expectedToken);
    }

    MS_throw(InvalidInputException, errorMessage);
}

void ParserGrammarExceptionHandler::handleProbabilityException(const std::string &initialString,
                                                               const std::string &errorString,
                                                               const std::string &expectedToken) {
    std::stringstream strStream;

    unsigned errorPositionIndex = initialString.length() - errorString.length();

    strStream   << getIntroductoryErrorMessage()
                << "Please change the value of the following invalid probability \""
                << initialString.substr(errorPositionIndex, expectedToken.length())
                << "\" such that it is in the interval [0, 1]. "
                << "You can find the error starting position emphasised by \">>>\" and \"<<<\" below (character "
                << (errorPositionIndex + 1)
                << "):" << std::endl
                << initialString.substr(0, errorPositionIndex) + ">>>" +
                   initialString.at(errorPositionIndex) + "<<<" + errorString.substr(1);

    MS_throw(InvalidInputException, strStream.str());
}

void ParserGrammarExceptionHandler::handleUnparseableInputException(const std::string &initialString, const std::string &errorString) {
    std::stringstream strStream;

    unsigned correctlyParsedStringLength = initialString.length() - errorString.length();
    std::string correctlyParsedString = initialString.substr(0, correctlyParsedStringLength);

    strStream   << getIntroductoryErrorMessage()
                << "Please rewrite the unparseable part \""
                << errorString
                << "\" of the query. "
                << "You can find the unparseable input emphasised by \">>>\" and \"<<<\" below (character "
                << (correctlyParsedString.length() + 1)
                << "): " << std::endl
                << correctlyParsedString + ">>>" + trimRight(errorString) + "<<<";

    MS_throw(InvalidInputException, strStream.str());
}

void ParserGrammarExceptionHandler::handleExtraInputException(const std::string &initialString, const std::string &extraInput) {
    std::stringstream strStream;

    unsigned correctlyParsedStringLength = initialString.length() - extraInput.length();
    std::string correctlyParsedString = initialString.substr(0, correctlyParsedStringLength);

    strStream   << getIntroductoryErrorMessage()
                << "Please remove the additional tokens \""
                << trimRight(extraInput)
                << "\" following the syntactically correct query \""
                << correctlyParsedString << "\". "
                << "You can find the extra input emphasised by \">>>\" and \"<<<\" below (character "
                << (correctlyParsedString.length() + 1)
                << "): " << std::endl
                << correctlyParsedString + ">>>" + trimRight(extraInput) + "<<<";

    MS_throw(InvalidInputException, strStream.str());
}

std::string ParserGrammarExceptionHandler::handleUnexpectedTokenInString(const std::string &initialString,
                                                                    const std::string &errorString,
                                                                    const std::string &expectedToken) {
    std::stringstream strStream;

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
                << "):" << std::endl
                << initialString.substr(0, errorPositionIndex) + ">>>" +
                   initialString.at(errorPositionIndex) + "<<<" + errorString.substr(1);

    return strStream.str();
}

std::string ParserGrammarExceptionHandler::handleExpectedTokenAtEndOfString(const std::string &initialString,
                                                                       const std::string &expectedToken) {
    std::stringstream strStream;

    strStream   << getIntroductoryErrorMessage()
                << "The token \""
                << expectedToken
                << "\" was expected after the provided input query and was not found. "
                << "The input query is displayed below: " << std::endl
                << initialString;

    return strStream.str();
}

std::string ParserGrammarExceptionHandler::trimRight(const std::string &inputString) {
    return StringManipulator::trimRight(inputString);
}

std::string ParserGrammarExceptionHandler::getIntroductoryErrorMessage() {
    std::stringstream strStream;

    strStream   << std::endl
                << "You have to consider the syntax rules specified by the grammar of the language "
                << "when writing logical queries." << std::endl << std::endl;

    return strStream.str();
}
