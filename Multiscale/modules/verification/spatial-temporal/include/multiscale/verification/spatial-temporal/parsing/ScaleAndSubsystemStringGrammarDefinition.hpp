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
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
            initializeErrorHandlingSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::initializeGrammar() {
            scaleAndSubsystemStringRule
                =   qi::lexeme[
                        +( qi::char_(SCALE_AND_SUBSYSTEM_STRING_PATTERN) )
                        >> qi::char_('.')
                        >> +( qi::char_(SCALE_AND_SUBSYSTEM_STRING_PATTERN) )
                    ];
        }

        //! Initialize debug support
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::assignNamesToRules() {
            scaleAndSubsystemStringRule.name("scaleAndSubsystemStringRule");
        }

        //! Initialize the debugging of rules
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::initializeRulesDebugging() {
            debug(scaleAndSubsystemStringRule);
        }

        //! Initialize the error handling routines
        template <typename Iterator>
        void ScaleAndSubsystemStringGrammar<Iterator>::initializeErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                scaleAndSubsystemStringRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

    };

};


#endif
