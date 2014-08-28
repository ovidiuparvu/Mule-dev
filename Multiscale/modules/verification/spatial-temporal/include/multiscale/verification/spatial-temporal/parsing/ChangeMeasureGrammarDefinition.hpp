#ifndef CHANGEMEASUREGRAMMARDEFINITION_HPP
#define CHANGEMEASUREGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ChangeMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/qi_and_predicate.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Create a lazy error handler function
        phoenix::function<UnexpectedTokenErrorHandler> const
            handleUnexpectedTokenError = UnexpectedTokenErrorHandler();


        template <typename Iterator>
        ChangeMeasureGrammar<Iterator>::ChangeMeasureGrammar()
            : ChangeMeasureGrammar::base_type(changeMeasureRule, "changeMeasureRule") {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void ChangeMeasureGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void ChangeMeasureGrammar<Iterator>::initialiseGrammar() {
            changeMeasureRule
                =   changeMeasureTypeParser;
        }

        //! Initialise debug support
        template <typename Iterator>
        void ChangeMeasureGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void ChangeMeasureGrammar<Iterator>::assignNamesToRules() {
            changeMeasureRule.name("changeMeasureRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void ChangeMeasureGrammar<Iterator>::initialiseRulesDebugging() {
            debug(changeMeasureRule);
        }

    };

};


#endif
