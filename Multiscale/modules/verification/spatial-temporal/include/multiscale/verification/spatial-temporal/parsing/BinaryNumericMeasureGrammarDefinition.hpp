#ifndef BINARYNUMERICMEASUREGRAMMARDEFINITION_HPP
#define BINARYNUMERICMEASUREGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/parsing/BinaryNumericMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        template <typename Iterator>
        BinaryNumericMeasureGrammar<Iterator>::BinaryNumericMeasureGrammar()
            : BinaryNumericMeasureGrammar::base_type(
                                               binaryNumericMeasureRule,
                                               "binaryNumericMeasureRule"
                                           ) {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void BinaryNumericMeasureGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void BinaryNumericMeasureGrammar<Iterator>::initialiseGrammar() {
            binaryNumericMeasureRule
                =   binaryNumericMeasureTypeParser;
        }

        //! Initialise debug support
        template <typename Iterator>
        void BinaryNumericMeasureGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void BinaryNumericMeasureGrammar<Iterator>::assignNamesToRules() {
            binaryNumericMeasureRule.name("binaryNumericMeasureRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void BinaryNumericMeasureGrammar<Iterator>::initialiseRulesDebugging() {
            debug(binaryNumericMeasureRule);
        }

    };

};


#endif
