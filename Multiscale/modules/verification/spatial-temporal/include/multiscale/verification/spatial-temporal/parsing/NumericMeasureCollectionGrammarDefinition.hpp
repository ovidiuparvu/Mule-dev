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
            initialiseNumericMeasureRule();
            initialiseNumericSpatialMeasureRule();
            initialiseNaryNumericMeasureRule();
            initialiseStatisticalMeasureRule();
            initialiseSpatialMeasureRule();
            initialiseSubsetRule();
            initialiseConstraintsRules();
            initialiseComparatorRules();
        }

        //! Initialise the numeric measure collection rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericMeasureCollectionRule() {
            numericMeasureCollectionRule
                =   temporalNumericMeasureCollectionRule
                |   spatialMeasureCollectionRule;

            temporalNumericMeasureCollectionRule
                =   (
                        '['
                        > qi::ulong_
                        > ','
                        > qi::ulong_
                        > ']'
                        > numericMeasureRule
                    );

            spatialMeasureCollectionRule
                =   (
                        spatialMeasureRule
                        > '('
                        > subsetRule
                        > ')'
                    );
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

        //! Initialise the n-ary numeric measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNaryNumericMeasureRule() {
            unaryNumericMeasureRule
                =   unaryNumericMeasureTypeParser;

            binaryNumericMeasureRule
                =   binaryNumericMeasureTypeParser;
        }

        //! Initialise the statistical measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseStatisticalMeasureRule() {
            unaryStatisticalMeasureRule
                =   unaryStatisticalMeasureTypeParser;

            binaryStatisticalMeasureRule
                =   binaryStatisticalMeasureTypeParser;

            binaryStatisticalQuantileMeasureRule
                =   binaryStatisticalQuantileMeasureTypeParser;
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
            assignNamesToNumericMeasureRules();
            assignNamesToNumericSpatialMeasureRules();
            assignNamesToNaryNumericMeasureRules();
            assignNamesToStatisticalMeasureRules();
            assignNamesToSubsetRules();
            assignNamesToConstraintsRules();
            assignNamesToSpatialMeasureRules();
            assignNamesToComparatorRules();
        }

        //! Assign names to the numeric measure collection rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToNumericMeasureCollectionRules() {
            numericMeasureCollectionRule        .name("numericMeasureCollectionRule");
            temporalNumericMeasureCollectionRule.name("temporalNumericMeasureCollectionRule");
            spatialMeasureCollectionRule        .name("spatialMeasureCollectionRule");
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

        //! Assign names to the n-ary numeric measure rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToNaryNumericMeasureRules() {
            unaryNumericMeasureRule     .name("unaryNumericMeasureRule");
            binaryNumericMeasureRule    .name("binaryNumericMeasureRule");
        }

        //! Assign names to the numeric statistical measure rules
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::assignNamesToStatisticalMeasureRules() {
            unaryStatisticalMeasureRule         .name("unaryStatisticalMeasureRule");
            binaryStatisticalMeasureRule        .name("binaryStatisticalMeasureRule");
            binaryStatisticalQuantileMeasureRule.name("binaryStatisticalQuantileMeasureRule");
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
            initialiseNumericMeasureRuleDebugging();
            initialiseNumericSpatialMeasureRuleDebugging();
            initialiseNaryNumericMeasureRuleDebugging();
            initialiseStatisticalMeasureRuleDebugging();
            initialiseSubsetRuleDebugging();
            initialiseConstraintsRulesDebugging();
            initialiseSpatialMeasureRuleDebugging();
            initialiseComparatorRuleDebugging();
        }

        //! Initialise debugging for the numeric measure collection rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNumericMeasureCollectionRuleDebugging() {
            debug(numericMeasureCollectionRule);
            debug(temporalNumericMeasureCollectionRule);
            debug(spatialMeasureCollectionRule);
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

        //! Initialise debugging for the n-ary numeric measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseNaryNumericMeasureRuleDebugging() {
            debug(unaryNumericMeasureRule);
            debug(binaryNumericMeasureRule);
        }

        //! Initialise debugging for the statistical measure rule
        template <typename Iterator>
        void NumericMeasureCollectionGrammar<Iterator>::initialiseStatisticalMeasureRuleDebugging() {
            debug(unaryStatisticalMeasureRule);
            debug(binaryStatisticalMeasureRule);
            debug(binaryStatisticalQuantileMeasureRule);
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
                temporalNumericMeasureCollectionRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                spatialMeasureCollectionRule,
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
