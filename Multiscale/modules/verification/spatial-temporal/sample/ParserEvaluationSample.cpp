/******************************************************************************
 *
 * WARNING! AUTO-GENERATED FILE.
 *
 * PLEASE DO NOT UPDATE THIS FILE MANUALLY. 
 * USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.
 *
 *****************************************************************************/

#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/Cluster.hpp"
#include "multiscale/verification/spatial-temporal/model/Region.hpp"
#include "multiscale/verification/spatial-temporal/model/SemanticType.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


// Initialise the provided trace
void initialiseTrace(SpatialTemporalTrace &trace) {
    // Variables initialisation
    std::size_t nrOfTimePoints = 12;

    NumericStateVariableId aNumericStateVariableId("A", 0);
    NumericStateVariableId bNumericStateVariableId("B", 0);

    double aMinValue = 1;
    double aMaxValue = 0;

    double bConstantValue = 3;

    double clustersClusterednessMinValue = 1;
    double clustersClusterednessMaxValue = -1;

    // Initialise timepoints
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

    // Initialise the aMaxValue field
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        aMaxValue = std::max(aMaxValue, timePoints[i].getNumericStateVariableValue(aNumericStateVariableId));
    }

    // Add spatial entities to each timepoint
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {

        // Add clusters to the timepoint
        for (std::size_t j = ((((i + 1) % 4) == 0) ? (i - 1) : 0); j <= i; j++) {
            std::shared_ptr<SpatialEntity> cluster = std::make_shared<Cluster>();

            clustersClusterednessMaxValue = std::max(clustersClusterednessMaxValue, static_cast<double>((j * 2.4) + clustersClusterednessMinValue));

            cluster->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, static_cast<double>((j * 2.4) + clustersClusterednessMinValue));
            cluster->setSpatialMeasureValue(SpatialMeasureType::Density, static_cast<double>(1E+37 - 0) / 2);
            cluster->setSpatialMeasureValue(SpatialMeasureType::Area, static_cast<double>(1E+37 - 0) / 2);
            cluster->setSpatialMeasureValue(SpatialMeasureType::Perimeter, static_cast<double>(1E+37 - 0) / 2);
            cluster->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, static_cast<double>(1E+37 - 0) / 2);
            cluster->setSpatialMeasureValue(SpatialMeasureType::Angle, static_cast<double>(360 - 0) / 2);
            cluster->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, static_cast<double>(1 - 0) / 2);
            cluster->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, static_cast<double>(1 - 0) / 2);
            cluster->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, static_cast<double>(1 - 0) / 2);
            cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidX, static_cast<double>(1E+37 - 0) / 2);
            cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidY, static_cast<double>(1E+37 - 0) / 2);
            cluster->setSemanticType(SemanticType::DEFAULT_VALUE);

            timePoints[i].addSpatialEntityAndType(cluster, SubsetSpecificType::Clusters);
        }

        // Add regions to the timepoint
        for (std::size_t k = 0; k <= i; k++) {
                std::shared_ptr<SpatialEntity> region = std::make_shared<Region>();

                region->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, static_cast<double>((k * 0.3) + 0.7));
                region->setSpatialMeasureValue(SpatialMeasureType::Density, static_cast<double>(1E+37 - 0) / 3);
                region->setSpatialMeasureValue(SpatialMeasureType::Area, static_cast<double>(1E+37 - 0) / 3);
                region->setSpatialMeasureValue(SpatialMeasureType::Perimeter, static_cast<double>(1E+37 - 0) / 3);
                region->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, static_cast<double>(1E+37 - 0) / 3);
                region->setSpatialMeasureValue(SpatialMeasureType::Angle, static_cast<double>(360 - 0) / 3);
                region->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, static_cast<double>(1 - 0) / 3);
                region->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, static_cast<double>(1 - 0) / 3);
                region->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, static_cast<double>(1 - 0) / 3);
                region->setSpatialMeasureValue(SpatialMeasureType::CentroidX, static_cast<double>(1E+37 - 0) / 3);
                region->setSpatialMeasureValue(SpatialMeasureType::CentroidY, static_cast<double>(1E+37 - 0) / 3);
                region->setSemanticType(SemanticType::DEFAULT_VALUE);

                timePoints[i].addSpatialEntityAndType(region, SubsetSpecificType::Regions);
            }
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
    TypeSemanticsTable typeSemanticsTable;
    AbstractSyntaxTree result;

    initialiseTrace(trace);

    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\tA multidimensional multiscale logical query parser and evaluator...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout
        << "Please enter a multidimensional multiscale logical query (or \"q\" to exit):" << std::endl
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
                          << (result.evaluate(trace, typeSemanticsTable) ? "true" : "false")
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