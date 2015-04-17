#include "multiscale/util/Filesystem.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/XmlValidator.hpp"
#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"
#include "multiscale/verification/spatial-temporal/model/ScaleAndSubsystem.hpp"
#include "multiscale/verification/spatial-temporal/model/MultiscaleArchitectureGraph.hpp"

#include <deque>

using namespace multiscale::verification;


MultiscaleArchitectureGraph::MultiscaleArchitectureGraph() {}

MultiscaleArchitectureGraph::~MultiscaleArchitectureGraph() {}

void
MultiscaleArchitectureGraph::readFromFile(const std::string &inputFilePath) {
    this->inputFilePath = inputFilePath;

    reset();
    read();
    validate();
}

void
MultiscaleArchitectureGraph::reset() {
    vertices.clear();
    predecessorIndices.clear();
    successorsIndices.clear();
}

void
MultiscaleArchitectureGraph::addRootVertex(const std::string &rootVertexScaleAndSubsystem) {
    if (isEmpty()) {
        addRootVertexToEmptyMultiscaleArchitectureGraph(rootVertexScaleAndSubsystem);
    } else {
        MS_throw(
            SpatialTemporalException,
            ERR_ADD_ROOT_VERTEX_NON_EMPTY_GRAPH
        );
    }
}

void
MultiscaleArchitectureGraph::addVertexAndCorrespondingEdge(const std::string &newVertexScaleAndSubsystem,
                                                           const std::string &predecessorVertexScaleAndSubsystem) {
    checkIfPredecessorVertexExists(
        predecessorVertexScaleAndSubsystem,
        newVertexScaleAndSubsystem
    );
    checkIfNewVertexDoesNotExist(
        predecessorVertexScaleAndSubsystem,
        newVertexScaleAndSubsystem
    );

    addVertexAndCorrespondingValidEdge(
        newVertexScaleAndSubsystem,
        predecessorVertexScaleAndSubsystem
    );
}

std::vector<std::pair<std::string, long>>
MultiscaleArchitectureGraph::getVertices() const {
    std::vector<std::pair<std::string, long>> verticesNamesAndIndices;

    for (const auto &vertex : vertices) {
        verticesNamesAndIndices.push_back(vertex);
    }

    return verticesNamesAndIndices;
}

std::vector<std::pair<long, long>>
MultiscaleArchitectureGraph::getEdges() const {
    std::vector<std::pair<long, long>> edges;

    std::size_t nrOfVertices = vertices.size();

    for (std::size_t i = 0; i < nrOfVertices; i++) {
        edges.push_back(
            std::pair<long, long>(
                static_cast<long>(i),
                predecessorIndices[i]
            )
        );
    }

    return edges;
}

bool
MultiscaleArchitectureGraph::existsScaleAndSubsystem(const std::string &scaleAndSubsystem) const {
    return (
        vertices.find(scaleAndSubsystem) != vertices.end()
    );
}

bool
MultiscaleArchitectureGraph::isScaleAndSubsystemSmallerThan(const std::string &lhsScaleAndSubsystem,
                                                            const std::string &rhsScaleAndSubsystem) const {
    checkIfComparedScaleAndSubsystemsAreEncodedByGraph(
        lhsScaleAndSubsystem,
        rhsScaleAndSubsystem
    );

    return (
        isValidScaleAndSubsystemSmallerThan(
            lhsScaleAndSubsystem,
            rhsScaleAndSubsystem
        )
    );
}

void
MultiscaleArchitectureGraph::read() {
    if (!Filesystem::isValidFilePath(inputFilePath, MULTISCALE_ARCHITECTURE_GRAPH_INPUT_FILE_EXTENSION)) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_INPUT_FILE_PATH_BEGIN +
            inputFilePath +
            ERR_INVALID_INPUT_FILE_PATH_END
        );
    }

    return readFromValidFile();
}

void
MultiscaleArchitectureGraph::readFromValidFile() {
    std::string xmlErrorMessage;

    if (!XmlValidator::isValidXmlFile(inputFilePath, MULTISCALE_ARCHITECTURE_GRAPH_XSD_PATH, xmlErrorMessage)) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_BEGIN +
            inputFilePath +
            ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_END +
            xmlErrorMessage
        );
    }

    return readFromValidXmlFile();
}

