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

    // Error related definitions
    const std::string ERR_MSG = "An error occurred: ";

};


#endif /* CORE_HPP */
