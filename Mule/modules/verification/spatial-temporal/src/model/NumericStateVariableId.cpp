#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/model/NumericStateVariableId.hpp"

#include <boost/functional/hash.hpp>

using namespace multiscale;
using namespace multiscale::verification;


NumericStateVariableId::NumericStateVariableId(const std::string &name,
                                               const std::string &semanticType)
                                               : name(name), semanticType(semanticType) {}

NumericStateVariableId::~NumericStateVariableId() {}

const std::string& NumericStateVariableId::getName() const {
    return name;
}

void NumericStateVariableId::setName(const std::string& name) {
    this->name = name;
}

std::string NumericStateVariableId::getSemanticType() const {
    return semanticType;
}

void NumericStateVariableId::setSemanticType(const std::string &semanticType) {
    this->semanticType = semanticType;
}

bool NumericStateVariableId::operator<(const NumericStateVariableId &rhs) const {
    if (this->name.compare(rhs.name) < 0) {
        return true;
    } else if (this->name.compare(rhs.name) == 0) {
        if (this->semanticType.compare(rhs.semanticType) < 0) {
            return true;
        }
    }

    return false;
}

std::string NumericStateVariableId::toString() const {
    return (
        OUTPUT_STRING_BEGIN +
        name + OUTPUT_STRING_SEPARATOR +
        semanticType +
        OUTPUT_STRING_END
    );
}


// Constants definition
const std::string NumericStateVariableId::OUTPUT_STRING_BEGIN       = "(";
const std::string NumericStateVariableId::OUTPUT_STRING_SEPARATOR   = ", ";
const std::string NumericStateVariableId::OUTPUT_STRING_END         = ")";
