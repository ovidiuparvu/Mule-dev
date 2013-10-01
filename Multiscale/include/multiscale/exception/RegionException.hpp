#ifndef REGIONEXCEPTION_HPP
#define REGIONEXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the Region instances
    class RegionException : public MultiscaleException {

        public:

            RegionException(const string &file, int line, const string &msg)
                            : MultiscaleException(file, line, msg) {}
            RegionException(const string &file, int line, const char *msg)
                            : MultiscaleException(file, line, msg) {}

    };

};

#endif
