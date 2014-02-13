/*=============================================================================
    Copyright (c) 2002-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A parser for arbitrary tuples. This example presents a parser
//  for an employee structure.
//
//  [ JDG May 9, 2007 ]
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_symbols.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>

#include <iostream>
#include <string>
#include <complex>

namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

#define BOOST_SPIRIT_DEBUG


namespace client
{
    ///////////////////////////////////////////////////////////////////////////
    //  Our employee struct
    ///////////////////////////////////////////////////////////////////////////
    //[tutorial_employee_struct
	typedef boost::variant<
		double,
		int
	> key_information;

    struct name {
        std::string surname;
        std::string forename;
    };

    struct employee
    {
        int age;
        client::name name;
        key_information info;
    };

    struct NameType : qi::symbols<char, std::string> {

    	NameType() {
    		add
    			("\"John\"", std::string("Doe"))
    		;
    	}

    } NameTypeParser;
    //]
}

// We need to tell fusion about our employee struct
// to make it a first-class fusion citizen. This has to
// be in global scope.

//[tutorial_employee_adapt_struct
BOOST_FUSION_ADAPT_STRUCT(
    client::name,
    (std::string, surname)
    (std::string, forename)
)

BOOST_FUSION_ADAPT_STRUCT(
    client::employee,
    (int, age)
    (client::name, name)
    (client::key_information, info)
)
//]

namespace client
{
    ///////////////////////////////////////////////////////////////////////////////
    //  Our employee parser
    ///////////////////////////////////////////////////////////////////////////////
    //[tutorial_employee_parser
    template <typename Iterator>
    struct employee_parser : qi::grammar<Iterator, employee(), ascii::space_type>
    {
        employee_parser() : employee_parser::base_type(start, "EmployeeParser")
        {
            using qi::int_;
            using qi::lit;
            using qi::double_;
            using qi::lexeme;
            using ascii::char_;

            quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];

            nameRule = quoted_string >> "," >> NameTypeParser;

            infoRule = double_ | int_;

            start =
                lit("employee")
                >> '{'
                >> (int_ >> ','
                >>  nameRule >> ','
                >>  infoRule)
                >>  '}'
                ;

            BOOST_SPIRIT_DEBUG_NODES(
				(quoted_string)
				(nameRule)
				(infoRule)
				(start)
			);

            debug(start);
            debug(infoRule);
            debug(nameRule);
            debug(quoted_string);
        }

        qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
        qi::rule<Iterator, client::name(), ascii::space_type> nameRule;
        qi::rule<Iterator, client::key_information(), ascii::space_type> infoRule;
        qi::rule<Iterator, client::employee(), ascii::space_type> start;
    };
    //]
}

////////////////////////////////////////////////////////////////////////////
//  Main program
////////////////////////////////////////////////////////////////////////////
int
main()
{
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tAn employee parser for Spirit...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout
        << "Give me an employee of the form :"
        << "employee{age, \"surname\", \"forename\", (salary OR years of experience) } \n";
    std::cout << "Type [q or Q] to quit\n\n";

    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef client::employee_parser<iterator_type> employee_parser;

    employee_parser g; // Our grammar
    std::string str;
    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        client::employee emp;
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = phrase_parse(iter, end, g, space, emp);

        std::cout  << emp.age << ", " << emp.name.forename << ","
                   << emp.name.surname << "," << emp.info << std::endl;

        if (r && iter == end)
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "\n-------------------------\n";
        }
        else
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}
