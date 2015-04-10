#include "multiscale/verification/spatial-temporal/parsing/ScaleAndSubsystemStringGrammarDefinition.hpp"

using namespace multiscale::verification;


// Define the iterator type
typedef std::string::const_iterator iteratorType;

// Explicitly instantiate the template for the given iterator type
template class ScaleAndSubsystemStringGrammar<iteratorType>;

// Constants
template <>
const std::string ScaleAndSubsystemStringGrammar<iteratorType>::SCALE_AND_SUBSYSTEM_STRING_PATTERN = "[0-9a-zA-Z]";

template <>
const std::string ScaleAndSubsystemStringGrammar<iteratorType>::SCALE_AND_SUBSYSTEM_LABEL = "scaleAndSubsystem";

