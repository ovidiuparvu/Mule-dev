#ifndef COMPARATORGRAMMAR_HPP
#define COMPARATORGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
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
