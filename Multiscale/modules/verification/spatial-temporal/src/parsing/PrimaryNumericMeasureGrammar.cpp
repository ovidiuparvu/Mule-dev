#include "multiscale/verification/spatial-temporal/attribute/SynthesizedAttribute.hpp"
#include "multiscale/verification/spatial-temporal/parsing/PrimaryNumericMeasureGrammarDefinition.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SpatialMeasureCollectionGrammar.hpp"

using namespace multiscale::verification;


// Define the iterator type
typedef std::string::const_iterator iteratorType;

// Explicitly instantiate the template for the given iterator type
template class PrimaryNumericMeasureGrammar<iteratorType>;
