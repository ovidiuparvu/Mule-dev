#include "multiscale/verification/spatial-temporal/parsing/ComparatorGrammarDefinition.hpp"

using namespace multiscale::verification;


// Define the iterator type
typedef std::string::const_iterator iteratorType;

// Explicitly instantiate the template for the given iterator type
template class ComparatorGrammar<iteratorType>;
