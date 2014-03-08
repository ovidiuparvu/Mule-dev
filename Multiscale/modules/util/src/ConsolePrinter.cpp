#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/ConsolePrinter.hpp"
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


void ConsolePrinter::printColouredMessage(const std::string &message, const ColourCode &colourCode) {
    if (isatty(fileno(stdout))) {
        printMessageUsingColour(message, ColourCode::YELLOW);
    } else {
        printMessage(message);
    }
}

void ConsolePrinter::printMessage(const std::string &message) {
    std::cout << message << std::endl;
}

void ConsolePrinter::printWarningMessage(const std::string &message) {
    // If the standard output is a terminal then print output in color
    if (isatty(fileno(stdout))) {
        printColouredWarningMessage(message, ColourCode::YELLOW);
    } else {
        printNonColouredWarningMessage(message);
    }
}

void ConsolePrinter::printMessageUsingColour(const std::string &message, const ColourCode &colourCode) {
    #if defined MULTISCALE_UNIX
        std::cout << getUnixColourCode(getColourCode(colourCode))
                  << message
                  << getResetCode()
                  << std::endl;
    #elif defined MULTISCALE_WINDOWS
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), getColourCode(colourCode));

        std::cout << message << std::endl;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), getResetCode());
    #else
        std::cout << message << std::endl;
    #endif
}

void ConsolePrinter::printColouredWarningMessage(const std::string &message, const ColourCode &colourCode) {
    #if defined MULTISCALE_UNIX
        std::cout << getUnixColourCode(getColourCode(colourCode))
                  << WARNING_TAG
                  << getResetCode()
                  << SEPARATOR
                  << message << std::endl;
    #elif defined MULTISCALE_WINDOWS
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), getColourCode(colourCode));

        std::cout << WARNING_TAG;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), getResetCode());

        std::cout << SEPARATOR << message << std::endl;
    #else
        std::cout << WARNING_TAG
                  << SEPARATOR
                  << message
                  << std::endl;
    #endif
}

void ConsolePrinter::printNonColouredWarningMessage(const std::string &message) {
    std::cout << WARNING_TAG
              << SEPARATOR
              << message
              << std::endl;
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
        return (WindowsColourCode::BLACK);
    }
#elif defined MULTISCALE_UNIX
    std::string ConsolePrinter::getResetCode() {
        return (CSI_START_TAG + CSI_RESET_CODE + CSI_COLOUR_CODE_END_TAG);
    }
#endif


// Constants
const std::string ConsolePrinter::SEPARATOR = " ";

const std::string ConsolePrinter::WARNING_TAG = "[ WARNING  ]";

const std::string ConsolePrinter::CSI_START_TAG             = "\033[";
const std::string ConsolePrinter::CSI_COLOUR_CODE_END_TAG   = "m";
const std::string ConsolePrinter::CSI_RESET_CODE            = "0";
const std::string ConsolePrinter::CSI_SEPARATOR             = ";";

const int         ConsolePrinter::CSI_COLOUR_START_VALUE    = 30;

const std::string ConsolePrinter::ERR_INVALID_COLOUR_CODE   = "The provided colour code is invalid. Please provide a valid colour code instead (see documentation for more details).";
