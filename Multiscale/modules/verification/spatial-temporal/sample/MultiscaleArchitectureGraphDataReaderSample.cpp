#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/MultiscaleException.hpp"
#include "multiscale/verification/spatial-temporal/model/MultiscaleArchitectureGraph.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace multiscale;
using namespace multiscale::verification;


// Print the vertices of the provided multiscale architecture graph
void printVerticesOfMultiscaleArchitectureGraph(const MultiscaleArchitectureGraph &multiscaleArchitectureGraph) {
    std::cout << "The vertices of the multiscale architecture graph: "
              << std::endl
              << std::endl;

    std::vector<std::pair<std::string, long>> vertices = multiscaleArchitectureGraph.getVertices();

    for (auto it = vertices.begin(); it != vertices.end(); it++) {
        std::cout << "Vertex name: "    << it->first
                  << ", Vertex index: " << it->second
                  << std::endl;
    }
}

// Print the edges of the provided multiscale architecture graph
void printEdgesOfMultiscaleArchitectureGraph(const MultiscaleArchitectureGraph &multiscaleArchitectureGraph) {
    std::cout << "The edges of the multiscale architecture graph: "
                  << std::endl
                  << std::endl;

    std::vector<std::pair<long, long>> edges = multiscaleArchitectureGraph.getEdges();

    for (auto it = edges.begin(); it != edges.end(); it++) {
        std::cout << "Edge tail endpoint vertex index: "    << it->first
                  << ", Edge head endpoint vertex index: "  << it->second
                  << std::endl;
    }
}


// Print the contents of the provided multiscale architecture graph
void printMultiscaleArchitectureGraphContents(const MultiscaleArchitectureGraph &multiscaleArchitectureGraph) {
    printVerticesOfMultiscaleArchitectureGraph(multiscaleArchitectureGraph);
    printEdgesOfMultiscaleArchitectureGraph(multiscaleArchitectureGraph);
}

// Read the multiscale architecture graph from the provided input file
void readMultiscaleArchitectureGraph(const std::string &inputFile,
                                     MultiscaleArchitectureGraph &multiscaleArchitectureGraph) {
    multiscaleArchitectureGraph.readFromFile(inputFile);
}

// Read the multiscale architecture graph from the provided input file
void readAndPrintMultiscaleArchitectureGraph(const std::string &inputFile) {
    try {
        MultiscaleArchitectureGraph multiscaleArchitectureGraph;

        readMultiscaleArchitectureGraph(inputFile, multiscaleArchitectureGraph);
        printMultiscaleArchitectureGraphContents(multiscaleArchitectureGraph);
    } catch (const MultiscaleException &ex) {
        ExceptionHandler::printDetailedErrorMessage(ex);
    }
}

// Main function
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: MultiscaleArchitectureGraphDataReaderSample <input-file>" << std::endl;

        return EXEC_ERR_CODE;
    }

    readAndPrintMultiscaleArchitectureGraph(std::string(argv[1]));

    return EXEC_SUCCESS_CODE;
}
