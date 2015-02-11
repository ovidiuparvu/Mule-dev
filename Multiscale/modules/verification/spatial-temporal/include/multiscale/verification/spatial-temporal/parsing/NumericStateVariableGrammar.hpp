#ifndef NUMERICSTATEVARIABLEGRAMMAR_HPP
#define NUMERICSTATEVARIABLEGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericStateVariableAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SemanticTypeStringGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        //! The grammar for parsing numeric state variable statements
        template <typename Iterator>
        class NumericStateVariableGrammar
            : public qi::grammar<Iterator, NumericStateVariableAttribute(), qi::space_type> {

            private:

                // Grammars

                SemanticTypeStringGrammar<Iterator>
                    semanticTypeRule;                           /*!< The grammar for parsing semantic types */

                // Rules

                qi::rule<Iterator, NumericStateVariableAttribute(), qi::space_type>
                    numericStateVariableRule;                   /*!< The rule for parsing a numeric state variable */
                qi::rule<Iterator, StateVariableAttribute(), qi::space_type>
                    stateVariableRule;                          /*!< The rule for parsing a state variable */
                qi::rule<Iterator, std::string(), qi::space_type>
                    stateVariableNameRule;                      /*!< The rule for parsing the name of a
                                                                     state variable without escaping white space */
                qi::rule<Iterator, SemanticTypeAttribute(), qi::space_type>
                    stateVariableTypeRule;                      /*!< The rule for parsing a state variable type */

            public:

                NumericStateVariableGrammar();

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
