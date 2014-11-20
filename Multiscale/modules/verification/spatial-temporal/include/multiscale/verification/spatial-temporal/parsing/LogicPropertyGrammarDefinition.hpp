#ifndef LOGICPROPERTYPARSERGRAMMARDEFINITION_HPP
#define LOGICPROPERTYPARSERGRAMMARDEFINITION_HPP

#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/LogicPropertyGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Create a lazy error handler function
        phoenix::function<ProbabilityErrorHandler> const
            handleProbabilityError = ProbabilityErrorHandler();
        phoenix::function<UnexpectedTokenErrorHandler> const
            handleUnexpectedTokenError = UnexpectedTokenErrorHandler();


        template <typename Iterator>
        LogicPropertyGrammar<Iterator>::LogicPropertyGrammar()
            : LogicPropertyGrammar::base_type(
                                        probabilisticLogicPropertyRule,
                                        "probabilisticLogicPropertyRule"
                                    ) {
            initialise();
        }

        //! Initialisation function
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialise() {
            initialiseGrammar();
            initialiseDebugSupport();
            initialiseErrorHandlingSupport();
        }

        //! Initialise the grammar
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseGrammar() {
            initialiseLogicPropertiesRules();
            initialiseSimilarityMeasureRules();
            initialiseComparatorRules();
        }

        //! Initialise the logic properties rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseLogicPropertiesRules() {
            initialiseProbabilisticLogicPropertyRule();
            initialiseLogicPropertyRule();
            initialisePrimaryLogicPropertyRule();
            initialiseComposedLogicPropertyRule();
        }

        //! Initialise the probabilistic logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseProbabilisticLogicPropertyRule() {
            probabilisticLogicPropertyRule
                =   'P'
                    > (
                        probabilisticLogicPropertyComparatorRule
                        > probabilityRule
                        > '['
                        > logicPropertyRule
                        > ']'
                    );

            probabilityRule
                %=  qi::eps
                    > qi::double_ [qi::_pass = (qi::_1 >= 0) && (qi::_1 <= 1)];
        }

        //! Initialise the logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseLogicPropertyRule() {
            logicPropertyRule
                =   primaryLogicPropertyRule
                    >>  *(
                            andLogicPropertyRule
                        |   orLogicPropertyRule
                        |   implicationLogicPropertyRule
                        |   equivalenceLogicPropertyRule
                        |   untilLogicPropertyRule
                        );
        }

        //! Initialise the primary logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialisePrimaryLogicPropertyRule() {
            primaryLogicPropertyRule
                =   temporalNumericComparisonRule
                |   changeTemporalNumericMeasureRule
                |   similarityTemporalNumericCollectionRule
                |   notLogicPropertyRule
                |   futureLogicPropertyRule
                |   globalLogicPropertyRule
                |   ('X' > (nextLogicPropertyRule | nextKLogicPropertyRule))
                |   ('(' > logicPropertyRule > ')');

            temporalNumericComparisonRule
                =   (
                        temporalNumericMeasureRule
                        > comparatorRule
                        > temporalNumericMeasureRule
                    );

            changeTemporalNumericMeasureRule
                =   (
                        changeMeasureRule
                        > '('
                        > temporalNumericMeasureRule
                        > ')'
                        > comparatorRule
                        > temporalNumericMeasureRule
                    );

            similarityTemporalNumericCollectionRule
                =   (
                        similarityMeasureRule
                        > '('
                        > temporalNumericCollectionRule
                        > ','
                        > temporalNumericCollectionRule
                        > ','
                        > qi::double_
                        > ')'
                    );

            notLogicPropertyRule
                =   ('~' > logicPropertyRule);

            futureLogicPropertyRule
                =   (
                        qi::lit('F')
                        > '['
                        > qi::ulong_
                        > ','
                        > (
                            qi::ulong_
                            > ']'
                            > logicPropertyRule
                        )
                    );

            globalLogicPropertyRule
                =   (
                        qi::lit('G')
                        > '['
                        > qi::ulong_
                        > ','
                        > (
                            qi::ulong_
                            > ']'
                            > logicPropertyRule
                        )
                    );

            nextLogicPropertyRule
                =   logicPropertyRule;

            nextKLogicPropertyRule
                =   (
                        '['
                        > qi::ulong_
                        > ']'
                        > logicPropertyRule
                    );
        }

        //! Initialise the composed logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseComposedLogicPropertyRule() {
            andLogicPropertyRule
                =   ('^' > logicPropertyRule);

            orLogicPropertyRule
                =   ('V' > logicPropertyRule);

            implicationLogicPropertyRule
                =   ("=>" > logicPropertyRule);

            equivalenceLogicPropertyRule
                =   ("<=>" > logicPropertyRule);

            untilLogicPropertyRule
                =   (
                        qi::lit('U')
                        > '['
                        > qi::ulong_
                        > ','
                        > (
                            qi::ulong_
                            > ']'
                            > logicPropertyRule
                        )
                    );
        }

        //! Initialise the similarity measure rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseSimilarityMeasureRules() {
            similarityMeasureRule
                =   similarityMeasureTypeParser;
        }

        //! Initialise the comparator rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseComparatorRules() {
            probabilisticLogicPropertyComparatorRule
                =   comparatorNonEqualTypeParser;
        }

        //! Initialise debug support
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initialiseRulesDebugging();
        }

        //! Assign names to the rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::assignNamesToRules() {
            assignNamesToLogicPropertiesRules();
            assignNamesToSimilarityMeasureRules();
            assignNamesToComparatorRules();
        }

        //! Assign names to logic properties rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::assignNamesToLogicPropertiesRules() {
            assignNamesToProbabilisticLogicPropertyRules();
            assignNamesToLogicPropertyRules();
            assignNamesToPrimaryLogicPropertyRules();
            assignNamesToComposedLogicPropertyRules();
        }

        //! Assign names to the probabilistic logic property rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::assignNamesToProbabilisticLogicPropertyRules() {
            probabilisticLogicPropertyRule  .name("probabilisticLogicPropertyRule");
            probabilityRule                 .name("probabilityRule");
        }

        //! Assign names to the logic property rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::assignNamesToLogicPropertyRules() {
            logicPropertyRule.name("logicPropertyRule");
        }

        //! Assign names to the primary logic property rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::assignNamesToPrimaryLogicPropertyRules() {
            primaryLogicPropertyRule            .name("primaryLogicPropertyRule");
            temporalNumericComparisonRule       .name("temporalNumericComparisonRule");
            changeTemporalNumericMeasureRule    .name("changeTemporalNumericMeasureRule");
            notLogicPropertyRule                .name("notLogicPropertyRule");
            futureLogicPropertyRule             .name("futureLogicPropertyRule");
            globalLogicPropertyRule             .name("globalLogicPropertyRule");
            nextLogicPropertyRule               .name("nextLogicPropertyRule");
            nextKLogicPropertyRule              .name("nextKLogicPropertyRule");
        }

        //! Assign names to the composed logic property rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::assignNamesToComposedLogicPropertyRules() {
            andLogicPropertyRule            .name("andLogicPropertyRule");
            orLogicPropertyRule             .name("orLogicPropertyRule");
            implicationLogicPropertyRule    .name("implicationLogicPropertyRule");
            equivalenceLogicPropertyRule    .name("equivalenceLogicPropertyRule");
            untilLogicPropertyRule          .name("untilLogicPropertyRule");
        }

        //! Assign names to the similarity measure rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::assignNamesToSimilarityMeasureRules() {
            similarityMeasureRule.name("similarityMeasureRule");
        }

        //! Assign names to the comparator rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::assignNamesToComparatorRules() {
            probabilisticLogicPropertyComparatorRule.name("probabilisticLogicPropertyComparatorRule");
        }

        //! Initialise the debugging of rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseRulesDebugging() {
            initialiseLogicPropertiesRulesDebugging();
            initialiseSimilarityMeasureRuleDebugging();
            initialiseComparatorRuleDebugging();
        }

        //! Initialise the debugging of the logic properties rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseLogicPropertiesRulesDebugging() {
            initialiseProbabilisticLogicPropertyRuleDebugging();
            initialiseLogicPropertyRuleDebugging();
            initialisePrimaryLogicPropertyRuleDebugging();
            initialiseComposedLogicPropertyRuleDebugging();
        }

        //! Initialise debugging for the probabilistic logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseProbabilisticLogicPropertyRuleDebugging() {
            debug(probabilisticLogicPropertyRule);
            debug(probabilityRule);
        }

        //! Initialise debugging for the logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseLogicPropertyRuleDebugging() {
            debug(logicPropertyRule);
        }

        //! Initialise debugging for the primary logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialisePrimaryLogicPropertyRuleDebugging() {
            debug(primaryLogicPropertyRule);
            debug(temporalNumericComparisonRule);
            debug(changeTemporalNumericMeasureRule);
            debug(notLogicPropertyRule);
            debug(futureLogicPropertyRule);
            debug(globalLogicPropertyRule);
            debug(nextLogicPropertyRule);
            debug(nextKLogicPropertyRule);
        }

        //! Initialise debugging for the composed logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseComposedLogicPropertyRuleDebugging() {
            debug(andLogicPropertyRule);
            debug(orLogicPropertyRule);
            debug(implicationLogicPropertyRule);
            debug(equivalenceLogicPropertyRule);
            debug(untilLogicPropertyRule);
        }

        //! Initialise debugging for the similarity measure rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseSimilarityMeasureRuleDebugging() {
            debug(similarityMeasureRule);
        }

        //! Initialise debugging for the comparator rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseComparatorRuleDebugging() {
            debug(probabilisticLogicPropertyComparatorRule);
        }

        //! Initialise the error handling routines
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseErrorHandlingSupport() {
            initialiseLogicPropertiesErrorHandlingSupport();
        }

        //! Initialise the logic properties error handling support
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseLogicPropertiesErrorHandlingSupport() {
            initialiseProbabilisticLogicPropertyErrorHandlingSupport();
            initialisePrimaryLogicPropertyErrorHandlingSupport();
            initialiseComposedLogicPropertyErrorHandlingSupport();
        }

        //! Initialise the probabilistic logic property error handling support
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseProbabilisticLogicPropertyErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                probabilisticLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                probabilityRule,
                multiscale::verification::handleProbabilityError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the primary logic property error handling support
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialisePrimaryLogicPropertyErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                primaryLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                temporalNumericComparisonRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                changeTemporalNumericMeasureRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                notLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                futureLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                globalLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                nextLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                nextKLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialise the compose logic property error handling support
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialiseComposedLogicPropertyErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                andLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                orLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                implicationLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                equivalenceLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                untilLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
        }

    };

};


#endif
