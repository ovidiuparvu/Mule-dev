#ifndef NUMERICMEASURECOLLECTIONGRAMMARDEFINITION_HPP
#define NUMERICMEASURECOLLECTIONGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/NumericMeasureCollectionGrammar.hpp"

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
        NumericMeasureCollectionGrammar<Iterator>::NumericMeasureCollectionGrammar()
            : NumericMeasureCollectionGrammar::base_type(
                                                   numericMeasureCollectionRule,
                                                   "numericMeasureCollectionRule"
                                               ) {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseGrammar() {
            initialiseNumericMeasureCollectionRule();
            initialiseTemporalNumericCollectionRule();
            initialiseChangeMeasureRule();
            initialiseTimeseriesMeasureRule();
            initialiseTimeseriesComponentRule();
            initialiseNumericMeasureRule();
            initialiseNumericSpatialMeasureRule();
            initialiseSpatialMeasureRule();
            initialiseSubsetRule();
            initialiseConstraintsRules();
            initialiseComparatorRules();
        }

        //! Initialise the numeric measure collection rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericMeasureCollectionRule() {
            numericMeasureCollectionRule
                =   temporalNumericCollectionRule
                |   spatialMeasureCollectionRule;

            spatialMeasureCollectionRule
                =   (
                        spatialMeasureRule
                        > '('
                        > subsetRule
                        > ')'
                    );
        }

        //! Initialise the temporal numeric collection rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseTemporalNumericCollectionRule() {
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
                        > temporalNumericCollectionRule
                        > ')'
                    );

            homogeneousHomogeneousTimeseriesRule
                =   (
                        homogeneousTimeseriesMeasureRule
                        > '('
                        > homogeneousTimeseriesComponentRule
                        > ','
                        > temporalNumericCollectionRule
                        > ')'
                    );
        }

        //! Initialise the change measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseChangeMeasureRule() {
            changeMeasureRule
                =   changeMeasureTypeParser;
        }

        //! Initialise the timeseries measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseTimeseriesMeasureRule() {
            timeseriesMeasureRule
                =   timeseriesMeasureTypeParser;

            homogeneousTimeseriesMeasureRule
                =   homogeneousTimeseriesMeasureTypeParser;
        }

        //! Initialise the timeseries component rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseTimeseriesComponentRule() {
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
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericMeasureRule() {
            numericMeasureRule
                =   primaryNumericMeasureRule
                |   unaryNumericNumericRule
                |   binaryNumericNumericRule;

            primaryNumericMeasureRule
                =   numericSpatialMeasureRule
                |   qi::double_
                |   numericStateVariableRule;

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

        //! Initialise the numeric spatial measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericSpatialMeasureRule() {
            numericSpatialMeasureRule
                =   unaryStatisticalSpatialRule
                |   binaryStatisticalSpatialRule
                |   binaryStatisticalQuantileSpatialRule;

            unaryStatisticalSpatialRule
                =   (
                        unaryStatisticalMeasureRule
                        > '('
                        > spatialMeasureCollectionRule
                        > ')'
                    );

            binaryStatisticalSpatialRule
                =   (
                        binaryStatisticalMeasureRule
                        > '('
                        > spatialMeasureCollectionRule
                        > ','
                        > spatialMeasureCollectionRule
                        > ')'
                    );

            binaryStatisticalQuantileSpatialRule
                =   (
                        binaryStatisticalQuantileMeasureRule
                        > '('
                        > spatialMeasureCollectionRule
                        > ','
                        > qi::double_
                        > ')'
                    );
        }

        //! Initialise the spatial measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseSpatialMeasureRule() {
            spatialMeasureRule
                =   spatialMeasureTypeParser;
        }

        //! Initialise the subset rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseSubsetRule() {
            subsetRule
                =   subsetSpecificRule
                |   filterSubsetRule
                |   subsetSubsetOperationRule;

            subsetSpecificRule
                =   subsetSpecificTypeParser;

            filterSubsetRule
                =   (
                        qi::lit("filter")
                        > '('
                        > subsetSpecificRule
                        > ','
                        > constraintRule
                        > ')'
                    );

            subsetSubsetOperationRule
                =   (
                        subsetOperationTypeParser
                        > '('
                        > subsetRule
                        > ','
                        > subsetRule
                        > ')'
                    );
        }

        //! Initialise the constraints rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseConstraintsRules() {
            initialiseConstraintRule();
            initialisePrimaryConstraintRule();
            initialiseFilterNumericMeasureRule();
            initialiseComposedConstraintRule();
        }

        //! Initialise the constraint rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseConstraintRule() {
            constraintRule
                =   primaryConstraintRule
                    >> *(
                            (orConstraintRule)
                        |   (andConstraintRule)
                        |   (implicationConstraintRule)
                        |   (equivalenceConstraintRule)
                    );
        }

        //! Initialise the primary constraint rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialisePrimaryConstraintRule() {
            primaryConstraintRule
                =   notConstraintRule
                |   unaryTypeConstraintRule
                |   unarySpatialConstraintRule
                |   ('(' > constraintRule > ')');

            notConstraintRule
                =   ('~' > constraintRule);

            unaryTypeConstraintRule
                =   qi::lit("type")
                    > comparatorRule
                    > filterNumericMeasureRule;

            unarySpatialConstraintRule
                =   spatialMeasureRule
                    > comparatorRule
                    > filterNumericMeasureRule;
        }

        //! Initialise the filter numeric measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseFilterNumericMeasureRule() {
            filterNumericMeasureRule
                =   primaryNumericMeasureRule
                |   spatialMeasureRule
                |   unaryNumericFilterRule
                |   binaryNumericFilterRule;

            unaryNumericFilterRule
                =   (
                        unaryNumericMeasureRule
                        > '('
                        > filterNumericMeasureRule
                        > ')'
                    );

            binaryNumericFilterRule
                =   (
                        binaryNumericMeasureRule
                        > '('
                        > filterNumericMeasureRule
                        > ','
                        > filterNumericMeasureRule
                        > ')'
                    );
        }

        //! Initialise the composed constraint rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseComposedConstraintRule() {
            andConstraintRule
                =   ('^' > constraintRule);

            orConstraintRule
                =   ('V' > constraintRule);

            implicationConstraintRule
                =   ("=>" > constraintRule);

            equivalenceConstraintRule
                =   ("<=>" > constraintRule);
        }

        //! Initialise the comparator rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseComparatorRules() {
            comparatorRule
                =   comparatorTypeParser;
        }

        //! Initialise debug support
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToRules() {
            assignNamesToNumericMeasureCollectionRules();
            assignNamesToTemporalNumericCollectionRules();
            assignNamesToChangeMeasureRules();
            assignNamesToTimeseriesMeasureRules();
            assignNamesToTimeseriesComponentRules();
            assignNamesToNumericMeasureRules();
            assignNamesToNumericSpatialMeasureRules();
            assignNamesToSubsetRules();
            assignNamesToConstraintsRules();
            assignNamesToSpatialMeasureRules();
            assignNamesToComparatorRules();
        }

        //! Assign names to the numeric measure collection rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToNumericMeasureCollectionRules() {
            numericMeasureCollectionRule        .name("numericMeasureCollectionRule");
            spatialMeasureCollectionRule        .name("spatialMeasureCollectionRule");
        }

        //! Assign names to the temporal numeric collection rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToTemporalNumericCollectionRules() {
            temporalNumericCollectionRule           .name("temporalNumericCollectionRule");
            temporalNumericMeasureCollectionRule    .name("temporalNumericMeasureCollectionRule");
            changeTemporalNumericCollectionRule     .name("changeTemporalNumericCollectionRule");
            timeseriesTimeseriesComponentRule       .name("timeseriesTimeseriesComponentRule");
            homogeneousHomogeneousTimeseriesRule    .name("homogeneousHomogeneousTimeseriesRule");
        }

        //! Assign names to the change measure rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToChangeMeasureRules() {
            changeMeasureRule.name("changeMeasureRule");
        }

        //! Assign names to the timeseries measure rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToTimeseriesMeasureRules() {
            timeseriesMeasureRule           .name("timeseriesMeasureRule");
            homogeneousTimeseriesMeasureRule.name("homogeneousTimeseriesMeasureRule");
        }

        //! Assign names to the timeseries component rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToTimeseriesComponentRules() {
            timeseriesComponentRule             .name("timeseriesComponentRule");
            heterogeneousTimeseriesComponentRule.name("heterogeneousTimeseriesComponentRule");
            homogeneousTimeseriesComponentRule  .name("homogeneousTimeseriesComponentRule");
        }

        //! Assign names to the numeric measure rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToNumericMeasureRules() {
            numericMeasureRule          .name("numericMeasureRule");
            primaryNumericMeasureRule   .name("primaryNumericMeasureRule");
            unaryNumericNumericRule     .name("unaryNumericNumericRule");
            binaryNumericNumericRule    .name("binaryNumericNumericRule");
        }

        //! Assign names to the numeric spatial measure rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToNumericSpatialMeasureRules() {
            numericSpatialMeasureRule           .name("numericSpatialRule");
            unaryStatisticalSpatialRule         .name("unarySubsetRule");
            binaryStatisticalSpatialRule        .name("binaryStatisticalSpatialRule");
            binaryStatisticalQuantileSpatialRule.name("binaryStatisticalQuantileSpatialRule");
        }

        //! Assign names to the subset rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToSubsetRules() {
            subsetRule                  .name("subsetRule");
            subsetSpecificRule          .name("subsetSpecificRule");
            filterSubsetRule            .name("filterSubsetRule");
            subsetSubsetOperationRule   .name("subsetSubsetOperationRule");
        }

        //! Assign names to constraints rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToConstraintsRules() {
            assignNamesToConstraintRules();
            assignNamesToPrimaryConstraintRules();
            assignNamesToFilterNumericMeasureRules();
            assignNamesToComposedConstraintRules();
        }

        //! Assign names to the constraint rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToConstraintRules() {
            constraintRule.name("constraintRule");
        }

        //! Assign names to the primary constraint rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToPrimaryConstraintRules() {
            primaryConstraintRule       .name("primaryConstraintRule");
            notConstraintRule           .name("notConstraintRule");
            unaryTypeConstraintRule     .name("unaryTypeConstraintRule");
            unarySpatialConstraintRule  .name("unarySpatialConstraintRule");
        }

        //! Assign names to the filter numeric measure rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToFilterNumericMeasureRules() {
            filterNumericMeasureRule.name("filterNumericMeasureRule");
            unaryNumericFilterRule  .name("unaryNumericFilterRule");
            binaryNumericFilterRule .name("binaryNumericFilterRule");
        }

        //! Assign names to the composed constraint rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToComposedConstraintRules() {
            andConstraintRule           .name("andConstraintRule");
            orConstraintRule            .name("orConstraintRule");
            implicationConstraintRule   .name("implicationConstraintRule");
            equivalenceConstraintRule   .name("equivalenceConstraintRule");
        }

        //! Assign names to the spatial measure rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToSpatialMeasureRules() {
            spatialMeasureRule.name("spatialMeasureRule");
        }

        //! Assign names to the comparator rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToComparatorRules() {
            comparatorRule.name("comparatorRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseRulesDebugging() {
            initialiseNumericMeasureCollectionRuleDebugging();
            initialiseTemporalNumericCollectionRuleDebugging();
            initialiseChangeMeasureRuleDebugging();
            initialiseTimeseriesMeasureRuleDebugging();
            initialiseTimeseriesComponentRuleDebugging();
            initialiseNumericMeasureRuleDebugging();
            initialiseNumericSpatialMeasureRuleDebugging();
            initialiseSubsetRuleDebugging();
            initialiseConstraintsRulesDebugging();
            initialiseSpatialMeasureRuleDebugging();
            initialiseComparatorRuleDebugging();
        }

        //! Initialise debugging for the numeric measure collection rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericMeasureCollectionRuleDebugging() {
            debug(numericMeasureCollectionRule);
            debug(spatialMeasureCollectionRule);
        }

        //! Initialise debugging for the temporal numeric collection rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseTemporalNumericCollectionRuleDebugging() {
            debug(temporalNumericCollectionRule);
            debug(temporalNumericMeasureCollectionRule);
            debug(changeTemporalNumericCollectionRule);
            debug(timeseriesTimeseriesComponentRule);
            debug(homogeneousHomogeneousTimeseriesRule);
        }

        //! Initialise debugging for the change measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseChangeMeasureRuleDebugging() {
            debug(changeMeasureRule);
        }

        //! Initialise debugging for the timeseries measures rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseTimeseriesMeasureRuleDebugging() {
            debug(timeseriesMeasureRule);
            debug(homogeneousTimeseriesMeasureRule);
        }

        //! Initialise debugging for the timeseries component rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseTimeseriesComponentRuleDebugging() {
            debug(timeseriesComponentRule);
            debug(homogeneousTimeseriesComponentRule);
            debug(heterogeneousTimeseriesComponentRule);
        }

        //! Initialise debugging for the numeric measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericMeasureRuleDebugging() {
            debug(numericMeasureRule);
            debug(primaryNumericMeasureRule);
            debug(unaryNumericNumericRule);
            debug(binaryNumericNumericRule);
        }

        //! Initialise debugging for the numeric spatial measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericSpatialMeasureRuleDebugging() {
            debug(numericSpatialMeasureRule);
            debug(unaryStatisticalSpatialRule);
            debug(binaryStatisticalSpatialRule);
            debug(binaryStatisticalQuantileSpatialRule);
        }

        //! Initialise debugging for the subset rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseSubsetRuleDebugging() {
            debug(subsetRule);
            debug(subsetSpecificRule);
            debug(filterSubsetRule);
            debug(subsetSubsetOperationRule);
        }

        //! Initialise the debugging of the constraints rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseConstraintsRulesDebugging() {
            initialiseConstraintRuleDebugging();
            initialisePrimaryConstraintRuleDebugging();
            initialiseFilterNumericMeasureRuleDebugging();
            initialiseComposedConstraintRuleDebugging();
        }

        //! Initialise debugging for the constraint rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseConstraintRuleDebugging() {
            debug(constraintRule);
        }

        //! Initialise debugging for the primary constraint rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialisePrimaryConstraintRuleDebugging() {
            debug(primaryConstraintRule);
            debug(notConstraintRule);
            debug(unaryTypeConstraintRule);
            debug(unarySpatialConstraintRule);
        }

        //! Initialise debugging for the filter numeric measure rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseFilterNumericMeasureRuleDebugging() {
            debug(filterNumericMeasureRule);
            debug(unaryNumericFilterRule);
            debug(binaryNumericFilterRule);
        }

        //! Initialise debugging for the composed constraint rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseComposedConstraintRuleDebugging() {
            debug(andConstraintRule);
            debug(orConstraintRule);
            debug(implicationConstraintRule);
            debug(equivalenceConstraintRule);
        }

        //! Initialise debugging for the spatial measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseSpatialMeasureRuleDebugging() {
            debug(spatialMeasureRule);
        }

        //! Initialise debugging for the comparator rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseComparatorRuleDebugging() {
            debug(comparatorRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseErrorHandlingSupport() {
            initialiseNumericMeasureCollectionErrorHandlingSupport();
            initialiseTemporalNumericCollectionErrorHandlingSupport();
            initialiseNumericMeasureErrorHandlingSupport();
            initialiseNumericSpatialMeasureErrorHandlingSupport();
            initialiseSubsetErrorHandlingSupport();
            initialiseConstraintsErrorHandlingSupport();
        }

        //! Initialise the numeric measure collection error handling support
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericMeasureCollectionErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                numericMeasureCollectionRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                spatialMeasureCollectionRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the temporal numeric collection error handling support
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseTemporalNumericCollectionErrorHandlingSupport() {
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
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericMeasureErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                unaryNumericNumericRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                binaryNumericNumericRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the numeric spatial measure error handling support
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericSpatialMeasureErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                unaryStatisticalSpatialRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                binaryStatisticalSpatialRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                binaryStatisticalQuantileSpatialRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the subset error handling support
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseSubsetErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                filterSubsetRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                subsetSubsetOperationRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the constraints error handling support
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseConstraintsErrorHandlingSupport() {
            initialisePrimaryConstraintErrorHandlingSupport();
            initialiseFilterNumericMeasureErrorHandlingSupport();
            initialiseComposedConstraintErrorHandlingSupport();
        }

        //! Initialise the primary constraint error handling support
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialisePrimaryConstraintErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                primaryConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                notConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                unaryTypeConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                unarySpatialConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the filter numeric measure error handling support
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseFilterNumericMeasureErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                filterNumericMeasureRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                unaryNumericFilterRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                binaryNumericFilterRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the composed constraint error handling support
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseComposedConstraintErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                andConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                orConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                implicationConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                equivalenceConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

    };

};


#endif
