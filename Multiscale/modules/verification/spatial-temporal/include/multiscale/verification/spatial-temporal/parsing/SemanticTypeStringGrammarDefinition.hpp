#ifndef SEMANTICTYPESTRINGGRAMMARDEFINITION_HPP
#define SEMANTICTYPESTRINGGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SemanticTypeStringGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Create a lazy error handler function
        phoenix::function<UnexpectedTokenErrorHandler> const
            handleUnexpectedTokenError = UnexpectedTokenErrorHandler();

        template <typename Iterator>
        SemanticTypeStringGrammar<Iterator>::SemanticTypeStringGrammar()
            : SemanticTypeStringGrammar::base_type(semanticTypeStringRule, "semanticTypeStringRule") {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void SemanticTypeStringGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void SemanticTypeStringGrammar<Iterator>::initialiseGrammar() {
            semanticTypeStringRule
                =   +( qi::char_(SEMANTIC_CRITERION_STRING_PATTERN) )
                    >> *(
                        qi::char_('.')
                        >> +(qi::char_(SEMANTIC_CRITERION_STRING_PATTERN))
                    );
        }

        //! Initialise debug support
        template <typename Iterator>
        void SemanticTypeStringGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void SemanticTypeStringGrammar<Iterator>::assignNamesToRules() {
            semanticTypeStringRule.name("semanticTypeStringRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void SemanticTypeStringGrammar<Iterator>::initialiseRulesDebugging() {
            debug(semanticTypeStringRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void SemanticTypeStringGrammar<Iterator>::initialiseErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                semanticTypeStringRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

    };

};


#endif