void
MultiscaleArchitectureGraph::readFromValidXmlFile() {
    pt::ptree propertyTree;

    read_xml(inputFilePath, propertyTree, pt::xml_parser::trim_whitespace);

    return constructFromPropertyTree(propertyTree);
}

void
MultiscaleArchitectureGraph::constructFromPropertyTree(const pt::ptree &propertyTree) {
    addVerticesFromPropertyTree(propertyTree);
    addEdgesFromPropertyTree(propertyTree);
}

void
MultiscaleArchitectureGraph::addVerticesFromPropertyTree(const pt::ptree &propertyTree) {
    pt::ptree vertices = propertyTree.get_child(LABEL_VERTICES);

    for (const auto &vertexPropertyTree : vertices) {
        addVertexFromPropertyTree(vertexPropertyTree.second);
    }
}

void
MultiscaleArchitectureGraph::addVertexFromPropertyTree(const pt::ptree &vertexPropertyTree) {
    std::string vertexScaleAndSubsystem = vertexPropertyTree.get<std::string>(LABEL_VERTEX_ID);

    // Add the vertex to the multiscale architecture graph
    addVertexByScaleAndSubsystem(vertexScaleAndSubsystem);
}

void
MultiscaleArchitectureGraph::addEdgesFromPropertyTree(const pt::ptree &propertyTree) {
    pt::ptree edges = propertyTree.get_child(LABEL_EDGES);

    for (const auto &edgePropertyTree : edges) {
        addEdgeFromPropertyTree(edgePropertyTree.second);
    }
}

void
MultiscaleArchitectureGraph::addEdgeFromPropertyTree(const pt::ptree &edgePropertyTree) {
    std::string predecessorVertexScaleAndSubsystem
        = edgePropertyTree.get<std::string>(LABEL_EDGE_BEGIN_VERTEX);
    std::string vertexScaleAndSubsystem
        = edgePropertyTree.get<std::string>(LABEL_EDGE_END_VERTEX);

    checkIfEdgeEndpointsAreDistinct(predecessorVertexScaleAndSubsystem, vertexScaleAndSubsystem);
    checkIfEdgeEndpointsAreEncodedByGraph(predecessorVertexScaleAndSubsystem, vertexScaleAndSubsystem);
    checkIfEdgeHeadEndpointHasIndegreeZero(predecessorVertexScaleAndSubsystem, vertexScaleAndSubsystem);

    addEdgeByEndpoints(predecessorVertexScaleAndSubsystem, vertexScaleAndSubsystem);
}

void
MultiscaleArchitectureGraph::validate() const {
    checkIfExistsUniqueRootVertex();
    checkIfValidIndegreeForNonRootVertices();
    checkIfExistsPathFromRootToOtherVertices();
}

void
MultiscaleArchitectureGraph::checkIfExistsUniqueRootVertex() const {
    if (!isUniqueRootVertex()) {
        MS_throw(
            SpatialTemporalException,
            ERR_ROOT_VERTEX_NOT_UNIQUE
        );
    }
}

bool
MultiscaleArchitectureGraph::isUniqueRootVertex() const {
    short nrOfRootVertices= 0;

    for (auto predecessorIndex : predecessorIndices) {
        if (predecessorIndex == NO_PREDECESSOR_INDEX) {
            nrOfRootVertices++;

            if (nrOfRootVertices > 1) {
                return false;
            }
        }
    }

    return (nrOfRootVertices == 1);
}

void
MultiscaleArchitectureGraph::checkIfValidIndegreeForNonRootVertices() const {
    // Do nothing because vertices which are non-root are ensured to have
    // a valid indegree (i.e. indegree = 1) since the predecessorIndices
    // collection allows storing only one predecessor for each vertex.
}

void
MultiscaleArchitectureGraph::checkIfExistsPathFromRootToOtherVertices() const {
    // Find the root vertex index
    long rootVertexIndex = computeRootVertexIndex();

    checkIfExistsPathFromRootToOtherVertices(rootVertexIndex);
}

