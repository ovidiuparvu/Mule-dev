#ifndef SCALEANDSUBSYSTEMGRAMMARDEFINITION_HPP
#define SCALEANDSUBSYSTEMSTRINGGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ScaleAndSubsystemStringGrammar.hpp"

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
        ScaleAndSubsystemStringGrammar<Iterator>::ScaleAndSubsystemStringGrammar()
        : ScaleAndSubsystemStringGrammar::base_type(
            scaleAndSubsystemStringRule,
            "scaleAndSubsystemStringRule"
        ) {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::initialiseGrammar() {
            scaleAndSubsystemStringRule
                =   qi::lexeme[
                        +( qi::char_(SCALE_AND_SUBSYSTEM_STRING_PATTERN) )
                        >> qi::char_('.')
                        >> +( qi::char_(SCALE_AND_SUBSYSTEM_STRING_PATTERN) )
                    ];
        }

        //! Initialise debug support
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::assignNamesToRules() {
            scaleAndSubsystemStringRule.name("scaleAndSubsystemStringRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::initialiseRulesDebugging() {
            debug(scaleAndSubsystemStringRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::initialiseErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                scaleAndSubsystemStringRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

    };

};


#endif
