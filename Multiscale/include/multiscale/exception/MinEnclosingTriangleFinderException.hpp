#ifndef MINENCLOSINGTRIANGLEFINDEREXCEPTION_HPP
#define MINENCLOSINGTRIANGLEFINDEREXCEPTION_HPP

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the minimum area enclosing triangle module
    class MinEnclosingTriangleFinderException : public runtime_error {

        public:

            MinEnclosingTriangleFinderException(const string &msg) : runtime_error(msg) {}
            MinEnclosingTriangleFinderException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
