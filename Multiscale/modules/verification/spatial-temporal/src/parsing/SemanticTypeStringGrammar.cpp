#include "multiscale/verification/spatial-temporal/parsing/SemanticTypeStringGrammarDefinition.hpp"

using namespace multiscale::verification;


// Define the iterator type
typedef std::string::const_iterator iteratorType;

// Explicitly instantiate the template for the given iterator type
template class SemanticTypeStringGrammar<iteratorType>;

// Constants
template <>
const std::string SemanticTypeStringGrammar<iteratorType>::SEMANTIC_CRITERION_STRING_PATTERN = "[0-9a-zA-Z]";
