#ifndef COMPARATORGRAMMAR_HPP
#define COMPARATORGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;


        //! The grammar for parsing comparator statements
        template <typename Iterator>
        class ComparatorGrammar
            : public qi::grammar<Iterator, ComparatorAttribute(), qi::space_type> {

            private:

                qi::rule<Iterator, ComparatorAttribute(), qi::space_type>
                    comparatorRule;             /*!< The rule for parsing a comparator */

                // Enumeration parsers

                ComparatorTypeParser
                    comparatorTypeParser;       /*!< The comparator type parser */

            public:

                ComparatorGrammar();

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
