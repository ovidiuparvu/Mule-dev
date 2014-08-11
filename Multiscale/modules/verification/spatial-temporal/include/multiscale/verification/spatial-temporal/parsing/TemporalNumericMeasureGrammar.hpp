#ifndef TEMPORALNUMERICMEASREGRAMMAR_HPP
#define TEMPORALNUMERICMEASREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureAttribute.hpp"
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
        namespace ascii = boost::spirit::ascii;

        // Create a lazy error handler function
        phoenix::function<UnexpectedTokenErrorHandler> const
            handleUnexpectedTokenError = UnexpectedTokenErrorHandler();


        //! The grammar for parsing temporal numeric measure statements
        template <typename Iterator>
        class TemporalNumericMeasureGrammar : public qi::grammar<
            Iterator, NumericMeasureAttribute(), ascii::space_type> {

            private:

                // Rules

                qi::rule<Iterator, NumericMeasureAttribute(), ascii::space_type>
                    numericMeasureRule;                         /*!< The rule for parsing a numeric measure */
                qi::rule<Iterator, PrimaryNumericMeasureAttribute(), ascii::space_type>
                    primaryNumericMeasureRule;                  /*!< The rule for parsing a primary numeric numeric
                                                                     attribute */
                qi::rule<Iterator, UnaryNumericNumericAttribute(), ascii::space_type>
                    unaryNumericNumericRule;                    /*!< The rule for parsing a unary numeric numeric
                                                                     attribute */
                qi::rule<Iterator, BinaryNumericNumericAttribute(), ascii::space_type>
                    binaryNumericNumericRule;                   /*!< The rule for parsing a binary numeric numeric
                                                                     attribute */

                qi::rule<Iterator, NumericSpatialMeasureAttribute(), ascii::space_type>
                    numericSpatialMeasureRule;                  /*!< The rule for parsing a numeric spatial measure */
                qi::rule<Iterator, UnarySubsetAttribute(), ascii::space_type>
                    unarySubsetRule;                            /*!< The rule for parsing a unary subset */
                qi::rule<Iterator, BinarySubsetAttribute(), ascii::space_type>
                    binarySubsetRule;                           /*!< The rule for parsing a binary subset */
                qi::rule<Iterator, TernarySubsetAttribute(), ascii::space_type>
                    ternarySubsetRule;                          /*!< The rule for parsing a ternary subset */
                qi::rule<Iterator, QuaternarySubsetAttribute(), ascii::space_type>
                    quaternarySubsetRule;                       /*!< The rule for parsing a quaternary subset */

                qi::rule<Iterator, UnarySubsetMeasureAttribute(), ascii::space_type>
                    unarySubsetMeasureRule;                     /*!< The rule for parsing a unary subset measure */
                qi::rule<Iterator, BinarySubsetMeasureAttribute(), ascii::space_type>
                    binarySubsetMeasureRule;                    /*!< The rule for parsing a binary subset measure */
                qi::rule<Iterator, TernarySubsetMeasureAttribute(), ascii::space_type>
                    ternarySubsetMeasureRule;                   /*!< The rule for parsing a ternary subset measure */
                qi::rule<Iterator, QuaternarySubsetMeasureAttribute(), ascii::space_type>
                    quaternarySubsetMeasureRule;                /*!< The rule for parsing a quaternary subset
                                                                     measure */

                qi::rule<Iterator, UnaryNumericMeasureAttribute(), ascii::space_type>
                    unaryNumericMeasureRule;                    /*!< The rule for parsing a unary numeric measure */
                qi::rule<Iterator, BinaryNumericMeasureAttribute(), ascii::space_type>
                    binaryNumericMeasureRule;                   /*!< The rule for parsing a binary numeric measure */

                qi::rule<Iterator, SubsetAttribute(), ascii::space_type>
                    subsetRule;                                 /*!< The rule for parsing a subset */
                qi::rule<Iterator, SubsetSpecificAttribute(), ascii::space_type>
                    subsetSpecificRule;                         /*!< The rule for parsing a specific subset */
                qi::rule<Iterator, FilterSubsetAttribute(), ascii::space_type>
                    filterSubsetRule;                           /*!< The rule for parsing a subset filter */
                qi::rule<Iterator, SubsetSubsetOperationAttribute(), ascii::space_type>
                    subsetSubsetOperationRule;                  /*!< The rule for parsing a subset subset operation */

                qi::rule<Iterator, ConstraintAttribute(), ascii::space_type>
                    constraintRule;                             /*!< The rule for parsing a constraint */

                qi::rule<Iterator, PrimaryConstraintAttribute(), ascii::space_type>
                    primaryConstraintRule;                      /*!< The rule for parsing a primary constraint */
                qi::rule<Iterator, NotConstraintAttribute(), ascii::space_type>
                    notConstraintRule;                          /*!< The rule for parsing a "not" constraint */
                qi::rule<Iterator, UnarySpatialConstraintAttribute(), ascii::space_type>
                    unarySpatialConstraintRule;                 /*!< The rule for parsing a unary spatial constraint */
                qi::rule<Iterator, UnaryTypeConstraintAttribute(), ascii::space_type>
                    unaryTypeConstraintRule;                    /*!< The rule for parsing a unary type constraint */

                qi::rule<Iterator, FilterNumericMeasureAttribute(), ascii::space_type>
                    filterNumericMeasureRule;                   /*!< The rule for parsing a filter numeric measure */
                qi::rule<Iterator, UnaryNumericFilterAttribute(), ascii::space_type>
                    unaryNumericFilterRule;                     /*!< The rule for parsing a unary numeric filter
                                                                     measure */
                qi::rule<Iterator, BinaryNumericFilterAttribute(), ascii::space_type>
                    binaryNumericFilterRule;                    /*!< The rule for parsing a binary numeric filter
                                                                     measure */

                qi::rule<Iterator, AndConstraintAttribute(), ascii::space_type>
                    andConstraintRule;                          /*!< The rule for parsing an "and" constraint */
                qi::rule<Iterator, OrConstraintAttribute(), ascii::space_type>
                    orConstraintRule;                           /*!< The rule for parsing an "or" constraint */
                qi::rule<Iterator, ImplicationConstraintAttribute(), ascii::space_type>
                    implicationConstraintRule;                  /*!< The rule for parsing an "implication"
                                                                     constraint */
                qi::rule<Iterator, EquivalenceConstraintAttribute(), ascii::space_type>
                    equivalenceConstraintRule;                  /*!< The rule for parsing an "equivalence"
                                                                     constraint */

                qi::rule<Iterator, SpatialMeasureAttribute(), ascii::space_type>
                    spatialMeasureRule;                         /*!< The rule for parsing a spatial measure */

                qi::rule<Iterator, ComparatorAttribute(), ascii::space_type>
                    comparatorRule;                             /*!< The rule for parsing a comparator */

                qi::rule<Iterator, NumericStateVariableAttribute(), ascii::space_type>
                    numericStateVariableRule;                   /*!< The rule for parsing a numeric state variable */
                qi::rule<Iterator, StateVariableAttribute(), ascii::space_type>
                    stateVariableRule;                          /*!< The rule for parsing a state variable */
                qi::rule<Iterator, std::string(), ascii::space_type>
                    stateVariableNameRule;                      /*!< The rule for parsing the name of a
                                                                     state variable without escaping white space */

                // Enumeration parsers

                UnarySubsetMeasureTypeParser
                    unarySubsetMeasureTypeParser;       /*!< The unary subset measure type parser */
                BinarySubsetMeasureTypeParser
                    binarySubsetMeasureTypeParser;      /*!< The binary subset measure type parser */
                TernarySubsetMeasureTypeParser
                    ternarySubsetMeasureTypeParser;     /*!< The ternary subset measure type parser */
                QuaternarySubsetMeasureTypeParser
                    quaternarySubsetMeasureTypeParser;  /*!< The quaternary subset measure type parser */

                UnaryNumericMeasureTypeParser
                    unaryNumericMeasureTypeParser;      /*!< The unary numeric measure type parser */
                BinaryNumericMeasureTypeParser
                    binaryNumericMeasureTypeParser;     /*!< The binary numeric measure type parser */

                SubsetSpecificTypeParser
                    subsetSpecificTypeParser;           /*!< The subset specific type parser */
                SubsetOperationTypeParser
                    subsetOperationTypeParser;          /*!< The subset operation type parser */

                SpatialMeasureTypeParser
                    spatialMeasureTypeParser;           /*!< The spatial measure type parser */

                ComparatorTypeParser
                    comparatorTypeParser;               /*!< The comparator type parser */

            public:

                TemporalNumericMeasureGrammar() : TemporalNumericMeasureGrammar::base_type(numericMeasureRule) {
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
                    initialiseNumericMeasureRule();
                    initialiseNumericSpatialMeasureRule();
                    initialiseNumericSpatialSubsetMeasureRule();
                    initialiseNaryNumericMeasureRule();
                    initialiseSubsetRule();
                    initialiseConstraintsRules();
                    initialiseSpatialMeasureRule();
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
                        =   unarySubsetRule
                        |   binarySubsetRule
                        |   ternarySubsetRule
                        |   quaternarySubsetRule;

                    unarySubsetRule
                        =   (
                                unarySubsetMeasureRule
                                > '('
                                > subsetRule
                                > ')'
                            );

                    binarySubsetRule
                        =   (
                                binarySubsetMeasureRule
                                > '('
                                > subsetRule
                                > ','
                                > spatialMeasureRule
                                > ')'
                            );

                    ternarySubsetRule
                        =   (
                                ternarySubsetMeasureRule
                                > '('
                                > subsetRule
                                > ','
                                > spatialMeasureRule
                                > ','
                                > qi::double_
                                > ')'
                            );

                    quaternarySubsetRule
                        =   (
                                quaternarySubsetMeasureRule
                                > '('
                                > subsetRule
                                > ','
                                > spatialMeasureRule
                                > ','
                                > subsetRule
                                > ','
                                > spatialMeasureRule
                                > ')'
                            );
                }

                //! Initialise the numeric spatial subset measure rule
                void initialiseNumericSpatialSubsetMeasureRule() {
                    unarySubsetMeasureRule
                        =   unarySubsetMeasureTypeParser;

                    binarySubsetMeasureRule
                        =   binarySubsetMeasureTypeParser;

                    ternarySubsetMeasureRule
                        =   ternarySubsetMeasureTypeParser;

                    quaternarySubsetMeasureRule
                        =   quaternarySubsetMeasureTypeParser;
                }

                //! Initialise the n-ary numeric measure rule
                void initialiseNaryNumericMeasureRule() {
                    unaryNumericMeasureRule
                        =   unaryNumericMeasureTypeParser;

                    binaryNumericMeasureRule
                        =   binaryNumericMeasureTypeParser;
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

                //! Initialise the spatial measure rule
                void initialiseSpatialMeasureRule() {
                    spatialMeasureRule
                        =   spatialMeasureTypeParser;
                }

                //! Initialise the comparator rules
                void initialiseComparatorRules() {
                    comparatorRule
                        =   comparatorTypeParser;
                }

                //! Initialise the numeric state variable rule
                void initialiseNumericStateVariableRule() {
                    numericStateVariableRule
                        =   stateVariableRule;

                    stateVariableRule
                        =   ('{' > stateVariableNameRule > '}');

                    stateVariableNameRule
                        =   qi::raw[ +(qi::char_ - qi::char_("{}")) ];
                }

                //! Initialise debug support
                void initialiseDebugSupport() {
                    assignNamesToRules();

                    // TODO: Uncomment this function call in case of debugging
                    // initialiseRulesDebugging();
                }

                //! Assign names to the rules
                void assignNamesToRules() {
                    assignNamesToNumericMeasureRules();
                    assignNamesToNumericSpatialMeasureRules();
                    assignNamesToNumericSpatialSubsetMeasureRules();
                    assignNamesToNaryNumericMeasureRules();
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

                //! Assign names to the numeric measure rules
                void assignNamesToNumericMeasureRules() {
                    numericMeasureRule          .name("numericMeasureRule");
                    primaryNumericMeasureRule   .name("primaryNumericMeasureRule");
                    unaryNumericNumericRule     .name("unaryNumericNumericRule");
                    binaryNumericNumericRule    .name("binaryNumericNumericRule");
                }

                //! Assign names to the numeric spatial measure rules
                void assignNamesToNumericSpatialMeasureRules() {
                    numericSpatialMeasureRule      .name("numericSpatialRule");
                    unarySubsetRule         .name("unarySubsetRule");
                    binarySubsetRule        .name("binarySubsetRule");
                    ternarySubsetRule       .name("ternarySubsetRule");
                    quaternarySubsetRule    .name("quaternarySubsetRule");
                }

                //! Assign names to the numeric spatial subset measure rules
                void assignNamesToNumericSpatialSubsetMeasureRules() {
                    unarySubsetMeasureRule      .name("unarySubsetMeasureRule");
                    binarySubsetMeasureRule     .name("binarySubsetMeasureRule");
                    ternarySubsetMeasureRule    .name("ternarySubsetMeasureRule");
                    quaternarySubsetMeasureRule .name("quaternarySubsetMeasureRule");
                }

                //! Assign names to the n-ary numeric measure rules
                void assignNamesToNaryNumericMeasureRules() {
                    unaryNumericMeasureRule     .name("unaryNumericMeasureRule");
                    binaryNumericMeasureRule    .name("binaryNumericMeasureRule");
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
                }

                //! Initialise the debugging of rules
                void initialiseRulesDebugging() {
                    initialiseNumericMeasureRuleDebugging();
                    initialiseNumericSpatialMeasureRuleDebugging();
                    initialiseSpatialSubsetMeasureRuleDebugging();
                    initialiseNaryNumericMeasureRuleDebugging();
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
                    debug(unarySubsetRule);
                    debug(binarySubsetRule);
                    debug(ternarySubsetRule);
                    debug(quaternarySubsetRule);
                }

                //! Initialise debugging for the spatial subset measure rule
                void initialiseSpatialSubsetMeasureRuleDebugging() {
                    debug(unarySubsetMeasureRule);
                    debug(binarySubsetMeasureRule);
                    debug(ternarySubsetMeasureRule);
                    debug(quaternarySubsetMeasureRule);
                }

                //! Initialise debugging for the n-ary numeric measure rule
                void initialiseNaryNumericMeasureRuleDebugging() {
                    debug(unaryNumericMeasureRule);
                    debug(binaryNumericMeasureRule);
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
                }

                //! Initialise the error handling routines
                void initialiseErrorHandlingSupport() {
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

                //! Initialise the numeric measure error handling support
                void initialiseNumericMeasureErrorHandlingSupport() {
                    qi::on_error<qi::fail>(unaryNumericNumericRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(binaryNumericNumericRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the numeric spatial measure error handling support
                void initialiseNumericSpatialMeasureErrorHandlingSupport() {
                    qi::on_error<qi::fail>(unarySubsetRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(binarySubsetRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(ternarySubsetRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(quaternarySubsetRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the subset error handling support
                void initialiseSubsetErrorHandlingSupport() {
                    qi::on_error<qi::fail>(filterSubsetRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(subsetSubsetOperationRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the primary constraint error handling support
                void initialisePrimaryConstraintErrorHandlingSupport() {
                    qi::on_error<qi::fail>(primaryConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(notConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(unaryTypeConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(unarySpatialConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the filter numeric measure error handling support
                void initialiseFilterNumericMeasureErrorHandlingSupport() {
                    qi::on_error<qi::fail>(filterNumericMeasureRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(unaryNumericFilterRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(binaryNumericFilterRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the composed constraint error handling support
                void initialiseComposedConstraintErrorHandlingSupport() {
                    qi::on_error<qi::fail>(andConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(orConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(implicationConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(equivalenceConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the state variable error handling support
                void initialiseStateVariableErrorHandlingSupport() {
                    qi::on_error<qi::fail>(stateVariableNameRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

        };

    };

};


#endif
