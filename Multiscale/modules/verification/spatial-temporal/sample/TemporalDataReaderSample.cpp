#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/verification/spatial-temporal/data/TemporalDataReader.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


// Print the given timepoint
void printTimePoint(TimePoint &timePoint) {
    std::cout << "Timepoint " << timePoint.getValue() << std::endl;

    for (auto it = timePoint.getNumericStateVariablesBeginIterator();
         it != timePoint.getNumericStateVariablesEndIterator();
         it++
    ) {
        std::cout << "\t"
                  << "Numeric state variable (name, value): ("
                  << it->first.getName() << ", "
                  << it->second << ")" << std::endl;
    }
}

// Print the given trace
void printSpatialTemporalTrace(SpatialTemporalTrace &trace) {
    std::cout << "---------------------------------------------------------" << std::endl;
    std::cout << "New spatial temporal trace" << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;

    for (unsigned int i = 0; i < trace.length(); i++) {
        TimePoint timePoint = trace.getTimePoint(i);

        printTimePoint(timePoint);
    }
}

// Read the input file, construct a spatial temporal trace from it and print the trace
int readAndPrintInputFile(const std::string &filePath) {
    try {
        TemporalDataReader reader;

        SpatialTemporalTrace trace = reader.readTimeseriesFromFile(filePath);

        printSpatialTemporalTrace(trace);
    } catch (const MultiscaleException &ex) {
        ExceptionHandler::printDetailedErrorMessage(ex);

        return EXEC_ERR_CODE;
    }

    return EXEC_SUCCESS_CODE;
}

// Main function
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: TemporalDataReaderSample <input-file>" << std::endl;

        return EXEC_ERR_CODE;
    }

    return readAndPrintInputFile(std::string(argv[1]));
}
