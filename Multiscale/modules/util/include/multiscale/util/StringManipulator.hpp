#ifndef STRINGMANIPULATOR_HPP
#define STRINGMANIPULATOR_HPP

#include "multiscale/core/UserDefinedTypeName.hpp"
#include "multiscale/exception/InvalidInputException.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;


namespace multiscale {

    //! Class for manipulating strings
    class StringManipulator {

        public:

            //! Count how many times character occurs in the given string
            /*!
             * \param searchChar    The search character of interest
             * \param inputString   The input string in which the character will be searched for
             */
            static unsigned long count(char searchChar, const std::string &inputString);

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

            //! Remove the trailing "new line" characters from the end of the string
            /*!
             * \param inputString   The given input string
             */
            static string trimRight(string &inputString);

            //! Remove the trailing "new line" characters from the end of the string
            /*!
             * \param inputString   The given input string
             */
            static string trimRight(const string &inputString);

            //! Convert the string to the given type
            /*!
             * \param inputString   The given input string
             */
            template <typename T>
            static T convert(const std::string &inputString) {
                stringstream stringStream(inputString);
                T outputVariable;

                stringStream >> outputVariable;

                if ((stringStream.fail()) || (!stringStream.eof())) {
                    MS_throw(
                        InvalidInputException,
                        ERR_INVALID_CONVERSION_BEGIN +
                        inputString +
                        ERR_INVALID_CONVERSION_MIDDLE +
                        multiscale::UserDefinedTypeName<T>::name() +
                        ERR_INVALID_CONVERSION_END
                    );
                }

                return outputVariable;
            }

            //! Convert the variable to a string
            /*!
             * \param variable Variable
             */
            template <typename T>
            static string toString(T variable) {
                ostringstream stringStream;

                stringStream << variable;

                return stringStream.str();
            }

        public:

            // Constants
            static const char DIR_SEPARATOR;

            static const std::string ERR_INVALID_CONVERSION_BEGIN;
            static const std::string ERR_INVALID_CONVERSION_MIDDLE;
            static const std::string ERR_INVALID_CONVERSION_END;

    };

};


#endif
