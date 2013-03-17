#ifndef STRINGMANIPULATOR_HPP_
#define STRINGMANIPULATOR_HPP_

#include <string>
#include <vector>
#include <sstream>

#define DIR_SEPARATOR '/'

using namespace std;

namespace multiscale {

    //! Class for manipulating strings
    class StringManipulator {

        public:

            //! Obtain the file name from the given file path
            /*!
             * \param filepath File path
             */
            static string filenameFromPath(const string &filepath);

            //! Replace a substring of the given string with another string
            /*!
             * \param initialString Initial string
             * \param replaceWhat Substring which will be replaced
             * \param replaceTo String which will be inserted instead of the replaceWhat string
             */
            static string replace(const string &initialString,
                                  const string &replaceWhat,
                                  const string &replaceTo);

            //! Split the given string into a vector of strings considering the given delimiter
            /*!
             * \param initialString Initial string
             * \param delimiter Delimiter
             */
            static vector<string> split(const string &initialString, const string &delimiter);

            //! Convert the variable to a string
            /*!
             * \param variable Variable
             */
            template <class T>
            static string toString(T variable) {
                ostringstream stringStream;

                stringStream << variable;

                return stringStream.str();
            }

    };

};

#endif
