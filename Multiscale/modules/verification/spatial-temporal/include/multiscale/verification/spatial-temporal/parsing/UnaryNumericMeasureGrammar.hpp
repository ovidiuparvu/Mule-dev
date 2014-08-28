#ifndef UNARYNUMERICMEASUREGRAMMAR_HPP
#define UNARYNUMERICMEASUREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnaryNumericMeasureAttribute.hpp"
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


        //! The grammar for parsing unary numeric measure statements
        template <typename Iterator>
        class UnaryNumericMeasureGrammar
            : public qi::grammar<Iterator, UnaryNumericMeasureAttribute(), qi::space_type> {

            private:

                qi::rule<Iterator, UnaryNumericMeasureAttribute(), qi::space_type>
                    unaryNumericMeasureRule;            /*!< The rule for parsing a unary numeric measure */

                // Enumeration parsers

                UnaryNumericMeasureTypeParser
                    unaryNumericMeasureTypeParser;      /*!< The unary numeric measure type parser */

            public:

                UnaryNumericMeasureGrammar();

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
