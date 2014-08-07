#ifndef MULTISCALEEXCEPTION_HPP
#define MULTISCALEEXCEPTION_HPP

#include "multiscale/util/StringManipulator.hpp"

#include <stdexcept>
#include <string>
#include <typeinfo>

using namespace std;

#define MS_throw(ex, msg)                               (throw ex(__FILE__, __LINE__, msg))
#define MS_throw_detailed(ex, startMsg, msg, endMsg)    (throw ex(__FILE__, __LINE__, startMsg + msg + endMsg))


namespace multiscale {

    //! Parent exception class for the project
    class MultiscaleException : public runtime_error {

        protected:

            string message;             /*!< The raw message of the exception */
            string explanatoryString;   /*!< User friendly exception message */

        public:

            MultiscaleException() : runtime_error("") {}

            explicit MultiscaleException(const string &file, int line, const string &msg)
                                        : runtime_error(msg) {}
            explicit MultiscaleException(const string &file, int line, const char *msg)
                                        : runtime_error(msg) {}

            //! Returns an explanatory string
            const char* what() const noexcept override {
                return explanatoryString.c_str();
            }

            //! Return the raw message of the exception
            std::string rawMessage() const noexcept {
                return message;
            }

        protected:

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
                message           = std::string(msg);
            }

    };


    // Constants
    const std::string ERR_UNDEFINED_ENUM_VALUE = "The provided enumeration value is invalid. Please use one of the available enumeration values instead.";

};


#endif
