#ifndef SCALEANDSUBSYSTEMSTRINGGRAMMAR_HPP
#define SCALEANDSUBSYSTEMSTRINGGRAMMAR_HPP

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        //! The grammar for parsing scale and subsystem string statements
        template <typename Iterator>
        class ScaleAndSubsystemStringGrammar
            : public qi::grammar<Iterator, std::string(), qi::space_type> {

            private:

                // Rules

                qi::rule<Iterator, std::string(), qi::space_type>
                    scaleAndSubsystemStringRule;                    /*!< The rule for parsing a string representing
                                                                         a scale and subsystem */


            public:

                ScaleAndSubsystemStringGrammar();

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


                // Constants
                static const std::string SCALE_AND_SUBSYSTEM_STRING_PATTERN;

            public:

                // Constants
                static const std::string SCALE_AND_SUBSYSTEM_LABEL;

        };

    };

};


#endif
