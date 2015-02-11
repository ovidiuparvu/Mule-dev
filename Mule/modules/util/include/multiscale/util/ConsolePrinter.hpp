#ifndef CONSOLEPRINTER_HPP
#define CONSOLEPRINTER_HPP

#include "multiscale/core/Multiscale.hpp"

#include <string>


namespace multiscale {

    // Enumeration for UNIX colour codes
    enum class UnixColourCode : unsigned int {
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
    enum class WindowsColourCode : unsigned int {
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

    // Enumeration for colour codes
    enum class ColourCode : unsigned int {
        BLACK   = 0,    /*!< Black non-colour */
        RED     = 1,    /*!< Red colour */
        GREEN   = 2,    /*!< Green colour */
        YELLOW  = 3,    /*!< Yellow colour */
        BLUE    = 4,    /*!< Blue colour */
        MAGENTA = 5,    /*!< Magenta colour */
        CYAN    = 6,    /*!< Cyan colour */
        WHITE   = 7     /*!< White non-colour */
    };


    //! Class used to print (coloured) messages to the console
    class ConsolePrinter {

        public:

            //! Print a new empty line
            static void printEmptyLine();

            //! Print a message to the standard output
            /*!
             * \param message The given message
             */
            static void printMessage(const std::string &message);

            //! Print a message with a coloured tag to the standard output
            /*!
             * \param message   The given message
             * \param tag       The given tag
             * \param tagColour The colour of the tag
             */
            static void printMessageWithColouredTag(const std::string &message, const std::string &tag,
                                                    const ColourCode &tagColour);

            //! Print a coloured message to the standard output
            /*! The message will be printed in colour if and only if the standard output is a terminal.
             *  Otherwise it will be printed without changing colour.
             *
             * \param message       The given message
             * \param colourCode    The colour code used for printing the message
             */
            static void printColouredMessage(const std::string &message, const ColourCode &colourCode);

            //! Print a coloured message with a coloured tag to the standard output
            /*!
             * \param message       The given message
             * \param messageColour The colour of the given message
             * \param tag           The given tag
             * \param tagColour     The colour of the given tag
             */
            static void printColouredMessageWithColouredTag(const std::string &message,
                                                            const ColourCode &messageColour,
                                                            const std::string &tag,
                                                            const ColourCode &tagColour);

            //! Print a warning containing the given message string to the standard output
            /*!
             * \param message The given message
             */
            static void printWarningMessage(const std::string &message);

        private:

            //! Print a (non-coloured) message to the standard output
            /*!
             * \param message               The given message
             * \param appendNewLineAtEnd    Flag indicating if a new line character should be printed in the end
             */
            static void printNonColouredMessage(const std::string &message,
                                                bool appendNewLineAtEnd = true);

            //! Check if the standard output is a terminal which supports colour
            static bool isStdOutTerminalWhichSupportsColour();

            //! Check if the terminal supports colour
            /*!
             * \param isTerminal    Flag indicating if the standard output is a terminal
             */
            static bool terminalSupportsColour(bool isTerminal);

            //! Check if the terminal supports colour
            /*! Assumption: Standard output is a terminal
             */
            static bool terminalSupportsColour();

            //! Print a coloured message to the standard output
            /*! The message will be printed in colour if and only if the standard output is a terminal.
             *  Otherwise it will be printed using default colour.
             *
             * \param message               The given message
             * \param colourCode            The given colour code
             * \param appendNewLineAtEnd    Flag indicating if a new line character should be printed in the end
             */
            static void printMessageUsingColour(const std::string &message, const ColourCode &colourCode,
                                                bool appendNewLineAtEnd = true);

            #ifdef MULTISCALE_WINDOWS
                //! Get the platform specific colour code for the given generic platform colour code
                /*!
                 * \param colourCode    The generic platform colour code
                 */
                static WindowsColourCode getColourCode(const ColourCode &colourCode);
            #elif defined MULTISCALE_UNIX
                //! Get the platform specific colour code for the given generic platform colour code
                /*!
                 * \param colourCode    The generic platform colour code
                 */
                static UnixColourCode getColourCode(const ColourCode &colourCode);
            #endif

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
            #ifdef MULTISCALE_WINDOWS
                static WindowsColourCode getResetCode();
            #elif defined MULTISCALE_UNIX
                static std::string getResetCode();
            #endif

            //! Print new line character if shouldPrint flag is true
            /*!
             * \param shouldPrint   Flag indicating if a new line character should be printed to the console
             */
            static void printNewLine(bool shouldPrint = true);


            // Constants
            static const std::string SEPARATOR;

            static const std::string WARNING_TAG;

            static const std::string CSI_START_TAG;
            static const std::string CSI_COLOUR_CODE_END_TAG;
            static const std::string CSI_RESET_CODE;
            static const std::string CSI_SEPARATOR;

            static const int         CSI_COLOUR_START_VALUE;

            static const std::string TERM_ENV_VARIABLE;

            static const std::string ERR_INVALID_COLOUR_CODE;
    };

};


#endif
