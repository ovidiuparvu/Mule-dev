#ifndef TEMPORALNUMERICMEASREGRAMMAR_HPP
#define TEMPORALNUMERICMEASREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"

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
        phoenix::function<UnexpectedTokenErrorHandler> const
            handleUnexpectedTokenError = UnexpectedTokenErrorHandler();


        //! The grammar for parsing temporal numeric measure statements
        template <typename Iterator>
        class TemporalNumericMeasureGrammar : public qi::grammar<
                                                         Iterator,
                                                         TemporalNumericMeasureAttribute(),
                                                         qi::space_type
                                                     > {

            private:

                // Rules

                qi::rule<Iterator, TemporalNumericMeasureAttribute(), qi::space_type>
                    temporalNumericMeasureRule;                 /*!< The rule for parsing a temporal numeric
                                                                     measure */
                qi::rule<Iterator, UnaryNumericTemporalAttribute(), qi::space_type>
                    unaryNumericTemporalRule;                   /*!< The rule for parsing a unary numeric
                                                                     temporal attribute */
                qi::rule<Iterator, BinaryNumericTemporalAttribute(), qi::space_type>
                    binaryNumericTemporalRule;                  /*!< The rule for parsing a binary numeric
                                                                     temporal attribute */

                qi::rule<Iterator, NumericStatisticalMeasureAttribute(), qi::space_type>
                    numericStatisticalMeasureRule;              /*!< The rule for parsing a numeric statistical
                                                                     measure */
                qi::rule<Iterator, UnaryStatisticalNumericAttribute(), qi::space_type>
                    unaryStatisticalNumericRule;                /*!< The rule for parsing a unary statistical
                                                                     numeric attribute */
                qi::rule<Iterator, BinaryStatisticalNumericAttribute(), qi::space_type>
                    binaryStatisticalNumericRule;               /*!< The rule for parsing a binary statistical
                                                                     numeric attribute */
                qi::rule<Iterator, BinaryStatisticalQuantileNumericAttribute(), qi::space_type>
                    binaryStatisticalQuantileNumericRule;       /*!< The rule for parsing a binary statistical
                                                                     quantile numeric attribute */

                qi::rule<Iterator, NumericMeasureCollectionAttribute(), qi::space_type>
                    numericMeasureCollectionRule;               /*!< The rule for parsing numeric measure
                                                                     collections */
                qi::rule<Iterator, TemporalNumericMeasureCollectionAttribute(), qi::space_type>
                    temporalNumericMeasureCollectionRule;       /*!< The rule for parsing temporal numeric measure
                                                                     collections */

                qi::rule<Iterator, NumericMeasureAttribute(), qi::space_type>
                    numericMeasureRule;                         /*!< The rule for parsing a numeric measure */
                qi::rule<Iterator, PrimaryNumericMeasureAttribute(), qi::space_type>
                    primaryNumericMeasureRule;                  /*!< The rule for parsing a primary numeric numeric
                                                                     attribute */
                qi::rule<Iterator, UnaryNumericNumericAttribute(), qi::space_type>
                    unaryNumericNumericRule;                    /*!< The rule for parsing a unary numeric numeric
                                                                     attribute */
                qi::rule<Iterator, BinaryNumericNumericAttribute(), qi::space_type>
                    binaryNumericNumericRule;                   /*!< The rule for parsing a binary numeric numeric
                                                                     attribute */

                qi::rule<Iterator, NumericSpatialMeasureAttribute(), qi::space_type>
                    numericSpatialMeasureRule;                  /*!< The rule for parsing a numeric spatial measure */
                qi::rule<Iterator, UnaryStatisticalSpatialAttribute(), qi::space_type>
                    unaryStatisticalSpatialRule;                /*!< The rule for parsing a unary statistical spatial
                                                                     attribute */
                qi::rule<Iterator, BinaryStatisticalSpatialAttribute(), qi::space_type>
                    binaryStatisticalSpatialRule;               /*!< The rule for parsing a binary statistical
                                                                     spatial attribute */
                qi::rule<Iterator, BinaryStatisticalQuantileSpatialAttribute(), qi::space_type>
                    binaryStatisticalQuantileSpatialRule;       /*!< The rule for parsing a binary statistical
                                                                     quantile spatial attribute */

                qi::rule<Iterator, UnaryStatisticalMeasureAttribute(), qi::space_type>
                    unaryStatisticalMeasureRule;                /*!< The rule for parsing a unary statistical
                                                                     measure */
                qi::rule<Iterator, BinaryStatisticalMeasureAttribute(), qi::space_type>
                    binaryStatisticalMeasureRule;               /*!< The rule for parsing a binary statistical
                                                                     measure */
                qi::rule<Iterator, BinaryStatisticalQuantileMeasureAttribute(), qi::space_type>
                    binaryStatisticalQuantileMeasureRule;       /*!< The rule for parsing a binary statistical
                                                                     quantile measure */

                qi::rule<Iterator, UnaryNumericMeasureAttribute(), qi::space_type>
                    unaryNumericMeasureRule;                    /*!< The rule for parsing a unary numeric measure */
                qi::rule<Iterator, BinaryNumericMeasureAttribute(), qi::space_type>
                    binaryNumericMeasureRule;                   /*!< The rule for parsing a binary numeric measure */

                qi::rule<Iterator, SpatialMeasureCollectionAttribute(), qi::space_type>
                    spatialMeasureCollectionRule;               /*!< The rule for parsing a spatial measure
                                                                     collection */

                qi::rule<Iterator, SpatialMeasureAttribute(), qi::space_type>
                    spatialMeasureRule;                         /*!< The rule for parsing a spatial measure */

                qi::rule<Iterator, SubsetAttribute(), qi::space_type>
                    subsetRule;                                 /*!< The rule for parsing a subset */
                qi::rule<Iterator, SubsetSpecificAttribute(), qi::space_type>
                    subsetSpecificRule;                         /*!< The rule for parsing a specific subset */
                qi::rule<Iterator, FilterSubsetAttribute(), qi::space_type>
                    filterSubsetRule;                           /*!< The rule for parsing a subset filter */
                qi::rule<Iterator, SubsetSubsetOperationAttribute(), qi::space_type>
                    subsetSubsetOperationRule;                  /*!< The rule for parsing a subset subset operation */

                qi::rule<Iterator, ConstraintAttribute(), qi::space_type>
                    constraintRule;                             /*!< The rule for parsing a constraint */

                qi::rule<Iterator, PrimaryConstraintAttribute(), qi::space_type>
                    primaryConstraintRule;                      /*!< The rule for parsing a primary constraint */
                qi::rule<Iterator, NotConstraintAttribute(), qi::space_type>
                    notConstraintRule;                          /*!< The rule for parsing a "not" constraint */
                qi::rule<Iterator, UnarySpatialConstraintAttribute(), qi::space_type>
                    unarySpatialConstraintRule;                 /*!< The rule for parsing a unary spatial constraint */
                qi::rule<Iterator, UnaryTypeConstraintAttribute(), qi::space_type>
                    unaryTypeConstraintRule;                    /*!< The rule for parsing a unary type constraint */

                qi::rule<Iterator, FilterNumericMeasureAttribute(), qi::space_type>
                    filterNumericMeasureRule;                   /*!< The rule for parsing a filter numeric measure */
                qi::rule<Iterator, UnaryNumericFilterAttribute(), qi::space_type>
                    unaryNumericFilterRule;                     /*!< The rule for parsing a unary numeric filter
                                                                     measure */
                qi::rule<Iterator, BinaryNumericFilterAttribute(), qi::space_type>
                    binaryNumericFilterRule;                    /*!< The rule for parsing a binary numeric filter
                                                                     measure */

                qi::rule<Iterator, AndConstraintAttribute(), qi::space_type>
                    andConstraintRule;                          /*!< The rule for parsing an "and" constraint */
                qi::rule<Iterator, OrConstraintAttribute(), qi::space_type>
                    orConstraintRule;                           /*!< The rule for parsing an "or" constraint */
                qi::rule<Iterator, ImplicationConstraintAttribute(), qi::space_type>
                    implicationConstraintRule;                  /*!< The rule for parsing an "implication"
                                                                     constraint */
                qi::rule<Iterator, EquivalenceConstraintAttribute(), qi::space_type>
                    equivalenceConstraintRule;                  /*!< The rule for parsing an "equivalence"
                                                                     constraint */

                qi::rule<Iterator, ComparatorAttribute(), qi::space_type>
                    comparatorRule;                             /*!< The rule for parsing a comparator */

                qi::rule<Iterator, NumericStateVariableAttribute(), qi::space_type>
                    numericStateVariableRule;                   /*!< The rule for parsing a numeric state variable */
                qi::rule<Iterator, StateVariableAttribute(), qi::space_type>
                    stateVariableRule;                          /*!< The rule for parsing a state variable */
                qi::rule<Iterator, std::string(), qi::space_type>
                    stateVariableNameRule;                      /*!< The rule for parsing the name of a
                                                                     state variable without escaping white space */
                qi::rule<Iterator, StateVariableTypeAttribute(), qi::space_type>
                    stateVariableTypeRule;                      /*!< The rule for parsing a state variable type */


                // Enumeration parsers

                UnaryStatisticalMeasureTypeParser
                    unaryStatisticalMeasureTypeParser;          /*!< The unary statistical measure type parser */
                BinaryStatisticalMeasureTypeParser
                    binaryStatisticalMeasureTypeParser;         /*!< The binary statistical measure type parser */
                BinaryStatisticalQuantileMeasureTypeParser
                    binaryStatisticalQuantileMeasureTypeParser; /*!< The binary statistical quantile measure type
                                                                     parser */

                UnaryNumericMeasureTypeParser
                    unaryNumericMeasureTypeParser;              /*!< The unary numeric measure type parser */
                BinaryNumericMeasureTypeParser
                    binaryNumericMeasureTypeParser;             /*!< The binary numeric measure type parser */

                SubsetSpecificTypeParser
                    subsetSpecificTypeParser;                   /*!< The subset specific type parser */
                SubsetOperationTypeParser
                    subsetOperationTypeParser;                  /*!< The subset operation type parser */

                SpatialMeasureTypeParser
                    spatialMeasureTypeParser;                   /*!< The spatial measure type parser */

                ComparatorTypeParser
                    comparatorTypeParser;                       /*!< The comparator type parser */

            public:

                TemporalNumericMeasureGrammar() : TemporalNumericMeasureGrammar::base_type(
                                                      temporalNumericMeasureRule
                                                  ) {
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
                    initialiseTemporalNumericMeasureRule();
                    initialiseNumericStatisticalMeasureRule();
                    initialiseNumericMeasureCollectionRule();
                    initialiseNumericMeasureRule();
                    initialiseNumericSpatialMeasureRule();
                    initialiseNaryNumericMeasureRule();
                    initialiseStatisticalMeasureRule();
                    initialiseSpatialMeasureRule();
                    initialiseSubsetRule();
                    initialiseConstraintsRules();
                    initialiseComparatorRules();
                    initialiseNumericStateVariableRule();
                }

                //! Initialise the constraints rules
                void initialiseConstraintsRules() {
                    initialiseConstraintRule();
                    initialisePrimaryConstraintRule();
                    initialiseFilterNumericMeasureRule();
                    initialiseComposedConstraintRule();
                }

                //! Initialise the temporal numeric measure rule
                void initialiseTemporalNumericMeasureRule() {
                    temporalNumericMeasureRule
                        =   qi::double_
                        |   numericStateVariableRule
                        |   numericStatisticalMeasureRule
                        |   unaryNumericTemporalRule
                        |   binaryNumericTemporalRule;

                    unaryNumericTemporalRule
                        =   (
                                unaryNumericMeasureRule
                                > '('
                                > temporalNumericMeasureRule
                                > ')'
                            );

                    binaryNumericTemporalRule
                        =   (
                                binaryNumericMeasureRule
                                > '('
                                > temporalNumericMeasureRule
                                > ','
                                > temporalNumericMeasureRule
                                > ')'
                            );
                }

                //! Initialise the numeric statistical measure rules
                void initialiseNumericStatisticalMeasureRule() {
                    numericStatisticalMeasureRule
                        =   unaryStatisticalNumericRule
                        |   binaryStatisticalNumericRule
                        |   binaryStatisticalQuantileNumericRule;

                    unaryStatisticalNumericRule
                        =   (
                                unaryStatisticalMeasureRule
                                > '('
                                > numericMeasureCollectionRule
                                > ')'
                            );

                    binaryStatisticalNumericRule
                        =   (
                                binaryStatisticalMeasureRule
                                > '('
                                > numericMeasureCollectionRule
                                > ','
                                > numericMeasureCollectionRule
                                > ')'
                            );

                    binaryStatisticalQuantileNumericRule
                        =   (
                                binaryStatisticalQuantileMeasureRule
                                > '('
                                > numericMeasureCollectionRule
                                > ','
                                > qi::double_
                                > ')'
                            );
                }

                //! Initialise the numeric measure collection rules
                void initialiseNumericMeasureCollectionRule() {
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
                void initialiseNumericMeasureRule() {
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
                void initialiseNumericSpatialMeasureRule() {
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
                void initialiseNaryNumericMeasureRule() {
                    unaryNumericMeasureRule
                        =   unaryNumericMeasureTypeParser;

                    binaryNumericMeasureRule
                        =   binaryNumericMeasureTypeParser;
                }

                //! Initialise the statistical measure rule
                void initialiseStatisticalMeasureRule() {
                    unaryStatisticalMeasureRule
                        =   unaryStatisticalMeasureTypeParser;

                    binaryStatisticalMeasureRule
                        =   binaryStatisticalMeasureTypeParser;

                    binaryStatisticalQuantileMeasureRule
                        =   binaryStatisticalQuantileMeasureTypeParser;
                }

                //! Initialise the spatial measure rule
                void initialiseSpatialMeasureRule() {
                    spatialMeasureRule
                        =   spatialMeasureTypeParser;
                }

                //! Initialise the subset rule
                void initialiseSubsetRule() {
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

                //! Initialise the constraint rule
                void initialiseConstraintRule() {
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
                void initialisePrimaryConstraintRule() {
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
                void initialiseFilterNumericMeasureRule() {
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
                void initialiseComposedConstraintRule() {
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
                void initialiseComparatorRules() {
                    comparatorRule
                        =   comparatorTypeParser;
                }

                //! Initialise the numeric state variable rule
                void initialiseNumericStateVariableRule() {
                    numericStateVariableRule
                        =   stateVariableRule
                            > -(stateVariableTypeRule);

                    stateVariableRule
                        =   ('{' > stateVariableNameRule > '}');

                    stateVariableNameRule
                        =   qi::raw[ +(qi::char_ - qi::char_("{}")) ];

                    stateVariableTypeRule
                        =   (
                                '('
                                > qi::lit("type")
                                > '='
                                > qi::ulong_
                                > ')'
                            );
                }

                //! Initialise debug support
                void initialiseDebugSupport() {
                    assignNamesToRules();

                    // TODO: Uncomment this function call in case of debugging
                    // initialiseRulesDebugging();
                }

                //! Assign names to the rules
                void assignNamesToRules() {
                    assignNamesToTemporalNumericMeasureRules();
                    assignNamesToNumericStatisticalMeasureRules();
                    assignNamesToNumericMeasureCollectionRules();
                    assignNamesToNumericMeasureRules();
                    assignNamesToNumericSpatialMeasureRules();
                    assignNamesToNaryNumericMeasureRules();
                    assignNamesToStatisticalMeasureRules();
                    assignNamesToSubsetRules();
                    assignNamesToConstraintsRules();
                    assignNamesToSpatialMeasureRules();
                    assignNamesToComparatorRules();
                    assignNamesToNumericStateVariableRules();
                }

                //! Assign names to constraints rules
                void assignNamesToConstraintsRules() {
                    assignNamesToConstraintRules();
                    assignNamesToPrimaryConstraintRules();
                    assignNamesToFilterNumericMeasureRules();
                    assignNamesToComposedConstraintRules();
                }

                //! Assign names to the temporal numeric measure rules
                void assignNamesToTemporalNumericMeasureRules() {
                    temporalNumericMeasureRule  .name("temporalNumericMeasureRule");
                    unaryNumericTemporalRule    .name("unaryNumericTemporalRule");
                    binaryNumericTemporalRule   .name("binaryNumericTemporalRule");
                }

                //! Assign names to the numeric statistical measure rules
                void assignNamesToNumericStatisticalMeasureRules() {
                    numericStatisticalMeasureRule       .name("numericStatisticalMeasureRule");
                    unaryStatisticalNumericRule         .name("unaryStatisticalNumericRule");
                    binaryStatisticalNumericRule        .name("binaryStatisticalNumericRule");
                    binaryStatisticalQuantileNumericRule.name("binaryStatisticalQuantileNumericRule");
                }

                //! Assign names to the numeric measure collection rules
                void assignNamesToNumericMeasureCollectionRules() {
                    numericMeasureCollectionRule        .name("numericMeasureCollectionRule");
                    temporalNumericMeasureCollectionRule.name("temporalNumericMeasureCollectionRule");
                    spatialMeasureCollectionRule        .name("spatialMeasureCollectionRule");
                }

                //! Assign names to the numeric measure rules
                void assignNamesToNumericMeasureRules() {
                    numericMeasureRule          .name("numericMeasureRule");
                    primaryNumericMeasureRule   .name("primaryNumericMeasureRule");
                    unaryNumericNumericRule     .name("unaryNumericNumericRule");
                    binaryNumericNumericRule    .name("binaryNumericNumericRule");
                }

                //! Assign names to the numeric spatial measure rules
                void assignNamesToNumericSpatialMeasureRules() {
                    numericSpatialMeasureRule           .name("numericSpatialRule");
                    unaryStatisticalSpatialRule         .name("unarySubsetRule");
                    binaryStatisticalSpatialRule        .name("binaryStatisticalSpatialRule");
                    binaryStatisticalQuantileSpatialRule.name("binaryStatisticalQuantileSpatialRule");
                }

                //! Assign names to the n-ary numeric measure rules
                void assignNamesToNaryNumericMeasureRules() {
                    unaryNumericMeasureRule     .name("unaryNumericMeasureRule");
                    binaryNumericMeasureRule    .name("binaryNumericMeasureRule");
                }

                //! Assign names to the numeric statistical measure rules
                void assignNamesToStatisticalMeasureRules() {
                    unaryStatisticalMeasureRule         .name("unaryStatisticalMeasureRule");
                    binaryStatisticalMeasureRule        .name("binaryStatisticalMeasureRule");
                    binaryStatisticalQuantileMeasureRule.name("binaryStatisticalQuantileMeasureRule");
                }

                //! Assign names to the subset rules
                void assignNamesToSubsetRules() {
                    subsetRule                  .name("subsetRule");
                    subsetSpecificRule          .name("subsetSpecificRule");
                    filterSubsetRule            .name("filterSubsetRule");
                    subsetSubsetOperationRule   .name("subsetSubsetOperationRule");
                }

                //! Assign names to the constraint rules
                void assignNamesToConstraintRules() {
                    constraintRule.name("constraintRule");
                }

                //! Assign names to the primary constraint rules
                void assignNamesToPrimaryConstraintRules() {
                    primaryConstraintRule       .name("primaryConstraintRule");
                    notConstraintRule           .name("notConstraintRule");
                    unaryTypeConstraintRule     .name("unaryTypeConstraintRule");
                    unarySpatialConstraintRule  .name("unarySpatialConstraintRule");
                }

                //! Assign names to the filter numeric measure rules
                void assignNamesToFilterNumericMeasureRules() {
                    filterNumericMeasureRule.name("filterNumericMeasureRule");
                    unaryNumericFilterRule  .name("unaryNumericFilterRule");
                    binaryNumericFilterRule .name("binaryNumericFilterRule");
                }

                //! Assign names to the composed constraint rules
                void assignNamesToComposedConstraintRules() {
                    andConstraintRule           .name("andConstraintRule");
                    orConstraintRule            .name("orConstraintRule");
                    implicationConstraintRule   .name("implicationConstraintRule");
                    equivalenceConstraintRule   .name("equivalenceConstraintRule");
                }

                //! Assign names to the spatial measure rules
                void assignNamesToSpatialMeasureRules() {
                    spatialMeasureRule.name("spatialMeasureRule");
                }

                //! Assign names to the comparator rules
                void assignNamesToComparatorRules() {
                    comparatorRule.name("comparatorRule");
                }

                //! Assign names to the numeric state variable rules
                void assignNamesToNumericStateVariableRules() {
                    numericStateVariableRule    .name("numericStateVariableRule");
                    stateVariableRule           .name("stateVariableRule");
                    stateVariableNameRule       .name("stateVariableNameRule");
                    stateVariableTypeRule       .name("stateVariableTypeRule");
                }

                //! Initialise the debugging of rules
                void initialiseRulesDebugging() {
                    initialiseTemporalNumericMeasureRuleDebugging();
                    initialiseNumericStatisticalMeasureRuleDebugging();
                    initialiseNumericMeasureCollectionRuleDebugging();
                    initialiseNumericMeasureRuleDebugging();
                    initialiseNumericSpatialMeasureRuleDebugging();
                    initialiseNaryNumericMeasureRuleDebugging();
                    initialiseStatisticalMeasureRuleDebugging();
                    initialiseSubsetRuleDebugging();
                    initialiseConstraintsRulesDebugging();
                    initialiseSpatialMeasureRuleDebugging();
                    initialiseComparatorRuleDebugging();
                    initialiseNumericStateVariableRuleDebugging();
                }

                //! Initialise the debugging of the constraints rules
                void initialiseConstraintsRulesDebugging() {
                    initialiseConstraintRuleDebugging();
                    initialisePrimaryConstraintRuleDebugging();
                    initialiseFilterNumericMeasureRuleDebugging();
                    initialiseComposedConstraintRuleDebugging();
                }

                //! Initialise debugging for the temporal numeric measure rule
                void initialiseTemporalNumericMeasureRuleDebugging() {
                    debug(temporalNumericMeasureRule);
                    debug(unaryNumericTemporalRule);
                    debug(binaryNumericTemporalRule);
                }

                //! Initialise debugging for the numeric statistical measure rule
                void initialiseNumericStatisticalMeasureRuleDebugging() {
                    debug(numericStatisticalMeasureRule);
                    debug(unaryStatisticalNumericRule);
                    debug(binaryStatisticalNumericRule);
                    debug(binaryStatisticalQuantileNumericRule);
                }

                //! Initialise debugging for the numeric measure collection rule
                void initialiseNumericMeasureCollectionRuleDebugging() {
                    debug(numericMeasureCollectionRule);
                    debug(temporalNumericMeasureCollectionRule);
                    debug(spatialMeasureCollectionRule);
                }

                //! Initialise debugging for the numeric measure rule
                void initialiseNumericMeasureRuleDebugging() {
                    debug(numericMeasureRule);
                    debug(primaryNumericMeasureRule);
                    debug(unaryNumericNumericRule);
                    debug(binaryNumericNumericRule);
                }

                //! Initialise debugging for the numeric spatial measure rule
                void initialiseNumericSpatialMeasureRuleDebugging() {
                    debug(numericSpatialMeasureRule);
                    debug(unaryStatisticalSpatialRule);
                    debug(binaryStatisticalSpatialRule);
                    debug(binaryStatisticalQuantileSpatialRule);
                }

                //! Initialise debugging for the n-ary numeric measure rule
                void initialiseNaryNumericMeasureRuleDebugging() {
                    debug(unaryNumericMeasureRule);
                    debug(binaryNumericMeasureRule);
                }

                //! Initialise debugging for the statistical measure rule
                void initialiseStatisticalMeasureRuleDebugging() {
                    debug(unaryStatisticalMeasureRule);
                    debug(binaryStatisticalMeasureRule);
                    debug(binaryStatisticalQuantileMeasureRule);
                }

                //! Initialise debugging for the subset rules
                void initialiseSubsetRuleDebugging() {
                    debug(subsetRule);
                    debug(subsetSpecificRule);
                    debug(filterSubsetRule);
                    debug(subsetSubsetOperationRule);
                }

                //! Initialise debugging for the constraint rule
                void initialiseConstraintRuleDebugging() {
                    debug(constraintRule);
                }

                //! Initialise debugging for the primary constraint rules
                void initialisePrimaryConstraintRuleDebugging() {
                    debug(primaryConstraintRule);
                    debug(notConstraintRule);
                    debug(unaryTypeConstraintRule);
                    debug(unarySpatialConstraintRule);
                }

                //! Initialise debugging for the filter numeric measure rules
                void initialiseFilterNumericMeasureRuleDebugging() {
                    debug(filterNumericMeasureRule);
                    debug(unaryNumericFilterRule);
                    debug(binaryNumericFilterRule);
                }

                //! Initialise debugging for the composed constraint rule
                void initialiseComposedConstraintRuleDebugging() {
                    debug(andConstraintRule);
                    debug(orConstraintRule);
                    debug(implicationConstraintRule);
                    debug(equivalenceConstraintRule);
                }

                //! Initialise debugging for the spatial measure rule
                void initialiseSpatialMeasureRuleDebugging() {
                    debug(spatialMeasureRule);
                }

                //! Initialise debugging for the comparator rule
                void initialiseComparatorRuleDebugging() {
                    debug(comparatorRule);
                }

                //! Initialise debugging for the state variable rule
                void initialiseNumericStateVariableRuleDebugging() {
                    debug(numericStateVariableRule);
                    debug(stateVariableRule);
                    debug(stateVariableNameRule);
                    debug(stateVariableTypeRule);
                }

                //! Initialise the error handling routines
                void initialiseErrorHandlingSupport() {
                    initialiseTemporalNumericMeasureErrorHandlingSupport();
                    initialiseNumericStatisticalMeasureErrorHandlingSupport();
                    initialiseNumericMeasureCollectionErrorHandlingSupport();
                    initialiseNumericMeasureErrorHandlingSupport();
                    initialiseNumericSpatialMeasureErrorHandlingSupport();
                    initialiseSubsetErrorHandlingSupport();
                    initialiseConstraintsErrorHandlingSupport();
                    initialiseStateVariableErrorHandlingSupport();
                }

                //! Initialise the constraints error handling support
                void initialiseConstraintsErrorHandlingSupport() {
                    initialisePrimaryConstraintErrorHandlingSupport();
                    initialiseFilterNumericMeasureErrorHandlingSupport();
                    initialiseComposedConstraintErrorHandlingSupport();
                }

                //! Initialise the temporal numeric measure error handling support
                void initialiseTemporalNumericMeasureErrorHandlingSupport() {
                    qi::on_error<qi::fail>(
                        temporalNumericMeasureRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                    qi::on_error<qi::fail>(
                        unaryNumericTemporalRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                    qi::on_error<qi::fail>(
                        binaryNumericTemporalRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                }

                //! Initialise the numeric statistical measure error handling support
                void initialiseNumericStatisticalMeasureErrorHandlingSupport() {
                    qi::on_error<qi::fail>(
                        unaryStatisticalNumericRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                    qi::on_error<qi::fail>(
                        binaryStatisticalNumericRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                    qi::on_error<qi::fail>(
                        binaryStatisticalQuantileNumericRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                }

                //! Initialise the numeric measure collection error handling support
                void initialiseNumericMeasureCollectionErrorHandlingSupport() {
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
                void initialiseNumericMeasureErrorHandlingSupport() {
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
                void initialiseNumericSpatialMeasureErrorHandlingSupport() {
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
                void initialiseSubsetErrorHandlingSupport() {
                    qi::on_error<qi::fail>(
                        filterSubsetRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                    qi::on_error<qi::fail>(
                        subsetSubsetOperationRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                }

                //! Initialise the primary constraint error handling support
                void initialisePrimaryConstraintErrorHandlingSupport() {
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
                void initialiseFilterNumericMeasureErrorHandlingSupport() {
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
                void initialiseComposedConstraintErrorHandlingSupport() {
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

                //! Initialise the state variable error handling support
                void initialiseStateVariableErrorHandlingSupport() {
                    qi::on_error<qi::fail>(
                        stateVariableNameRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                    qi::on_error<qi::fail>(
                        stateVariableTypeRule,
                        multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2)
                    );
                }

        };

    };

};


#endif
