#ifndef NUMERICSTATEVARIABLEGRAMMARDEFINITION_HPP
#define NUMERICSTATEVARIABLEGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/NumericStateVariableGrammar.hpp"

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
        NumericStateVariableGrammar<Iterator>::NumericStateVariableGrammar()
            : NumericStateVariableGrammar::base_type(numericStateVariableRule, "numericStateVariableRule") {
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
            initializeErrorHandlingSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::initializeGrammar() {
            numericStateVariableRule
                =   stateVariableRule
                    > -(stateVariableScaleAndSubsystemRule);

            stateVariableRule
                =   ('{' > stateVariableNameRule > '}');

            stateVariableNameRule
                =   qi::raw[ +(qi::char_ - qi::char_("{}")) ];

            stateVariableScaleAndSubsystemRule
                =   (
                        '('
                        > qi::lit(ScaleAndSubsystemStringGrammar<Iterator>::SCALE_AND_SUBSYSTEM_LABEL)
                        > '='
                        > scaleAndSubsystemRule
                        > ')'
                    );
        }

        //! Initialize debug support
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::assignNamesToRules() {
            numericStateVariableRule            .name("numericStateVariableRule");
            stateVariableRule                   .name("stateVariableRule");
            stateVariableNameRule               .name("stateVariableNameRule");
            stateVariableScaleAndSubsystemRule  .name("stateVariableScaleAndSubsystemRule");
        }

        //! Initialize the debugging of rules
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::initializeRulesDebugging() {
            debug(numericStateVariableRule);
            debug(stateVariableRule);
            debug(stateVariableNameRule);
            debug(stateVariableScaleAndSubsystemRule);
        }

        //! Initialize the error handling routines
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::initializeErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                stateVariableNameRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                stateVariableScaleAndSubsystemRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

    };

};


#endif
