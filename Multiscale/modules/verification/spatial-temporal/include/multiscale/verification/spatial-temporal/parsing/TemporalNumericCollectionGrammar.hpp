#ifndef TEMPORALNUMERICCOLLECTIONGRAMMAR_HPP
#define TEMPORALNUMERICCOLLECTIONGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericCollectionAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/BinaryNumericMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ChangeMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/PrimaryNumericMeasureGrammar.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"
#include "multiscale/verification/spatial-temporal/parsing/UnaryNumericMeasureGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;


        //! The grammar for parsing temporal numeric collection statements
        template <typename Iterator>
        class TemporalNumericCollectionGrammar
            : public qi::grammar<Iterator, TemporalNumericCollectionAttribute(), qi::space_type> {

            private:

                // Grammars

                std::shared_ptr<SpatialMeasureCollectionGrammar<Iterator>>
                    spatialMeasureCollectionGrammar;               /*!< The grammar for parsing spatial measure
                                                                        collection which will be passed by reference
                                                                        to the primary numeric measure grammar */

                std::shared_ptr<PrimaryNumericMeasureGrammar<Iterator>>
                    primaryNumericMeasureRule;                      /*!< The grammar for parsing primary numeric
                                                                         measures */
                UnaryNumericMeasureGrammar<Iterator>
                    unaryNumericMeasureRule;                        /*!< The grammar for parsing unary numeric
                                                                         measures */
                BinaryNumericMeasureGrammar<Iterator>
                    binaryNumericMeasureRule;                       /*!< The grammar for parsing binary numeric
                                                                         measures */

                ChangeMeasureGrammar<Iterator>
                    changeMeasureRule;                              /*!< The grammar for parsing change measures */

                // Rules

                qi::rule<Iterator, TemporalNumericCollectionAttribute(), qi::space_type>
                    temporalNumericCollectionRule;                  /*!< The rule for parsing temporal numeric
                                                                         collections */
                qi::rule<Iterator, TemporalNumericMeasureCollectionAttribute(), qi::space_type>
                    temporalNumericMeasureCollectionRule;           /*!< The rule for parsing temporal numeric measure
                                                                         collections */
                qi::rule<Iterator, ChangeTemporalNumericCollectionAttribute(), qi::space_type>
                    changeTemporalNumericCollectionRule;            /*!< The rule for parsing a change temporal numeric
                                                                         collections attribute */
                qi::rule<Iterator, TimeSeriesTimeSeriesComponentAttribute(), qi::space_type>
                    timeSeriesTimeSeriesComponentRule;              /*!< The rule for parsing a time series time series
                                                                         component attribute */
                qi::rule<Iterator, HomogeneousHomogeneousTimeSeriesAttribute(), qi::space_type>
                    homogeneousHomogeneousTimeSeriesRule;           /*!< The rule for parsing a homogeneous homogeneous
                                                                         time series measure attribute */

                qi::rule<Iterator, TimeSeriesMeasureAttribute(), qi::space_type>
                    timeSeriesMeasureRule;                          /*!< The rule for parsing a time series measure */
                qi::rule<Iterator, HomogeneousTimeSeriesMeasureAttribute(), qi::space_type>
                    homogeneousTimeSeriesMeasureRule;               /*!< The rule for parsing a homogeneous time series
                                                                         measure */

                qi::rule<Iterator, TimeSeriesComponentAttribute(), qi::space_type>
                    timeSeriesComponentRule;                        /*!< The rule for parsing a time series
                                                                         component */
                qi::rule<Iterator, HeterogeneousTimeSeriesComponentAttribute(), qi::space_type>
                    heterogeneousTimeSeriesComponentRule;           /*!< The rule for parsing a heterogeneous
                                                                         time series component */
                qi::rule<Iterator, HomogeneousTimeSeriesComponentAttribute(), qi::space_type>
                    homogeneousTimeSeriesComponentRule;             /*!< The rule for parsing a homogeneous time series
                                                                         component */

                qi::rule<Iterator, NumericMeasureAttribute(), qi::space_type>
                    numericMeasureRule;                             /*!< The rule for parsing a numeric measure */
                qi::rule<Iterator, UnaryNumericNumericAttribute(), qi::space_type>
                    unaryNumericNumericRule;                        /*!< The rule for parsing a unary numeric numeric
                                                                         attribute */
                qi::rule<Iterator, BinaryNumericNumericAttribute(), qi::space_type>
                    binaryNumericNumericRule;                       /*!< The rule for parsing a binary numeric numeric
                                                                         attribute */

                // Enumeration parsers

                TimeSeriesMeasureTypeParser
                    timeSeriesMeasureTypeParser;                    /*!< The time series measure type parser */
                HomogeneousTimeSeriesMeasureTypeParser
                    homogeneousTimeSeriesMeasureTypeParser;         /*!< The homogeneous time series measure type
                                                                         parser */

                HeterogeneousTimeSeriesComponentTypeParser
                    heterogeneousTimeSeriesComponentTypeParser;     /*!< The heterogeneous time series component type
                                                                         parser */
                HomogeneousTimeSeriesComponentTypeParser
                    homogeneousTimeSeriesComponentTypeParser;       /*!< The homogeneous time series component type
                                                                         parser */

                // Define an unsigned real number parser

                qi::real_parser<double, qi::ureal_policies<double>>
                    unsignedRealParser;                             /*!< The unsigned real number parser */

            public:

                TemporalNumericCollectionGrammar();

            private:

                //! Initialisation function
                void initialize();

                //! Initialize the grammar
                void initializeGrammar();

                //! Initialize the temporal numeric collection rule
                void initializeTemporalNumericCollectionRule();

                //! Initialize the time series measure rule
                void initializeTimeSeriesMeasureRule();

                //! Initialize the time series component rule
                void initializeTimeSeriesComponentRule();

                //! Initialize the numeric measure rule
                void initializeNumericMeasureRule();

                //! Initialize debug support
                void initializeDebugSupport();

                //! Assign names to the rules
                void assignNamesToRules();

                //! Assign names to the temporal numeric collection rule
                void assignNamesToTemporalNumericCollectionRules();

                //! Assign names to the time series measure rule
                void assignNamesToTimeSeriesMeasureRules();

                //! Assign names to the time series component rule
                void assignNamesToTimeSeriesComponentRules();

                //! Assign names to the numeric measure rules
                void assignNamesToNumericMeasureRules();

                //! Initialize the debugging of rules
                void initializeRulesDebugging();

                //! Initialize debugging for the temporal numeric collection rule
                void initializeTemporalNumericCollectionRuleDebugging();

                //! Initialize debugging for the time series measure rule
                void initializeTimeSeriesMeasureRuleDebugging();

                //! Initialize debugging for the time series component rule
                void initializeTimeSeriesComponentRuleDebugging();

                //! Initialize debugging for the numeric measure rule
                void initializeNumericMeasureRuleDebugging();

                //! Initialize the error handling routines
                void initializeErrorHandlingSupport();

                //! Initialize the temporal numeric collection error handling support
                void initializeTemporalNumericCollectionErrorHandlingSupport();

                //! Initialize the numeric measure error handling support
                void initializeNumericMeasureErrorHandlingSupport();

        };

    };

};


#endif
