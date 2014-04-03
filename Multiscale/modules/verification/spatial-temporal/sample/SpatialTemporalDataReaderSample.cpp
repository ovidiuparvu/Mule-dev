#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataReader.hpp"

#include <iostream>
#include <string>

using namespace multiscale;
using namespace multiscale::verification;


// Print the regions corresponding to the given timepoint
void printRegions(TimePoint &timePoint) {
    for (auto it = timePoint.getRegionsBeginIterator(); it != timePoint.getRegionsEndIterator(); it++) {
        std::cout << "\tRegion" << std::endl;

        std::cout << "\t\tClusteredness: "      << (*it).getClusteredness() << std::endl;
        std::cout << "\t\tDensity: "            << (*it).getDensity() << std::endl;
        std::cout << "\t\tArea: "               << (*it).getArea() << std::endl;
        std::cout << "\t\tPerimeter: "          << (*it).getPerimeter() << std::endl;
        std::cout << "\t\tDistanceFromOrigin: " << (*it).getDistanceFromOrigin() << std::endl;
        std::cout << "\t\tAngle: "              << (*it).getAngle() << std::endl;
        std::cout << "\t\tTriangleMeasure: "    << (*it).getTriangleMeasure() << std::endl;
        std::cout << "\t\tRectangleMeasure: "   << (*it).getRectangleMeasure() << std::endl;
        std::cout << "\t\tCircleMeasure: "      << (*it).getCircleMeasure() << std::endl;
        std::cout << "\t\tCentroidX: "          << (*it).getCentroidX() << std::endl;
        std::cout << "\t\tCentroidY: "          << (*it).getCentroidY() << std::endl;
    }
}

// Print the clusters corresponding to the given timepoint
void printClusters(TimePoint &timePoint) {
    for (auto it = timePoint.getClustersBeginIterator(); it != timePoint.getClustersEndIterator(); it++) {
        std::cout << "\tCluster" << std::endl;

        std::cout << "\t\tClusteredness: "      << (*it).getClusteredness() << std::endl;
        std::cout << "\t\tDensity: "            << (*it).getDensity() << std::endl;
        std::cout << "\t\tArea: "               << (*it).getArea() << std::endl;
        std::cout << "\t\tPerimeter: "          << (*it).getPerimeter() << std::endl;
        std::cout << "\t\tDistanceFromOrigin: " << (*it).getDistanceFromOrigin() << std::endl;
        std::cout << "\t\tAngle: "              << (*it).getAngle() << std::endl;
        std::cout << "\t\tTriangleMeasure: "    << (*it).getTriangleMeasure() << std::endl;
        std::cout << "\t\tRectangleMeasure: "   << (*it).getRectangleMeasure() << std::endl;
        std::cout << "\t\tCircleMeasure: "      << (*it).getCircleMeasure() << std::endl;
        std::cout << "\t\tCentroidX: "          << (*it).getCentroidX() << std::endl;
        std::cout << "\t\tCentroidY: "          << (*it).getCentroidY() << std::endl;
    }
}

// Print the given timepoint
void printTimePoint(TimePoint &timePoint) {
    std::cout << "Timepoint " << timePoint.getValue() << std::endl;

    printClusters(timePoint);
    printRegions(timePoint);
}

// Print the given trace
void printTrace(SpatialTemporalTrace &trace) {
    std::cout << "---------------------------------------------------------" << std::endl;
    std::cout << "New spatial temporal trace" << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;

    for (unsigned int i = 0; i < trace.length(); i++) {
        TimePoint timePoint = trace.getTimePoint(i);

        printTimePoint(timePoint);
    }
}

// Read the valid xml files from the input folder
void readValidXmlFiles(SpatialTemporalDataReader &reader) {
    while (reader.hasNext()) {
        SpatialTemporalTrace trace = reader.getNextSpatialTemporalTrace();

        printTrace(trace);
    }
}

// Read valid xml files from folder
void readValidXmlFilesFromFolder(const std::string &path) {
    try {
        SpatialTemporalDataReader reader(path);

        readValidXmlFiles(reader);
    } catch (const MultiscaleException &ex) {
        ExceptionHandler::printErrorMessage(ex);
    }
}

// Main function
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: SpatialTemporalDataReader <input-folder>" << std::endl;

        return 1;
    }

    readValidXmlFilesFromFolder(std::string(argv[1]));

    return 0;
}
