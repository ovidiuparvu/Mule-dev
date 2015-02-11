#ifndef PRIMARYNUMERICMEASUREGRAMMARDEFINITION_HPP
#define PRIMARYNUMERICMEASUREGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/PrimaryNumericMeasureGrammar.hpp"

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
        PrimaryNumericMeasureGrammar<Iterator>::PrimaryNumericMeasureGrammar(
            SpatialMeasureCollectionGrammar<Iterator> *spatialMeasureCollectionGrammar)
            : PrimaryNumericMeasureGrammar::base_type(primaryNumericMeasureRule, "primaryNumericMeasureRule"),
              spatialMeasureCollectionRule(spatialMeasureCollectionGrammar) {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::initialiseGrammar() {
            initialisePrimaryNumericMeasureRule();
            initialiseNumericSpatialMeasureRule();
        }

        //! Initialise the primary numeric measure rule
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::initialisePrimaryNumericMeasureRule() {
            primaryNumericMeasureRule
                =   numericSpatialMeasureRule
                |   qi::double_
                |   numericStateVariableRule;
        }

        //! Initialise the numeric spatial measure rule
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::initialiseNumericSpatialMeasureRule() {
            numericSpatialMeasureRule
                =   unaryStatisticalSpatialRule
                |   binaryStatisticalSpatialRule
                |   binaryStatisticalQuantileSpatialRule;

            unaryStatisticalSpatialRule
                =   (
                        unaryStatisticalMeasureRule
                        > '('
                        > (*spatialMeasureCollectionRule)
                        > ')'
                    );

            binaryStatisticalSpatialRule
                =   (
                        binaryStatisticalMeasureRule
                        > '('
                        > (*spatialMeasureCollectionRule)
                        > ','
                        > (*spatialMeasureCollectionRule)
                        > ')'
                    );

            binaryStatisticalQuantileSpatialRule
                =   (
                        binaryStatisticalQuantileMeasureRule
                        > '('
                        > (*spatialMeasureCollectionRule)
                        > ','
                        > qi::double_
                        > ')'
                    );
        }

        //! Initialise debug support
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::assignNamesToRules() {
            assignNamesToPrimaryNumericMeasureRules();
            assignNamesToNumericSpatialMeasureRules();
        }

        //! Assign names to the primary numeric measure rules
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::assignNamesToPrimaryNumericMeasureRules() {
            primaryNumericMeasureRule.name("primaryNumericMeasureRule");
        }

        //! Assign names to the numeric spatial measure rules
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::assignNamesToNumericSpatialMeasureRules() {
            numericSpatialMeasureRule           .name("numericSpatialRule");
            unaryStatisticalSpatialRule         .name("unarySubsetRule");
            binaryStatisticalSpatialRule        .name("binaryStatisticalSpatialRule");
            binaryStatisticalQuantileSpatialRule.name("binaryStatisticalQuantileSpatialRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::initialiseRulesDebugging() {
            initialisePrimaryNumericMeasureRuleDebugging();
            initialiseNumericSpatialMeasureRuleDebugging();
        }

        //! Initialise debugging for the primary numeric measure rule
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::initialisePrimaryNumericMeasureRuleDebugging() {
            debug(primaryNumericMeasureRule);
        }

        //! Initialise debugging for the numeric spatial measure rule
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::initialiseNumericSpatialMeasureRuleDebugging() {
            debug(numericSpatialMeasureRule);
            debug(unaryStatisticalSpatialRule);
            debug(binaryStatisticalSpatialRule);
            debug(binaryStatisticalQuantileSpatialRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::initialiseErrorHandlingSupport() {
            initialiseNumericSpatialMeasureErrorHandlingSupport();
        }

        //! Initialise the numeric spatial measure error handling support
        template <typename Iterator>
        void PrimaryNumericMeasureGrammar<Iterator>::initialiseNumericSpatialMeasureErrorHandlingSupport() {
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

    };

};


#endif
