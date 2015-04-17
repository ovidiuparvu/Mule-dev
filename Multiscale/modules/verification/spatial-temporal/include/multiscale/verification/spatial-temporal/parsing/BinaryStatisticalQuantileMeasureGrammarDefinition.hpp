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
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void BinaryStatisticalQuantileMeasureGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void BinaryStatisticalQuantileMeasureGrammar<Iterator>::initializeGrammar() {
            binaryStatisticalQuantileMeasureRule
                =   binaryStatisticalQuantileMeasureTypeParser;
        }

        //! Initialize debug support
        template <typename Iterator>
        void BinaryStatisticalQuantileMeasureGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void BinaryStatisticalQuantileMeasureGrammar<Iterator>::assignNamesToRules() {
            binaryStatisticalQuantileMeasureRule.name("binaryStatisticalQuantileMeasureRule");
        }

        //! Initialize the debugging of rules
        template <typename Iterator>
        void BinaryStatisticalQuantileMeasureGrammar<Iterator>::initializeRulesDebugging() {
            debug(binaryStatisticalQuantileMeasureRule);
        }

    };

};


#endif
