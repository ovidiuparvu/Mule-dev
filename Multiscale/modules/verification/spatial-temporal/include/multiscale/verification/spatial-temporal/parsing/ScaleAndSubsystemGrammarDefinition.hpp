#ifndef SCALEANDSUBSYSTEMGRAMMARDEFINITION_HPP
#define SCALEANDSUBSYSTEMGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ScaleAndSubsystemGrammar.hpp"

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
        ScaleAndSubsystemGrammar<Iterator>::ScaleAndSubsystemGrammar()
            : ScaleAndSubsystemGrammar::base_type(scaleAndSubsystemRule, "scaleAndSubsystemRule") {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::initialiseGrammar() {
            scaleAndSubsystemRule
                =   scaleAndSubsystemStringRule;
        }

        //! Initialise debug support
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::assignNamesToRules() {
            scaleAndSubsystemRule.name("scaleAndSubsystemRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::initialiseRulesDebugging() {
            debug(scaleAndSubsystemRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::initialiseErrorHandlingSupport() {
            // Do nothing
        }

    };

};


#endif
