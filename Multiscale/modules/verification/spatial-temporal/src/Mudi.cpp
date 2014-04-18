/**
 * This program is used for multidimensional model checking
 *
 * Author: Ovidiu Parvu
 * Date created: 16.03.2014
 * Date modified: 18.03.2014
 */

#include "multiscale/verification/spatial-temporal/exception/ModelCheckingHelpRequestException.hpp"
#include "multiscale/verification/spatial-temporal/execution/CommandLineModelChecking.hpp"

using namespace multiscale::verification;


// Run the model checking task
void runModelCheckingTask(int argc, char **argv) {
    CommandLineModelChecking modelChecking;

    modelChecking.initialise(argc, argv);
    modelChecking.execute();
}

// Main function
int main(int argc, char** argv) {
    try {
        runModelCheckingTask(argc, argv);
    } catch(const ModelCheckingHelpRequestException &e) {
        return EXEC_SUCCESS_CODE;
    } catch(const exception &e) {
        ExceptionHandler::printErrorMessage(e);

        return EXEC_ERR_CODE;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;

        return EXEC_ERR_CODE;
    }

    return EXEC_SUCCESS_CODE;
}
