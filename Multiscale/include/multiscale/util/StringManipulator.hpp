#ifndef STRINGMANIPULATOR_HPP_
#define STRINGMANIPULATOR_HPP_

#include <string>
#include <vector>
#include <sstream>

#define DIR_SEPARATOR '/'

using namespace std;

namespace multiscale {

    class StringManipulator {

        public:

            static string 			filenameFromPath(string& filepath);
            static string 			replace 		(string& initialString,
                                                     string  replaceWhat,
                                                     string  replaceTo);
            static vector<string>	split			(string  initialString,
                                                     string  delimiter);
            template <class T>
            static string toString(T number) {
                ostringstream stringStream;

                stringStream << number;

                return stringStream.str();
            }

    };

};

#endif
