#ifndef SEMANTICTYPEGRAMMARDEFINITION_HPP
#define SEMANTICTYPEGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SemanticTypeGrammar.hpp"

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
        SemanticTypeGrammar<Iterator>::SemanticTypeGrammar()
            : SemanticTypeGrammar::base_type(semanticTypeRule, "semanticTypeRule") {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void SemanticTypeGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void SemanticTypeGrammar<Iterator>::initialiseGrammar() {
            semanticTypeRule
                =   semanticTypeStringRule;
        }

        //! Initialise debug support
        template <typename Iterator>
        void SemanticTypeGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void SemanticTypeGrammar<Iterator>::assignNamesToRules() {
            semanticTypeRule.name("semanticTypeRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void SemanticTypeGrammar<Iterator>::initialiseRulesDebugging() {
            debug(semanticTypeRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void SemanticTypeGrammar<Iterator>::initialiseErrorHandlingSupport() {
            // Do nothing
        }

    };

};


#endif
