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
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::initialiseGrammar() {
            numericStateVariableRule
                =   stateVariableRule
                    > -(stateVariableTypeRule);

            stateVariableRule
                =   ('{' > stateVariableNameRule > '}');

            stateVariableNameRule
                =   qi::raw[ +(qi::char_ - qi::char_("{}")) ];

            stateVariableTypeRule
                =   (
                        '('
                        > qi::lit("type")
                        > '='
                        > semanticTypeRule
                        > ')'
                    );
        }

        //! Initialise debug support
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::assignNamesToRules() {
            numericStateVariableRule    .name("numericStateVariableRule");
            stateVariableRule           .name("stateVariableRule");
            stateVariableNameRule       .name("stateVariableNameRule");
            stateVariableTypeRule       .name("stateVariableTypeRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::initialiseRulesDebugging() {
            debug(numericStateVariableRule);
            debug(stateVariableRule);
            debug(stateVariableNameRule);
            debug(stateVariableTypeRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void NumericStateVariableGrammar<Iterator>::initialiseErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                stateVariableNameRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                stateVariableTypeRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

    };

};


#endif
