#ifndef PROBABILISTICBOUNDEDLINEARSPATIALTEMPORALLOGICPARSER_HPP
#define PROBABILISTICBOUNDEDLINEARSPATIALTEMPORALLOGICPARSER_HPP

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

namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;

using namespace boost::spirit;


namespace multiscale {

    namespace verification {

        template <typename Iterator>
        class ParserGrammar : public qi::grammar<Iterator, std::string(), ascii::space_type> {

            private:

                qi::rule<Iterator, std::string(), ascii::space_type> start;

            public:

                ParserGrammar() : ParserGrammar::base_type(start) {
                    using ascii::char_;
                    using ascii::string;
                    using namespace labels;

                    using phoenix::construct;
                    using phoenix::val;

                    start
                        %=  lexeme[+(char_ - "1")]
                            > lit("1")
                            > lit("2");

                    // Error handling routine
                    qi::on_error<qi::fail>
                    (
                        start
                      , std::cout
                            << val("An error occurred! Expecting ")
                            << _4                               // what failed?
                            << val(" before: \"")
                            << construct<std::string>(_3, _2)   // iterators to error-pos, end
                            << val(" (column ")
                            << val(construct<std::string>(_1, _2))
                            << val(")\"")
                            << std::endl
                    );
                }

        };

    };

};

#endif
