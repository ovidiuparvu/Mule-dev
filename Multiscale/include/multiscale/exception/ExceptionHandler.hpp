#ifndef EXCEPTIONHANDLER_HPP
#define EXCEPTIONHANDLER_HPP

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/MultiscaleException.hpp"

#include <iostream>
#include <string>


namespace multiscale {

    //! Exception handler class
    class ExceptionHandler {

        public:

            //! Print the detailed error message
            /*! The error message is printed using the ex.what() method
             *
             * \param ex Exception
             */
            static void printDetailedErrorMessage(const std::exception &ex) {
                std::cerr << std::endl << ERR_MSG << std::endl
                          << std::endl << ex.what()
                          << std::endl << std::endl;
            }

            //! Print the raw error message
            /*! The error message is printed using the ex.rawMessage() method
             *
             * \param ex Exception
             */
            static void printRawErrorMessage(const MultiscaleException &ex) {
                std::cerr << std::endl << ERR_MSG << std::endl
                          << std::endl << ex.rawMessage()
                          << std::endl << std::endl;
            }

    };

};


#endif
