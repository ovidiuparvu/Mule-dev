#ifndef BINARYSTATISTICALQUANTILEMEASUREGRAMMAR_HPP
#define BINARYSTATISTICALQUANTILEMEASUREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalQuantileMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;


        //! The grammar for parsing binary statistical quantile measure statements
        template <typename Iterator>
        class BinaryStatisticalQuantileMeasureGrammar
            : public qi::grammar<Iterator, BinaryStatisticalQuantileMeasureAttribute(), qi::space_type> {

            private:

                qi::rule<Iterator, BinaryStatisticalQuantileMeasureAttribute(), qi::space_type>
                    binaryStatisticalQuantileMeasureRule;       /*!< The rule for parsing a binary statistical
                                                                     quantile measure */

                // Enumeration parsers

                BinaryStatisticalQuantileMeasureTypeParser
                    binaryStatisticalQuantileMeasureTypeParser; /*!< The binary statistical quantile measure type
                                                                     parser */

            public:

                BinaryStatisticalQuantileMeasureGrammar();

            private:

                //! Initialisation function
                void initialise();

                //! Initialise the grammar
                void initialiseGrammar();

                //! Initialise debug support
                void initialiseDebugSupport();

                //! Assign names to the rules
                void assignNamesToRules();

                //! Initialise the debugging of rules
                void initialiseRulesDebugging();

        };

    };

};


#endif
