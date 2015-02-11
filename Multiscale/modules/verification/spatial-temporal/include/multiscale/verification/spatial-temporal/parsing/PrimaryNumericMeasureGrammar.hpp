#ifndef PRIMARYNUMERICMEASUREGRAMMAR_HPP
#define PRIMARYNUMERICMEASUREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/PrimaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryNumericMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryStatisticalMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryStatisticalQuantileMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/NumericStateVariableGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SpatialMeasureCollectionGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"
#include "multiscale/verification/spatial-temporal/parsing/UnaryNumericMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/UnaryStatisticalMeasureGrammar.hpp"

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
        class SpatialMeasureCollectionGrammar;


        //! The grammar for parsing primary numeric measure statements
        template <typename Iterator>
        class PrimaryNumericMeasureGrammar
            : public qi::grammar<Iterator, PrimaryNumericMeasureAttribute(), qi::space_type> {

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

                SpatialMeasureCollectionGrammar<Iterator>*
                    spatialMeasureCollectionRule;                   /*!< The grammar for parsing spatial measure
                                                                         collections */

                // Rules

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

            public:

                PrimaryNumericMeasureGrammar(SpatialMeasureCollectionGrammar<Iterator>
                                             *spatialMeasureCollectionGrammar);

            private:

                //! Initialisation function
                void initialise();

                //! Initialise the grammar
                void initialiseGrammar();

                //! Initialise the primary numeric measure rule
                void initialisePrimaryNumericMeasureRule();

                //! Initialise the numeric spatial measure rule
                void initialiseNumericSpatialMeasureRule();

                //! Initialise debug support
                void initialiseDebugSupport();

                //! Assign names to the rules
                void assignNamesToRules();

                //! Assign names to the primary numeric measure rules
                void assignNamesToPrimaryNumericMeasureRules();

                //! Assign names to the numeric spatial measure rules
                void assignNamesToNumericSpatialMeasureRules();

                //! Initialise the debugging of rules
                void initialiseRulesDebugging();

                //! Initialise debugging for the primary numeric measure rule
                void initialisePrimaryNumericMeasureRuleDebugging();

                //! Initialise debugging for the numeric spatial measure rule
                void initialiseNumericSpatialMeasureRuleDebugging();

                //! Initialise the error handling routines
                void initialiseErrorHandlingSupport();

                //! Initialise the numeric spatial measure error handling support
                void initialiseNumericSpatialMeasureErrorHandlingSupport();

        };

    };

};


#endif
