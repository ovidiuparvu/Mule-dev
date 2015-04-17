/******************************************************************************
/*{% for line in auto_generated_warning %}*/
 /*{{ line }}*/
/*{% endfor %}*/
 *****************************************************************************/

#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
/*{% for spatial_entity in spatial_entities %}*/
#include "multiscale/verification/spatial-temporal/model//*{{ spatial_entity.name|first_to_upper }}*/.hpp"
/*{% endfor %}*/
#include "multiscale/verification/spatial-temporal/model/ScaleAndSubsystem.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


// Initialize the provided trace
void initializeTrace(SpatialTemporalTrace &trace) {
    // Variables initialisation
    std::size_t nrOfTimePoints = 12;

    NumericStateVariableId aNumericStateVariableId("A", ScaleAndSubsystem::DEFAULT_VALUE);
    NumericStateVariableId bNumericStateVariableId("B", ScaleAndSubsystem::DEFAULT_VALUE);

    double aMinValue = 1;
    double aMaxValue = 0;

    double bConstantValue = 3;

    double /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MinValue = 1;
    double /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MaxValue = -1;

    // Initialize timepoints
    trace.clear();

    std::vector<TimePoint> timePoints;

    // Add timepoints containing the numeric state variable "B" to the collection of timepoints
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        timePoints.push_back(TimePoint(i));
        timePoints[i].addNumericStateVariable(bNumericStateVariableId, bConstantValue);
    }

    // Add a second numeric state variable to the collection of timepoints
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        if (i % 4 == 0) {
            timePoints[i].addNumericStateVariable(aNumericStateVariableId, aMinValue);
        } else {
            timePoints[i].addNumericStateVariable(aNumericStateVariableId, aMinValue + i);
        }
    }

    // Initialize the aMaxValue field
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        aMaxValue = std::max(aMaxValue, timePoints[i].getNumericStateVariableValue(aNumericStateVariableId));
    }

    // Add spatial entities to each timepoint
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {

        // Add /*{{ spatial_entities[0].name }}*/s to the timepoint
        for (std::size_t j = ((((i + 1) % 4) == 0) ? (i - 1) : 0); j <= i; j++) {
            std::shared_ptr<SpatialEntity> /*{{ spatial_entities[0].name }}*/ = std::make_shared</*{{ spatial_entities[0].name|first_to_upper }}*/>();

            /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MaxValue = std::max(/*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MaxValue, static_cast<double>((j * 2.4) + /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MinValue));

            /*{{ spatial_entities[0].name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measures[0].name|first_to_upper }}*/, static_cast<double>((j * 2.4) + /*{{ spatial_entities[0].name }}*/s/*{{ spatial_measures[0].name|first_to_upper }}*/MinValue));
        /*{% for spatial_measure in spatial_measures[1:] %}*/
            /*{{ spatial_entities[0].name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/, static_cast<double>(/*{{ spatial_measure.max_value }}*/ - /*{{ spatial_measure.min_value }}*/) / 2);
        /*{% endfor %}*/
            /*{{ spatial_entities[0].name }}*/->setScaleAndSubsystem(ScaleAndSubsystem::DEFAULT_VALUE);

            timePoints[i].addSpatialEntityAndType(/*{{ spatial_entities[0].name }}*/, SubsetSpecificType::/*{{ spatial_entities[0].name|first_to_upper }}*/s);
        }

    /*{% for spatial_entity in spatial_entities[1:] %}*/
        // Add /*{{ spatial_entity.name }}*/s to the timepoint
        for (std::size_t k = 0; k <= i; k++) {
                std::shared_ptr<SpatialEntity> /*{{ spatial_entity.name }}*/ = std::make_shared</*{{ spatial_entity.name|first_to_upper }}*/>();

                /*{{ spatial_entity.name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measures[0].name|first_to_upper }}*/, static_cast<double>((k * 0.3) + 0.7));
            /*{% for spatial_measure in spatial_measures[1:] %}*/
                /*{{ spatial_entity.name }}*/->setSpatialMeasureValue(SpatialMeasureType::/*{{ spatial_measure.name|first_to_upper }}*/, static_cast<double>(/*{{ spatial_measure.max_value }}*/ - /*{{ spatial_measure.min_value }}*/) / 3);
            /*{% endfor %}*/
                /*{{ spatial_entity.name }}*/->setScaleAndSubsystem(ScaleAndSubsystem::DEFAULT_VALUE);

                timePoints[i].addSpatialEntityAndType(/*{{ spatial_entity.name }}*/, SubsetSpecificType::/*{{ spatial_entity.name|first_to_upper }}*/s);
            }
    /*{% endfor %}*/
    }

    // Add all timepoints to the trace
    for (TimePoint &timePoint : timePoints) {
        trace.addTimePoint(timePoint);
    }
}

//  Main program
int main(int argc, char **argv) {
    std::string test;
    SpatialTemporalTrace trace;
    MultiscaleArchitectureGraph multiscaleArchitectureGraph;
    AbstractSyntaxTree result;

    initializeTrace(trace);

    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\tA multiscale multidimensional logic query parser and evaluator...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout
        << "Please enter a multiscale multidimensional logic query (or \"q\" to exit):" << std::endl
        << std::endl;


    while (getline(std::cin, test)) {
        if (test.compare("q") == 0) {
            break;
        }

        Parser parser(test);

        try {
            if (parser.parse(result)) {
                std::cout << "-----------------------------------------------------" << std::endl;
                std::cout << " Parsing succeeded"
                          << " and the AST evaluates to " 
                          << (result.evaluate(trace, multiscaleArchitectureGraph) ? "true" : "false")
                          << "!" << std::endl;
                std::cout << "-----------------------------------------------------" << std::endl << std::endl;
            } else {
                std::cout << "-----------------------------------------------------" << std::endl;
                std::cout << " Parsing failed!" << std::endl;
                std::cout << "-----------------------------------------------------" << std::endl << std::endl;
            }
        } catch(const std::exception &e) {
            ExceptionHandler::printDetailedErrorMessage(e);

            return EXEC_ERR_CODE;
        } catch(...) {
            std::cerr << "Exception of unknown type!" << std::endl;
        }
    }

    return -1;
}
