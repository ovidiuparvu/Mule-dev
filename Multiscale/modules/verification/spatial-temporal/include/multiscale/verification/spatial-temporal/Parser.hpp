#ifndef PARSER_HPP
#define PARSER_HPP

#include "multiscale/verification/spatial-temporal/Car.hpp"
#include "multiscale/verification/spatial-temporal/ParserGrammar.hpp"
#include "multiscale/verification/spatial-temporal/exception/ParserGrammarExtraInputException.hpp"
#include "multiscale/verification/spatial-temporal/exception/ParserGrammarUnexpectedTokenException.hpp"

#include <string>

using namespace std;


namespace multiscale {

    namespace verification {

        //! Class used for parsing (P)BLSTL logical queries
        class Parser {

            private:

                string logicalQuery;                            /*!< The logical query to be parsed */

                string::const_iterator logicalQueryIterator;    /*!< Iterator of the logical query */
                string::const_iterator logicalQueryEnd;         /*!< Iterator pointing at the end of the
                                                                     logical query */

                ParserGrammar<string::const_iterator> grammar;  /*!< The grammar used for parsing logical queries */

            public:

                Parser(const string &logicalQuery);
                ~Parser();

                //! Parse the logical query
                /*!
                 * \param parseResult The result of the parsing procedure
                 */
                bool parse(Car &parseResult);

            private:

                //! Initialisation function
                void initialise();

                //! Parse the logical query
                /*!
                 * \param parseResult The result of the parsing procedure
                 */
                bool parseLogicalQuery(Car &parseResult);

                //! Check if the string was parsed completely
                bool isStringParsedCompletely();

                //! Handle ParserGrammarUnexpectedTokenException exceptions
                /*!
                 * \param exception The exception
                 */
                void handleUnexpectedTokenException(const ParserGrammarUnexpectedTokenException &exception);

                //! Handle ParserGrammarExtraInputException exceptions
                /*!
                 * \param exception The exception
                 */
                void handleExtraInputException(const ParserGrammarExtraInputException &exception);


        };

    };

};

#endif
