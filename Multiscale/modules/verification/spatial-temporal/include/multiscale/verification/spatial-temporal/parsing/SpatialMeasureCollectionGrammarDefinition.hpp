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
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
            initializeErrorHandlingSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeGrammar() {
            initializeSpatialMeasureCollectionRule();
            initializeSpatialMeasureRule();
            initializeSubsetRule();
            initializeConstraintsRules();
        }

        //! Initialize the spatial measure collection rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeSpatialMeasureCollectionRule() {
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

        //! Initialize the spatial measure rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeSpatialMeasureRule() {
            spatialMeasureRule
                =   spatialMeasureTypeParser;
        }

        //! Initialize the subset rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeSubsetRule() {
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

        //! Initialize the constraints rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeConstraintsRules() {
            initializeConstraintRule();
            initializePrimaryConstraintRule();
            initializeFilterNumericMeasureRule();
            initializeComposedConstraintRule();
        }

        //! Initialize the constraint rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeConstraintRule() {
            constraintRule
                =   primaryConstraintRule
                    >> *(
                            (orConstraintRule)
                        |   (andConstraintRule)
                        |   (implicationConstraintRule)
                        |   (equivalenceConstraintRule)
                    );
        }

        //! Initialize the primary constraint rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializePrimaryConstraintRule() {
            primaryConstraintRule
                =   notConstraintRule
                |   unaryScaleAndSubsystemConstraintRule
                |   unarySpatialConstraintRule
                |   ('(' > constraintRule > ')');

            notConstraintRule
                =   ('~' > constraintRule);

            unaryScaleAndSubsystemConstraintRule
                =   qi::lit(ScaleAndSubsystemStringGrammar<Iterator>::SCALE_AND_SUBSYSTEM_LABEL)
                    > comparatorRule
                    > scaleAndSubsystemRule;

            unarySpatialConstraintRule
                =   spatialMeasureRule
                    > comparatorRule
                    > filterNumericMeasureRule;
        }

        //! Initialize the filter numeric measure rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeFilterNumericMeasureRule() {
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

        //! Initialize the composed constraint rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeComposedConstraintRule() {
            andConstraintRule
                =   ('^' > constraintRule);

            orConstraintRule
                =   ('V' > constraintRule);

            implicationConstraintRule
                =   ("=>" > constraintRule);

            equivalenceConstraintRule
                =   ("<=>" > constraintRule);
        }

        //! Initialize debug support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
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
            primaryConstraintRule               .name("primaryConstraintRule");
            notConstraintRule                   .name("notConstraintRule");
            unaryScaleAndSubsystemConstraintRule.name("unaryScaleAndSubsystemConstraintRule");
            unarySpatialConstraintRule          .name("unarySpatialConstraintRule");
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

        //! Initialize the debugging of rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeRulesDebugging() {
            initializeSpatialMeasureCollectionRuleDebugging();
            initializeSpatialMeasureRuleDebugging();
            initializeSubsetRuleDebugging();
            initializeConstraintsRulesDebugging();
        }

        //! Initialize debugging for the spatial measure collection rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeSpatialMeasureCollectionRuleDebugging() {
            debug(spatialMeasureCollectionRule);
            debug(primarySpatialMeasureCollectionRule);
            debug(unaryNumericSpatialMeasureCollectionRule);
            debug(binaryNumericSpatialMeasureCollectionRule);
        }

        //! Initialize debugging for the spatial measure rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeSpatialMeasureRuleDebugging() {
            debug(spatialMeasureRule);
        }

        //! Initialize debugging for the subset rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeSubsetRuleDebugging() {
            debug(subsetRule);
            debug(subsetSpecificRule);
            debug(filterSubsetRule);
            debug(subsetSubsetOperationRule);
        }

        //! Initialize the debugging of the constraints rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeConstraintsRulesDebugging() {
            initializeConstraintRuleDebugging();
            initializePrimaryConstraintRuleDebugging();
            initializeFilterNumericMeasureRuleDebugging();
            initializeComposedConstraintRuleDebugging();
        }

        //! Initialize debugging for the constraint rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeConstraintRuleDebugging() {
            debug(constraintRule);
        }

        //! Initialize debugging for the primary constraint rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializePrimaryConstraintRuleDebugging() {
            debug(primaryConstraintRule);
            debug(notConstraintRule);
            debug(unaryScaleAndSubsystemConstraintRule);
            debug(unarySpatialConstraintRule);
        }

        //! Initialize debugging for the filter numeric measure rules
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeFilterNumericMeasureRuleDebugging() {
            debug(filterNumericMeasureRule);
            debug(unaryNumericFilterRule);
            debug(binaryNumericFilterRule);
        }

        //! Initialize debugging for the composed constraint rule
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeComposedConstraintRuleDebugging() {
            debug(andConstraintRule);
            debug(orConstraintRule);
            debug(implicationConstraintRule);
            debug(equivalenceConstraintRule);
        }

        //! Initialize the error handling routines
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeErrorHandlingSupport() {
            initializeSpatialMeasureCollectionErrorHandlingSupport();
            initializeSubsetErrorHandlingSupport();
            initializeConstraintsErrorHandlingSupport();
        }

        //! Initialize the spatial measure collection error handling support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeSpatialMeasureCollectionErrorHandlingSupport() {
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

        //! Initialize the subset error handling support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeSubsetErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                filterSubsetRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                subsetSubsetOperationRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialize the constraints error handling support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeConstraintsErrorHandlingSupport() {
            initializePrimaryConstraintErrorHandlingSupport();
            initializeFilterNumericMeasureErrorHandlingSupport();
            initializeComposedConstraintErrorHandlingSupport();
        }

        //! Initialize the primary constraint error handling support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializePrimaryConstraintErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                primaryConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                notConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                unaryScaleAndSubsystemConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                unarySpatialConstraintRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialize the filter numeric measure error handling support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeFilterNumericMeasureErrorHandlingSupport() {
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

        //! Initialize the composed constraint error handling support
        template <typename Iterator>
        void SpatialMeasureCollectionGrammar<Iterator>::initializeComposedConstraintErrorHandlingSupport() {
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
