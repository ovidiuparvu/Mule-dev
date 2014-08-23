#ifndef TEMPORALNUMERICMEASUREGRAMMARDEFINITION_HPP
#define TEMPORALNUMERICMEASUREGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/TemporalNumericMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/qi_and_predicate.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Create a lazy error handler function
        phoenix::function<UnexpectedTokenErrorHandler> const
            handleUnexpectedTokenError = UnexpectedTokenErrorHandler();


        template <typename Iterator>
        TemporalNumericMeasureGrammar<Iterator>::TemporalNumericMeasureGrammar()
            : TemporalNumericMeasureGrammar::base_type(temporalNumericMeasureRule, "temporalNumericMeasureRule") {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseGrammar() {
            initialiseTemporalNumericMeasureRule();
            initialiseNumericStatisticalMeasureRule();
            initialiseNaryNumericMeasureRule();
            initialiseStatisticalMeasureRule();
        }

        //! Initialise the temporal numeric measure rule
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseTemporalNumericMeasureRule() {
            temporalNumericMeasureRule
                =   qi::double_
                |   numericStateVariableRule
                |   numericStatisticalMeasureRule
                |   unaryNumericTemporalRule
                |   binaryNumericTemporalRule;

            unaryNumericTemporalRule
                =   (
                        unaryNumericMeasureRule
                        > '('
                        > temporalNumericMeasureRule
                        > ')'
                    );

            binaryNumericTemporalRule
                =   (
                        binaryNumericMeasureRule
                        > '('
                        > temporalNumericMeasureRule
                        > ','
                        > temporalNumericMeasureRule
                        > ')'
                    );
        }

        //! Initialise the numeric statistical measure rules
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseNumericStatisticalMeasureRule() {
            numericStatisticalMeasureRule
                =   unaryStatisticalNumericRule
                |   binaryStatisticalNumericRule
                |   binaryStatisticalQuantileNumericRule;

            unaryStatisticalNumericRule
                =   (
                        unaryStatisticalMeasureRule
                        > '('
                        > numericMeasureCollectionRule
                        > ')'
                    );

            binaryStatisticalNumericRule
                =   (
                        binaryStatisticalMeasureRule
                        > '('
                        > numericMeasureCollectionRule
                        > ','
                        > numericMeasureCollectionRule
                        > ')'
                    );

            binaryStatisticalQuantileNumericRule
                =   (
                        binaryStatisticalQuantileMeasureRule
                        > '('
                        > numericMeasureCollectionRule
                        > ','
                        > qi::double_
                        > ')'
                    );
        }

        //! Initialise the n-ary numeric measure rule
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseNaryNumericMeasureRule() {
            unaryNumericMeasureRule
                =   unaryNumericMeasureTypeParser;

            binaryNumericMeasureRule
                =   binaryNumericMeasureTypeParser;
        }

        //! Initialise the statistical measure rule
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseStatisticalMeasureRule() {
            unaryStatisticalMeasureRule
                =   unaryStatisticalMeasureTypeParser;

            binaryStatisticalMeasureRule
                =   binaryStatisticalMeasureTypeParser;

            binaryStatisticalQuantileMeasureRule
                =   binaryStatisticalQuantileMeasureTypeParser;
        }

        //! Initialise debug support
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::assignNamesToRules() {
            assignNamesToTemporalNumericMeasureRules();
            assignNamesToNumericStatisticalMeasureRules();
            assignNamesToNaryNumericMeasureRules();
            assignNamesToStatisticalMeasureRules();
        }

        //! Assign names to the temporal numeric measure rules
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::assignNamesToTemporalNumericMeasureRules() {
            temporalNumericMeasureRule  .name("temporalNumericMeasureRule");
            unaryNumericTemporalRule    .name("unaryNumericTemporalRule");
            binaryNumericTemporalRule   .name("binaryNumericTemporalRule");
        }

        //! Assign names to the numeric statistical measure rules
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::assignNamesToNumericStatisticalMeasureRules() {
            numericStatisticalMeasureRule       .name("numericStatisticalMeasureRule");
            unaryStatisticalNumericRule         .name("unaryStatisticalNumericRule");
            binaryStatisticalNumericRule        .name("binaryStatisticalNumericRule");
            binaryStatisticalQuantileNumericRule.name("binaryStatisticalQuantileNumericRule");
        }

        //! Assign names to the n-ary numeric measure rules
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::assignNamesToNaryNumericMeasureRules() {
            unaryNumericMeasureRule     .name("unaryNumericMeasureRule");
            binaryNumericMeasureRule    .name("binaryNumericMeasureRule");
        }

        //! Assign names to the numeric statistical measure rules
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::assignNamesToStatisticalMeasureRules() {
            unaryStatisticalMeasureRule         .name("unaryStatisticalMeasureRule");
            binaryStatisticalMeasureRule        .name("binaryStatisticalMeasureRule");
            binaryStatisticalQuantileMeasureRule.name("binaryStatisticalQuantileMeasureRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseRulesDebugging() {
            initialiseTemporalNumericMeasureRuleDebugging();
            initialiseNumericStatisticalMeasureRuleDebugging();
            initialiseNaryNumericMeasureRuleDebugging();
            initialiseStatisticalMeasureRuleDebugging();
        }

        //! Initialise debugging for the temporal numeric measure rule
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseTemporalNumericMeasureRuleDebugging() {
            debug(temporalNumericMeasureRule);
            debug(unaryNumericTemporalRule);
            debug(binaryNumericTemporalRule);
        }

        //! Initialise debugging for the numeric statistical measure rule
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseNumericStatisticalMeasureRuleDebugging() {
            debug(numericStatisticalMeasureRule);
            debug(unaryStatisticalNumericRule);
            debug(binaryStatisticalNumericRule);
            debug(binaryStatisticalQuantileNumericRule);
        }

        //! Initialise debugging for the n-ary numeric measure rule
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseNaryNumericMeasureRuleDebugging() {
            debug(unaryNumericMeasureRule);
            debug(binaryNumericMeasureRule);
        }

        //! Initialise debugging for the statistical measure rule
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseStatisticalMeasureRuleDebugging() {
            debug(unaryStatisticalMeasureRule);
            debug(binaryStatisticalMeasureRule);
            debug(binaryStatisticalQuantileMeasureRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseErrorHandlingSupport() {
            initialiseTemporalNumericMeasureErrorHandlingSupport();
            initialiseNumericStatisticalMeasureErrorHandlingSupport();
        }

        //! Initialise the temporal numeric measure error handling support
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseTemporalNumericMeasureErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                temporalNumericMeasureRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                unaryNumericTemporalRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                binaryNumericTemporalRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the numeric statistical measure error handling support
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseNumericStatisticalMeasureErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                unaryStatisticalNumericRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                binaryStatisticalNumericRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                binaryStatisticalQuantileNumericRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

    };

};


#endif
