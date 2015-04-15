#ifndef MULTISCALEARCHITECTUREGRAPH_HPP
#define MULTISCALEARCHITECTUREGRAPH_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <string>
#include <unordered_map>

namespace pt = boost::property_tree;


namespace multiscale {

    namespace verification {

        //! Class for defining a multiscale architecture graph
        /*! The multiscale architecture graph encodes the hierarchical organization of
         *  the scales and subsystems and is represented as a rooted directed tree.
         */
        class MultiscaleArchitectureGraph {

            private:

                std::string
                    inputFilePath;                  /*!< The path to the input file */

                std::unordered_map<std::string, long>
                    vertices;                       /*!< The associative container storing the scale and subsystem
                                                         of each vertex and its corresponding index (0-based indexing).

                                                         TODO: In case the data structure for this field is changed
                                                         update the description of the predecessorIndices field
                                                         accordingly. */

                std::vector<long>
                    predecessorIndices;             /*!< The collection storing the index of the predecessor for each
                                                         vertex. The index of each vertex is stored in the
                                                         associative container called "vertices". In case a vertex
                                                         does not have a predecessor (i.e. it is the root) its
                                                         predecessor index is set to NO_PREDECESSOR_INDEX. */
                std::vector<std::vector<long>>
                    successorsIndices;              /*!< The collection storing the index of the successors for each
                                                         vertex. The index of each vertex is stored in the
                                                         associative container called "vertices". */

            public:

                MultiscaleArchitectureGraph();
                ~MultiscaleArchitectureGraph();

                //! Read the multiscale architecture graph from the provided input file
                /*! Warning: The contents of the existing multiscale architecture graph will be overwritten by the
                 *           contents stored in the provided input file.
                 *
                 * \param inputFilePath The path to the input file
                 */
                void readFromFile(const std::string &inputFilePath);

                //! Reset the multiscale architecture graph such that it does not contain any vertices or edges
                void reset();

                //! Add the root vertex to the multiscale architecture graph using the provided scale and subsystem
                /*! Precondition: The provided scale and subsystem is in a valid format.
                 *
                 * \param rootVertexScaleAndSubsystem   The scale and subsystem of the root vertex
                 */
                void addRootVertex(const std::string &rootVertexScaleAndSubsystem);

                //! Add a vertex and its corresponding incoming edge to the graph
                /*! The method requires specifying both the vertex and its predecessor because this
                 *  will ensure that the resulting graph is connected and acyclic.
                 *
                 *  The intuitive proof for the (weakly) connected property is that all vertices except
                 *  the root will have indegree 1 and there will exist a directed path from the root to
                 *  them.
                 *
                 *  The intuitive proof for the acyclic property is that the number of edges in
                 *  the graph will be always |vertices| - 1, where |vertices| represents the number of
                 *  elements in the set vertices.
                 *
                 * \param newVertexScaleAndSubsystem            The scale and subsystem of the new vertex to be added
                 *                                              to the multiscale architecture graph
                 * \param predecessorVertexScaleAndSubsystem    The scale and subsystem of the existing vertex which
                 *                                              will be the predecessor/parent of the new vertex
                 */
                void addVertexAndCorrespondingEdge(const std::string &newVertexScaleAndSubsystem,
                                                   const std::string &predecessorVertexScaleAndSubsystem);

                //! Return a copy of the vertices scales and subsystems, and indices
                std::vector<std::pair<std::string, long>> getVertices() const;

                //! Return a copy of the edges where the edges' endpoints are specified by vertex indices
                std::vector<std::pair<long, long>> getEdges() const;

                //! Check if the given scale and subsystem exists in the multiscale architecture graph
                /*! Precondition: The provided scale and subsystem is in a valid format.
                 *
                 * \param scaleAndSubsystem The provided scale and subsystem
                 */
                bool existsScaleAndSubsystem(const std::string &scaleAndSubsystem) const;

                //! Check if the left hand side scale and subsystem < right hand side scale and subsystem
                /*! To determine the truth value the partial order imposed by the rooted directed tree representation
                 *  is considered i.e. v1 < v2 if and only if the path from the root to v1 passes through v2.
                 *
                 * \param lhsScaleAndSubsystem  The left hand side scale and subsystem
                 * \param rhsScaleAndSubsystem  The right hand side scale and subsystem
                 */
                bool isScaleAndSubsystemSmallerThan(const std::string &lhsScaleAndSubsystem,
                                                    const std::string &rhsScaleAndSubsystem) const;

