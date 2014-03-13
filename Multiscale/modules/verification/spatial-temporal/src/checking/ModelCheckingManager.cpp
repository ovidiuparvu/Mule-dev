#include "multiscale/verification/spatial-temporal/checking/ModelCheckingManager.hpp"

using namespace multiscale::verification;


ModelCheckingManager::ModelCheckingManager(const std::string &logicQueriesFilepath,
                                           const std::string &tracesFolderPath) {
    initialise(logicQueriesFilepath, tracesFolderPath);
}

ModelCheckingManager::~ModelCheckingManager() {
    abstractSyntaxTrees.clear();
    logicQueries.clear();
    modelCheckers.clear();
}

//void Model
