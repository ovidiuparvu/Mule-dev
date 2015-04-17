#ifndef CHANGEMEASUREGRAMMARDEFINITION_HPP
#define CHANGEMEASUREGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ChangeMeasureGrammar.hpp"

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
        ChangeMeasureGrammar<Iterator>::ChangeMeasureGrammar()
            : ChangeMeasureGrammar::base_type(changeMeasureRule, "changeMeasureRule") {
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void ChangeMeasureGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void ChangeMeasureGrammar<Iterator>::initializeGrammar() {
            // In order to be a successful parse the change measure
            // should be followed by a "(". The "(" character is not
            // explicitly consumed i.e. the "&" predicate is used for
            // look-ahead techniques.
            //
            // At the time of writing this look-ahead technique was
            // employed to avoid ambiguity in the grammar between
            // "density" and "d"
            changeMeasureRule
                =   changeMeasureTypeParser
                    >> &qi::lit('(');
        }

        //! Initialize debug support
        template <typename Iterator>
        void ChangeMeasureGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void ChangeMeasureGrammar<Iterator>::assignNamesToRules() {
            changeMeasureRule.name("changeMeasureRule");
        }

        //! Initialize the debugging of rules
        template <typename Iterator>
        void ChangeMeasureGrammar<Iterator>::initializeRulesDebugging() {
            debug(changeMeasureRule);
        }

    };

};


#endif
