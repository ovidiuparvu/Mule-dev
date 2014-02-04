#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include <boost/spirit/include/qi.hpp>
#include <string>

using namespace std;
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

	};

};

#endif
