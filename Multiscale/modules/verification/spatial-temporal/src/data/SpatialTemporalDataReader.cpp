#include "multiscale/exception/RuntimeException.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataReader.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace multiscale::verification;

namespace pt = boost::property_tree;


SpatialTemporalDataReader::SpatialTemporalDataReader(const std::string &folderPath) {
    initialise(folderPath);
}

SpatialTemporalDataReader::~SpatialTemporalDataReader() {
    processedInputFiles.clear();
    unprocessedInputFiles.clear();
}

bool SpatialTemporalDataReader::hasNext() {
    if (hasValidNext()) {
        return true;
    } else {
        updateFilesLists();

        return hasValidNext();
    }
}

SpatialTemporalTrace SpatialTemporalDataReader::getNextSpatialTemporalTrace() {
    if (!hasNext()) {
        MS_throw(RuntimeException, ERR_NO_VALID_INPUT_FILES_REMAINING);
    }

    return generateSpatialTemporalTrace();
}

void SpatialTemporalDataReader::initialise(const std::string &folderPath) {
    validateFolderPath(folderPath);

    this->folderPath = folderPath;

    initialise();
}

void SpatialTemporalDataReader::initialise() {
    processedInputFiles.clear();
    unprocessedInputFiles.clear();
}

bool SpatialTemporalDataReader::hasValidNext() {
    std::unordered_set<std::string>::iterator it = unprocessedInputFiles.begin();

    while (it != unprocessedInputFiles.end()) {
        if (isValidInputFile(*it)) {
            return true;
        }

        // Add it to processed files because it is invalid
        processedInputFiles.insert(*it);

        // Remove the invalid file from the set of unprocessed files
        it = unprocessedInputFiles.erase(it);
    }

    return false;
}

SpatialTemporalTrace SpatialTemporalDataReader::generateSpatialTemporalTrace() {
    std::string inputFilepath = getFirstValidUnprocessedInputFilepath();

    return generateSpatialTemporalTrace(inputFilepath);
}

SpatialTemporalTrace SpatialTemporalDataReader::generateSpatialTemporalTrace(const std::string &inputFilepath) {
    pt::ptree propertyTree;

    read_xml(inputFilepath, propertyTree, pt::xml_parser::trim_whitespace);

    return generateSpatialTemporalTrace(propertyTree);
}

SpatialTemporalTrace SpatialTemporalDataReader::generateSpatialTemporalTrace(const pt::ptree &tree) {
    SpatialTemporalTrace trace;

    for (const pt::ptree &timePointTree : tree.get_child(LABEL_EXPERIMENT)) {
        addTimePointToTrace(timePointTree, trace);
    }

    return trace;
}

void SpatialTemporalDataReader::addTimePointToTrace(const pt::ptree &timePointTree, SpatialTemporalTrace &trace) {
    TimePoint timePoint;

    convertTimePointPropertyTreeToTrace(timePointTree, timePoint);

    trace.addTimePoint(timePoint);
}

void SpatialTemporalDataReader::convertTimePointPropertyTreeToTrace(const pt::ptree &timePointTree,
                                                                    TimePoint &timePoint) {
    unsigned long timePointValue;

    if (timePointHasValue(timePointTree, timePointValue)) {
        timePoint.setValue(timePointValue);
    }

    addNumericStateVariablesToTimePoint(timePointTree, timePoint);
    addSpatialEntitiesToTimePoint(timePointTree, timePoint);
}

bool SpatialTemporalDataReader::timePointHasValue(const pt::ptree &propertyTree, unsigned long &value) {
    boost::optional<unsigned long> timePointValue = propertyTree.get_optional<unsigned long>(LABEL_TIMEPOINT_VALUE);

    if (timePointValue.is_initialized()) {
        value = *timePointValue;

        return true;
    }

    return false;
}

void SpatialTemporalDataReader::addNumericStateVariablesToTimePoint(const pt::ptree &timePointTree,
                                                                    TimePoint &timePoint) {
    for (const pt::ptree &numericStateVariableTree : timePointTree.get_child(LABEL_NUMERIC_STATE_VARIABLE)) {
        addNumericStateVariableToTimePoint(numericStateVariableTree, timePoint);
    }
}

