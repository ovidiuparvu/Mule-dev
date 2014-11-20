#ifndef BINARYSTATISTICALQUANTILEMEASUREGRAMMARDEFINITION_HPP
#define BINARYSTATISTICALQUANTILEMEASUREGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/parsing/BinaryStatisticalQuantileMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        template <typename Iterator>
        BinaryStatisticalQuantileMeasureGrammar<Iterator>::BinaryStatisticalQuantileMeasureGrammar()
            : BinaryStatisticalQuantileMeasureGrammar::base_type(
                                                           binaryStatisticalQuantileMeasureRule,
                                                           "binaryStatisticalQuantileMeasureRule"
                                                       ) {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void BinaryStatisticalQuantileMeasureGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void BinaryStatisticalQuantileMeasureGrammar<Iterator>::initialiseGrammar() {
            binaryStatisticalQuantileMeasureRule
                =   binaryStatisticalQuantileMeasureTypeParser;
        }

        //! Initialise debug support
        template <typename Iterator>
        void BinaryStatisticalQuantileMeasureGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void BinaryStatisticalQuantileMeasureGrammar<Iterator>::assignNamesToRules() {
            binaryStatisticalQuantileMeasureRule.name("binaryStatisticalQuantileMeasureRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void BinaryStatisticalQuantileMeasureGrammar<Iterator>::initialiseRulesDebugging() {
            debug(binaryStatisticalQuantileMeasureRule);
        }

    };

};


#endif
