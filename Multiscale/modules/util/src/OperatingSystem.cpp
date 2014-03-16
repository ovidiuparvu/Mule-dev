#include "multiscale/util/OperatingSystem.hpp"

#include <cstdlib>

using namespace multiscale;


std::string OperatingSystem::getEnvironmentVariable(const std::string &name) {
    const char *environmentVariableValue = std::getenv(name.c_str());

    if (environmentVariableValue) {
        return std::string(environmentVariableValue);
    }

    return std::string();
}
