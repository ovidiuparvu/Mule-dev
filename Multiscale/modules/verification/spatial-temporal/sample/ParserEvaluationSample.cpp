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

    double clustersClusterednessMinValue = 0;
    double clustersClusterednessMaxValue = 1;
    double clustersDensityMinValue = 0;
    double clustersDensityMaxValue = 1;
    double clustersAreaMinValue = 0;
    double clustersAreaMaxValue = 1E+6;
    double clustersPerimeterMinValue = 0;
    double clustersPerimeterMaxValue = 1E+6;
    double clustersDistanceFromOriginMinValue = 0;
    double clustersDistanceFromOriginMaxValue = 1E+6;
    double clustersAngleMinValue = 0;
    double clustersAngleMaxValue = 360;
    double clustersTriangleMeasureMinValue = 0;
    double clustersTriangleMeasureMaxValue = 1;
    double clustersRectangleMeasureMinValue = 0;
    double clustersRectangleMeasureMaxValue = 1;
    double clustersCircleMeasureMinValue = 0;
    double clustersCircleMeasureMaxValue = 1;
    double clustersCentroidXMinValue = 0;
    double clustersCentroidXMaxValue = 1E+6;
    double clustersCentroidYMinValue = 0;
    double clustersCentroidYMaxValue = 1E+6;
    double regionsClusterednessMinValue = 0;
    double regionsClusterednessMaxValue = 1;
    double regionsDensityMinValue = 0;
    double regionsDensityMaxValue = 1;
    double regionsAreaMinValue = 0;
    double regionsAreaMaxValue = 1E+6;
    double regionsPerimeterMinValue = 0;
    double regionsPerimeterMaxValue = 1E+6;
    double regionsDistanceFromOriginMinValue = 0;
    double regionsDistanceFromOriginMaxValue = 1E+6;
    double regionsAngleMinValue = 0;
    double regionsAngleMaxValue = 360;
    double regionsTriangleMeasureMinValue = 0;
    double regionsTriangleMeasureMaxValue = 1;
    double regionsRectangleMeasureMinValue = 0;
    double regionsRectangleMeasureMaxValue = 1;
    double regionsCircleMeasureMinValue = 0;
    double regionsCircleMeasureMaxValue = 1;
    double regionsCentroidXMinValue = 0;
    double regionsCentroidXMaxValue = 1E+6;
    double regionsCentroidYMinValue = 0;
    double regionsCentroidYMaxValue = 1E+6;

    // Initialize time points
    trace.clear();

    std::vector<TimePoint> timePoints;

    // Add time points containing the numeric state variable "B" to the collection of time points
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {
        timePoints.push_back(TimePoint(i));
        timePoints[i].addNumericStateVariable(bNumericStateVariableId, bConstantValue);
    }

    // Add a second numeric state variable to the collection of time points
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

    // Add spatial entities to each time point
    for (std::size_t i = 0; i < nrOfTimePoints; i++) {

        // Add clusters to the time point
        for (std::size_t j = ((((i + 1) % 4) == 0) ? (i - 1) : 0); j <= i; j++) {
            std::shared_ptr<SpatialEntity> cluster = std::make_shared<Cluster>();

            cluster->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, ((i != 0) ? (static_cast<double>(j) / static_cast<double>(nrOfTimePoints - 1)) : 0) * (clustersClusterednessMaxValue - clustersClusterednessMinValue) + clustersClusterednessMinValue);
            cluster->setSpatialMeasureValue(SpatialMeasureType::Density, (static_cast<double>(1) / static_cast<double>(2)) * (clustersDensityMaxValue - clustersDensityMinValue) + clustersDensityMinValue);
            cluster->setSpatialMeasureValue(SpatialMeasureType::Area, (static_cast<double>(1) / static_cast<double>(2)) * (clustersAreaMaxValue - clustersAreaMinValue) + clustersAreaMinValue);
            cluster->setSpatialMeasureValue(SpatialMeasureType::Perimeter, (static_cast<double>(1) / static_cast<double>(2)) * (clustersPerimeterMaxValue - clustersPerimeterMinValue) + clustersPerimeterMinValue);
            cluster->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, (static_cast<double>(1) / static_cast<double>(2)) * (clustersDistanceFromOriginMaxValue - clustersDistanceFromOriginMinValue) + clustersDistanceFromOriginMinValue);
            cluster->setSpatialMeasureValue(SpatialMeasureType::Angle, (static_cast<double>(1) / static_cast<double>(2)) * (clustersAngleMaxValue - clustersAngleMinValue) + clustersAngleMinValue);
            cluster->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, (static_cast<double>(1) / static_cast<double>(2)) * (clustersTriangleMeasureMaxValue - clustersTriangleMeasureMinValue) + clustersTriangleMeasureMinValue);
            cluster->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, (static_cast<double>(1) / static_cast<double>(2)) * (clustersRectangleMeasureMaxValue - clustersRectangleMeasureMinValue) + clustersRectangleMeasureMinValue);
            cluster->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, (static_cast<double>(1) / static_cast<double>(2)) * (clustersCircleMeasureMaxValue - clustersCircleMeasureMinValue) + clustersCircleMeasureMinValue);
            cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidX, (static_cast<double>(1) / static_cast<double>(2)) * (clustersCentroidXMaxValue - clustersCentroidXMinValue) + clustersCentroidXMinValue);
            cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidY, (static_cast<double>(1) / static_cast<double>(2)) * (clustersCentroidYMaxValue - clustersCentroidYMinValue) + clustersCentroidYMinValue);
            cluster->setScaleAndSubsystem(ScaleAndSubsystem::DEFAULT_VALUE);

            timePoints[i].addSpatialEntityAndType(cluster, SubsetSpecificType::Clusters);
        }

        // Add regions to the time point
        for (std::size_t k = 0; k <= i; k++) {
            std::shared_ptr<SpatialEntity> region = std::make_shared<Region>();

            region->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, ((i != 0) ? (static_cast<double>(k) / (static_cast<double>(nrOfTimePoints - 1) * 1.2)) : 0) * (regionsClusterednessMaxValue - regionsClusterednessMinValue) + regionsClusterednessMinValue);
            region->setSpatialMeasureValue(SpatialMeasureType::Density, (static_cast<double>(1) / static_cast<double>(3)) * (regionsDensityMaxValue - regionsDensityMinValue) + regionsDensityMinValue);
            region->setSpatialMeasureValue(SpatialMeasureType::Area, (static_cast<double>(1) / static_cast<double>(3)) * (regionsAreaMaxValue - regionsAreaMinValue) + regionsAreaMinValue);
            region->setSpatialMeasureValue(SpatialMeasureType::Perimeter, (static_cast<double>(1) / static_cast<double>(3)) * (regionsPerimeterMaxValue - regionsPerimeterMinValue) + regionsPerimeterMinValue);
            region->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, (static_cast<double>(1) / static_cast<double>(3)) * (regionsDistanceFromOriginMaxValue - regionsDistanceFromOriginMinValue) + regionsDistanceFromOriginMinValue);
            region->setSpatialMeasureValue(SpatialMeasureType::Angle, (static_cast<double>(1) / static_cast<double>(3)) * (regionsAngleMaxValue - regionsAngleMinValue) + regionsAngleMinValue);
            region->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, (static_cast<double>(1) / static_cast<double>(3)) * (regionsTriangleMeasureMaxValue - regionsTriangleMeasureMinValue) + regionsTriangleMeasureMinValue);
            region->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, (static_cast<double>(1) / static_cast<double>(3)) * (regionsRectangleMeasureMaxValue - regionsRectangleMeasureMinValue) + regionsRectangleMeasureMinValue);
            region->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, (static_cast<double>(1) / static_cast<double>(3)) * (regionsCircleMeasureMaxValue - regionsCircleMeasureMinValue) + regionsCircleMeasureMinValue);
            region->setSpatialMeasureValue(SpatialMeasureType::CentroidX, (static_cast<double>(1) / static_cast<double>(3)) * (regionsCentroidXMaxValue - regionsCentroidXMinValue) + regionsCentroidXMinValue);
            region->setSpatialMeasureValue(SpatialMeasureType::CentroidY, (static_cast<double>(1) / static_cast<double>(3)) * (regionsCentroidYMaxValue - regionsCentroidYMinValue) + regionsCentroidYMinValue);
            region->setScaleAndSubsystem(ScaleAndSubsystem::DEFAULT_VALUE);

            timePoints[i].addSpatialEntityAndType(region, SubsetSpecificType::Regions);
        }
    }

    // Add all time points to the trace
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