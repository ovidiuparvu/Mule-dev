#ifndef SEMANTICTYPESTRINGGRAMMAR_HPP
#define SEMANTICTYPESTRINGGRAMMAR_HPP

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        //! The grammar for parsing semantic type string statements
        template <typename Iterator>
        class SemanticTypeStringGrammar
            : public qi::grammar<Iterator, std::string(), qi::space_type> {

            private:

                // Rules

                qi::rule<Iterator, std::string(), qi::space_type>
                    semanticTypeStringRule;                         /*!< The rule for parsing a string representing
                                                                         a semantic type */


            public:

                SemanticTypeStringGrammar();

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


                // Constants
                static const std::string SEMANTIC_CRITERION_STRING_PATTERN;

        };

    };

};


#endif