            private:

                //! Read the multiscale architecture graph from the provided input file
                void read();

                //! Read the multiscale architecture graph from the provided valid input file
                /*!
                 * Precondition: The provided input file path points to a regular file with the correct extension.
                 */
                void readFromValidFile();

                //! Read the multiscale architecture graph from the provided valid xml input file
                /*!
                 * Precondition: The provided input file path points to a valid xml file (relative to xsd).
                 */
                void readFromValidXmlFile();

                //! Construct the multiscale architecture graph from the provided property tree
                /*!
                 * \param propertyTree  The property tree corresponding to the xml input file
                 */
                void constructFromPropertyTree(const pt::ptree &propertyTree);

                //! Add vertices to the multiscale architecture graph
                /*!
                 * \param propertyTree  The property tree corresponding to the xml input file
                 */
                void addVerticesFromPropertyTree(const pt::ptree &propertyTree);

                //! Add a vertex to the multiscale architecture graph corresponding to the given property tree
                /*!
                 * \param vertexPropertyTree    The property tree corresponding to a vertex
                 */
                void addVertexFromPropertyTree(const pt::ptree &vertexPropertyTree);

                //! Add the edges to the multiscale architecture graph
                /*!
                 * \param propertyTree  The property tree corresponding to the xml input file
                 */
                void addEdgesFromPropertyTree(const pt::ptree &propertyTree);

                //! Add an edge to the multiscale architecture graph corresponding to the given property tree
                /*!
                 * \param edgePropertyTree  The property tree corresponding to an edge
                 */
                void addEdgeFromPropertyTree(const pt::ptree &edgePropertyTree);

                //! Check if the multiscale architecture graph is a rooted directed tree
                void validate() const;

                //! Check if the multiscale architecture graph contains a unique root vertex and throw exception if not
                void checkIfExistsUniqueRootVertex() const;

                //! Check if the multiscale architecture graph contains a unique root vertex
                bool isUniqueRootVertex() const;

                //! Check if all vertices except the root have indegree 1 and throw exception if not
                void checkIfValidIndegreeForNonRootVertices() const;

                //! Check if there is a path from the root to all other vertices and throw exception if not
                void checkIfExistsPathFromRootToOtherVertices() const;

                //! Check if there is a path from the root to all other vertices and throw exception if not
                /*! Using the successor relation we will check if all vertices are (in)directly connected
                 *  to the root vertex. If not an exception is thrown.
                 *
                 * \param rootVertexIndex   Index corresponding to the root vertex
                 */
                void checkIfExistsPathFromRootToOtherVertices(long rootVertexIndex) const;

                //! Check if there exist unvisited vertices in the given collection and throw an exception if yes
                /*!
                 * \param rootVertexIndex   Index corresponding to the root vertex
                 * \param visitedVertices   Collection recording which vertices can be visited when starting
                 *                          from the root
                 */
                void checkIfExistUnvisitedVertices(long rootVertexIndex,
                                                   const std::vector<bool> &visitedVertices) const;

                //! Check if the multiscale architecture graph does not contain vertices and edges
                bool isEmpty() const;

                //! Add the root vertex to the empty multiscale architecture graph using the given scale and subsystem
                /*! Precondition: The number of vertices and edges in the graph is 0.
                 *
                 * \param rootVertexScaleAndSubsystem   The scale and subsystem of the root vertex
                 */
                void addRootVertexToEmptyMultiscaleArchitectureGraph(const std::string &rootVertexScaleAndSubsystem);

                //! Add a vertex and its corresponding valid incoming edge to the graph
                /*!
                 * \param vertexScaleAndSubsystem               The scale and subsystem of the new vertex to be added
                 *                                              to the multiscale architecture graph
                 * \param predecessorVertexScaleAndSubsystem    The scale and subsystem of the existing vertex which
                 *                                              will be the predecessor/parent of the new vertex
                 */
                void addVertexAndCorrespondingValidEdge(const std::string &vertexScaleAndSubsystem,
                                                        const std::string &predecessorVertexScaleAndSubsystem);

