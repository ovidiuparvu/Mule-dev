#ifndef TEMPORALNUMERICMEASUREGRAMMAR_HPP
#define TEMPORALNUMERICMEASUREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryNumericMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryStatisticalMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryStatisticalQuantileMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/NumericStateVariableGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SpatialMeasureCollectionGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"
#include "multiscale/verification/spatial-temporal/parsing/TemporalNumericCollectionGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/UnaryNumericMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/UnaryStatisticalMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;


        //! The grammar for parsing temporal numeric measure statements
        template <typename Iterator>
        class TemporalNumericMeasureGrammar
            : public qi::grammar<Iterator, TemporalNumericMeasureAttribute(), qi::space_type> {

            private:

                // Grammars

                UnaryStatisticalMeasureGrammar<Iterator>
                    unaryStatisticalMeasureRule;                /*!< The grammar for parsing a unary statistical
                                                                     measure */
                BinaryStatisticalMeasureGrammar<Iterator>
                    binaryStatisticalMeasureRule;               /*!< The grammar for parsing a binary statistical
                                                                     measure */
                BinaryStatisticalQuantileMeasureGrammar<Iterator>
                    binaryStatisticalQuantileMeasureRule;       /*!< The grammar for parsing a binary statistical
                                                                     quantile measure */

                UnaryNumericMeasureGrammar<Iterator>
                    unaryNumericMeasureRule;                    /*!< The grammar for parsing a unary numeric
                                                                     measure */
                BinaryNumericMeasureGrammar<Iterator>
                    binaryNumericMeasureRule;                   /*!< The grammar for parsing a binary numeric
                                                                     measure */

                TemporalNumericCollectionGrammar<Iterator>
                    temporalNumericCollectionRule;              /*!< The grammar for parsing a temporal numeric
                                                                     collection */
                SpatialMeasureCollectionGrammar<Iterator>
                    spatialMeasureCollectionRule;               /*!< The grammar for parsing a spatial measure
                                                                     collection */

                NumericStateVariableGrammar<Iterator>
                    numericStateVariableRule;                   /*!< The grammar for parsing a numeric state
                                                                     variable */

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
                    numericMeasureCollectionRule;                   /*!< The rule for parsing numeric measure
                                                                         collections */

            public:

                TemporalNumericMeasureGrammar();

            private:

                //! Initialisation function
                void initialize();

                //! Initialize the grammar
                void initializeGrammar();

                //! Initialize the temporal numeric measure rule
                void initializeTemporalNumericMeasureRule();

                //! Initialize the numeric statistical measure rules
                void initializeNumericStatisticalMeasureRule();

                //! Initialize the numeric measure collection rule
                void initializeNumericMeasureCollectionRule();

                //! Initialize debug support
                void initializeDebugSupport();

                //! Assign names to the rules
                void assignNamesToRules();

                //! Assign names to the temporal numeric measure rules
                void assignNamesToTemporalNumericMeasureRules();

                //! Assign names to the numeric statistical measure rules
                void assignNamesToNumericStatisticalMeasureRules();

                //! Assign names to the numeric measure collection rules
                void assignNamesToNumericMeasureCollectionRules();

                //! Initialize the debugging of rules
                void initializeRulesDebugging();

                //! Initialize debugging for the temporal numeric measure rule
                void initializeTemporalNumericMeasureRuleDebugging();

                //! Initialize debugging for the numeric statistical measure rule
                void initializeNumericStatisticalMeasureRuleDebugging();

                //! Initialize debugging for the numeric measure collection rule
                void initializeNumericMeasureCollectionRuleDebugging();

                //! Initialize the error handling routines
                void initializeErrorHandlingSupport();

                //! Initialize the temporal numeric measure error handling support
                void initializeTemporalNumericMeasureErrorHandlingSupport();

                //! Initialize the numeric statistical measure error handling support
                void initializeNumericStatisticalMeasureErrorHandlingSupport();

        };

    };

};


#endif
