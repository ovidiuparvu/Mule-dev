#ifndef UNEXPECTEDTOKENERRORHANDLER_HPP
#define UNEXPECTEDTOKENERRORHANDLER_HPP

#include "multiscale/verification/spatial-temporal/exception/ParserGrammarUnexpectedTokenException.hpp"

#include <boost/spirit/include/qi.hpp>
#include <string>

namespace qi = boost::spirit::qi;


namespace multiscale {

    namespace verification {

        //! Structure for defining the error handler for unexpected token errors
        struct UnexpectedTokenErrorHandler {

            public:

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
                    std::string errorString          = std::string(errorPosition, last);
                    std::string expectedTokenString  = getExpectedTokenAsString(expectedToken);

                    throw ParserGrammarUnexpectedTokenException(expectedTokenString, errorString);
                }

            private:

                //! Convert the expected token to a string
                /*! Convert the expected token to a string and remove enclosing quotes
                 *
                 * \param expectedToken The expected token (not a string)
                 */
                std::string getExpectedTokenAsString(qi::info const &expectedToken) const {
                    std::stringstream strStream;

                    strStream << expectedToken;

                    std::string expectedTokenString  = strStream.str();

                    // Remove the enclosing quotes
                    return (expectedTokenString.substr(1, (expectedTokenString.length() - 2)));
                }

        };

    };

};


#endif
