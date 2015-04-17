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
            initialize();
        }

        //! Initialisation function
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initialize() {
            initializeGrammar();
            initializeDebugSupport();
            initializeErrorHandlingSupport();
        }

        //! Initialize the grammar
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeGrammar() {
            initializeLogicPropertiesRules();
            initializeSimilarityMeasureRules();
            initializeComparatorRules();
        }

        //! Initialize the logic properties rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeLogicPropertiesRules() {
            initializeProbabilisticLogicPropertyRule();
            initializeLogicPropertyRule();
            initializePrimaryLogicPropertyRule();
            initializeComposedLogicPropertyRule();
        }

        //! Initialize the probabilistic logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeProbabilisticLogicPropertyRule() {
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

        //! Initialize the logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeLogicPropertyRule() {
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

        //! Initialize the primary logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializePrimaryLogicPropertyRule() {
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

        //! Initialize the composed logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeComposedLogicPropertyRule() {
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

        //! Initialize the similarity measure rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeSimilarityMeasureRules() {
            similarityMeasureRule
                =   similarityMeasureTypeParser;
        }

        //! Initialize the comparator rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeComparatorRules() {
            probabilisticLogicPropertyComparatorRule
                =   comparatorNonEqualTypeParser;
        }

        //! Initialize debug support
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeDebugSupport() {
            assignNamesToRules();

            // TODO: Uncomment this function call in case of debugging
            // initializeRulesDebugging();
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

        //! Initialize the debugging of rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeRulesDebugging() {
            initializeLogicPropertiesRulesDebugging();
            initializeSimilarityMeasureRuleDebugging();
            initializeComparatorRuleDebugging();
        }

        //! Initialize the debugging of the logic properties rules
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeLogicPropertiesRulesDebugging() {
            initializeProbabilisticLogicPropertyRuleDebugging();
            initializeLogicPropertyRuleDebugging();
            initializePrimaryLogicPropertyRuleDebugging();
            initializeComposedLogicPropertyRuleDebugging();
        }

        //! Initialize debugging for the probabilistic logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeProbabilisticLogicPropertyRuleDebugging() {
            debug(probabilisticLogicPropertyRule);
            debug(probabilityRule);
        }

        //! Initialize debugging for the logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeLogicPropertyRuleDebugging() {
            debug(logicPropertyRule);
        }

        //! Initialize debugging for the primary logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializePrimaryLogicPropertyRuleDebugging() {
            debug(primaryLogicPropertyRule);
            debug(temporalNumericComparisonRule);
            debug(changeTemporalNumericMeasureRule);
            debug(notLogicPropertyRule);
            debug(futureLogicPropertyRule);
            debug(globalLogicPropertyRule);
            debug(nextLogicPropertyRule);
            debug(nextKLogicPropertyRule);
        }

        //! Initialize debugging for the composed logic property rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeComposedLogicPropertyRuleDebugging() {
            debug(andLogicPropertyRule);
            debug(orLogicPropertyRule);
            debug(implicationLogicPropertyRule);
            debug(equivalenceLogicPropertyRule);
            debug(untilLogicPropertyRule);
        }

        //! Initialize debugging for the similarity measure rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeSimilarityMeasureRuleDebugging() {
            debug(similarityMeasureRule);
        }

        //! Initialize debugging for the comparator rule
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeComparatorRuleDebugging() {
            debug(probabilisticLogicPropertyComparatorRule);
        }

        //! Initialize the error handling routines
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeErrorHandlingSupport() {
            initializeLogicPropertiesErrorHandlingSupport();
        }

        //! Initialize the logic properties error handling support
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeLogicPropertiesErrorHandlingSupport() {
            initializeProbabilisticLogicPropertyErrorHandlingSupport();
            initializePrimaryLogicPropertyErrorHandlingSupport();
            initializeComposedLogicPropertyErrorHandlingSupport();
        }

        //! Initialize the probabilistic logic property error handling support
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeProbabilisticLogicPropertyErrorHandlingSupport() {
            qi::on_error<qi::fail>(
                probabilisticLogicPropertyRule,
                multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
            );
            qi::on_error<qi::fail>(
                probabilityRule,
                multiscale::verification::handleProbabilityError(qi::_4, qi::_3, qi::_2)
            );
        }

        //! Initialize the primary logic property error handling support
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializePrimaryLogicPropertyErrorHandlingSupport() {
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

        //! Initialize the compose logic property error handling support
        template <typename Iterator>
        void LogicPropertyGrammar<Iterator>::initializeComposedLogicPropertyErrorHandlingSupport() {
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