void
MultiscaleArchitectureGraph::checkIfExistsPathFromRootToOtherVertices(long rootVertexIndex) const {
    std::vector<bool> visitedVertices(vertices.size(), false);

    // Initialize vertices deque
    std::deque<long> verticesDeque = {rootVertexIndex};

    // Visit all vertices reachable from the root vertex
    while (!verticesDeque.empty()) {
        // Obtain the index of the next vertex
        long vertexIndex = verticesDeque.back();

        // Remove the index from the deque
        verticesDeque.pop_back();

        // Mark the vertex as visited
        visitedVertices[vertexIndex] = true;

        // Add the successors of the vertex to the deque
        for (long successor : successorsIndices[vertexIndex]) {
            // There is no need to check if the vertex was already visited because
            // the maximum indegree for any vertex in the graph is one.
            verticesDeque.push_front(successor);
        }
    }

    checkIfExistUnvisitedVertices(rootVertexIndex, visitedVertices);
}

void
MultiscaleArchitectureGraph::checkIfExistUnvisitedVertices(long rootVertexIndex,
                                                           const std::vector<bool> &visitedVertices) const {
    std::size_t nrOfVertices = visitedVertices.size();

    for (std::size_t i = 0; i < nrOfVertices; i++) {
        if (visitedVertices[i] == false) {
            MS_throw(
                SpatialTemporalException,
                ERR_NO_PATH_FROM_ROOT_TO_VERTEX_BEGIN +
                computeVertexName(rootVertexIndex) +
                ERR_NO_PATH_FROM_ROOT_TO_VERTEX_MIDDLE +
                computeVertexName(i) +
                ERR_NO_PATH_FROM_ROOT_TO_VERTEX_END
            );
        }
    }
}

bool
MultiscaleArchitectureGraph::isEmpty() const {
    return (
        vertices.empty() &&
        predecessorIndices.empty() &&
        successorsIndices.empty()
    );
}

void
MultiscaleArchitectureGraph::addRootVertexToEmptyMultiscaleArchitectureGraph(const std::string
                                                                             &rootVertexScaleAndSubsystem) {
    addVertexByScaleAndSubsystem(rootVertexScaleAndSubsystem);

    // Set the root vertex predecessor index
    predecessorIndices.back() = ROOT_VERTEX_PREDECESSOR_INDEX;
}

void
MultiscaleArchitectureGraph::addVertexAndCorrespondingValidEdge(const std::string &vertexScaleAndSubsystem,
                                                                const std::string
                                                                &predecessorVertexScaleAndSubsystem) {
    addVertexByScaleAndSubsystem(vertexScaleAndSubsystem);

    // Compute the predecessor vertex index
    long predecessorVertexIndex = vertices[predecessorVertexScaleAndSubsystem];

    // Set the predecessor of the new vertex
    predecessorIndices.back() = predecessorVertexIndex;

    // Set the successor of the predecessor vertex
    successorsIndices[predecessorVertexIndex].push_back(vertices[vertexScaleAndSubsystem]);
}

void
MultiscaleArchitectureGraph::addVertexByScaleAndSubsystem(const std::string &vertexScaleAndSubsystem) {
    long nrOfVertices = static_cast<long>(vertices.size());

    // The index corresponding to the new vertex is |vertices|
    vertices[vertexScaleAndSubsystem] = (nrOfVertices);

    // Add an element to the predecessors collection corresponding to the new vertex
    predecessorIndices.push_back(NO_PREDECESSOR_INDEX);

    // Add an element to the successors collection corresponding to the new vertex
    successorsIndices.push_back(std::vector<long>());
}

void
MultiscaleArchitectureGraph::addEdgeByEndpoints(const std::string &edgeTailEndpoint,
                                                const std::string &edgeHeadEndpoint) {
    long edgeTailEndpointIndex = vertices[edgeTailEndpoint];
    long edgeHeadEndpointIndex = vertices[edgeHeadEndpoint];

    // Update the predecessor relationship
    predecessorIndices[edgeHeadEndpointIndex] = edgeTailEndpointIndex;

    // Update the successor relationship
    (successorsIndices[edgeTailEndpointIndex]).push_back(edgeHeadEndpointIndex);
}

