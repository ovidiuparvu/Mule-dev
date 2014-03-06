#include "multiscale/util/ConsolePrinter.hpp"

#include <iostream>

using namespace multiscale;


void ConsolePrinter::printWarningMessage(const std::string &message) {
    // If the Operating System is UNIX based
#ifdef __unix__
    std::cout << "\033[0;33m[ WARNING  ]\033[0m " << message << std::endl;
#elif defined _WIN32
    #include <windows.h>

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

    std::cout << "[ WARNING  ] ";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);

    std::cout << message << std::endl;
#else
    std::cout << "[ WARNING  ] " << message << std::endl;
#endif
}