                //! Add a vertex with the given scale and subsystem to the graph
                /*! Precondition: The provided scale and subsystem is in a valid format.
                 *
                 * \param vertexScaleAndSubsystem   The scale and subsystem of the vertex
                 */
                void addVertexByScaleAndSubsystem(const std::string &vertexScaleAndSubsystem);

                //! Add an edge to the graph considering the given endpoints (i.e. scales and subsystems)
                /*! Precondition: The edge is valid and can be added to the graph.
                 *
                 * \param edgeTailEndpoint  The edge tail end point identified by its corresponding scale and
                 *                          subsystem
                 * \param edgeHeadEndpoint  The edge head end point identified by its corresponding scale and
                 *                          subsystem
                 */
                void addEdgeByEndpoints(const std::string &edgeTailEndpoint,
                                        const std::string &edgeHeadEndpoint);

                //! Check if predecessor vertex belongs to graph and throw exception if not
                /*!
                 * \param predecessorVertexScaleAndSubsystem    The scale and subsystem corresponding to the
                 *                                              predecessor vertex
                 * \param newVertexScaleAndSubsystem            The scale and subsystem corresponding to the
                 *                                              new vertex
                 */
                void checkIfPredecessorVertexExists(const std::string &predecessorVertexScaleAndSubsystem,
                                                    const std::string &newVertexScaleAndSubsystem) const;

                //! Check if new vertex does not belong to graph and throw exception if it does
                /*!
                 * \param predecessorVertexScaleAndSubsystem    The scale and subsystem corresponding to the
                 *                                              predecessor vertex
                 * \param newVertexScaleAndSubsystem            The scale and subsystem corresponding to the
                 *                                              new vertex
                 */
                void checkIfNewVertexDoesNotExist(const std::string &predecessorVertexScaleAndSubsystem,
                                                  const std::string &newVertexScaleAndSubsystem) const;

                //! Check if the provided edge endpoints are distinct and throw exception if not
                /*!
                 * \param firstEdgeEndpoint     The first considered edge endpoint (i.e. scale and subsystem)
                 * \param secondEdgeEndpoint    The second considered edge endpoint (i.e. scale and subsystem)
                 */
                void checkIfEdgeEndpointsAreDistinct(const std::string &firstEdgeEndpoint,
                                                     const std::string &secondEdgeEndpoint) const;

                //! Check if the provided edge endpoints are encoded by the graph and throw exception if not
                /*!
                 * \param firstEdgeEndpoint     The first considered edge endpoint (i.e. scale and subsystem)
                 * \param secondEdgeEndpoint    The second considered edge endpoint (i.e. scale and subsystem)
                 */
                void checkIfEdgeEndpointsAreEncodedByGraph(const std::string &firstEdgeEndpoint,
                                                           const std::string &secondEdgeEndpoint) const;

                //! Check if the provided edge head endpoint has indegree zero and throw exception if not
                /*!
                 * \param edgeTailEndpoint  The edge tail end point identified by its corresponding scale and
                 *                          subsystem
                 * \param edgeHeadEndpoint  The edge head end point identified by its corresponding scale and
                 *                          subsystem
                 */
                void checkIfEdgeHeadEndpointHasIndegreeZero(const std::string &edgeTailEndpoint,
                                                            const std::string &edgeHeadEndpoint) const;

                //! Check if the compared scales and subsystems are encoded by the graph and throw exception if not
                /*! This function is called to check if the scales and subsystems are encoded by the graph before
                 *  attempting to compare them.
                 *
                 * \param firstScaleAndSubsystem    The first considered scale and subsystem
                 * \param secondScaleAndSubsystem   The second considered scale and subsystem
                 */
                void checkIfComparedScaleAndSubsystemsAreEncodedByGraph(const std::string &firstScaleAndSubsystem,
                                                                        const std::string
                                                                        &secondScaleAndSubsystem) const;

                //! Check if the valid left hand side scale and subsystem < right hand side scale and subsystem
                /*! Precondition: The multiscale architecture graph is a valid rooted directed tree.
                 *
                 * \param lhsScaleAndSubsystem  The left hand side scale and subsystem
                 * \param rhsScaleAndSubsystem  The right hand side scale and subsystem
                 */
                bool isValidScaleAndSubsystemSmallerThan(const std::string &lhsScaleAndSubsystem,
                                                         const std::string &rhsScaleAndSubsystem) const;