void
MultiscaleArchitectureGraph::checkIfPredecessorVertexExists(const std::string &predecessorVertexScaleAndSubsystem,
                                                            const std::string &newVertexScaleAndSubsystem) const {
    if (!existsScaleAndSubsystem(predecessorVertexScaleAndSubsystem)) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_BEGIN +
            predecessorVertexScaleAndSubsystem +
            ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_MIDDLE1 +
            newVertexScaleAndSubsystem +
            ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_MIDDLE2 +
            predecessorVertexScaleAndSubsystem +
            ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_END
        );
    }
}

void
MultiscaleArchitectureGraph::checkIfNewVertexDoesNotExist(const std::string &predecessorVertexScaleAndSubsystem,
                                                          const std::string &newVertexScaleAndSubsystem) const {
    if (existsScaleAndSubsystem(newVertexScaleAndSubsystem)) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_BEGIN +
            predecessorVertexScaleAndSubsystem +
            ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_MIDDLE1 +
            newVertexScaleAndSubsystem +
            ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_MIDDLE2 +
            newVertexScaleAndSubsystem +
            ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_END
        );
    }
}

void
MultiscaleArchitectureGraph::checkIfEdgeEndpointsAreDistinct(const std::string &firstEdgeEndpoint,
                                                             const std::string &secondEdgeEndpoint) const {
    if (firstEdgeEndpoint.compare(secondEdgeEndpoint) == 0) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_EDGE_IDENTICAL_ENDPOINTS_BEGIN +
            firstEdgeEndpoint +
            ERR_INVALID_EDGE_IDENTICAL_ENDPOINTS_MIDDLE +
            secondEdgeEndpoint +
            ERR_INVALID_EDGE_IDENTICAL_ENDPOINTS_END
        );
    }
}

void
MultiscaleArchitectureGraph::checkIfEdgeEndpointsAreEncodedByGraph(const std::string &firstEdgeEndpoint,
                                                                   const std::string &secondEdgeEndpoint) const {
    if (!existsScaleAndSubsystem(firstEdgeEndpoint)) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_BEGIN +
            firstEdgeEndpoint +
            ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE1 +
            secondEdgeEndpoint +
            ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE2 +
            firstEdgeEndpoint +
            ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_END
        );
    } else if (!existsScaleAndSubsystem(secondEdgeEndpoint)) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_BEGIN +
            firstEdgeEndpoint +
            ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE1 +
            secondEdgeEndpoint +
            ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE2 +
            secondEdgeEndpoint +
            ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_END
        );
    }
}

void
MultiscaleArchitectureGraph::checkIfEdgeHeadEndpointHasIndegreeZero(const std::string &edgeTailEndpoint,
                                                                    const std::string &edgeHeadEndpoint) const {
    // The vertex indices are always greater than 0
    std::size_t edgeHeadEndpointVertexIndex = static_cast<std::size_t>(vertices.at(edgeHeadEndpoint));

    if (predecessorIndices.at(edgeHeadEndpointVertexIndex) != NO_PREDECESSOR_INDEX) {
        MS_throw(
            SpatialTemporalException,
            ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_BEGIN +
            edgeTailEndpoint +
            ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_MIDDLE1 +
            edgeHeadEndpoint +
            ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_MIDDLE2 +
            edgeHeadEndpoint +
            ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_END
        );
    }
}

void
MultiscaleArchitectureGraph::checkIfComparedScaleAndSubsystemsAreEncodedByGraph(const std::string
                                                                                &firstScaleAndSubsystem,
                                                                                const std::string
                                                                                &secondScaleAndSubsystem) const {
    if (!existsScaleAndSubsystem(firstScaleAndSubsystem)) {
        MS_throw(
            SpatialTemporalException,
            ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_BEGIN +
            firstScaleAndSubsystem +
            ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_MIDDLE1 +
            secondScaleAndSubsystem +
            ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_MIDDLE2 +
            firstScaleAndSubsystem +
            ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_END
        );
    } else if (!existsScaleAndSubsystem(secondScaleAndSubsystem)) {
        MS_throw(
            SpatialTemporalException,
            ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_BEGIN +
            firstScaleAndSubsystem +
            ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_MIDDLE1 +
            secondScaleAndSubsystem +
            ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_MIDDLE2 +
            secondScaleAndSubsystem +
            ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_END
        );
    }
}

