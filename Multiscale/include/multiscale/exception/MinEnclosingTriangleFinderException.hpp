#ifndef MINENCLOSINGTRIANGLEFINDEREXCEPTION_HPP
#define MINENCLOSINGTRIANGLEFINDEREXCEPTION_HPP

#include "multiscale/exception/MultiscaleException.hpp" 

#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the minimum area enclosing triangle module
    class MinEnclosingTriangleFinderException : public MultiscaleException {

        public:

            MinEnclosingTriangleFinderException(const string &file, int line, const string &msg)
                                                : MultiscaleException(file, line, msg) {}
            MinEnclosingTriangleFinderException(const string &file, int line, const char *msg)
                                                : MultiscaleException(file, line, msg) {}

    };

};

#endif
