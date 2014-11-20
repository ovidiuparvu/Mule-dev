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
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void UnaryStatisticalMeasureGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void UnaryStatisticalMeasureGrammar<Iterator>::initialiseGrammar() {
            unaryStatisticalMeasureRule
                =   unaryStatisticalMeasureTypeParser;
        }

        //! Initialise debug support
        template <typename Iterator>
        void UnaryStatisticalMeasureGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void UnaryStatisticalMeasureGrammar<Iterator>::assignNamesToRules() {
            unaryStatisticalMeasureRule.name("unaryStatisticalMeasureRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void UnaryStatisticalMeasureGrammar<Iterator>::initialiseRulesDebugging() {
            debug(unaryStatisticalMeasureRule);
        }

    };

};


#endif
