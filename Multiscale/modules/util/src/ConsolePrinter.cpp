#include "multiscale/util/ConsolePrinter.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <iostream>
#if defined (_WIN32) || defined (_WIN64)
    #include <windows.h>
#endif

using namespace multiscale;


void ConsolePrinter::printWarningMessage(const std::string &message) {
    // If the Operating System is UNIX based
#if defined (__unix__)
    std::cout << getUnixColourCode(UnixColourCode::YELLOW)
              << WARNING_TAG
              << getUnixResetCode()
              << SEPARATOR
              << message << std::endl;
#elif defined (_WIN32) || defined (_WIN64)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WindowsColourCode::DARK_YELLOW);

    std::cout << WARNING_TAG;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WindowsColourCode::BLACK);

    std::cout << SEPARATOR << message << std::endl;
#else
    std::cout << WARNING_TAG
              << SEPARATOR
              << message
              << std::endl;
#endif
}

std::string ConsolePrinter::getUnixColourCode(const UnixColourCode &unixColourCode) {
    return (CSI_START_TAG + CSI_RESET_CODE + CSI_SEPARATOR +
            unixColourCodeToString(unixColourCode) + CSI_COLOUR_CODE_END_TAG);
}

std::string ConsolePrinter::unixColourCodeToString(const UnixColourCode &unixColourCode) {
    return StringManipulator::toString(CSI_COLOUR_START_VALUE + static_cast<int>(unixColourCode));
}

std::string ConsolePrinter::getUnixResetCode() {
    return (CSI_START_TAG + CSI_RESET_CODE + CSI_COLOUR_CODE_END_TAG);
}


// Constants
const std::string ConsolePrinter::SEPARATOR = " ";

const std::string ConsolePrinter::WARNING_TAG = "[ WARNING  ]";

const std::string ConsolePrinter::CSI_START_TAG             = "\033[";
const std::string ConsolePrinter::CSI_COLOUR_CODE_END_TAG   = "m";
const std::string ConsolePrinter::CSI_RESET_CODE            = "0";
const std::string ConsolePrinter::CSI_SEPARATOR             = ";";

const int         ConsolePrinter::CSI_COLOUR_START_VALUE    = 30;
