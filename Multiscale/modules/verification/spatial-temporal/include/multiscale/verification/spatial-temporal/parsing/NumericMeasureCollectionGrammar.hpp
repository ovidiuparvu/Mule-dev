#ifndef NUMERICMEASURECOLLECTIONGRAMMAR_HPP
#define NUMERICMEASURECOLLECTIONGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/NumericMeasureCollectionAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryNumericMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryStatisticalMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryStatisticalQuantileMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/NumericStateVariableGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"
#include "multiscale/verification/spatial-temporal/parsing/UnaryNumericMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/UnaryStatisticalMeasureGrammar.hpp"

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


        //! The grammar for parsing numeric measure collection statements
        template <typename Iterator>
        class NumericMeasureCollectionGrammar
            : public qi::grammar<Iterator, NumericMeasureCollectionAttribute(), qi::space_type> {

            private:

                // Grammars

                NumericStateVariableGrammar<Iterator>
                    numericStateVariableRule;                       /*!< The grammar for parsing numeric state
                                                                         variables */

                UnaryStatisticalMeasureGrammar<Iterator>
                    unaryStatisticalMeasureRule;                    /*!< The grammar for parsing unary statistical
                                                                         measures */
                BinaryStatisticalMeasureGrammar<Iterator>
                    binaryStatisticalMeasureRule;                   /*!< The grammar for parsing binary statistical
                                                                         measures */
                BinaryStatisticalQuantileMeasureGrammar<Iterator>
                    binaryStatisticalQuantileMeasureRule;           /*!< The grammar for parsing binary statistical
                                                                         quantile measures */

                UnaryNumericMeasureGrammar<Iterator>
                    unaryNumericMeasureRule;                        /*!< The grammar for parsing unary numeric
                                                                         measures */
                BinaryNumericMeasureGrammar<Iterator>
                    binaryNumericMeasureRule;                       /*!< The grammar for parsing binary numeric
                                                                         measures */

                // Rules

                qi::rule<Iterator, NumericMeasureCollectionAttribute(), qi::space_type>
                    numericMeasureCollectionRule;                   /*!< The rule for parsing numeric measure
                                                                         collections */

                qi::rule<Iterator, TemporalNumericCollectionAttribute(), qi::space_type>
                    temporalNumericCollectionRule;                  /*!< The rule for parsing temporal numeric
                                                                         collections */
                qi::rule<Iterator, TemporalNumericMeasureCollectionAttribute(), qi::space_type>
                    temporalNumericMeasureCollectionRule;           /*!< The rule for parsing temporal numeric measure
                                                                         collections */
                qi::rule<Iterator, ChangeTemporalNumericCollectionAttribute(), qi::space_type>
                    changeTemporalNumericCollectionRule;            /*!< The rule for parsing a change temporal numeric
                                                                         collections attribute */
                qi::rule<Iterator, TimeseriesTimeseriesComponentAttribute(), qi::space_type>
                    timeseriesTimeseriesComponentRule;              /*!< The rule for parsing a timeseries timeseries
                                                                         component attribute */
                qi::rule<Iterator, HomogeneousHomogeneousTimeseriesAttribute(), qi::space_type>
                    homogeneousHomogeneousTimeseriesRule;           /*!< The rule for parsing a homogeneous homogeneous
                                                                         timeseries measure attribute */

                qi::rule<Iterator, ChangeMeasureAttribute(), qi::space_type>
                    changeMeasureRule;                              /*!< The rule for parsing a change measure */

                qi::rule<Iterator, TimeseriesMeasureAttribute(), qi::space_type>
                    timeseriesMeasureRule;                          /*!< The rule for parsing a timeseries measure */
                qi::rule<Iterator, HomogeneousTimeseriesMeasureAttribute(), qi::space_type>
                    homogeneousTimeseriesMeasureRule;               /*!< The rule for parsing a homogeneous timeseries
                                                                         measure */

                qi::rule<Iterator, TimeseriesComponentAttribute(), qi::space_type>
                    timeseriesComponentRule;                        /*!< The rule for parsing a timeseries
                                                                         component */
                qi::rule<Iterator, HeterogeneousTimeseriesComponentAttribute(), qi::space_type>
                    heterogeneousTimeseriesComponentRule;           /*!< The rule for parsing a heterogeneous
                                                                         timeseries component */
                qi::rule<Iterator, HomogeneousTimeseriesComponentAttribute(), qi::space_type>
                    homogeneousTimeseriesComponentRule;             /*!< The rule for parsing a homogeneous timeseries
                                                                         component */

                qi::rule<Iterator, NumericMeasureAttribute(), qi::space_type>
                    numericMeasureRule;                             /*!< The rule for parsing a numeric measure */
                qi::rule<Iterator, PrimaryNumericMeasureAttribute(), qi::space_type>
                    primaryNumericMeasureRule;                      /*!< The rule for parsing a primary numeric numeric
                                                                         attribute */
                qi::rule<Iterator, UnaryNumericNumericAttribute(), qi::space_type>
                    unaryNumericNumericRule;                        /*!< The rule for parsing a unary numeric numeric
                                                                         attribute */
                qi::rule<Iterator, BinaryNumericNumericAttribute(), qi::space_type>
                    binaryNumericNumericRule;                       /*!< The rule for parsing a binary numeric numeric
                                                                         attribute */

                qi::rule<Iterator, NumericSpatialMeasureAttribute(), qi::space_type>
                    numericSpatialMeasureRule;                      /*!< The rule for parsing a numeric spatial measure */
                qi::rule<Iterator, UnaryStatisticalSpatialAttribute(), qi::space_type>
                    unaryStatisticalSpatialRule;                    /*!< The rule for parsing a unary statistical
                                                                         spatial attribute */
                qi::rule<Iterator, BinaryStatisticalSpatialAttribute(), qi::space_type>
                    binaryStatisticalSpatialRule;                   /*!< The rule for parsing a binary statistical
                                                                         spatial attribute */
                qi::rule<Iterator, BinaryStatisticalQuantileSpatialAttribute(), qi::space_type>
                    binaryStatisticalQuantileSpatialRule;           /*!< The rule for parsing a binary statistical
                                                                         quantile spatial attribute */

                qi::rule<Iterator, SpatialMeasureCollectionAttribute(), qi::space_type>
                    spatialMeasureCollectionRule;                   /*!< The rule for parsing a spatial measure
                                                                         collection */

                qi::rule<Iterator, SpatialMeasureAttribute(), qi::space_type>
                    spatialMeasureRule;                             /*!< The rule for parsing a spatial measure */

                qi::rule<Iterator, SubsetAttribute(), qi::space_type>
                    subsetRule;                                     /*!< The rule for parsing a subset */
                qi::rule<Iterator, SubsetSpecificAttribute(), qi::space_type>
                    subsetSpecificRule;                             /*!< The rule for parsing a specific subset */
                qi::rule<Iterator, FilterSubsetAttribute(), qi::space_type>
                    filterSubsetRule;                               /*!< The rule for parsing a subset filter */
                qi::rule<Iterator, SubsetSubsetOperationAttribute(), qi::space_type>
                    subsetSubsetOperationRule;                      /*!< The rule for parsing a subset subset
                                                                         operation */

                qi::rule<Iterator, ConstraintAttribute(), qi::space_type>
                    constraintRule;                                 /*!< The rule for parsing a constraint */

                qi::rule<Iterator, PrimaryConstraintAttribute(), qi::space_type>
                    primaryConstraintRule;                          /*!< The rule for parsing a primary constraint */
                qi::rule<Iterator, NotConstraintAttribute(), qi::space_type>
                    notConstraintRule;                              /*!< The rule for parsing a "not" constraint */
                qi::rule<Iterator, UnarySpatialConstraintAttribute(), qi::space_type>
                    unarySpatialConstraintRule;                     /*!< The rule for parsing a unary spatial
                                                                         constraint */
                qi::rule<Iterator, UnaryTypeConstraintAttribute(), qi::space_type>
                    unaryTypeConstraintRule;                        /*!< The rule for parsing a unary type
                                                                         constraint */

                qi::rule<Iterator, FilterNumericMeasureAttribute(), qi::space_type>
                    filterNumericMeasureRule;                       /*!< The rule for parsing a filter numeric
                                                                         measure */
                qi::rule<Iterator, UnaryNumericFilterAttribute(), qi::space_type>
                    unaryNumericFilterRule;                         /*!< The rule for parsing a unary numeric filter
                                                                         measure */
                qi::rule<Iterator, BinaryNumericFilterAttribute(), qi::space_type>
                    binaryNumericFilterRule;                        /*!< The rule for parsing a binary numeric filter
                                                                         measure */

                qi::rule<Iterator, AndConstraintAttribute(), qi::space_type>
                    andConstraintRule;                              /*!< The rule for parsing an "and" constraint */
                qi::rule<Iterator, OrConstraintAttribute(), qi::space_type>
                    orConstraintRule;                               /*!< The rule for parsing an "or" constraint */
                qi::rule<Iterator, ImplicationConstraintAttribute(), qi::space_type>
                    implicationConstraintRule;                      /*!< The rule for parsing an "implication"
                                                                         constraint */
                qi::rule<Iterator, EquivalenceConstraintAttribute(), qi::space_type>
                    equivalenceConstraintRule;                      /*!< The rule for parsing an "equivalence"
                                                                         constraint */

                qi::rule<Iterator, ComparatorAttribute(), qi::space_type>
                    comparatorRule;                                 /*!< The rule for parsing a comparator */

                // Enumeration parsers

                ChangeMeasureTypeParser
                    changeMeasureTypeParser;                        /*!< The change measure type parser */

                TimeseriesMeasureTypeParser
                    timeseriesMeasureTypeParser;                    /*!< The timeseries measure type parser */
                HomogeneousTimeseriesMeasureTypeParser
                    homogeneousTimeseriesMeasureTypeParser;         /*!< The homogeneous timeseries measure type
                                                                         parser */

                HeterogeneousTimeseriesComponentTypeParser
                    heterogeneousTimeseriesComponentTypeParser;     /*!< The heterogeneous timeseries component type
                                                                         parser */
                HomogeneousTimeseriesComponentTypeParser
                    homogeneousTimeseriesComponentTypeParser;       /*!< The homogeneous timeseries component type
                                                                         parser */

                SubsetSpecificTypeParser
                    subsetSpecificTypeParser;                       /*!< The subset specific type parser */
                SubsetOperationTypeParser
                    subsetOperationTypeParser;                      /*!< The subset operation type parser */

                SpatialMeasureTypeParser
                    spatialMeasureTypeParser;                       /*!< The spatial measure type parser */

                ComparatorTypeParser
                    comparatorTypeParser;                           /*!< The comparator type parser */

            public:

                NumericMeasureCollectionGrammar();

            private:

                //! Initialisation function
                void initialise();

                //! Initialise the grammar
                void initialiseGrammar();

                //! Initialise the numeric measure collection rules
                void initialiseNumericMeasureCollectionRule();

                //! Initialise the temporal numeric collection rule
                void initialiseTemporalNumericCollectionRule();

                //! Initialise the change measure rule
                void initialiseChangeMeasureRule();

                //! Initialise the timeseries measure rule
                void initialiseTimeseriesMeasureRule();

                //! Initialise the timeseries component rule
                void initialiseTimeseriesComponentRule();

                //! Initialise the numeric measure rule
                void initialiseNumericMeasureRule();

                //! Initialise the numeric spatial measure rule
                void initialiseNumericSpatialMeasureRule();

                //! Initialise the spatial measure rule
                void initialiseSpatialMeasureRule();

                //! Initialise the subset rule
                void initialiseSubsetRule();

                //! Initialise the constraints rules
                void initialiseConstraintsRules();

                //! Initialise the constraint rule
                void initialiseConstraintRule();

                //! Initialise the primary constraint rule
                void initialisePrimaryConstraintRule();

                //! Initialise the filter numeric measure rule
                void initialiseFilterNumericMeasureRule();

                //! Initialise the composed constraint rule
                void initialiseComposedConstraintRule();

                //! Initialise the comparator rules
                void initialiseComparatorRules();

                //! Initialise debug support
                void initialiseDebugSupport();

                //! Assign names to the rules
                void assignNamesToRules();

                //! Assign names to the numeric measure collection rules
                void assignNamesToNumericMeasureCollectionRules();

                //! Assign names to the temporal numeric collection rule
                void assignNamesToTemporalNumericCollectionRules();

                //! Assign names to the change measure rule
                void assignNamesToChangeMeasureRules();

                //! Assign names to the timeseries measure rule
                void assignNamesToTimeseriesMeasureRules();

                //! Assign names to the timeseries component rule
                void assignNamesToTimeseriesComponentRules();

                //! Assign names to the numeric measure rules
                void assignNamesToNumericMeasureRules();

                //! Assign names to the numeric spatial measure rules
                void assignNamesToNumericSpatialMeasureRules();

                //! Assign names to the subset rules
                void assignNamesToSubsetRules();

                //! Assign names to constraints rules
                void assignNamesToConstraintsRules();

                //! Assign names to the constraint rules
                void assignNamesToConstraintRules();

                //! Assign names to the primary constraint rules
                void assignNamesToPrimaryConstraintRules();

                //! Assign names to the filter numeric measure rules
                void assignNamesToFilterNumericMeasureRules();

                //! Assign names to the composed constraint rules
                void assignNamesToComposedConstraintRules();

                //! Assign names to the spatial measure rules
                void assignNamesToSpatialMeasureRules();

                //! Assign names to the comparator rules
                void assignNamesToComparatorRules();

                //! Initialise the debugging of rules
                void initialiseRulesDebugging();

                //! Initialise debugging for the numeric measure collection rule
                void initialiseNumericMeasureCollectionRuleDebugging();

                //! Initialise debugging for the temporal numeric collection rule
                void initialiseTemporalNumericCollectionRuleDebugging();

                //! Initialise debugging for the change measure rule
                void initialiseChangeMeasureRuleDebugging();

                //! Initialise debugging for the timeseries measure rule
                void initialiseTimeseriesMeasureRuleDebugging();

                //! Initialise debugging for the timeseries component rule
                void initialiseTimeseriesComponentRuleDebugging();

                //! Initialise debugging for the numeric measure rule
                void initialiseNumericMeasureRuleDebugging();

                //! Initialise debugging for the numeric spatial measure rule
                void initialiseNumericSpatialMeasureRuleDebugging();

                //! Initialise debugging for the subset rules
                void initialiseSubsetRuleDebugging();

                //! Initialise the debugging of the constraints rules
                void initialiseConstraintsRulesDebugging();

                //! Initialise debugging for the constraint rule
                void initialiseConstraintRuleDebugging();

                //! Initialise debugging for the primary constraint rules
                void initialisePrimaryConstraintRuleDebugging();

                //! Initialise debugging for the filter numeric measure rules
                void initialiseFilterNumericMeasureRuleDebugging();

                //! Initialise debugging for the composed constraint rule
                void initialiseComposedConstraintRuleDebugging();

                //! Initialise debugging for the spatial measure rule
                void initialiseSpatialMeasureRuleDebugging();

                //! Initialise debugging for the comparator rule
                void initialiseComparatorRuleDebugging();

                //! Initialise the error handling routines
                void initialiseErrorHandlingSupport();

                //! Initialise the numeric measure collection error handling support
                void initialiseNumericMeasureCollectionErrorHandlingSupport();

                //! Initialise the temporal numeric collection error handling support
                void initialiseTemporalNumericCollectionErrorHandlingSupport();

                //! Initialise the numeric measure error handling support
                void initialiseNumericMeasureErrorHandlingSupport();

                //! Initialise the numeric spatial measure error handling support
                void initialiseNumericSpatialMeasureErrorHandlingSupport();

                //! Initialise the subset error handling support
                void initialiseSubsetErrorHandlingSupport();

                //! Initialise the constraints error handling support
                void initialiseConstraintsErrorHandlingSupport();

                //! Initialise the primary constraint error handling support
                void initialisePrimaryConstraintErrorHandlingSupport();

                //! Initialise the filter numeric measure error handling support
                void initialiseFilterNumericMeasureErrorHandlingSupport();

                //! Initialise the composed constraint error handling support
                void initialiseComposedConstraintErrorHandlingSupport();

        };

    };

};


#endif
