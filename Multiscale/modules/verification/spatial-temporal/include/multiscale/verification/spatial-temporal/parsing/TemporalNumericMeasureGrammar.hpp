#ifndef TEMPORALNUMERICMEASUREGRAMMAR_HPP
#define TEMPORALNUMERICMEASUREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/NumericMeasureCollectionGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/NumericStateVariableGrammar.hpp"
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


        //! The grammar for parsing temporal numeric measure statements
        template <typename Iterator>
        class TemporalNumericMeasureGrammar
            : public qi::grammar<Iterator, TemporalNumericMeasureAttribute(), qi::space_type> {

            private:

                // Grammars

                NumericMeasureCollectionGrammar<Iterator>
                    numericMeasureCollectionRule;               /*!< The grammar for parsing a numeric measure
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


            public:

                TemporalNumericMeasureGrammar();

            private:

                //! Initialisation function
                void initialise();

                //! Initialise the grammar
                void initialiseGrammar();

                //! Initialise the temporal numeric measure rule
                void initialiseTemporalNumericMeasureRule();

                //! Initialise the numeric statistical measure rules
                void initialiseNumericStatisticalMeasureRule();

                //! Initialise the n-ary numeric measure rule
                void initialiseNaryNumericMeasureRule();

                //! Initialise the statistical measure rule
                void initialiseStatisticalMeasureRule();

                //! Initialise debug support
                void initialiseDebugSupport();

                //! Assign names to the rules
                void assignNamesToRules();

                //! Assign names to the temporal numeric measure rules
                void assignNamesToTemporalNumericMeasureRules();

                //! Assign names to the numeric statistical measure rules
                void assignNamesToNumericStatisticalMeasureRules();

                //! Assign names to the n-ary numeric measure rules
                void assignNamesToNaryNumericMeasureRules();

                //! Assign names to the numeric statistical measure rules
                void assignNamesToStatisticalMeasureRules();

                //! Initialise the debugging of rules
                void initialiseRulesDebugging();

                //! Initialise debugging for the temporal numeric measure rule
                void initialiseTemporalNumericMeasureRuleDebugging();

                //! Initialise debugging for the numeric statistical measure rule
                void initialiseNumericStatisticalMeasureRuleDebugging();

                //! Initialise debugging for the n-ary numeric measure rule
                void initialiseNaryNumericMeasureRuleDebugging();

                //! Initialise debugging for the statistical measure rule
                void initialiseStatisticalMeasureRuleDebugging();

                //! Initialise the error handling routines
                void initialiseErrorHandlingSupport();

                //! Initialise the temporal numeric measure error handling support
                void initialiseTemporalNumericMeasureErrorHandlingSupport();

                //! Initialise the numeric statistical measure error handling support
                void initialiseNumericStatisticalMeasureErrorHandlingSupport();

        };

    };

};


#endif
