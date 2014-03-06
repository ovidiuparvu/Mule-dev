#ifndef CONSOLEPRINTER_HPP
#define CONSOLEPRINTER_HPP

#include <string>


namespace multiscale {

    //! Class used to print messages to the console
    class ConsolePrinter {

        public:

            //! Print a warning containing the given message string
            /*!
             * \param message The given message
             */
            static void printWarningMessage(const std::string &message);

    };

};

#endif
