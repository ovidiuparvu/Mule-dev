#ifndef PARSERGRAMMAR_HPP
#define PARSERGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/exception/ParserGrammarUnexpectedTokenException.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace phoenix = boost::phoenix;

using namespace boost::spirit;


namespace multiscale {

    namespace verification {

        //! Structure for defining the error handler
        struct ErrorHandler {
            //! Structure for specifying the type of the result
            template <typename, typename, typename>
            struct result { typedef void type; };

            //! Overloaded operator
            /*!
             * \param expectedToken The expected token
             * \param errorPosition Iterator pointing to the error position
             * \param last          Iterator pointing to the end of the query
             */
            template<typename Iterator>
            void operator()(qi::info const &expectedToken, Iterator errorPosition, Iterator last) const {
                string errorString          = string(errorPosition, last);
                string expectedTokenString  = getExpectedTokenAsString(expectedToken);

                throw ParserGrammarUnexpectedTokenException(expectedTokenString, errorString);
            }

            //! Convert the expected token to a string
            /*! Convert the expected token to a string and remove enclosing quotes
             *
             * \param expectedToken The expected token (not a string)
             */
            string getExpectedTokenAsString(qi::info const &expectedToken) const {
                stringstream strStream;

                strStream << expectedToken;

                string expectedTokenString  = strStream.str();

                // Remove the enclosing quotes
                return expectedTokenString.substr(1, (expectedTokenString.length() - 2));
            }

        };

        // Create a lazy error handler function
        phoenix::function<ErrorHandler> const handleError = ErrorHandler();


        //! The grammar for parsing (P)BLSTL spatial-temporal logical queries
        template <typename Iterator>
        class ParserGrammar : public qi::grammar<Iterator, string(), ascii::space_type> {

            private:

                qi::rule<Iterator, string(), ascii::space_type> start; /*!< The starting element for the parser */

            public:

                ParserGrammar() : ParserGrammar::base_type(start) {
                    start
                        %=  lexeme[+(ascii::char_ - "1")]
                            > lit("1")
                            > lit("2");

                    // Error handling routine
                    qi::on_error<qi::fail>(start, multiscale::verification::handleError(_4, _3, _2));
                }

        };

    };

};

#endif
