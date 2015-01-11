/**
 * This program is used for multidimensional multiscale model checking
 *
 * Author: Ovidiu Parvu
 * Date created: 16.03.2014
 */

#include "multiscale/verification/spatial-temporal/exception/ModelCheckingHelpRequestException.hpp"
#include "multiscale/verification/spatial-temporal/execution/CommandLineModelChecking.hpp"

#include <ctime>

using namespace multiscale::verification;


// Run the model checking task
void runModelCheckingTask(int argc, char **argv) {
    CommandLineModelChecking modelChecking;

    modelChecking.initialise(argc, argv);
    modelChecking.execute();
}

// Main function
int main(int argc, char** argv) {
    // Initialise the random number generator
    std::srand(static_cast<unsigned>(std::time(0)));

    try {
        runModelCheckingTask(argc, argv);
    } catch(const ModelCheckingHelpRequestException &e) {
        return EXEC_SUCCESS_CODE;
    } catch(const MultiscaleException &e) {
        ExceptionHandler::printRawErrorMessage(e);
        ExceptionHandler::printHelpMessage();

        return EXEC_ERR_CODE;
    } catch(const std::exception &e) {
        ExceptionHandler::printDetailedErrorMessage(e);
        ExceptionHandler::printHelpMessage();

        return EXEC_ERR_CODE;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;

        return EXEC_ERR_CODE;
    }

    return EXEC_SUCCESS_CODE;
}
