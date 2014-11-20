#ifndef BINARYSTATISTICALMEASUREGRAMMARDEFINITION_HPP
#define BINARYSTATISTICALMEASUREGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/parsing/BinaryStatisticalMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        template <typename Iterator>
        BinaryStatisticalMeasureGrammar<Iterator>::BinaryStatisticalMeasureGrammar()
            : BinaryStatisticalMeasureGrammar::base_type(
                                                   binaryStatisticalMeasureRule,
                                                   "binaryStatisticalMeasureRule"
                                               ) {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void BinaryStatisticalMeasureGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void BinaryStatisticalMeasureGrammar<Iterator>::initialiseGrammar() {
            binaryStatisticalMeasureRule
                =   binaryStatisticalMeasureTypeParser;
        }

        //! Initialise debug support
        template <typename Iterator>
        void BinaryStatisticalMeasureGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void BinaryStatisticalMeasureGrammar<Iterator>::assignNamesToRules() {
            binaryStatisticalMeasureRule.name("binaryStatisticalMeasureRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void BinaryStatisticalMeasureGrammar<Iterator>::initialiseRulesDebugging() {
            debug(binaryStatisticalMeasureRule);
        }

    };

};


#endif
