#ifndef CONSOLEPRINTER_HPP
#define CONSOLEPRINTER_HPP

#include <string>


namespace multiscale {

    // Enumeration for UNIX colour codes
    enum class UnixColourCode : int {
        BLACK   = 0,    /*!< Black non-colour */
        RED     = 1,    /*!< Red colour */
        GREEN   = 2,    /*!< Green colour */
        YELLOW  = 3,    /*!< Yellow colour */
        BLUE    = 4,    /*!< Blue colour */
        MAGENTA = 5,    /*!< Magenta colour */
        CYAN    = 6,    /*!< Cyan colour */
        WHITE   = 7     /*!< White non-colour */
    };

    // Enumeration for Windows colour codes
    enum class WindowsColourCode : int {
        BLACK           = 0,    /*!< Black non-colour */
        DARK_BLUE       = 1,    /*!< Dark blue colour */
        DARK_GREEN      = 2,    /*!< Dark green colour */
        DARK_CYAN       = 3,    /*!< Dark cyan colour */
        DARK_RED        = 4,    /*!< Dark red colour */
        DARK_MAGENTA    = 5,    /*!< Dark magenta colour */
        DARK_YELLOW     = 6,    /*!< Dark yellow colour */
        DARK_WHITE      = 7,    /*!< White non-colour */
        GRAY            = 8,    /*!< Gray non-colour */
        BLUE            = 9,    /*!< Blue colour */
        GREEN           = 10,   /*!< Green colour */
        CYAN            = 11,   /*!< Cyan colour */
        RED             = 12,   /*!< Red colour */
        MAGENTA         = 13,   /*!< Magenta colour */
        YELLOW          = 14,   /*!< Yellow colour */
        WHITE           = 15    /*!< Faint white non-colour */
    };


    //! Class used to print (coloured) messages to the console
    class ConsolePrinter {

        public:

            //! Print a warning containing the given message string
            /*!
             * \param message The given message
             */
            static void printWarningMessage(const std::string &message);

        private:

            //! Get the CSI string representation corresponding to the given UNIX colour code
            /*!
             * \param unixColourCode    The given UNIX colour code
             */
            static std::string getUnixColourCode(const UnixColourCode &unixColourCode);

            //! Get the string representation corresponding to the given UNIX colour code
            /*!
             * \param unixColourCode    The given UNIX colour code
             */
            static std::string unixColourCodeToString(const UnixColourCode &unixColourCode);

            //! Get the CSI string representation for resetting all attributes (including colour)
            static std::string getUnixResetCode();


            // Constants
            static const std::string SEPARATOR;

            static const std::string WARNING_TAG;

            static const std::string CSI_START_TAG;
            static const std::string CSI_COLOUR_CODE_END_TAG;
            static const std::string CSI_RESET_CODE;
            static const std::string CSI_SEPARATOR;

            static const int         CSI_COLOUR_START_VALUE;

    };

};

#endif
