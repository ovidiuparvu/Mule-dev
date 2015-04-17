#ifndef UNARYSTATISTICALMEASUREGRAMMARDEFINITION_HPP
#define UNARYSTATISTICALMEASUREGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/parsing/UnaryStatisticalMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        template <typename Iterator>
        UnaryStatisticalMeasureGrammar<Iterator>::UnaryStatisticalMeasureGrammar()
            : UnaryStatisticalMeasureGrammar::base_type(
                                                  unaryStatisticalMeasureRule,
                                                  "unaryStatisticalMeasureRule"
                                              ) {
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void UnaryStatisticalMeasureGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void UnaryStatisticalMeasureGrammar<Iterator>::initializeGrammar() {
            unaryStatisticalMeasureRule
                =   unaryStatisticalMeasureTypeParser;
        }

        //! Initialize debug support
        template <typename Iterator>
        void UnaryStatisticalMeasureGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void UnaryStatisticalMeasureGrammar<Iterator>::assignNamesToRules() {
            unaryStatisticalMeasureRule.name("unaryStatisticalMeasureRule");
        }

        //! Initialize the debugging of rules
        template <typename Iterator>
        void UnaryStatisticalMeasureGrammar<Iterator>::initializeRulesDebugging() {
            debug(unaryStatisticalMeasureRule);
        }

    };

};


#endif
