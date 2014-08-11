#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/model/Cluster.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


// Initialise the provided trace
void initialiseTrace(SpatialTemporalTrace &trace) {
    trace.clear();

    std::vector<TimePoint> timePoints;

    // Add 12 timepoints containing the numeric state variable "B" to the collection of timepoints
    for (int i = 0; i < 12; i++) {
        timePoints.push_back(TimePoint(i));
        timePoints[i].addNumericStateVariable("B", 3);
    }

    // Add a second numeric state variable to the collection of timepoints
    timePoints[0].addNumericStateVariable("A", 4);
    timePoints[1].addNumericStateVariable("A", 5);
    timePoints[2].addNumericStateVariable("A", 6);
    timePoints[3].addNumericStateVariable("A", 10);
    timePoints[4].addNumericStateVariable("A", 8);
    timePoints[5].addNumericStateVariable("A", 6);
    timePoints[6].addNumericStateVariable("A", 4);
    timePoints[7].addNumericStateVariable("A", 1);
    timePoints[8].addNumericStateVariable("A", 5);
    timePoints[9].addNumericStateVariable("A", 7);
    timePoints[10].addNumericStateVariable("A", 9);
    timePoints[11].addNumericStateVariable("A", 12);

    // Add spatial entities to each timepoint
    for (int i = 0; i < 12; i++) {

        // Add clusters to the timepoint
        for (int k = ((((i + 1) % 4) == 0) ? (i - 1) : 0); k <= i; k++) {
            std::shared_ptr<SpatialEntity> cluster = std::make_shared<Cluster>();

            cluster->setSpatialMeasureValue(SpatialMeasureType::Clusteredness, static_cast<double>((k * 2.4) + 1));
            cluster->setSpatialMeasureValue(SpatialMeasureType::Density, static_cast<double>((1E+37 - 0) / 2));
            cluster->setSpatialMeasureValue(SpatialMeasureType::Area, static_cast<double>((1E+37 - 0) / 2));
            cluster->setSpatialMeasureValue(SpatialMeasureType::Perimeter, static_cast<double>((1E+37 - 0) / 2));
            cluster->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin, static_cast<double>((1E+37 - 0) / 2));
            cluster->setSpatialMeasureValue(SpatialMeasureType::Angle, static_cast<double>((360 - 0) / 2));
            cluster->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure, static_cast<double>((1 - 0) / 2));
            cluster->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure, static_cast<double>((1 - 0) / 2));
            cluster->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure, static_cast<double>((1 - 0) / 2));
            cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidX, static_cast<double>((1E+37 - 0) / 2));
            cluster->setSpatialMeasureValue(SpatialMeasureType::CentroidY, static_cast<double>((1E+37 - 0) / 2));

            timePoints[i].addSpatialEntity(cluster, SubsetSpecificType::Clusters);
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
                          << " and the AST evaluates to " << (result.evaluate(trace) ? "true" : "false")
                          << "!" << std::endl;
                std::cout << "-----------------------------------------------------" << std::endl << std::endl;
            } else {
                std::cout << "-----------------------------------------------------" << std::endl;
                std::cout << " Parsing failed!" << std::endl;
                std::cout << "-----------------------------------------------------" << std::endl << std::endl;
            }
        } catch(const exception &e) {
            ExceptionHandler::printErrorMessage(e);

            return EXEC_ERR_CODE;
        } catch(...) {
            cerr << "Exception of unknown type!" << std::endl;
        }
    }

    return -1;
}
