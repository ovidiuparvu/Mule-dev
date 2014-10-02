#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataReader.hpp"

#include <iostream>
#include <string>

using namespace multiscale;
using namespace multiscale::verification;


// Print the spatial entities corresponding to the given timepoint and of the requested type
void printSpatialEntities(TimePoint &timePoint, const SubsetSpecificType &spatialEntityType) {
    for (auto it = timePoint.getSpatialEntitiesBeginIterator(spatialEntityType);
         it != timePoint.getSpatialEntitiesEndIterator(spatialEntityType); it++) {
        std::cout << "\t SpatialEntity" << std::endl;

        std::cout << (*(*it)).toString() << std::endl;
    }
}

// Print the given timepoint
void printTimePoint(TimePoint &timePoint) {
    std::cout << "Timepoint " << timePoint.getValue() << std::endl;

    for (std::size_t i = 0; i < NR_SUBSET_SPECIFIC_TYPES; i++) {
        std::cout << "Subset specific type " << i << ": " << std::endl;

        printSpatialEntities(timePoint, subsetspecific::computeSubsetSpecificType(i));
    }
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
        ExceptionHandler::printDetailedErrorMessage(ex);
    }
}

// Main function
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: SpatialTemporalDataReaderSample <input-folder>" << std::endl;

        return EXEC_ERR_CODE;
    }

    readValidXmlFilesFromFolder(std::string(argv[1]));

    return EXEC_SUCCESS_CODE;
}
