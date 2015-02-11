#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/RuntimeException.hpp"
#include "multiscale/util/ConsolePrinter.hpp"
#include "multiscale/util/Filesystem.hpp"
#include "multiscale/util/OperatingSystem.hpp"

#include <chrono>
#include <thread>

using namespace multiscale;


std::string OperatingSystem::getEnvironmentVariable(const std::string &name) {
    const char *environmentVariableValue = std::getenv(name.c_str());

    if (environmentVariableValue) {
        return std::string(environmentVariableValue);
    }

    return std::string();
}

void OperatingSystem::executeProgram(const std::string &path) {
    try {
        executeProgramAndVerifyPath(path);
    } catch (const MultiscaleException &ex) {
        ConsolePrinter::printWarningMessage(ex.rawMessage());
    } catch (const std::exception &ex) {
        ExceptionHandler::printDetailedErrorMessage(ex);
    }
}

void OperatingSystem::executeProgramAndVerifyPath(const std::string &path) {
    if (Filesystem::isValidFilePath(path)) {
        executeProgramOSSpecific(path);
    } else {
        MS_throw(InvalidInputException, ERR_INVALID_PROGRAM_PATH + path);
    }
}

#if defined MULTISCALE_UNIX
    void OperatingSystem::executeProgramOSSpecific(const std::string &path) {
        auto pid = fork();

        if (pid == 0) {
            executeChildProcessOperations(path);
        } else if (pid < 0) {
            // If an error occurred while executing fork()
            MS_throw(RuntimeException, ERR_EXECUTE_PROGRAM + path);
        } else {
            // Stop child process after TIMEOUT_NR_SECONDS have passed
            if (waitpid(pid, NULL, WNOHANG) == 0) {
                stopChildProcessExecutionAfterTimeout(pid);
            }
        }
    }
#elif defined MULTISCALE_WINDOWS
    void OperatingSystem::executeProgramOSSpecific(const std::string &path) {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &pi, sizeof(pi) );

        // Start the child process.
        executeChildProcessOperations(path, si, pi);

        // Wait until child process exits.
        if (WaitForSingleObject(pi.hProcess, 0) != WAIT_OBJECT_0) {
            stopChildProcessExecutionAfterTimeout(pi);
        }

        // Close process and thread handles.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
#endif

#if defined MULTISCALE_UNIX
    void OperatingSystem::executeChildProcessOperations(const std::string &path) {
        // If in the child process
        if (execl(path.c_str(), path.c_str(), (char*) NULL) == -1) {
            // If an error occurred while running execl() command
            MS_throw(RuntimeException, ERR_EXECUTE_PROGRAM + path);
        }

        // Exit process in case of errors
        exit(1);
    }
#elif defined MULTISCALE_WINDOWS
    void OperatingSystem::executeChildProcessOperations(const std::string &path, STARTUPINFO &si,
                                                        PROCESS_INFORMATION &pi) {
        std::string nativeFormatPath = nativeWindowsFormatPath(path);

        if( !CreateProcess( NULL,       // No module name (use command line)
            &nativeFormatPath[0],       // Command line
            NULL,                       // Process handle not inheritable
            NULL,                       // Thread handle not inheritable
            FALSE,                      // Set handle inheritance to FALSE
            0,                          // No creation flags
            NULL,                       // Use parent's environment block
            NULL,                       // Use parent's starting directory
            &si,                        // Pointer to STARTUPINFO structure
            &pi )                       // Pointer to PROCESS_INFORMATION structure
        ) {
            MS_throw(RuntimeException, ERR_EXECUTE_PROGRAM + path);
        }
    }
#endif

#if defined MULTISCALE_WINDOWS
    std::string OperatingSystem::nativeWindowsFormatPath(const std::string &path) {
        return Filesystem::nativeFormatFilePath(path);
    }
#endif

#if defined MULTISCALE_UNIX
    void OperatingSystem::stopChildProcessExecutionAfterTimeout(const pid_t &pid) {
        unsigned int nrOfTimeouts = 0;
        bool hasChildProcessExited = false;

        while ((nrOfTimeouts < TIMEOUT_MAX_NR_SECONDS) && (!hasChildProcessExited)) {
            std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT_NR_SECONDS));

            updateChildProcessStatus(pid, hasChildProcessExited, nrOfTimeouts);
        }

        if (!hasChildProcessExited) {
            kill(pid, SIGKILL);
        }
    }
#elif defined MULTISCALE_WINDOWS
    void OperatingSystem::stopChildProcessExecutionAfterTimeout(const PROCESS_INFORMATION &processInformation) {
        unsigned int nrOfTimeouts = 0;
        bool hasChildProcessExited = false;

        while ((nrOfTimeouts < TIMEOUT_MAX_NR_SECONDS) && (!hasChildProcessExited)) {
            std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT_NR_SECONDS));

            updateChildProcessStatus(processInformation, hasChildProcessExited, nrOfTimeouts);
        }

        if (!hasChildProcessExited) {
            TerminateProcess(processInformation.hProcess, 0);
        }
    }
#endif

#if defined MULTISCALE_UNIX
    void OperatingSystem::updateChildProcessStatus(const pid_t &pid, bool &hasChildProcessExited,
                                                   unsigned int &nrOfTimeouts) {
        if (waitpid(pid, NULL, WNOHANG) == 0) {
            nrOfTimeouts++;
        } else {
            hasChildProcessExited = true;
        }
    }
#elif defined MULTISCALE_WINDOWS
    void OperatingSystem::updateChildProcessStatus(const PROCESS_INFORMATION &processInformation,
                                                   bool &hasChildProcessExited, unsigned int &nrOfTimeouts) {
        if (WaitForSingleObject(processInformation.hProcess, 0) != WAIT_OBJECT_0) {
            nrOfTimeouts++;
        } else {
            hasChildProcessExited = true;
        }
    }
#endif


// Constants
const std::string OperatingSystem::ERR_EXECUTE_PROGRAM      = "The process executing the program located at the following path could not be created: ";
const std::string OperatingSystem::ERR_INVALID_PROGRAM_PATH = "The process was not created because the provided program path is invalid: ";

const unsigned int OperatingSystem::TIMEOUT_MAX_NR_SECONDS  = 100;
const unsigned int OperatingSystem::TIMEOUT_NR_SECONDS      = 1;
