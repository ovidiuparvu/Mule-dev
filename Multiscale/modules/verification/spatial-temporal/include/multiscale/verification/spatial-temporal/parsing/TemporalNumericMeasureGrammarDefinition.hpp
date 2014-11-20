#ifndef TEMPORALNUMERICMEASUREGRAMMARDEFINITION_HPP
#define TEMPORALNUMERICMEASUREGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/TemporalNumericMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

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
            initialiseNumericMeasureCollectionRule();
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

        //! Initialise the numeric measure collection rule
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseNumericMeasureCollectionRule() {
            numericMeasureCollectionRule
                =   temporalNumericCollectionRule
                |   spatialMeasureCollectionRule;
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
            assignNamesToNumericMeasureCollectionRules();
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

        //! Assign names to the numeric measure collection rules
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::assignNamesToNumericMeasureCollectionRules() {
            numericMeasureCollectionRule.name("numericMeasureCollectionRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseRulesDebugging() {
            initialiseTemporalNumericMeasureRuleDebugging();
            initialiseNumericStatisticalMeasureRuleDebugging();
            initialiseNumericMeasureCollectionRuleDebugging();
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

        //! Initialise debugging for the numeric measure collection rule
        template <typename Iterator>
        void TemporalNumericMeasureGrammar<Iterator>::initialiseNumericMeasureCollectionRuleDebugging() {
            debug(numericMeasureCollectionRule);
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
