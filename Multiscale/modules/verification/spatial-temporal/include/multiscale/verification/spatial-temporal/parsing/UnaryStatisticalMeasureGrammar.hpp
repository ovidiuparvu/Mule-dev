#ifndef UNARYSTATISTICALMEASUREGRAMMAR_HPP
#define UNARYSTATISTICALMEASUREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/UnaryStatisticalMeasureAttribute.hpp"
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


        //! The grammar for parsing unary statistical measure statements
        template <typename Iterator>
        class UnaryStatisticalMeasureGrammar
            : public qi::grammar<Iterator, UnaryStatisticalMeasureAttribute(), qi::space_type> {

            private:

                qi::rule<Iterator, UnaryStatisticalMeasureAttribute(), qi::space_type>
                    unaryStatisticalMeasureRule;        /*!< The rule for parsing a unary statistical
                                                             measure */

                // Enumeration parsers

                UnaryStatisticalMeasureTypeParser
                    unaryStatisticalMeasureTypeParser;  /*!< The unary statistical measure type parser */

            public:

                UnaryStatisticalMeasureGrammar();

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
