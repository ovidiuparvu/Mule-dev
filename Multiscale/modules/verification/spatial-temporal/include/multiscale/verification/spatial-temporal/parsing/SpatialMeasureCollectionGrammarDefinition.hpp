#ifndef SPATIALMEASURECOLLECTIONGRAMMARDEFINITION_HPP
#define SPATIALMEASURECOLLECTIONGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SpatialMeasureCollectionGrammar.hpp"

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
        SpatialMeasureCollectionGrammar<Iterator>::SpatialMeasureCollectionGrammar()
            : SpatialMeasureCollectionGrammar::base_type(
                                                   spatialMeasureCollectionRule,
                                                   "spatialMeasureCollectionRule"
                                               ),
              primaryNumericMeasureRule(
                  std::make_shared<PrimaryNumericMeasureGrammar<Iterator>>(this)
              ) {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseGrammar() {
            initialiseSpatialMeasureCollectionRule();
            initialiseSpatialMeasureRule();
            initialiseSubsetRule();
            initialiseConstraintsRules();
        }

        //! Initialise the spatial measure collection rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseSpatialMeasureCollectionRule() {
            spatialMeasureCollectionRule
                =   primarySpatialMeasureCollectionRule
                |   unaryNumericSpatialMeasureCollectionRule
                |   binaryNumericSpatialMeasureCollectionRule;

            primarySpatialMeasureCollectionRule
                =   (
                        spatialMeasureRule
                        > '('
                        > subsetRule
                        > ')'
                    );

            unaryNumericSpatialMeasureCollectionRule
                =   (
                        unaryNumericMeasureRule
                        > '('
                        > spatialMeasureCollectionRule
                        > ')'
                    );

            binaryNumericSpatialMeasureCollectionRule
                =   (
                        binaryNumericMeasureRule
                        > '('
                        > spatialMeasureCollectionRule
                        > ','
                        > spatialMeasureCollectionRule
                        > ')'
                    );
        }

        //! Initialise the spatial measure rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseSpatialMeasureRule() {
            spatialMeasureRule
                =   spatialMeasureTypeParser;
        }

        //! Initialise the subset rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseSubsetRule() {
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
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseConstraintsRules() {
            initialiseConstraintRule();
            initialisePrimaryConstraintRule();
            initialiseFilterNumericMeasureRule();
            initialiseComposedConstraintRule();
        }

        //! Initialise the constraint rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseConstraintRule() {
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
        void SpatialMeasureCollectionGrammar<Iterator>::initialisePrimaryConstraintRule() {
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
                    > semanticTypeRule;

            unarySpatialConstraintRule
                =   spatialMeasureRule
                    > comparatorRule
                    > filterNumericMeasureRule;
        }

        //! Initialise the filter numeric measure rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseFilterNumericMeasureRule() {
            filterNumericMeasureRule
                =   (*primaryNumericMeasureRule)
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
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseComposedConstraintRule() {
            andConstraintRule
                =   ('^' > constraintRule);

            orConstraintRule
                =   ('V' > constraintRule);

            implicationConstraintRule
                =   ("=>" > constraintRule);

            equivalenceConstraintRule
                =   ("<=>" > constraintRule);
        }

        //! Initialise debug support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::assignNamesToRules() {
            assignNamesToSpatialMeasureCollectionRules();
            assignNamesToSpatialMeasureRules();
            assignNamesToSubsetRules();
            assignNamesToConstraintsRules();
        }

        //! Assign names to the spatial measure collection rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::assignNamesToSpatialMeasureCollectionRules() {
            spatialMeasureCollectionRule                .name("spatialMeasureCollectionRule");
            primarySpatialMeasureCollectionRule         .name("primarySpatialMeasureCollectionRule");
            unaryNumericSpatialMeasureCollectionRule    .name("unaryNumericSpatialMeasureCollectionRule");
            binaryNumericSpatialMeasureCollectionRule   .name("binaryNumericSpatialMeasureCollectionRule");
        }

        //! Assign names to the spatial measure rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::assignNamesToSpatialMeasureRules() {
            spatialMeasureRule.name("spatialMeasureRule");
        }

        //! Assign names to the subset rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::assignNamesToSubsetRules() {
            subsetRule                  .name("subsetRule");
            subsetSpecificRule          .name("subsetSpecificRule");
            filterSubsetRule            .name("filterSubsetRule");
            subsetSubsetOperationRule   .name("subsetSubsetOperationRule");
        }

        //! Assign names to constraints rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::assignNamesToConstraintsRules() {
            assignNamesToConstraintRules();
            assignNamesToPrimaryConstraintRules();
            assignNamesToFilterNumericMeasureRules();
            assignNamesToComposedConstraintRules();
        }

        //! Assign names to the constraint rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::assignNamesToConstraintRules() {
            constraintRule.name("constraintRule");
        }

        //! Assign names to the primary constraint rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::assignNamesToPrimaryConstraintRules() {
            primaryConstraintRule       .name("primaryConstraintRule");
            notConstraintRule           .name("notConstraintRule");
            unaryTypeConstraintRule     .name("unaryTypeConstraintRule");
            unarySpatialConstraintRule  .name("unarySpatialConstraintRule");
        }

        //! Assign names to the filter numeric measure rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::assignNamesToFilterNumericMeasureRules() {
            filterNumericMeasureRule.name("filterNumericMeasureRule");
            unaryNumericFilterRule  .name("unaryNumericFilterRule");
            binaryNumericFilterRule .name("binaryNumericFilterRule");
        }

        //! Assign names to the composed constraint rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::assignNamesToComposedConstraintRules() {
            andConstraintRule           .name("andConstraintRule");
            orConstraintRule            .name("orConstraintRule");
            implicationConstraintRule   .name("implicationConstraintRule");
            equivalenceConstraintRule   .name("equivalenceConstraintRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseRulesDebugging() {
            initialiseSpatialMeasureCollectionRuleDebugging();
            initialiseSpatialMeasureRuleDebugging();
            initialiseSubsetRuleDebugging();
            initialiseConstraintsRulesDebugging();
        }

        //! Initialise debugging for the spatial measure collection rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseSpatialMeasureCollectionRuleDebugging() {
            debug(spatialMeasureCollectionRule);
            debug(primarySpatialMeasureCollectionRule);
            debug(unaryNumericSpatialMeasureCollectionRule);
            debug(binaryNumericSpatialMeasureCollectionRule);
        }

        //! Initialise debugging for the spatial measure rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseSpatialMeasureRuleDebugging() {
            debug(spatialMeasureRule);
        }

        //! Initialise debugging for the subset rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseSubsetRuleDebugging() {
            debug(subsetRule);
            debug(subsetSpecificRule);
            debug(filterSubsetRule);
            debug(subsetSubsetOperationRule);
        }

        //! Initialise the debugging of the constraints rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseConstraintsRulesDebugging() {
            initialiseConstraintRuleDebugging();
            initialisePrimaryConstraintRuleDebugging();
            initialiseFilterNumericMeasureRuleDebugging();
            initialiseComposedConstraintRuleDebugging();
        }

        //! Initialise debugging for the constraint rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseConstraintRuleDebugging() {
            debug(constraintRule);
        }

        //! Initialise debugging for the primary constraint rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialisePrimaryConstraintRuleDebugging() {
            debug(primaryConstraintRule);
            debug(notConstraintRule);
            debug(unaryTypeConstraintRule);
            debug(unarySpatialConstraintRule);
        }

        //! Initialise debugging for the filter numeric measure rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseFilterNumericMeasureRuleDebugging() {
            debug(filterNumericMeasureRule);
            debug(unaryNumericFilterRule);
            debug(binaryNumericFilterRule);
        }

        //! Initialise debugging for the composed constraint rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseComposedConstraintRuleDebugging() {
            debug(andConstraintRule);
            debug(orConstraintRule);
            debug(implicationConstraintRule);
            debug(equivalenceConstraintRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseErrorHandlingSupport() {
            initialiseSpatialMeasureCollectionErrorHandlingSupport();
            initialiseSubsetErrorHandlingSupport();
            initialiseConstraintsErrorHandlingSupport();
        }

        //! Initialise the spatial measure collection error handling support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseSpatialMeasureCollectionErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                primarySpatialMeasureCollectionRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                unaryNumericSpatialMeasureCollectionRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                binaryNumericSpatialMeasureCollectionRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the subset error handling support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseSubsetErrorHandlingSupport() {
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
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseConstraintsErrorHandlingSupport() {
            initialisePrimaryConstraintErrorHandlingSupport();
            initialiseFilterNumericMeasureErrorHandlingSupport();
            initialiseComposedConstraintErrorHandlingSupport();
        }

        //! Initialise the primary constraint error handling support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialisePrimaryConstraintErrorHandlingSupport() {
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
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseFilterNumericMeasureErrorHandlingSupport() {
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
        void SpatialMeasureCollectionGrammar<Iterator>::initialiseComposedConstraintErrorHandlingSupport() {
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
