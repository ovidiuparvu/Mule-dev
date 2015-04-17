#ifndef LOGICPROPERTYPARSERGRAMMAR_HPP
#define LOGICPROPERTYPARSERGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/handler/ProbabilityErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ChangeMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ComparatorGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"
#include "multiscale/verification/spatial-temporal/parsing/TemporalNumericCollectionGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/TemporalNumericMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;


        //! The grammar for parsing logic properties
        template <typename Iterator>
        class LogicPropertyGrammar : public qi::grammar<
            Iterator, ProbabilisticLogicPropertyAttribute(), qi::space_type> {

            private:

                // Grammars

                TemporalNumericMeasureGrammar<Iterator>
                    temporalNumericMeasureRule;                 /*!< The grammar for parsing a temporal numeric
                                                                     measure */

                TemporalNumericCollectionGrammar<Iterator>
                    temporalNumericCollectionRule;              /*!< The grammar for parsing a temporal numeric
                                                                     collection */

                ChangeMeasureGrammar<Iterator>
                    changeMeasureRule;                          /*!< The grammar for parsing a change measure */
                ComparatorGrammar<Iterator>
                    comparatorRule;                             /*!< The grammar for parsing a comparator */

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
                qi::rule<Iterator, TemporalNumericComparisonAttribute(), qi::space_type>
                    temporalNumericComparisonRule;              /*!< The rule for parsing a temporal numeric
                                                                     comparison */
                qi::rule<Iterator, ChangeTemporalNumericMeasureAttribute(), qi::space_type>
                    changeTemporalNumericMeasureRule;           /*!< The rule for parsing a change temporal numeric
                                                                     measure */
                qi::rule<Iterator, SimilarityTemporalNumericCollectionAttribute(), qi::space_type>
                    similarityTemporalNumericCollectionRule;    /*!< The rule for parsing a similarity temporal numeric
                                                                     collection attribute */
                qi::rule<Iterator, SimilarityMeasureAttribute(), qi::space_type>
                    similarityMeasureRule;                      /*!< The rule for parsing a similarity measure */
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
                    probabilisticLogicPropertyComparatorRule;   /*!< The rule for parsing a comparator for a
                                                                     probabilistic logic property */

                // Enumeration parsers

                SimilarityMeasureTypeParser
                    similarityMeasureTypeParser;        /*!< The similarity measure type parser */

                ComparatorNonEqualTypeParser
                    comparatorNonEqualTypeParser;       /*!< The comparator type parser which does not accept
                                                             the "=" symbol */

            public:

                LogicPropertyGrammar();

            private:

                //! Initialisation function
                void initialize();

                //! Initialize the grammar
                void initializeGrammar();

                //! Initialize the logic properties rules
                void initializeLogicPropertiesRules();

                //! Initialize the probabilistic logic property rule
                void initializeProbabilisticLogicPropertyRule();

                //! Initialize the logic property rule
                void initializeLogicPropertyRule();

                //! Initialize the primary logic property rule
                void initializePrimaryLogicPropertyRule();

                //! Initialize the composed logic property rule
                void initializeComposedLogicPropertyRule();

                //! Initialize the similarity measure rules
                void initializeSimilarityMeasureRules();

                //! Initialize the comparator rules
                void initializeComparatorRules();

                //! Initialize debug support
                void initializeDebugSupport();

                //! Assign names to the rules
                void assignNamesToRules();

                //! Assign names to logic properties rules
                void assignNamesToLogicPropertiesRules();

                //! Assign names to the probabilistic logic property rules
                void assignNamesToProbabilisticLogicPropertyRules();

                //! Assign names to the logic property rules
                void assignNamesToLogicPropertyRules();

                //! Assign names to the primary logic property rules
                void assignNamesToPrimaryLogicPropertyRules();

                //! Assign names to the composed logic property rules
                void assignNamesToComposedLogicPropertyRules();

                //! Assign names to the similarity measure rules
                void assignNamesToSimilarityMeasureRules();

                //! Assign names to the comparator rules
                void assignNamesToComparatorRules();

                //! Initialize the debugging of rules
                void initializeRulesDebugging();

                //! Initialize the debugging of the logic properties rules
                void initializeLogicPropertiesRulesDebugging();

                //! Initialize debugging for the probabilistic logic property rule
                void initializeProbabilisticLogicPropertyRuleDebugging();

                //! Initialize debugging for the logic property rule
                void initializeLogicPropertyRuleDebugging();

                //! Initialize debugging for the primary logic property rule
                void initializePrimaryLogicPropertyRuleDebugging();

                //! Initialize debugging for the composed logic property rule
                void initializeComposedLogicPropertyRuleDebugging();

                //! Initialize debugging for the similarity measure rule
                void initializeSimilarityMeasureRuleDebugging();

                //! Initialize debugging for the comparator rule
                void initializeComparatorRuleDebugging();

                //! Initialize the error handling routines
                void initializeErrorHandlingSupport();

                //! Initialize the logic properties error handling support
                void initializeLogicPropertiesErrorHandlingSupport();

                //! Initialize the probabilistic logic property error handling support
                void initializeProbabilisticLogicPropertyErrorHandlingSupport();

                //! Initialize the primary logic property error handling support
                void initializePrimaryLogicPropertyErrorHandlingSupport();

                //! Initialize the compose logic property error handling support
                void initializeComposedLogicPropertyErrorHandlingSupport();

        };

    };

};


#endif
