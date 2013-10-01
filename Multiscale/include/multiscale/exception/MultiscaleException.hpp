#ifndef MULTISCALEEXCEPTION_HPP
#define MULTISCALEEXCEPTION_HPP

#include "multiscale/util/StringManipulator.hpp"

#include <stdexcept>
#include <string>
#include <typeinfo>

using namespace std;

#define MS_throw(ex, msg) (throw ex(__FILE__, __LINE__, msg))


namespace multiscale {

    //! Parent exception class for the project
    class MultiscaleException : public runtime_error {

        private:

            string explanatoryString;

        public:

            // Constructor
            explicit MultiscaleException(const string &file, int line, const string &msg) : runtime_error(msg) {
                constructExplanatoryString<const string &>(file, line, msg);
            }

            // Constructor
            explicit MultiscaleException(const string &file, int line, const char *msg) : runtime_error(msg) {
                constructExplanatoryString<const char *>(file, line, msg);
            }

            //! Returns an explanatory string
            const char* what() const noexcept {
                return explanatoryString.c_str();
            }

        private:

            //! Construct the explanatory string
            /*!
             * \param file  File where the error occurred
             * \param line  Line number where the error occurred
             * \param msg   Error message
             */
            template <typename T>
            void constructExplanatoryString(const string &file, int line, T msg) {
                stringstream strStream;

                strStream << "File: " << file << ", " << endl
                          << "Line: " << line << ", " << endl
                          << "Type: " << typeid(*this).name() << ", " << endl
                          << "Error message: " << msg;

                explanatoryString = strStream.str();
            }

    };

};

#endif
