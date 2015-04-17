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
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void BinaryNumericMeasureGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void BinaryNumericMeasureGrammar<Iterator>::initializeGrammar() {
            binaryNumericMeasureRule
                =   binaryNumericMeasureTypeParser;
        }

        //! Initialize debug support
        template <typename Iterator>
        void BinaryNumericMeasureGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void BinaryNumericMeasureGrammar<Iterator>::assignNamesToRules() {
            binaryNumericMeasureRule.name("binaryNumericMeasureRule");
        }

        //! Initialize the debugging of rules
        template <typename Iterator>
        void BinaryNumericMeasureGrammar<Iterator>::initializeRulesDebugging() {
            debug(binaryNumericMeasureRule);
        }

    };

};


#endif
