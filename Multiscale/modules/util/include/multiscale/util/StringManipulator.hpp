#ifndef STRINGMANIPULATOR_HPP
#define STRINGMANIPULATOR_HPP

#include "multiscale/core/UserDefinedTypeName.hpp"
#include "multiscale/exception/InvalidInputException.hpp"

#include <string>
#include <vector>
#include <sstream>


namespace multiscale {

    //! Class for manipulating std::strings
    class StringManipulator {

        public:

            //! Count how many times character occurs in the given std::string
            /*!
             * \param searchChar    The search character of interest
             * \param inputString   The input std::string in which the character will be searched for
             */
            static unsigned long count(char searchChar, const std::string &inputString);

            //! Obtain the file name from the given file path
            /*!
             * \param filepath File path
             */
            static std::string filenameFromPath(const std::string &filepath);

            //! Replace a substd::string of the given std::string with another std::string
            /*!
             * \param initialString Initial std::string
             * \param replaceWhat Substd::string which will be replaced
             * \param replaceTo String which will be inserted instead of the replaceWhat std::string
             */
            static std::string replace(const std::string &initialString,
                                       const std::string &replaceWhat,
                                       const std::string &replaceTo);

            //! Split the given std::string into a std::vector of std::strings considering the given delimiter
            /*!
             * \param initialString Initial std::string
             * \param delimiter Delimiter
             */
            static std::vector<std::string> split(const std::string &initialString, const std::string &delimiter);

            //! Remove the trailing "new line" characters from the end of the std::string
            /*!
             * \param inputString   The given input std::string
             */
            static std::string trimRight(std::string &inputString);

            //! Remove the trailing "new line" characters from the end of the std::string
            /*!
             * \param inputString   The given input std::string
             */
            static std::string trimRight(const std::string &inputString);

            //! Convert the std::string to the given type
            /*!
             * \param inputString   The given input std::string
             */
            template <typename T>
            static T convert(const std::string &inputString) {
                std::stringstream stringStream(inputString);
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

            //! Convert the variable to a std::string
            /*!
             * \param variable Variable
             */
            template <typename T>
            static std::string toString(T variable) {
                std::ostringstream stringStream;

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
