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

    // Error related definitions
   const int ERR_CODE = 1;
   const std::string ERR_MSG = "An error occurred: ";

};


#endif /* CORE_HPP */