void SpatialTemporalDataReader::addNumericStateVariableToTimePoint(const pt::ptree &numericStateVariableTree,
                                                                   TimePoint &timePoint) {
    std::string name  = numericStateVariableTree.get<std::string>(LABEL_NUMERIC_STATE_VARIABLE_NAME);
    double      value = numericStateVariableTree.get<double>(LABEL_NUMERIC_STATE_VARIABLE_VALUE);

    timePoint.addNumericStateVariable(name, value);
}

void SpatialTemporalDataReader::addSpatialEntitiesToTimePoint(const pt::ptree &timePointTree, TimePoint &timePoint) {
    for (const pt::ptree &spatialEntityTree : timePointTree.get_child(LABEL_SPATIAL_ENTITY)) {
        addSpatialEntityToTimePoint(spatialEntityTree, timePoint);
    }
}

void SpatialTemporalDataReader::addSpatialEntityToTimePoint(const pt::ptree &spatialEntityTree,
                                                            TimePoint &timePoint) {
    std::string spatialEntityType = spatialEntityTree.get<std::string>(LABEL_SPATIAL_ENTITY_PSEUDO3D_TYPE);

    switch (spatialEntityType) {
        case PSEUDO3D_SPATIAL_ENTITY_TYPE_CLUSTER:
            addClusterToTimePoint(spatialEntityTree, timePoint);
            break;

        case PSEUDO3D_SPATIAL_ENTITY_TYPE_REGION:
            addRegionToTimePoint(spatialEntityTree, timePoint);
            break;

        default:
            MS_throw(UnexpectedBehaviourException, ERR_UNDEFINED_SPATIAL_ENTITY_TYPE);
    }
}

void SpatialTemporalDataReader::addClusterToTimePoint(const pt::ptree &clusterTree, TimePoint &timePoint) {
    Cluster cluster;

    cluster.setClusteredness(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_CLUSTEREDNESS));
    cluster.setDensity(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_DENSITY));
    cluster.setArea(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_AREA));
    cluster.setPerimeter(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_PERIMETER));
    cluster.setDistanceFromOrigin(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_DISTANCE_FROM_ORIGIN));
    cluster.setAngle(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_ANGLE));
    cluster.setTriangleMeasure(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_TRIANGLE_MEASURE));
    cluster.setRectangleMeasure(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_RECTANGLE_MEASURE));
    cluster.setCircleMeasure(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_CIRCLE_MEASURE));
    cluster.setCentroidX(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_CENTROID_X));
    cluster.setCentroidY(clusterTree.get<double>(LABEL_SPATIAL_ENTITY_CENTROID_Y));

    timePoint.addCluster(cluster);
}

void SpatialTemporalDataReader::addRegionToTimePoint(const pt::ptree &regionTree, TimePoint &timePoint) {
    Cluster region;

    region.setClusteredness(regionTree.get<double>(LABEL_SPATIAL_ENTITY_CLUSTEREDNESS));
    region.setDensity(regionTree.get<double>(LABEL_SPATIAL_ENTITY_DENSITY));
    region.setArea(regionTree.get<double>(LABEL_SPATIAL_ENTITY_AREA));
    region.setPerimeter(regionTree.get<double>(LABEL_SPATIAL_ENTITY_PERIMETER));
    region.setDistanceFromOrigin(regionTree.get<double>(LABEL_SPATIAL_ENTITY_DISTANCE_FROM_ORIGIN));
    region.setAngle(regionTree.get<double>(LABEL_SPATIAL_ENTITY_ANGLE));
    region.setTriangleMeasure(regionTree.get<double>(LABEL_SPATIAL_ENTITY_TRIANGLE_MEASURE));
    region.setRectangleMeasure(regionTree.get<double>(LABEL_SPATIAL_ENTITY_RECTANGLE_MEASURE));
    region.setCircleMeasure(regionTree.get<double>(LABEL_SPATIAL_ENTITY_CIRCLE_MEASURE));
    region.setCentroidX(regionTree.get<double>(LABEL_SPATIAL_ENTITY_CENTROID_X));
    region.setCentroidY(regionTree.get<double>(LABEL_SPATIAL_ENTITY_CENTROID_Y));

    timePoint.addCluster(region);
}

std::string SpatialTemporalDataReader::getFirstValidUnprocessedInputFilepath() {
    if (!hasNext()) {
        MS_throw(RuntimeException, ERR_NO_VALID_INPUT_FILES_REMAINING);
    }

    std::unordered_set<std::string>::iterator it = unprocessedInputFiles.begin();

    return (*it);
}

void SpatialTemporalDataReader::updateFilesLists() {
    // TODO: Implement
}
