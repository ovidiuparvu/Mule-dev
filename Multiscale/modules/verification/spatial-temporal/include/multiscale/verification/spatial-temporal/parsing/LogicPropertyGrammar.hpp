#ifndef LOGICPROPERTYPARSERGRAMMAR_HPP
#define LOGICPROPERTYPARSERGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/handler/ProbabilityErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"
#include "multiscale/verification/spatial-temporal/parsing/TemporalNumericMeasureGrammar.hpp"

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

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        // Create a lazy error handler function
        phoenix::function<ProbabilityErrorHandler> const handleProbabilityError = ProbabilityErrorHandler();


        //! The grammar for parsing logic properties
        template <typename Iterator>
        class LogicPropertyGrammar : public qi::grammar<
            Iterator, ProbabilisticLogicPropertyAttribute(), qi::space_type> {

            private:

                // Grammars

                TemporalNumericMeasureGrammar<Iterator>
                    numericMeasureRule;                         /*!< The rule for parsing a numeric measure */

                // Rules

                qi::rule<Iterator, ProbabilisticLogicPropertyAttribute(), qi::space_type>
                    probabilisticLogicPropertyRule;             /*!< The rule for parsing a probabilistic logic
                                                                     property */
                qi::rule<Iterator, double(), qi::space_type>
                    probabilityRule;                            /*!< The rule for parsing a probability value */
                qi::rule<Iterator, LogicPropertyAttribute(), qi::space_type>
                    logicPropertyRule;                          /*!< The rule for parsing a logic property */

                qi::rule<Iterator, PrimaryLogicPropertyAttribute(), qi::space_type>
                    primaryLogicPropertyRule;                   /*!< The rule for parsing a primary logic property */
                qi::rule<Iterator, ChangeMeasureAttribute(), qi::space_type>
                    changeMeasureRule;                          /*!< The rule for parsing a change measure */
                qi::rule<Iterator, ChangeTemporalNumericMeasureAttribute(), qi::space_type>
                    changeTemporalNumericMeasureRule;           /*!< The rule for parsing a change temporal numeric
                                                                     measure */
                qi::rule<Iterator, TemporalNumericComparisonAttribute(), qi::space_type>
                    temporalNumericComparisonRule;              /*!< The rule for parsing a temporal numeric
                                                                     comparison */
                qi::rule<Iterator, NotLogicPropertyAttribute(), qi::space_type>
                    notLogicPropertyRule;                       /*!< The rule for parsing a "not" logic property */
                qi::rule<Iterator, FutureLogicPropertyAttribute(), qi::space_type>
                    futureLogicPropertyRule;                    /*!< The rule for parsing a "future" logic property */
                qi::rule<Iterator, GlobalLogicPropertyAttribute(), qi::space_type>
                    globalLogicPropertyRule;                    /*!< The rule for parsing a "global" logic property */
                qi::rule<Iterator, NextLogicPropertyAttribute(), qi::space_type>
                    nextLogicPropertyRule;                      /*!< The rule for parsing a "next" logic property */
                qi::rule<Iterator, NextKLogicPropertyAttribute(), qi::space_type>
                    nextKLogicPropertyRule;                     /*!< The rule for parsing a "next K" logic property */

                qi::rule<Iterator, AndLogicPropertyAttribute(), qi::space_type>
                    andLogicPropertyRule;                       /*!< The rule for parsing an "and" logic property */
                qi::rule<Iterator, OrLogicPropertyAttribute(), qi::space_type>
                    orLogicPropertyRule;                        /*!< The rule for parsing an "or" logic property */
                qi::rule<Iterator, ImplicationLogicPropertyAttribute(), qi::space_type>
                    implicationLogicPropertyRule;               /*!< The rule for parsing an "implication" logic
                                                                     property */
                qi::rule<Iterator, EquivalenceLogicPropertyAttribute(), qi::space_type>
                    equivalenceLogicPropertyRule;               /*!< The rule for parsing an "equivalence" logic
                                                                     property */
                qi::rule<Iterator, UntilLogicPropertyAttribute(), qi::space_type>
                    untilLogicPropertyRule;                     /*!< The rule for parsing an "until" logic property */

                qi::rule<Iterator, PrimaryNumericMeasureAttribute(), qi::space_type>
                    primaryNumericMeasureRule;                  /*!< The rule for parsing a primary numeric numeric
                                                                     attribute */
                qi::rule<Iterator, UnaryNumericNumericAttribute(), qi::space_type>
                    unaryNumericNumericRule;                    /*!< The rule for parsing a unary numeric numeric
                                                                     attribute */
                qi::rule<Iterator, BinaryNumericNumericAttribute(), qi::space_type>
                    binaryNumericNumericRule;                   /*!< The rule for parsing a binary numeric numeric
                                                                     attribute */

                qi::rule<Iterator, ComparatorAttribute(), qi::space_type>
                    comparatorRule;                             /*!< The rule for parsing a comparator */
                qi::rule<Iterator, ComparatorAttribute(), qi::space_type>
                    probabilisticLogicPropertyComparatorRule;   /*!< The rule for parsing a comparator for a
                                                                     probabilistic logic property */

                // Enumeration parsers

                ChangeMeasureTypeParser
                    changeMeasureTypeParser;            /*!< The change measure type parser */
                ComparatorTypeParser
                    comparatorTypeParser;               /*!< The comparator type parser */
                ComparatorNonEqualTypeParser
                    comparatorNonEqualTypeParser;       /*!< The comparator type parser which does not accept
                                                             the "=" symbol */


            public:

                LogicPropertyGrammar() : LogicPropertyGrammar::base_type(probabilisticLogicPropertyRule) {
                    initialise();
                }

            private:

                //! Initialisation function
                void initialise() {
                    initialiseGrammar();
                    initialiseDebugSupport();
                    initialiseErrorHandlingSupport();
                }

                //! Initialise the grammar
                void initialiseGrammar() {
                    initialiseLogicPropertiesRules();
                    initialiseChangeMeasureRule();
                    initialiseComparatorRules();
                }

                //! Initialise the logic properties rules
                void initialiseLogicPropertiesRules() {
                    initialiseProbabilisticLogicPropertyRule();
                    initialiseLogicPropertyRule();
                    initialisePrimaryLogicPropertyRule();
                    initialiseComposedLogicPropertyRule();
                }

                //! Initialise the probabilistic logic property rule
                void initialiseProbabilisticLogicPropertyRule() {
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
                void initialiseLogicPropertyRule() {
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
                void initialisePrimaryLogicPropertyRule() {
                    primaryLogicPropertyRule
                        =   temporalNumericComparisonRule
                        |   changeTemporalNumericMeasureRule
                        |   notLogicPropertyRule
                        |   futureLogicPropertyRule
                        |   globalLogicPropertyRule
                        |   ('X' > (nextLogicPropertyRule | nextKLogicPropertyRule))
                        |   ('(' > logicPropertyRule > ')');

                    temporalNumericComparisonRule
                        =   (
                                numericMeasureRule
                                > comparatorRule
                                > numericMeasureRule
                            );

                    changeTemporalNumericMeasureRule
                        =   (
                                changeMeasureRule
                                > '('
                                > numericMeasureRule
                                > ')'
                                > comparatorRule
                                > numericMeasureRule
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
                void initialiseComposedLogicPropertyRule() {
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

                //! Initialise the change measure rule
                void initialiseChangeMeasureRule() {
                    changeMeasureRule
                        =   changeMeasureTypeParser;
                }

                //! Initialise the comparator rules
                void initialiseComparatorRules() {
                    comparatorRule
                        =   comparatorTypeParser;

                    probabilisticLogicPropertyComparatorRule
                        =   comparatorNonEqualTypeParser;
                }

                //! Initialise debug support
                void initialiseDebugSupport() {
                    assignNamesToRules();

                    // TODO: Uncomment this function call in case of debugging
                    // initialiseRulesDebugging();
                }

                //! Assign names to the rules
                void assignNamesToRules() {
                    assignNamesToLogicPropertiesRules();
                    assignNamesToChangeMeasureRules();
                    assignNamesToComparatorRules();
                }

                //! Assign names to logic properties rules
                void assignNamesToLogicPropertiesRules() {
                    assignNamesToProbabilisticLogicPropertyRules();
                    assignNamesToLogicPropertyRules();
                    assignNamesToPrimaryLogicPropertyRules();
                    assignNamesToComposedLogicPropertyRules();
                }

                //! Assign names to the probabilistic logic property rules
                void assignNamesToProbabilisticLogicPropertyRules() {
                    probabilisticLogicPropertyRule  .name("probabilisticLogicPropertyRule");
                    probabilityRule                 .name("probabilityRule");
                }

                //! Assign names to the logic property rules
                void assignNamesToLogicPropertyRules() {
                    logicPropertyRule.name("logicPropertyRule");
                }

                //! Assign names to the primary logic property rules
                void assignNamesToPrimaryLogicPropertyRules() {
                    primaryLogicPropertyRule            .name("primaryLogicPropertyRule");
                    changeTemporalNumericMeasureRule    .name("changeTemporalNumericMeasureRule");
                    temporalNumericComparisonRule       .name("temporalNumericComparisonRule");
                    notLogicPropertyRule                .name("notLogicPropertyRule");
                    futureLogicPropertyRule             .name("futureLogicPropertyRule");
                    globalLogicPropertyRule             .name("globalLogicPropertyRule");
                    nextLogicPropertyRule               .name("nextLogicPropertyRule");
                    nextKLogicPropertyRule              .name("nextKLogicPropertyRule");
                }

                //! Assign names to the composed logic property rules
                void assignNamesToComposedLogicPropertyRules() {
                    andLogicPropertyRule            .name("andLogicPropertyRule");
                    orLogicPropertyRule             .name("orLogicPropertyRule");
                    implicationLogicPropertyRule    .name("implicationLogicPropertyRule");
                    equivalenceLogicPropertyRule    .name("equivalenceLogicPropertyRule");
                    untilLogicPropertyRule          .name("untilLogicPropertyRule");
                }

                //! Assign names to the change measure rules
                void assignNamesToChangeMeasureRules() {
                    changeMeasureRule.name("changeMeasureRule");
                }

                //! Assign names to the comparator rules
                void assignNamesToComparatorRules() {
                    comparatorRule                          .name("comparatorRule");
                    probabilisticLogicPropertyComparatorRule.name("probabilisticLogicPropertyComparatorRule");
                }

                //! Initialise the debugging of rules
                void initialiseRulesDebugging() {
                    initialiseLogicPropertiesRulesDebugging();
                    initialiseChangeMeasureRuleDebugging();
                    initialiseComparatorRuleDebugging();
                }

                //! Initialise the debugging of the logic properties rules
                void initialiseLogicPropertiesRulesDebugging() {
                    initialiseProbabilisticLogicPropertyRuleDebugging();
                    initialiseLogicPropertyRuleDebugging();
                    initialisePrimaryLogicPropertyRuleDebugging();
                    initialiseComposedLogicPropertyRuleDebugging();
                }

                //! Initialise debugging for the probabilistic logic property rule
                void initialiseProbabilisticLogicPropertyRuleDebugging() {
                    debug(probabilisticLogicPropertyRule);
                    debug(probabilityRule);
                }

                //! Initialise debugging for the logic property rule
                void initialiseLogicPropertyRuleDebugging() {
                    debug(logicPropertyRule);
                }

                //! Initialise debugging for the primary logic property rule
                void initialisePrimaryLogicPropertyRuleDebugging() {
                    debug(primaryLogicPropertyRule);
                    debug(changeTemporalNumericMeasureRule);
                    debug(temporalNumericComparisonRule);
                    debug(notLogicPropertyRule);
                    debug(futureLogicPropertyRule);
                    debug(globalLogicPropertyRule);
                    debug(nextLogicPropertyRule);
                    debug(nextKLogicPropertyRule);
                }

                //! Initialise debugging for the composed logic property rule
                void initialiseComposedLogicPropertyRuleDebugging() {
                    debug(andLogicPropertyRule);
                    debug(orLogicPropertyRule);
                    debug(implicationLogicPropertyRule);
                    debug(equivalenceLogicPropertyRule);
                    debug(untilLogicPropertyRule);
                }

                //! Initialise debugging for the change measure rule
                void initialiseChangeMeasureRuleDebugging() {
                    debug(changeMeasureRule);
                }

                //! Initialise debugging for the comparator rule
                void initialiseComparatorRuleDebugging() {
                    debug(comparatorRule);
                    debug(probabilisticLogicPropertyComparatorRule);
                }

                //! Initialise the error handling routines
                void initialiseErrorHandlingSupport() {
                    initialiseLogicPropertiesErrorHandlingSupport();
                }

                //! Initialise the logic properties error handling support
                void initialiseLogicPropertiesErrorHandlingSupport() {
                    initialiseProbabilisticLogicPropertyErrorHandlingSupport();
                    initialisePrimaryLogicPropertyErrorHandlingSupport();
                    initialiseComposedLogicPropertyErrorHandlingSupport();
                }

                //! Initialise the probabilistic logic property error handling support
                void initialiseProbabilisticLogicPropertyErrorHandlingSupport() {
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
                void initialisePrimaryLogicPropertyErrorHandlingSupport() {
                    qi::on_error<qi::fail>(
                        primaryLogicPropertyRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                    qi::on_error<qi::fail>(
                        changeTemporalNumericMeasureRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                    qi::on_error<qi::fail>(
                        temporalNumericComparisonRule,
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
                void initialiseComposedLogicPropertyErrorHandlingSupport() {
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

};


#endif
