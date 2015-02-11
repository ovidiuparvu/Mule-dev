#ifndef BINARYSTATISTICALMEASUREGRAMMAR_HPP
#define BINARYSTATISTICALMEASUREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryStatisticalMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;


        //! The grammar for parsing binary statistical measure statements
        template <typename Iterator>
        class BinaryStatisticalMeasureGrammar
            : public qi::grammar<Iterator, BinaryStatisticalMeasureAttribute(), qi::space_type> {

            private:

                qi::rule<Iterator, BinaryStatisticalMeasureAttribute(), qi::space_type>
                    binaryStatisticalMeasureRule;       /*!< The rule for parsing a binary statistical
                                                             measure */

                // Enumeration parsers

                BinaryStatisticalMeasureTypeParser
                    binaryStatisticalMeasureTypeParser; /*!< The binary statistical measure type parser */

            public:

                BinaryStatisticalMeasureGrammar();

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
