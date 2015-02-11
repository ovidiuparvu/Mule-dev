#include "multiscale/verification/spatial-temporal/parsing/ChangeMeasureGrammarDefinition.hpp"

using namespace multiscale::verification;


// Define the iterator type
typedef std::string::const_iterator iteratorType;

// Explicitly instantiate the template for the given iterator type
template class ChangeMeasureGrammar<iteratorType>;
