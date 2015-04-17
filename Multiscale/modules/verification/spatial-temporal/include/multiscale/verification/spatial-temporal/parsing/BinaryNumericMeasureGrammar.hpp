#ifndef BINARYNUMERICMEASUREGRAMMAR_HPP
#define BINARYNUMERICMEASUREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/BinaryNumericMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;


        //! The grammar for parsing binary numeric measure statements
        template <typename Iterator>
        class BinaryNumericMeasureGrammar
            : public qi::grammar<Iterator, BinaryNumericMeasureAttribute(), qi::space_type> {

            private:

                qi::rule<Iterator, BinaryNumericMeasureAttribute(), qi::space_type>
                    binaryNumericMeasureRule;           /*!< The rule for parsing a binary numeric measure */

                // Enumeration parsers

                BinaryNumericMeasureTypeParser
                    binaryNumericMeasureTypeParser;     /*!< The binary numeric measure type parser */

            public:

                BinaryNumericMeasureGrammar();

            private:

                //! Initialisation function
                void initialize();

                //! Initialize the grammar
                void initializeGrammar();

                //! Initialize debug support
                void initializeDebugSupport();

                //! Assign names to the rules
                void assignNamesToRules();

                //! Initialize the debugging of rules
                void initializeRulesDebugging();

        };

    };

};


#endif
