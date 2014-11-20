#ifndef TEMPORALNUMERICCOLLECTIONGRAMMARDEFINITION_HPP
#define TEMPORALNUMERICCOLLECTIONGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SpatialMeasureCollectionGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/TemporalNumericCollectionGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

#include <memory>
#include <string>


namespace multiscale {

    namespace verification {

        // Create a lazy error handler function
        phoenix::function<UnexpectedTokenErrorHandler> const
            handleUnexpectedTokenError = UnexpectedTokenErrorHandler();


        template <typename Iterator>
        TemporalNumericCollectionGrammar<Iterator>::TemporalNumericCollectionGrammar()
            : TemporalNumericCollectionGrammar::base_type(
                                                    temporalNumericCollectionRule,
                                                    "temporalNumericCollectionRule"
                                                ) {
            // Define the dependent sub-grammars
            spatialMeasureCollectionGrammar = std::make_shared<SpatialMeasureCollectionGrammar<Iterator>>();
            primaryNumericMeasureRule = std::make_shared<PrimaryNumericMeasureGrammar<Iterator>>(
                                            spatialMeasureCollectionGrammar.get()
                                        );

            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseGrammar() {
            initialiseTemporalNumericCollectionRule();
            initialiseTimeseriesMeasureRule();
            initialiseTimeseriesComponentRule();
            initialiseNumericMeasureRule();
        }

        //! Initialise the temporal numeric collection rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseTemporalNumericCollectionRule() {
            temporalNumericCollectionRule
                =   temporalNumericMeasureCollectionRule
                |   changeTemporalNumericCollectionRule
                |   timeseriesTimeseriesComponentRule
                |   homogeneousHomogeneousTimeseriesRule;

            temporalNumericMeasureCollectionRule
                =   (
                        '['
                        > qi::ulong_
                        > ','
                        > qi::ulong_
                        > ']'
                        > numericMeasureRule
                    );

            changeTemporalNumericCollectionRule
                =   (
                        changeMeasureRule
                        > '('
                        > temporalNumericCollectionRule
                        > ')'
                    );

            timeseriesTimeseriesComponentRule
                =   (
                        timeseriesMeasureRule
                        > '('
                        > timeseriesComponentRule
                        > ','
                        > temporalNumericMeasureCollectionRule
                        > ')'
                    );

            homogeneousHomogeneousTimeseriesRule
                =   (
                        homogeneousTimeseriesMeasureRule
                        > '('
                        > homogeneousTimeseriesComponentRule
                        > ','
                        > temporalNumericMeasureCollectionRule
                        > ')'
                    );
        }

        //! Initialise the timeseries measure rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseTimeseriesMeasureRule() {
            timeseriesMeasureRule
                =   timeseriesMeasureTypeParser;

            homogeneousTimeseriesMeasureRule
                =   homogeneousTimeseriesMeasureTypeParser;
        }

        //! Initialise the timeseries component rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseTimeseriesComponentRule() {
            timeseriesComponentRule
                =   heterogeneousTimeseriesComponentRule
                |   homogeneousTimeseriesComponentRule;

            heterogeneousTimeseriesComponentRule
                =   heterogeneousTimeseriesComponentTypeParser;

            homogeneousTimeseriesComponentRule
                =   homogeneousTimeseriesComponentTypeParser;
        }

        //! Initialise the numeric measure rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseNumericMeasureRule() {
            numericMeasureRule
                =   (*primaryNumericMeasureRule)
                |   unaryNumericNumericRule
                |   binaryNumericNumericRule;

            unaryNumericNumericRule
                =   (
                        unaryNumericMeasureRule
                        > '('
                        > numericMeasureRule
                        > ')'
                    );

            binaryNumericNumericRule
                =   (
                        binaryNumericMeasureRule
                        > '('
                        > numericMeasureRule
                        > ','
                        > numericMeasureRule
                        > ')'
                    );
        }

        //! Initialise debug support
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::assignNamesToRules() {
            assignNamesToTemporalNumericCollectionRules();
            assignNamesToTimeseriesMeasureRules();
            assignNamesToTimeseriesComponentRules();
            assignNamesToNumericMeasureRules();
        }

        //! Assign names to the temporal numeric collection rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::assignNamesToTemporalNumericCollectionRules() {
            temporalNumericCollectionRule           .name("temporalNumericCollectionRule");
            temporalNumericMeasureCollectionRule    .name("temporalNumericMeasureCollectionRule");
            changeTemporalNumericCollectionRule     .name("changeTemporalNumericCollectionRule");
            timeseriesTimeseriesComponentRule       .name("timeseriesTimeseriesComponentRule");
            homogeneousHomogeneousTimeseriesRule    .name("homogeneousHomogeneousTimeseriesRule");
        }

        //! Assign names to the timeseries measure rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::assignNamesToTimeseriesMeasureRules() {
            timeseriesMeasureRule           .name("timeseriesMeasureRule");
            homogeneousTimeseriesMeasureRule.name("homogeneousTimeseriesMeasureRule");
        }

        //! Assign names to the timeseries component rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::assignNamesToTimeseriesComponentRules() {
            timeseriesComponentRule             .name("timeseriesComponentRule");
            heterogeneousTimeseriesComponentRule.name("heterogeneousTimeseriesComponentRule");
            homogeneousTimeseriesComponentRule  .name("homogeneousTimeseriesComponentRule");
        }

        //! Assign names to the numeric measure rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::assignNamesToNumericMeasureRules() {
            numericMeasureRule          .name("numericMeasureRule");
            unaryNumericNumericRule     .name("unaryNumericNumericRule");
            binaryNumericNumericRule    .name("binaryNumericNumericRule");
        }


        //! Initialise the debugging of rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseRulesDebugging() {
            initialiseTemporalNumericCollectionRuleDebugging();
            initialiseTimeseriesMeasureRuleDebugging();
            initialiseTimeseriesComponentRuleDebugging();
            initialiseNumericMeasureRuleDebugging();
        }

        //! Initialise debugging for the temporal numeric collection rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseTemporalNumericCollectionRuleDebugging() {
            debug(temporalNumericCollectionRule);
            debug(temporalNumericMeasureCollectionRule);
            debug(changeTemporalNumericCollectionRule);
            debug(timeseriesTimeseriesComponentRule);
            debug(homogeneousHomogeneousTimeseriesRule);
        }

        //! Initialise debugging for the timeseries measures rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseTimeseriesMeasureRuleDebugging() {
            debug(timeseriesMeasureRule);
            debug(homogeneousTimeseriesMeasureRule);
        }

        //! Initialise debugging for the timeseries component rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseTimeseriesComponentRuleDebugging() {
            debug(timeseriesComponentRule);
            debug(homogeneousTimeseriesComponentRule);
            debug(heterogeneousTimeseriesComponentRule);
        }

        //! Initialise debugging for the numeric measure rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseNumericMeasureRuleDebugging() {
            debug(numericMeasureRule);
            debug(unaryNumericNumericRule);
            debug(binaryNumericNumericRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseErrorHandlingSupport() {
            initialiseTemporalNumericCollectionErrorHandlingSupport();
            initialiseNumericMeasureErrorHandlingSupport();
        }

        //! Initialise the temporal numeric collection error handling support
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseTemporalNumericCollectionErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                temporalNumericCollectionRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                temporalNumericMeasureCollectionRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                timeseriesTimeseriesComponentRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                homogeneousHomogeneousTimeseriesRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the numeric measure error handling support
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialiseNumericMeasureErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                unaryNumericNumericRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                binaryNumericNumericRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

    };

};


#endif
