#ifndef CHANGEMEASUREGRAMMAR_HPP
#define CHANGEMEASUREGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/ChangeMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;


        //! The grammar for parsing change measure statements
        template <typename Iterator>
        class ChangeMeasureGrammar
            : public qi::grammar<Iterator, ChangeMeasureAttribute(), qi::space_type> {

            private:

                qi::rule<Iterator, ChangeMeasureAttribute(), qi::space_type>
                    changeMeasureRule;          /*!< The rule for parsing a change measure */

                // Enumeration parsers

                ChangeMeasureTypeParser
                    changeMeasureTypeParser;    /*!< The change measure type parser */

            public:

                ChangeMeasureGrammar();

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
