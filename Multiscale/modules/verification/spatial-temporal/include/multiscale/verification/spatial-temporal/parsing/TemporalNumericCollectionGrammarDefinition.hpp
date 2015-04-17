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
            initializeTimeseriesMeasureRule();
            initializeTimeseriesComponentRule();
            initializeNumericMeasureRule();
        }

        //! Initialize the temporal numeric collection rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTemporalNumericCollectionRule() {
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

        //! Initialize the timeseries measure rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTimeseriesMeasureRule() {
            timeseriesMeasureRule
                =   timeseriesMeasureTypeParser;

            homogeneousTimeseriesMeasureRule
                =   homogeneousTimeseriesMeasureTypeParser;
        }

        //! Initialize the timeseries component rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTimeseriesComponentRule() {
            timeseriesComponentRule
                =   heterogeneousTimeseriesComponentRule
                |   homogeneousTimeseriesComponentRule;

            heterogeneousTimeseriesComponentRule
                =   heterogeneousTimeseriesComponentTypeParser;

            homogeneousTimeseriesComponentRule
                =   homogeneousTimeseriesComponentTypeParser;
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


        //! Initialize the debugging of rules
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeRulesDebugging() {
            initializeTemporalNumericCollectionRuleDebugging();
            initializeTimeseriesMeasureRuleDebugging();
            initializeTimeseriesComponentRuleDebugging();
            initializeNumericMeasureRuleDebugging();
        }

        //! Initialize debugging for the temporal numeric collection rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTemporalNumericCollectionRuleDebugging() {
            debug(temporalNumericCollectionRule);
            debug(temporalNumericMeasureCollectionRule);
            debug(changeTemporalNumericCollectionRule);
            debug(timeseriesTimeseriesComponentRule);
            debug(homogeneousHomogeneousTimeseriesRule);
        }

        //! Initialize debugging for the timeseries measures rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTimeseriesMeasureRuleDebugging() {
            debug(timeseriesMeasureRule);
            debug(homogeneousTimeseriesMeasureRule);
        }

        //! Initialize debugging for the timeseries component rule
        template <typename Iterator>
        void TemporalNumericCollectionGrammar<Iterator>::initializeTimeseriesComponentRuleDebugging() {
            debug(timeseriesComponentRule);
            debug(homogeneousTimeseriesComponentRule);
            debug(heterogeneousTimeseriesComponentRule);
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
                timeseriesTimeseriesComponentRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                homogeneousHomogeneousTimeseriesRule,
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
