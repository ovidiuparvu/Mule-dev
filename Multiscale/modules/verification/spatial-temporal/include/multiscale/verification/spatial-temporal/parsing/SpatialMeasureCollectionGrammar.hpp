#ifndef SPATIALMEASURECOLLECTIONGRAMMAR_HPP
#define SPATIALMEASURECOLLECTIONGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericSpatialAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/PrimarySpatialMeasureCollectionAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ScaleAndSubsystemAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureCollectionAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericSpatialAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryNumericMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ComparatorGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ScaleAndSubsystemGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"
#include "multiscale/verification/spatial-temporal/parsing/UnaryNumericMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <memory>
#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;


        // Forward declaration of classes
        template <typename Iterator>
        class PrimaryNumericMeasureGrammar;


        //! The grammar for parsing spatial measure collection statements
        template <typename Iterator>
        class SpatialMeasureCollectionGrammar
            : public qi::grammar<Iterator, SpatialMeasureCollectionAttribute(), qi::space_type> {

            private:

                // Grammars

                std::shared_ptr<PrimaryNumericMeasureGrammar<Iterator>>
                    primaryNumericMeasureRule;                      /*!< The grammar for parsing primary numeric
                                                                         measures */

                UnaryNumericMeasureGrammar<Iterator>
                    unaryNumericMeasureRule;                        /*!< The grammar for parsing unary numeric
                                                                         measures */
                BinaryNumericMeasureGrammar<Iterator>
                    binaryNumericMeasureRule;                       /*!< The grammar for parsing binary numeric
                                                                         measures */

                ComparatorGrammar<Iterator>
                    comparatorRule;                                 /*!< The grammar for parsing comparators */

                ScaleAndSubsystemGrammar<Iterator>
                    scaleAndSubsystemRule;                          /*!< The grammar for parsing scales and
                                                                         subsystems */

                // Rules

                qi::rule<Iterator, SpatialMeasureCollectionAttribute(), qi::space_type>
                    spatialMeasureCollectionRule;                   /*!< The rule for parsing a spatial measure
                                                                         collection */

                qi::rule<Iterator, PrimarySpatialMeasureCollectionAttribute(), qi::space_type>
                    primarySpatialMeasureCollectionRule;            /*!< The rule for parsing a primary spatial
                                                                         measure collection */
                qi::rule<Iterator, UnaryNumericSpatialAttribute(), qi::space_type>
                    unaryNumericSpatialMeasureCollectionRule;       /*!< The rule for parsing a unary numeric spatial
                                                                         measure collection */
                qi::rule<Iterator, BinaryNumericSpatialAttribute(), qi::space_type>
                    binaryNumericSpatialMeasureCollectionRule;      /*!< The rule for parsing a binary numeric spatial
                                                                         measure collection */

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
                qi::rule<Iterator, UnaryScaleAndSubsystemConstraintAttribute(), qi::space_type>
                    unaryScaleAndSubsystemConstraintRule;           /*!< The rule for parsing a unary scale and
                                                                         subsystem constraint */

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

                // Enumeration parsers

                SubsetSpecificTypeParser
                    subsetSpecificTypeParser;                       /*!< The subset specific type parser */
                SubsetOperationTypeParser
                    subsetOperationTypeParser;                      /*!< The subset operation type parser */

                SpatialMeasureTypeParser
                    spatialMeasureTypeParser;                       /*!< The spatial measure type parser */

            public:

                SpatialMeasureCollectionGrammar();

            private:

                //! Initialisation function
                void initialize();

                //! Initialize the grammar
                void initializeGrammar();

                //! Initialize the spatial measure collection rule
                void initializeSpatialMeasureCollectionRule();

                //! Initialize the spatial measure rule
                void initializeSpatialMeasureRule();

                //! Initialize the subset rule
                void initializeSubsetRule();

                //! Initialize the constraints rules
                void initializeConstraintsRules();

                //! Initialize the constraint rule
                void initializeConstraintRule();

                //! Initialize the primary constraint rule
                void initializePrimaryConstraintRule();

                //! Initialize the filter numeric measure rule
                void initializeFilterNumericMeasureRule();

                //! Initialize the composed constraint rule
                void initializeComposedConstraintRule();

                //! Initialize debug support
                void initializeDebugSupport();

                //! Assign names to the rules
                void assignNamesToRules();

                //! Assign names to the spatial measure collection rules
                void assignNamesToSpatialMeasureCollectionRules();

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

                //! Initialize the debugging of rules
                void initializeRulesDebugging();

                //! Initialize debugging for the spatial measure collection rule
                void initializeSpatialMeasureCollectionRuleDebugging();

                //! Initialize debugging for the numeric spatial measure rule
                void initializeSpatialMeasureRuleDebugging();

                //! Initialize debugging for the subset rules
                void initializeSubsetRuleDebugging();

                //! Initialize the debugging of the constraints rules
                void initializeConstraintsRulesDebugging();

                //! Initialize debugging for the constraint rule
                void initializeConstraintRuleDebugging();

                //! Initialize debugging for the primary constraint rules
                void initializePrimaryConstraintRuleDebugging();

                //! Initialize debugging for the filter numeric measure rules
                void initializeFilterNumericMeasureRuleDebugging();

                //! Initialize debugging for the composed constraint rule
                void initializeComposedConstraintRuleDebugging();

                //! Initialize the error handling routines
                void initializeErrorHandlingSupport();

                //! Initialize the numeric measure collection error handling support
                void initializeSpatialMeasureCollectionErrorHandlingSupport();

                //! Initialize the subset error handling support
                void initializeSubsetErrorHandlingSupport();

                //! Initialize the constraints error handling support
                void initializeConstraintsErrorHandlingSupport();

                //! Initialize the primary constraint error handling support
                void initializePrimaryConstraintErrorHandlingSupport();

                //! Initialize the filter numeric measure error handling support
                void initializeFilterNumericMeasureErrorHandlingSupport();

                //! Initialize the composed constraint error handling support
                void initializeComposedConstraintErrorHandlingSupport();

        };

    };

};


#endif
