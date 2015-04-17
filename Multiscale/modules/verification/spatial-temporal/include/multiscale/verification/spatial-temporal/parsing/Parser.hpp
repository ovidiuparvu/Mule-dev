#ifndef PARSER_HPP
#define PARSER_HPP

#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/parsing/LogicPropertyGrammar.hpp"

#include <string>

using namespace multiscale::verification;


namespace multiscale {

    namespace verification {

        //! Class used for parsing (P)BLSTL logical queries
        class Parser {

            private:

                std::string logicalQuery;                                   /*!< The logical query to be parsed */

                std::string::const_iterator logicalQueryIterator;           /*!< Iterator of the logical query */
                std::string::const_iterator logicalQueryEnd;                /*!< Iterator pointing at the end of the
                                                                                 logical query */

                LogicPropertyGrammar<std::string::const_iterator> grammar;  /*!< The grammar used for parsing logic
                                                                                 properties */

            public:

                Parser(const std::string &logicalQuery);
                ~Parser();

                //! Set the value of the logical query
                void setLogicalQuery(const std::string &logicalQuery);

                //! Parse the logical query
                /*!
                 * \param parseResult The result of the parsing procedure
                 */
                bool parse(AbstractSyntaxTree &parseResult);

            private:

                //! Initialisation function
                void initialize();

                //! Parse the logical query and wrap the ProbabilisticLogicProperty into an AbstractSyntaxTree instance
                /*!
                 * \param parseResult The result of the parsing procedure
                 */
                bool parseLogicalQuery(AbstractSyntaxTree &parseResult);

                //! Parse the logical query and construct the abstract syntax tree
                /*!
                 * \param parseResult The result of the parsing procedure
                 */
                bool parseLogicalQuery(ProbabilisticLogicPropertyAttribute &parseResult);

                //! Check if an error case was encountered
                /*!
                 * \param isSuccessfulParse    The parse was successful or not
                 */
                void checkIfErrorCase(bool isSuccessfulParse);

                //! Check if the string was parsed completely
                bool isStringParsedCompletely();

        };

    };

};


#endif
