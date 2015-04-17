#ifndef SCALEANDSUBSYSTEMGRAMMAR_HPP
#define SCALEANDSUBSYSTEMGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/ScaleAndSubsystemAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/ScaleAndSubsystemStringGrammar.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        //! The grammar for parsing scale and subsystem statements
        template <typename Iterator>
        class ScaleAndSubsystemGrammar
            : public qi::grammar<Iterator, ScaleAndSubsystemAttribute(), qi::space_type> {

            private:

                // Grammars

                ScaleAndSubsystemStringGrammar<Iterator>
                    scaleAndSubsystemStringRule;                /*!< The rule for parsing a string representing
                                                                     a scale and subsystem */

                // Rules

                qi::rule<Iterator, ScaleAndSubsystemAttribute(), qi::space_type>
                    scaleAndSubsystemRule;                      /*!< The rule for parsing a scale and subsystem */

            public:

                ScaleAndSubsystemGrammar();

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

                //! Initialize the error handling routines
                void initializeErrorHandlingSupport();

        };

    };

};


#endif
