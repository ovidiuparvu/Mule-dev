#ifndef SEMANTICTYPEGRAMMAR_HPP
#define SEMANTICTYPEGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/SemanticTypeAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SemanticTypeStringGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        //! The grammar for parsing semantic type statements
        template <typename Iterator>
        class SemanticTypeGrammar
            : public qi::grammar<Iterator, SemanticTypeAttribute(), qi::space_type> {

            private:

                // Grammars

                SemanticTypeStringGrammar<Iterator>
                    semanticTypeStringRule;                     /*!< The rule for parsing a string representing
                                                                     a semantic type */

                // Rules

                qi::rule<Iterator, SemanticTypeAttribute(), qi::space_type>
                    semanticTypeRule;                           /*!< The rule for parsing a semantic type */

            public:

                SemanticTypeGrammar();

            private:

                //! Initialisation function
                void initialise();

                //! Initialise the grammar
                void initialiseGrammar();

                //! Initialise debug support
                void initialiseDebugSupport();

                //! Assign names to the rules
                void assignNamesToRules();

                //! Initialise the debugging of rules
                void initialiseRulesDebugging();

                //! Initialise the error handling routines
                void initialiseErrorHandlingSupport();

        };

    };

};


#endif
