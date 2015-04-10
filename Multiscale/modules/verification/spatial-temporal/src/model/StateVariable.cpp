#include "multiscale/verification/spatial-temporal/model/StateVariable.hpp"

using namespace multiscale::verification;


StateVariable::StateVariable() {}

StateVariable::~StateVariable() {}

std::string StateVariable::getScaleAndSubsystem() const {
    return scaleAndSubsystem;
}

void StateVariable::setScaleAndSubsystem(const std::string &scaleAndSubsystem) {
    this->scaleAndSubsystem = scaleAndSubsystem;
}
