#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingManager.hpp"

using namespace multiscale::verification;


ModelCheckingManager::ModelCheckingManager(const std::string &logicPropertyFilepath,
                                           const std::string &tracesFolderPath) {
    initialise(logicPropertyFilepath, tracesFolderPath);
}

ModelCheckingManager::~ModelCheckingManager() {
    abstractSyntaxTrees.clear();
    logicProperties.clear();
    modelCheckers.clear();
}

void ModelCheckingManager::runFrequencyModelChecking() {
    parseLogicProperties();
    createModelCheckers();
    runModelCheckers();
    outputModelCheckersResults();
}

void ModelCheckingManager::initialise(const std::string &logicPropertyFilepath,
                                      const std::string &tracesFolderPath) {
    initialiseLogicProperties(logicPropertyFilepath);
    initialiseTraceReader(tracesFolderPath);
}

void ModelCheckingManager::initialiseLogicProperties(const std::string &logicPropertiesFilepath) {
    logicProperties = logicPropertyReader.readLogicPropertiesFromFile(logicPropertiesFilepath);
}

void ModelCheckingManager::initialiseTraceReader(const std::string &tracesFolderPath) {
    traceReader = SpatialTemporalDataReader(tracesFolderPath);
}

void ModelCheckingManager::parseLogicProperties() {
    for (const auto &logicProperty : logicProperties) {
        // Inform user which logic property will be parsed
        std::cout << "[ PARSING ] " << logicProperty << std::endl;

        if (parseLogicProperty(logicProperty)) {
            std::cout << "[ SUCCESS ]" << std::endl;
        } else {
            std::cout << "[ FAIL    ]" << std::endl;
        }
    }
}

bool ModelCheckingManager::parseLogicProperty(const std::string &logicProperty) {
    try {
        return isValidLogicProperty(logicProperty);
    } catch (const InvalidInputException &ex) {
        ExceptionHandler::printErrorMessage(ex);

        return false;
    }
}

bool ModelCheckingManager::isValidLogicProperty(const std::string &logicProperty) {
    AbstractSyntaxTree syntaxTree;

    parser.setLogicalQuery(logicProperty);

    if (parser.parse(syntaxTree)) {
        abstractSyntaxTrees.push_back(syntaxTree);

        return true;
    }

    return false;
}

void ModelCheckingManager::createModelCheckers() {
    for (const auto &abstractSyntaxTree : abstractSyntaxTrees) {
        std::shared_ptr<ModelChecker> modelChecker = FrequencyModelChecker(abstractSyntaxTree);

        // TODO: Implement
    }
}
