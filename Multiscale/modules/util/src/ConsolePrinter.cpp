#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/ConsolePrinter.hpp"
#include "multiscale/util/OperatingSystem.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <iostream>

#if defined MULTISCALE_WINDOWS
    #include <io.h>
    #include <windows.h>

    #define isatty _isatty
    #define fileno _fileno
#elif defined MULTISCALE_UNIX
    #include <unistd.h>
#endif

using namespace multiscale;


void ConsolePrinter::printEmptyLine() {
    printNewLine(true);
}

void ConsolePrinter::printMessage(const std::string &message) {
    printNonColouredMessage(message, true);
}

void ConsolePrinter::printMessageWithColouredTag(const std::string &message, const std::string &tag,
                                                 const ColourCode &tagColour) {
    // If the standard output is a terminal then print output in colour
    if (isStdOutTerminalWhichSupportsColour()) {
        printMessageUsingColour(tag + SEPARATOR, tagColour, false);
    } else {
        printNonColouredMessage(tag + SEPARATOR, false);
    }

    printNonColouredMessage(message, true);
}

void ConsolePrinter::printColouredMessage(const std::string &message, const ColourCode &colourCode) {
    // If the standard output is a terminal then print output in colour
    if (isStdOutTerminalWhichSupportsColour()) {
        printMessageUsingColour(message, colourCode);
    } else {
        printNonColouredMessage(message, true);
    }
}

void ConsolePrinter::printColouredMessageWithColouredTag(const std::string &message,
                                                         const ColourCode &messageColour,
                                                         const std::string &tag,
                                                         const ColourCode &tagColour) {
    // If the standard output is a terminal then print output in colour
    if (isStdOutTerminalWhichSupportsColour()) {
        printMessageUsingColour(tag + SEPARATOR, tagColour, false);
        printMessageUsingColour(message, messageColour);
    } else {
        printNonColouredMessage(tag + SEPARATOR, false);
        printNonColouredMessage(message, true);
    }
}

void ConsolePrinter::printWarningMessage(const std::string &message) {
    printMessageWithColouredTag(message, WARNING_TAG, ColourCode::YELLOW);
}

void ConsolePrinter::printNonColouredMessage(const std::string &message,
                                             bool appendNewLineAtEnd) {
    std::cout << message;

    printNewLine(appendNewLineAtEnd);
}

bool ConsolePrinter::isStdOutTerminalWhichSupportsColour() {
    #if defined MULTISCALE_UNIX
        bool isATerminal     = isatty(fileno(stdout));
        bool isColourSupport = terminalSupportsColour(isATerminal);

        return (isATerminal && isColourSupport);
    #elif defined MULTISCALE_WINDOWS
        return isatty(fileno(stdout));
    #else
        return false;
    #endif
}

bool ConsolePrinter::terminalSupportsColour(bool isTerminal) {
    if (isTerminal) {
        return terminalSupportsColour();
    }

    return false;
}

bool ConsolePrinter::terminalSupportsColour() {
    std::string termType = OperatingSystem::getEnvironmentVariable(TERM_ENV_VARIABLE);

    return (
        (termType.compare("xterm")           == 0) ||
        (termType.compare("xterm-color")     == 0) ||
        (termType.compare("xterm-256color")  == 0) ||
        (termType.compare("screen")          == 0) ||
        (termType.compare("screen-256color") == 0) ||
        (termType.compare("linux")           == 0) ||
        (termType.compare("cygwin")          == 0)
    );
}

void ConsolePrinter::printMessageUsingColour(const std::string &message,
                                             const ColourCode &colourCode,
                                             bool appendNewLineAtEnd) {
    #if defined MULTISCALE_UNIX
        std::cout << getUnixColourCode(getColourCode(colourCode))
                  << message
                  << getResetCode();

        printNewLine(appendNewLineAtEnd);
    #elif defined MULTISCALE_WINDOWS
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<unsigned short>(getColourCode(colourCode)));

        std::cout << message;

        printNewLine(appendNewLineAtEnd);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<unsigned short>(getResetCode()));
    #else
        std::cout << message;

        printNewLine(appendNewLineAtEnd);
    #endif
}

