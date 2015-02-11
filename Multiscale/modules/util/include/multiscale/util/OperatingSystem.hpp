#ifndef OPERATINGSYSTEM_HPP
#define OPERATINGSYSTEM_HPP

#include "multiscale/core/Multiscale.hpp"

#include <cstdlib>
#include <string>
#if defined MULTISCALE_UNIX
    #include <signal.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>
#elif defined MULTISCALE_WINDOWS
    #include <windows.h>
    #include <stdio.h>
    #include <tchar.h>
#endif


namespace multiscale {

    //! Class for executing operating system related functions
    class OperatingSystem {

        public:

            //! Get the value of the environment variable having the given name
            /*!
             * \param name The name of the environment variable
             */
            static std::string getEnvironmentVariable(const std::string &name);

            //! Create a child process and execute the program with the given path
            /*!
             * \param path  The path to the program which will be executed
             */
            static void executeProgram(const std::string &path);

        private:

            //! Create a child process and execute the program with the given path if the provided path is valid
            /*!
             * \param path  The path to the program which will be executed
             */
            static void executeProgramAndVerifyPath(const std::string &path);

            //! Create a child process and execute the program with the given path considering the specific Operating system
            /*!
             * \param path  The path to the program which will be executed
             */
            static void executeProgramOSSpecific(const std::string &path);

            #if defined MULTISCALE_UNIX
                //! Execute child process operations
                /*!
                 * \param path  The path to the program which will be executed
                 */
                static void executeChildProcessOperations(const std::string &path);
            #elif defined MULTISCALE_WINDOWS
                //! Execute child process operations
                /*!
                 * \param path  The path to the program which will be executed
                 * \param si    The process startup information
                 * \param pi    The process information
                 */
                static void executeChildProcessOperations(const std::string &path, STARTUPINFO &si,
                                                          PROCESS_INFORMATION &pi);
            #endif

            #if defined MULTISCALE_WINDOWS
                //! Convert the given path to a Windows compliant path
                /*!
                 * \param path  The path to the program which will be executed
                 */
                static std::string nativeWindowsFormatPath(const std::string &path);
            #endif

            #if defined MULTISCALE_UNIX
                //! Stop the child process after TIMEOUT_NR_SECONDS * TIMEOUT_MAX_NR have passed
                /*!
                 * \param pid   The id of the child process
                 */
                static void stopChildProcessExecutionAfterTimeout(const pid_t &pid);
            #elif defined MULTISCALE_WINDOWS
                //! Stop the child process after TIMEOUT_NR_SECONDS * TIMEOUT_MAX_NR have passed
                /*!
                 * \param processInformation   Information about the child process
                 */
                static void stopChildProcessExecutionAfterTimeout(const PROCESS_INFORMATION &processInformation);
            #endif

            #if defined MULTISCALE_UNIX
                //! Update the child process status
                /*!
                 * \param pid                   The id of the child process
                 * \param hasChildProcessExited Flag indicating if the child process exited
                 * \param nrOfTimeouts          The number of timeouts so far
                 */
                static void updateChildProcessStatus(const pid_t &pid, bool &hasChildProcessExited,
                                                     unsigned int &nrOfTimeouts);
            #elif defined MULTISCALE_WINDOWS
                //! Update the child process status
                /*!
                 * \param processInformation    Information about the child process
                 * \param hasChildProcessExited Flag indicating if the child process exited
                 * \param nrOfTimeouts          The number of timeouts so far
                 */
                static void updateChildProcessStatus(const PROCESS_INFORMATION &processInformation,
                                                     bool &hasChildProcessExited, unsigned int &nrOfTimeouts);
            #endif


            // Constants
            static const std::string ERR_EXECUTE_PROGRAM;
            static const std::string ERR_INVALID_PROGRAM_PATH;

            static const unsigned int TIMEOUT_MAX_NR_SECONDS;
            static const unsigned int TIMEOUT_NR_SECONDS;

    };

};

#endif
