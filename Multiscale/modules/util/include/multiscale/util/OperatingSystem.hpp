#ifndef OPERATINGSYSTEM_HPP
#define OPERATINGSYSTEM_HPP

#include <string>


namespace multiscale {

    //! Class for executing operating system related functions
    class OperatingSystem {

        public:

            //! Get the value of the environment variable having the given name
            /*!
             * \param name The name of the environment variable
             */
            static std::string getEnvironmentVariable(const std::string &name);

    };

};

#endif
