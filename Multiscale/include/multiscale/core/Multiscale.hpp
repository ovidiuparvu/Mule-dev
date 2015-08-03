#ifndef MULTISCALE_HPP
#define MULTISCALE_HPP

#include <string>

// Core definitions available for the entire multiscale project


// Platform dependent macro definitions

#if defined (_WIN32) || defined (WIN32) || defined (_WIN64) || defined (WIN64)
    #define MULTISCALE_WINDOWS
#elif defined (__unix__)
    #define MULTISCALE_UNIX
#endif


namespace multiscale {

    // Execution return codes
    const int EXEC_SUCCESS_CODE = 0;
    const int EXEC_ERR_CODE     = 1;

    // Delimiters
    const std::string LINE_DELIMITER = "\n";

    // Error related definitions
    const std::string ERR_MSG = "An error occurred: ";

    // Specific error messages
    const std::string ERR_UNDEFINED_ENUM_VALUE = "The provided enumeration value is invalid. Please use one of the available enumeration values instead.";

    const std::string ERR_INDEX_OUT_OF_BOUNDS_BEGIN = "The provided index value (";
    const std::string ERR_INDEX_OUT_OF_BOUNDS_END   = ") is invalid. Please change.";

};


#endif