bool
MultiscaleArchitectureGraph::isValidScaleAndSubsystemSmallerThan(const std::string &lhsScaleAndSubsystem,
                                                                 const std::string &rhsScaleAndSubsystem) const {
    long lhsScaleAndSubsystemIndex = vertices.at(lhsScaleAndSubsystem);
    long rhsScaleAndSubsystemIndex = vertices.at(rhsScaleAndSubsystem);

    // Check if one of the lhs scale and subsystem's predecessors if the rhs scale and subsystem
    while (lhsScaleAndSubsystemIndex != ROOT_VERTEX_PREDECESSOR_INDEX) {
        lhsScaleAndSubsystemIndex = predecessorIndices[lhsScaleAndSubsystemIndex];

        if (lhsScaleAndSubsystemIndex == rhsScaleAndSubsystemIndex) {
            return true;
        }
    }

    return false;
}

long
MultiscaleArchitectureGraph::computeRootVertexIndex() const {
    std::size_t nrOfVertices = vertices.size();

    for (std::size_t i = 0; i < nrOfVertices; i++) {
        if (predecessorIndices[i] == ROOT_VERTEX_PREDECESSOR_INDEX) {
            return i;
        }
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return 0;
}

std::string
MultiscaleArchitectureGraph::computeVertexName(long vertexIndex) const {
    for (auto it = vertices.begin(); it != vertices.end(); it++) {
        if (it->second == vertexIndex) {
            return (it->first);
        }
    }

    // Line added to avoid "control reaches end of non-void function" warnings
    return "";
}


// Constants
const long MultiscaleArchitectureGraph::NO_PREDECESSOR_INDEX            = -1;
const long MultiscaleArchitectureGraph::ROOT_VERTEX_PREDECESSOR_INDEX   = NO_PREDECESSOR_INDEX;

const std::string MultiscaleArchitectureGraph::LABEL_MULTISCALE_ARCHITECTURE_GRAPH  = "multiscaleArchitectureGraph";
const std::string MultiscaleArchitectureGraph::LABEL_VERTICES                       = LABEL_MULTISCALE_ARCHITECTURE_GRAPH + ".vertices";
const std::string MultiscaleArchitectureGraph::LABEL_EDGES                          = LABEL_MULTISCALE_ARCHITECTURE_GRAPH + ".edges";

const std::string MultiscaleArchitectureGraph::LABEL_VERTEX     = "vertex";
const std::string MultiscaleArchitectureGraph::LABEL_VERTEX_ID  = "<xmlattr>.id";

const std::string MultiscaleArchitectureGraph::LABEL_EDGE               = "edge";
const std::string MultiscaleArchitectureGraph::LABEL_EDGE_BEGIN_VERTEX  = "<xmlattr>.beginVertex";
const std::string MultiscaleArchitectureGraph::LABEL_EDGE_END_VERTEX    = "<xmlattr>.endVertex";

const std::string MultiscaleArchitectureGraph::MULTISCALE_ARCHITECTURE_GRAPH_INPUT_FILE_EXTENSION = ".xml";
const std::string MultiscaleArchitectureGraph::MULTISCALE_ARCHITECTURE_GRAPH_XSD_PATH             = "/usr/local/share/mule/config/verification/spatial-temporal/schema/multiscale_architecture_graph.xsd";

const std::string MultiscaleArchitectureGraph::ERR_INVALID_INPUT_FILE_PATH_BEGIN   = "The provided input file path (";
const std::string MultiscaleArchitectureGraph::ERR_INVALID_INPUT_FILE_PATH_END     = ") does not point to a regular file with the required extension (" + MULTISCALE_ARCHITECTURE_GRAPH_INPUT_FILE_EXTENSION + "). Please change.";

const std::string MultiscaleArchitectureGraph::ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_BEGIN    = "The provided xml input file (";
const std::string MultiscaleArchitectureGraph::ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_END      = ") is invalid relative to the xsd file (" + MULTISCALE_ARCHITECTURE_GRAPH_XSD_PATH + "). ";

const std::string MultiscaleArchitectureGraph::ERR_ADD_ROOT_VERTEX_NON_EMPTY_GRAPH  = "It is not possible to add a root vertex to a non-empty multiscale architecture graph. Please clear the contents of the graph before adding a root vertex to it.";

const std::string MultiscaleArchitectureGraph::ERR_ROOT_VERTEX_NOT_UNIQUE  = "The multiscale architecture graph is invalid because it does not contain a unique root vertex. Please change.";

const std::string MultiscaleArchitectureGraph::ERR_NO_ROOT_VERTEX   = "The multiscale architecture graph should but does not contain any root vertices. Please change.";

const std::string MultiscaleArchitectureGraph::ERR_NO_PATH_FROM_ROOT_TO_VERTEX_BEGIN    = "The multiscale architecture graph is invalid because there exists no path from the root vertex ";
const std::string MultiscaleArchitectureGraph::ERR_NO_PATH_FROM_ROOT_TO_VERTEX_MIDDLE   = " to the vertex ";
const std::string MultiscaleArchitectureGraph::ERR_NO_PATH_FROM_ROOT_TO_VERTEX_END      = ". Please change.";

const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_BEGIN     = "The edge (";
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_MIDDLE1   = ", ";
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_MIDDLE2   = ")";

const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_BEGIN     = ERR_INVALID_EDGE_BEGIN;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_MIDDLE1   = ERR_INVALID_EDGE_MIDDLE1;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_MIDDLE2   = ERR_INVALID_EDGE_MIDDLE2 + " cannot be added to the multiscale architecture graph because the edge tail endpoint \"";
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_END       = "\" is not a vertex of the graph. Please change.";

const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_BEGIN     = ERR_INVALID_EDGE_BEGIN;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_MIDDLE1   = ERR_INVALID_EDGE_MIDDLE1;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_MIDDLE2   = ERR_INVALID_EDGE_MIDDLE2 + " cannot be added to the multiscale architecture graph because the edge head endpoint \"";
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_END       = "\" is not a new but an existing vertex of the graph. Please change.";

const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_IDENTICAL_ENDPOINTS_BEGIN   = ERR_INVALID_EDGE_BEGIN;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_IDENTICAL_ENDPOINTS_MIDDLE  = ERR_INVALID_EDGE_MIDDLE1;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_IDENTICAL_ENDPOINTS_END     = ERR_INVALID_EDGE_MIDDLE2 + " cannot be added to the multiscale architecture graph because the edge endpoints are identical and they should be distinct. Please change.";

const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_BEGIN   = ERR_INVALID_EDGE_BEGIN;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE1 = ERR_INVALID_EDGE_MIDDLE1;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE2 = ERR_INVALID_EDGE_MIDDLE2 + " cannot be added to the multiscale architecture graph because the edge tail endpoint \"";
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_END     = "\" is not a vertex of the graph. Please change.";

const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_BEGIN   = ERR_INVALID_EDGE_BEGIN;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE1 = ERR_INVALID_EDGE_MIDDLE1;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE2 = ERR_INVALID_EDGE_MIDDLE2 + " cannot be added to the multiscale architecture graph because the edge head endpoint ";
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_END     = ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_END;

const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_BEGIN   = ERR_INVALID_EDGE_BEGIN;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_MIDDLE1 = ERR_INVALID_EDGE_MIDDLE1;
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_MIDDLE2 = ERR_INVALID_EDGE_MIDDLE2 + " cannot be added to the multiscale architecture graph because the edge head endpoint \"";
const std::string MultiscaleArchitectureGraph::ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_END     = "\" has an indegree different from zero. Please change.";

const std::string MultiscaleArchitectureGraph::ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_BEGIN      = "The provided scales and subsystems \"";
const std::string MultiscaleArchitectureGraph::ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_MIDDLE1    = "\" and \"";
const std::string MultiscaleArchitectureGraph::ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_MIDDLE2    = "\" cannot be compared because the scale and subsystem \"";
const std::string MultiscaleArchitectureGraph::ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_END        = "\" is not encoded by the multiscale architecture graph. Please change.";
