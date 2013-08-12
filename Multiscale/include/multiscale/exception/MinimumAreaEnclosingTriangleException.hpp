#ifndef MINIMUMAREAENCLOSINGTRIANGLEEXCEPTION_HPP
#define MINIMUMAREAENCLOSINGTRIANGLEEXCEPTION_HPP

#include <stdexcept>
#include <string>

using namespace std;

namespace multiscale {

    //! Exception class for the minimum area enclosing triangle module
    class MinimumAreaEnclosingTriangleException : public runtime_error {

        public:

            MinimumAreaEnclosingTriangleException(const string &msg) : runtime_error(msg) {}
            MinimumAreaEnclosingTriangleException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
