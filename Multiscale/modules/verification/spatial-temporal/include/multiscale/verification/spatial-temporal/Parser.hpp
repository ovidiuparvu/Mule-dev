#ifndef PARSER_HPP
#define PARSER_HPP

#include "multiscale/verification/spatial-temporal/attribute/SynthesizedAttribute.hpp"
#include "multiscale/verification/spatial-temporal/ParserGrammar.hpp"

#include <string>

using namespace multiscale::verification;


namespace multiscale {

    namespace verification {

        //! Class used for parsing (P)BLSTL logical queries
        class Parser {

            private:

                std::string logicalQuery;                            /*!< The logical query to be parsed */

                std::string::const_iterator logicalQueryIterator;    /*!< Iterator of the logical query */
                std::string::const_iterator logicalQueryEnd;         /*!< Iterator pointing at the end of the
                                                                     	  logical query */

                ParserGrammar<std::string::const_iterator> grammar;  /*!< The grammar used for parsing logical queries */

            public:

                Parser(const std::string &logicalQuery);
                ~Parser();

                //! Set the value of the logical query
                void setLogicalQuery(const std::string &logicalQuery);

                //! Parse the logical query
                /*!
                 * \param parseResult The result of the parsing procedure
                 */
                bool parse(ProbabilisticLogicPropertyAttribute &parseResult);

            private:

                //! Initialisation function
                void initialise();

                //! Parse the logical query
                /*!
                 * \param parseResult The result of the parsing procedure
                 */
                bool parseLogicalQuery(ProbabilisticLogicPropertyAttribute &parseResult);

                //! Check if an error case was encountered
                /*!
                 * \param isSuccessfulParse	The parse was successful or not
                 */
                void checkIfErrorCase(bool isSuccessfulParse);

                //! Check if the string was parsed completely
                bool isStringParsedCompletely();

        };

    };

};

#endif