#ifdef MULTISCALE_WINDOWS
    WindowsColourCode ConsolePrinter::getColourCode(const ColourCode &colourCode) {
        switch (colourCode) {
            case ColourCode::BLACK:
                return WindowsColourCode::BLACK;

            case ColourCode::RED:
                return WindowsColourCode::DARK_RED;

            case ColourCode::GREEN:
                return WindowsColourCode::DARK_GREEN;

            case ColourCode::YELLOW:
                return WindowsColourCode::DARK_YELLOW;

            case ColourCode::BLUE:
                return WindowsColourCode::DARK_BLUE;

            case ColourCode::MAGENTA:
                return WindowsColourCode::DARK_MAGENTA;

            case ColourCode::CYAN:
                return WindowsColourCode::DARK_CYAN;

            case ColourCode::WHITE:
                return WindowsColourCode::DARK_WHITE;

            default:
                MS_throw(InvalidInputException, ERR_INVALID_COLOUR_CODE);
        }

        // Line added to avoid "control reaches end of non-void function" warnings
        return WindowsColourCode::BLACK;
    }
#elif defined MULTISCALE_UNIX
    UnixColourCode ConsolePrinter::getColourCode(const ColourCode &colourCode) {
        switch (colourCode) {
            case ColourCode::BLACK:
                return UnixColourCode::BLACK;

            case ColourCode::RED:
                return UnixColourCode::RED;

            case ColourCode::GREEN:
                return UnixColourCode::GREEN;

            case ColourCode::YELLOW:
                return UnixColourCode::YELLOW;

            case ColourCode::BLUE:
                return UnixColourCode::BLUE;

            case ColourCode::MAGENTA:
                return UnixColourCode::MAGENTA;

            case ColourCode::CYAN:
                return UnixColourCode::CYAN;

            case ColourCode::WHITE:
                return UnixColourCode::WHITE;

            default:
                MS_throw(InvalidInputException, ERR_INVALID_COLOUR_CODE);
        }

        // Line added to avoid "control reaches end of non-void function" warnings
        return UnixColourCode::BLACK;
    }
#endif

std::string ConsolePrinter::getUnixColourCode(const UnixColourCode &unixColourCode) {
    return (CSI_START_TAG + CSI_RESET_CODE + CSI_SEPARATOR +
            unixColourCodeToString(unixColourCode) + CSI_COLOUR_CODE_END_TAG);
}

std::string ConsolePrinter::unixColourCodeToString(const UnixColourCode &unixColourCode) {
    return StringManipulator::toString(CSI_COLOUR_START_VALUE + static_cast<int>(unixColourCode));
}

#ifdef MULTISCALE_WINDOWS
    WindowsColourCode ConsolePrinter::getResetCode() {
        return (WindowsColourCode::DARK_WHITE);
    }
#elif defined MULTISCALE_UNIX
    std::string ConsolePrinter::getResetCode() {
        return (CSI_START_TAG + CSI_RESET_CODE + CSI_COLOUR_CODE_END_TAG);
    }
#endif

void ConsolePrinter::printNewLine(bool shouldPrint) {
    if (shouldPrint) {
        std::cout << std::endl;
    }
}


// Constants
const std::string ConsolePrinter::SEPARATOR = " ";

const std::string ConsolePrinter::WARNING_TAG = "[ WARNING  ]";

const std::string ConsolePrinter::CSI_START_TAG             = "\033[";
const std::string ConsolePrinter::CSI_COLOUR_CODE_END_TAG   = "m";
const std::string ConsolePrinter::CSI_RESET_CODE            = "0";
const std::string ConsolePrinter::CSI_SEPARATOR             = ";";

const int         ConsolePrinter::CSI_COLOUR_START_VALUE    = 30;

const std::string ConsolePrinter::TERM_ENV_VARIABLE         = "TERM";

const std::string ConsolePrinter::ERR_INVALID_COLOUR_CODE   = "The provided colour code is invalid. Please provide a valid colour code instead (see documentation for more details).";
