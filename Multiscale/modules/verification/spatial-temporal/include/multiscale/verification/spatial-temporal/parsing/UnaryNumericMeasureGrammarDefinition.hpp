#ifndef UNARYNUMERICMEASUREGRAMMARDEFINITION_HPP
#define UNARYNUMERICMEASUREGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/parsing/UnaryNumericMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        template <typename Iterator>
        UnaryNumericMeasureGrammar<Iterator>::UnaryNumericMeasureGrammar()
            : UnaryNumericMeasureGrammar::base_type(
                                              unaryNumericMeasureRule,
                                              "unaryNumericMeasureRule"
                                          ) {
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void UnaryNumericMeasureGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void UnaryNumericMeasureGrammar<Iterator>::initializeGrammar() {
            unaryNumericMeasureRule
                =   unaryNumericMeasureTypeParser;
        }

        //! Initialize debug support
        template <typename Iterator>
        void UnaryNumericMeasureGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void UnaryNumericMeasureGrammar<Iterator>::assignNamesToRules() {
            unaryNumericMeasureRule.name("unaryNumericMeasureRule");
        }

        //! Initialize the debugging of rules
        template <typename Iterator>
        void UnaryNumericMeasureGrammar<Iterator>::initializeRulesDebugging() {
            debug(unaryNumericMeasureRule);
        }

    };

};


#endif
