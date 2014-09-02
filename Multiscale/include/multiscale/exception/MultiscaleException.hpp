#ifndef MULTISCALEEXCEPTION_HPP
#define MULTISCALEEXCEPTION_HPP

#include "multiscale/core/Multiscale.hpp"

#include <stdexcept>
#include <string>
#include <sstream>
#include <typeinfo>

#define MS_throw(ex, msg)                               (throw ex(__FILE__, __LINE__, msg))
#define MS_throw_detailed(ex, startMsg, msg, endMsg)    (throw ex(__FILE__, __LINE__, startMsg + msg + endMsg))


namespace multiscale {

    //! Parent exception class for the project
    class MultiscaleException : public std::runtime_error {

        protected:

            std::string message;             /*!< The raw message of the exception */
            std::string explanatoryString;   /*!< User friendly exception message */

        public:

            MultiscaleException() : std::runtime_error("") {}

            explicit MultiscaleException(const std::string &file, int line, const std::string &msg)
                                        : std::runtime_error(msg) {}
            explicit MultiscaleException(const std::string &file, int line, const char *msg)
                                        : std::runtime_error(msg) {}

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
            void constructExplanatoryString(const std::string &file, int line, T msg) {
                std::stringstream strStream;

                strStream << "File: " << file << ", " << std::endl
                          << "Line: " << line << ", " << std::endl
                          << "Type: " << typeid(*this).name() << ", " << std::endl
                          << "Error message: " << msg;

                explanatoryString = strStream.str();
                message           = std::string(msg);
            }

    };

};


#endif