                //! Compute the index of the root vertex
                /*!
                 *  Precondition: The root vertex is unique.
                 */
                long computeRootVertexIndex() const;

                //! Retrieve the name corresponding to the provided vertex index
                /*!
                 * Warning: The complexity of this method is O(n) where n is the number of vertices.
                 *          Therefore it is inefficient and should be used rarely. If this method needs to
                 *          be executed often then a different data structure should be employed for
                 *          recording vertices names.
                 *
                 * \param vertexIndex   The index corresponding to the vertex
                 */
                std::string computeVertexName(long vertexIndex) const;


                // Constants
                static const long   NO_PREDECESSOR_INDEX;
                static const long   ROOT_VERTEX_PREDECESSOR_INDEX;

                static const std::string LABEL_MULTISCALE_ARCHITECTURE_GRAPH;
                static const std::string LABEL_VERTICES;
                static const std::string LABEL_EDGES;

                static const std::string LABEL_VERTEX;
                static const std::string LABEL_VERTEX_ID;

                static const std::string LABEL_EDGE;
                static const std::string LABEL_EDGE_BEGIN_VERTEX;
                static const std::string LABEL_EDGE_END_VERTEX;

                static const std::string MULTISCALE_ARCHITECTURE_GRAPH_INPUT_FILE_EXTENSION;
                static const std::string MULTISCALE_ARCHITECTURE_GRAPH_XSD_PATH;

                static const std::string ERR_INVALID_INPUT_FILE_PATH_BEGIN;
                static const std::string ERR_INVALID_INPUT_FILE_PATH_END;

                static const std::string ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_BEGIN;
                static const std::string ERR_INVALID_INPUT_FILE_RELATIVE_TO_XSD_END;

                static const std::string ERR_ADD_ROOT_VERTEX_NON_EMPTY_GRAPH;

                static const std::string ERR_ROOT_VERTEX_NOT_UNIQUE;

                static const std::string ERR_NO_ROOT_VERTEX;

                static const std::string ERR_NO_PATH_FROM_ROOT_TO_VERTEX_BEGIN;
                static const std::string ERR_NO_PATH_FROM_ROOT_TO_VERTEX_MIDDLE;
                static const std::string ERR_NO_PATH_FROM_ROOT_TO_VERTEX_END;

                static const std::string ERR_INVALID_EDGE_BEGIN;
                static const std::string ERR_INVALID_EDGE_MIDDLE1;
                static const std::string ERR_INVALID_EDGE_MIDDLE2;

                static const std::string ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_BEGIN;
                static const std::string ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_MIDDLE1;
                static const std::string ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_MIDDLE2;
                static const std::string ERR_INVALID_EDGE_PREDECESSOR_VERTEX_DOES_NOT_EXIST_END;

                static const std::string ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_BEGIN;
                static const std::string ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_MIDDLE1;
                static const std::string ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_MIDDLE2;
                static const std::string ERR_INVALID_EDGE_NEW_VERTEX_EXISTS_END;

                static const std::string ERR_INVALID_EDGE_IDENTICAL_ENDPOINTS_BEGIN;
                static const std::string ERR_INVALID_EDGE_IDENTICAL_ENDPOINTS_MIDDLE;
                static const std::string ERR_INVALID_EDGE_IDENTICAL_ENDPOINTS_END;

                static const std::string ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_BEGIN;
                static const std::string ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE1;
                static const std::string ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE2;
                static const std::string ERR_INVALID_EDGE_TAIL_ENDPOINT_NOT_ENCODED_BY_GRAPH_END;

                static const std::string ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_BEGIN;
                static const std::string ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE1;
                static const std::string ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_MIDDLE2;
                static const std::string ERR_INVALID_EDGE_HEAD_ENDPOINT_NOT_ENCODED_BY_GRAPH_END;

                static const std::string ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_BEGIN;
                static const std::string ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_MIDDLE1;
                static const std::string ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_MIDDLE2;
                static const std::string ERR_INVALID_EDGE_HEAD_ENDPOINT_INDEGREE_NOT_ZERO_END;

                static const std::string ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_BEGIN;
                static const std::string ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_MIDDLE1;
                static const std::string ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_MIDDLE2;
                static const std::string ERR_COMPARE_SCALE_AND_SUBSYSTEMS_NOT_ENCODED_BY_GRAPH_END;

        };

    };

};


#endif
