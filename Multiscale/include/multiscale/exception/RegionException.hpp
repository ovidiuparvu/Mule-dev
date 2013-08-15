#ifndef REGIONEXCEPTION_HPP
#define REGIONEXCEPTION_HPP

#include <stdexcept>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception class for the Region instances
    class RegionException : public runtime_error {

        public:

            RegionException(const string &msg) : runtime_error(msg) {}
            RegionException(const char *msg) : runtime_error(msg) {}

    };

};

#endif
