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
        : ScaleAndSubsystemGrammar::base_type(
            scaleAndSubsystemRule,
            "scaleAndSubsystemRule"
        ) {
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
            initializeErrorHandlingSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::initializeGrammar() {
            scaleAndSubsystemRule
                =   scaleAndSubsystemStringRule;
        }

        //! Initialize debug support
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::assignNamesToRules() {
            scaleAndSubsystemRule.name("scaleAndSubsystemRule");
        }

        //! Initialize the debugging of rules
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::initializeRulesDebugging() {
            debug(scaleAndSubsystemRule);
        }

        //! Initialize the error handling routines
        template <typename Iterator>
        void ScaleAndSubsystemGrammar<Iterator>::initializeErrorHandlingSupport() {
            // Do nothing
        }

    };

};


#endif
