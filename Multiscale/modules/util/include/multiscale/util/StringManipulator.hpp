#ifndef STRINGMANIPULATOR_HPP
#define STRINGMANIPULATOR_HPP

#include "multiscale/core/UserDefinedTypeName.hpp"
#include "multiscale/exception/InvalidInputException.hpp"

#include <string>
#include <vector>
#include <sstream>


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

            //! Escape carriage return characters in the provided string
            /*!
             * \param initialString The provided initial string
             */
            static std::string escapeCarriageReturns(const std::string &initialString);

            //! Obtain the file name from the given file path
            /*!
             * \param filepath File path
             */
            static std::string filenameFromPath(const std::string &filepath);

            //! Replace a substd::string of the given std::string with another string
            /*!
             * \param initialString Initial string
             * \param replaceWhat Substring which will be replaced
             * \param replaceTo String which will be inserted instead of the replaceWhat string
             */
            static std::string replace(const std::string &initialString,
                                       const std::string &replaceWhat,
                                       const std::string &replaceTo);

            //! Split the given std::string into a std::vector of strings considering the given delimiter
            /*!
             * \param initialString Initial string
             * \param delimiter     Delimiter
             */
            static std::vector<std::string> split(const std::string &initialString,
                                                  const std::string &delimiter);

            //! Remove the trailing "new line" characters from the end of the string
            /*!
             * \param inputString   The given input string
             */
            static std::string trimRight(std::string &inputString);

            //! Remove the trailing "new line" characters from the end of the string
            /*!
             * \param inputString   The given input string
             */
            static std::string trimRight(const std::string &inputString);

            //! Convert the string to the given type
            /*!
             * \param inputString   The given input string
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
                        escapeCarriageReturns(inputString) +
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


    // Explicit template specializations
    template <>
    unsigned long StringManipulator::convert(const std::string &inputString);

    template <>
    long StringManipulator::convert(const std::string &inputString);

    template <>
    int StringManipulator::convert(const std::string &inputString);

    template <>
    float StringManipulator::convert(const std::string &inputString);

    template <>
    double StringManipulator::convert(const std::string &inputString);


};


#endif
