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
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void UnaryNumericMeasureGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void UnaryNumericMeasureGrammar<Iterator>::initialiseGrammar() {
            unaryNumericMeasureRule
                =   unaryNumericMeasureTypeParser;
        }

        //! Initialise debug support
        template <typename Iterator>
        void UnaryNumericMeasureGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void UnaryNumericMeasureGrammar<Iterator>::assignNamesToRules() {
            unaryNumericMeasureRule.name("unaryNumericMeasureRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void UnaryNumericMeasureGrammar<Iterator>::initialiseRulesDebugging() {
            debug(unaryNumericMeasureRule);
        }

    };

};


#endif
