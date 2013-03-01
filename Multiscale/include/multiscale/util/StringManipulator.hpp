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

            static string           filenameFromPath(const string &filepath);
            static string           replace         (const string &initialString,
                                                     const string &replaceWhat,
                                                     const string &replaceTo);
            static vector<string>   split           (const string &initialString,
                                                     const string &delimiter);
            template <class T>
            static string toString(T variable) {
                ostringstream stringStream;

                stringStream << variable;

                return stringStream.str();
            }

    };

};

#endif
