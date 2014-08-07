#ifndef INPUTSTRINGPARSER_HPP
#define INPUTSTRINGPARSER_HPP

#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <string>

using namespace multiscale::verification;


/////////////////////////////////////////////////////////////////
//
// Test function
//
/////////////////////////////////////////////////////////////////

namespace multiscaletest {

    namespace verification {

        //! Parse the input string and return the result of the parsing
        /*!
         * \param inputString The input string
         */
        bool parseInputString(const std::string &inputString) {
            AbstractSyntaxTree parseResult;
            Parser parser(inputString);

            return parser.parse(parseResult);
        }

    };

};


#endif
