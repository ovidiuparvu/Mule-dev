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

            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
            initializeErrorHandlingSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeGrammar() {
            initializeTemporalNumericCollectionRule();
            initializeTimeSeriesMeasureRule();
            initializeTimeSeriesComponentRule();
            initializeNumericMeasureRule();
        }

        //! Initialize the temporal numeric collection rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTemporalNumericCollectionRule() {
            temporalNumericCollectionRule
                =   temporalNumericMeasureCollectionRule
                |   changeTemporalNumericCollectionRule
                |   timeSeriesTimeSeriesComponentRule
                |   homogeneousHomogeneousTimeSeriesRule;

            temporalNumericMeasureCollectionRule
                =   (
                        '['
                        > unsignedRealParser
                        > ','
                        > unsignedRealParser
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

            timeSeriesTimeSeriesComponentRule
                =   (
                        timeSeriesMeasureRule
                        > '('
                        > timeSeriesComponentRule
                        > ','
                        > temporalNumericMeasureCollectionRule
                        > ')'
                    );

            homogeneousHomogeneousTimeSeriesRule
                =   (
                        homogeneousTimeSeriesMeasureRule
                        > '('
                        > homogeneousTimeSeriesComponentRule
                        > ','
                        > temporalNumericMeasureCollectionRule
                        > ')'
                    );
        }

        //! Initialize the time series measure rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTimeSeriesMeasureRule() {
            timeSeriesMeasureRule
                =   timeSeriesMeasureTypeParser;

            homogeneousTimeSeriesMeasureRule
                =   homogeneousTimeSeriesMeasureTypeParser;
        }

        //! Initialize the time series component rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTimeSeriesComponentRule() {
            timeSeriesComponentRule
                =   heterogeneousTimeSeriesComponentRule
                |   homogeneousTimeSeriesComponentRule;

            heterogeneousTimeSeriesComponentRule
                =   heterogeneousTimeSeriesComponentTypeParser;

            homogeneousTimeSeriesComponentRule
                =   homogeneousTimeSeriesComponentTypeParser;
        }

        //! Initialize the numeric measure rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeNumericMeasureRule() {
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

        //! Initialize debug support
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::assignNamesToRules() {
            assignNamesToTemporalNumericCollectionRules();
            assignNamesToTimeSeriesMeasureRules();
            assignNamesToTimeSeriesComponentRules();
            assignNamesToNumericMeasureRules();
        }

        //! Assign names to the temporal numeric collection rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::assignNamesToTemporalNumericCollectionRules() {
            temporalNumericCollectionRule           .name("temporalNumericCollectionRule");
            temporalNumericMeasureCollectionRule    .name("temporalNumericMeasureCollectionRule");
            changeTemporalNumericCollectionRule     .name("changeTemporalNumericCollectionRule");
            timeSeriesTimeSeriesComponentRule       .name("timeSeriesTimeSeriesComponentRule");
            homogeneousHomogeneousTimeSeriesRule    .name("homogeneousHomogeneousTimeSeriesRule");
        }

        //! Assign names to the time series measure rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::assignNamesToTimeSeriesMeasureRules() {
            timeSeriesMeasureRule           .name("timeSeriesMeasureRule");
            homogeneousTimeSeriesMeasureRule.name("homogeneousTimeSeriesMeasureRule");
        }

        //! Assign names to the time series component rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::assignNamesToTimeSeriesComponentRules() {
            timeSeriesComponentRule             .name("timeSeriesComponentRule");
            heterogeneousTimeSeriesComponentRule.name("heterogeneousTimeSeriesComponentRule");
            homogeneousTimeSeriesComponentRule  .name("homogeneousTimeSeriesComponentRule");
        }

        //! Assign names to the numeric measure rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::assignNamesToNumericMeasureRules() {
            numericMeasureRule          .name("numericMeasureRule");
            unaryNumericNumericRule     .name("unaryNumericNumericRule");
            binaryNumericNumericRule    .name("binaryNumericNumericRule");
        }


        //! Initialize the debugging of rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeRulesDebugging() {
            initializeTemporalNumericCollectionRuleDebugging();
            initializeTimeSeriesMeasureRuleDebugging();
            initializeTimeSeriesComponentRuleDebugging();
            initializeNumericMeasureRuleDebugging();
        }

        //! Initialize debugging for the temporal numeric collection rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTemporalNumericCollectionRuleDebugging() {
            debug(temporalNumericCollectionRule);
            debug(temporalNumericMeasureCollectionRule);
            debug(changeTemporalNumericCollectionRule);
            debug(timeSeriesTimeSeriesComponentRule);
            debug(homogeneousHomogeneousTimeSeriesRule);
        }

        //! Initialize debugging for the time series measures rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTimeSeriesMeasureRuleDebugging() {
            debug(timeSeriesMeasureRule);
            debug(homogeneousTimeSeriesMeasureRule);
        }

        //! Initialize debugging for the time series component rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTimeSeriesComponentRuleDebugging() {
            debug(timeSeriesComponentRule);
            debug(homogeneousTimeSeriesComponentRule);
            debug(heterogeneousTimeSeriesComponentRule);
        }

        //! Initialize debugging for the numeric measure rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeNumericMeasureRuleDebugging() {
            debug(numericMeasureRule);
            debug(unaryNumericNumericRule);
            debug(binaryNumericNumericRule);
        }

        //! Initialize the error handling routines
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeErrorHandlingSupport() {
            initializeTemporalNumericCollectionErrorHandlingSupport();
            initializeNumericMeasureErrorHandlingSupport();
        }

        //! Initialize the temporal numeric collection error handling support
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTemporalNumericCollectionErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                temporalNumericCollectionRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                temporalNumericMeasureCollectionRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                timeSeriesTimeSeriesComponentRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                homogeneousHomogeneousTimeSeriesRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialize the numeric measure error handling support
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeNumericMeasureErrorHandlingSupport() {
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
