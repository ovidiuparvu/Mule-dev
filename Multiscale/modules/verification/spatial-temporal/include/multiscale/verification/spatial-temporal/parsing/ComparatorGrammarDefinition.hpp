#ifndef COMPARATORGRAMMARDEFINITION_HPP
#define COMPARATORGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ComparatorGrammar.hpp"

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
        ComparatorGrammar<Iterator>::ComparatorGrammar()
            : ComparatorGrammar::base_type(comparatorRule, "comparatorRule") {
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void ComparatorGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void ComparatorGrammar<Iterator>::initializeGrammar() {
            comparatorRule
                =   comparatorTypeParser;
        }

        //! Initialize debug support
        template <typename Iterator>
        void ComparatorGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void ComparatorGrammar<Iterator>::assignNamesToRules() {
            comparatorRule.name("comparatorRule");
        }

        //! Initialize the debugging of rules
        template <typename Iterator>
        void ComparatorGrammar<Iterator>::initializeRulesDebugging() {
            debug(comparatorRule);
        }

    };

};


#endif
