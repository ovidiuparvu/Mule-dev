#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/RuntimeException.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/Filesystem.hpp"
#include "multiscale/util/XmlValidator.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataReader.hpp"

#include <iostream>
#include <limits>

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
    return hasValidNext();
}

void SpatialTemporalDataReader::refresh() {
    updateFilesLists();
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
    SpatialTemporalTrace trace = generateSpatialTemporalTrace(inputFilepath);

    // Add the file to the list of processed files
    processedInputFiles.insert(inputFilepath);

    return trace;
}

SpatialTemporalTrace SpatialTemporalDataReader::generateSpatialTemporalTrace(const std::string &inputFilepath) {
    pt::ptree propertyTree;

    read_xml(inputFilepath, propertyTree, pt::xml_parser::trim_whitespace);

    return generateSpatialTemporalTrace(propertyTree);
}

SpatialTemporalTrace SpatialTemporalDataReader::generateSpatialTemporalTrace(const pt::ptree &tree) {
    SpatialTemporalTrace trace;

    for (const auto &timePointTreePair : tree.get_child(LABEL_EXPERIMENT)) {
        addTimePointToTrace(timePointTreePair.second, trace);
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
    setTimePointValue(timePointTree, timePoint);
    addEntitiesToTimePoint(timePointTree, timePoint);
}

void SpatialTemporalDataReader::setTimePointValue(const pt::ptree &timePointTree, TimePoint &timePoint) {
    unsigned long timePointValue;

    if (timePointHasValue(timePointTree, timePointValue)) {
        timePoint.setValue(timePointValue);
    } else {
        timePoint.setValue(std::numeric_limits<unsigned long>::max());
    }
}

bool SpatialTemporalDataReader::timePointHasValue(const pt::ptree &propertyTree, unsigned long &value) {
    boost::optional<unsigned long> timePointValue = propertyTree.get_optional<unsigned long>(LABEL_TIMEPOINT_VALUE);

    if (timePointValue.is_initialized()) {
        value = *timePointValue;

        return true;
    }

    return false;
}

void SpatialTemporalDataReader::addEntitiesToTimePoint(const pt::ptree &timePointTree,
                                                       TimePoint &timePoint) {
    for (const auto &entityTree : timePointTree) {
        if (entityTree.first.compare(LABEL_NUMERIC_STATE_VARIABLE) == 0) {
            addNumericStateVariableToTimePoint(entityTree.second, timePoint);
        } else if (entityTree.first.compare(LABEL_SPATIAL_ENTITY) == 0) {
            addSpatialEntityToTimePoint(entityTree.second, timePoint);
        }
    }
}

void SpatialTemporalDataReader::addNumericStateVariableToTimePoint(const pt::ptree &numericStateVariableTree,
                                                                   TimePoint &timePoint) {
    std::string name  = numericStateVariableTree.get<std::string>(LABEL_NUMERIC_STATE_VARIABLE_NAME);
    double      value = numericStateVariableTree.get<double>(LABEL_NUMERIC_STATE_VARIABLE_VALUE);

    timePoint.addNumericStateVariable(name, value);
}

void SpatialTemporalDataReader::addSpatialEntityToTimePoint(const pt::ptree &spatialEntityTree,
                                                            TimePoint &timePoint) {
    std::string spatialEntityType = spatialEntityTree.get<std::string>(LABEL_SPATIAL_ENTITY_PSEUDO3D_TYPE);

    if (spatialEntityType.compare(PSEUDO3D_SPATIAL_ENTITY_TYPE_CLUSTER) == 0) {
        addClusterToTimePoint(spatialEntityTree, timePoint);
    } else if (spatialEntityType.compare(PSEUDO3D_SPATIAL_ENTITY_TYPE_REGION) == 0) {
        addRegionToTimePoint(spatialEntityTree, timePoint);
    } else {
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
    Region region;

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

    timePoint.addRegion(region);
}

std::string SpatialTemporalDataReader::getFirstValidUnprocessedInputFilepath() {
    if (!hasNext()) {
        MS_throw(RuntimeException, ERR_NO_VALID_INPUT_FILES_REMAINING);
    }

    // Obtain the valid unprocessed input file
    std::unordered_set<std::string>::iterator it = unprocessedInputFiles.begin();
    std::string validUnprocessedFile = (*it);

    // Remove it from the list of unprocessed files
    unprocessedInputFiles.erase(it);

    return validUnprocessedFile;
}

void SpatialTemporalDataReader::updateFilesLists() {
    std::vector<std::string> filesInFolder = Filesystem::getFilesInFolder(folderPath, INPUT_FILES_EXTENSION);

    for (const std::string &file : filesInFolder) {
        if (processedInputFiles.find(file) == processedInputFiles.end()) {
            // Since this is a set each element will be added only if the set does not contain the element already
            unprocessedInputFiles.insert(file);
        }
    }
}

bool SpatialTemporalDataReader::isValidInputFile(const std::string &inputFilepath) {
    return (XmlValidator::isValidXmlFile(inputFilepath, INPUT_FILES_SCHEMA_PATH));
}

void SpatialTemporalDataReader::validateFolderPath(const std::string &folderPath) {
    if (!Filesystem::isValidFolderPath(folderPath)) {
        MS_throw(InvalidInputException, ERR_INVALID_FOLDER_PATH);
    }
}


// Constants
const std::string SpatialTemporalDataReader::ERR_INVALID_FOLDER_PATH               = "The provided path does not point to a folder. Please change.";
const std::string SpatialTemporalDataReader::ERR_NO_VALID_INPUT_FILES_REMAINING    = "There are no valid unprocessed input files remaining.";
const std::string SpatialTemporalDataReader::ERR_UNDEFINED_SPATIAL_ENTITY_TYPE     = "The provided spatial entity type is invalid.";

const std::string SpatialTemporalDataReader::LABEL_EXPERIMENT                      = "experiment";
const std::string SpatialTemporalDataReader::LABEL_TIMEPOINT_VALUE                 = "<xmlattr>.value";

const std::string SpatialTemporalDataReader::LABEL_NUMERIC_STATE_VARIABLE          = "numericStateVariable";
const std::string SpatialTemporalDataReader::LABEL_NUMERIC_STATE_VARIABLE_NAME     = "name";
const std::string SpatialTemporalDataReader::LABEL_NUMERIC_STATE_VARIABLE_VALUE    = "value";

const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY                  = "spatialEntity";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_PSEUDO3D_TYPE    = "pseudo3D.<xmlattr>.type";

const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_CLUSTEREDNESS         = "pseudo3D.clusteredness";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_DENSITY               = "pseudo3D.density";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_AREA                  = "pseudo3D.area";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_PERIMETER             = "pseudo3D.perimeter";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_DISTANCE_FROM_ORIGIN  = "pseudo3D.distanceFromOrigin";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_ANGLE                 = "pseudo3D.angle";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_TRIANGLE_MEASURE      = "pseudo3D.triangleMeasure";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_RECTANGLE_MEASURE     = "pseudo3D.rectangleMeasure";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_CIRCLE_MEASURE        = "pseudo3D.circleMeasure";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_CENTROID_X            = "pseudo3D.centroid.x";
const std::string SpatialTemporalDataReader::LABEL_SPATIAL_ENTITY_CENTROID_Y            = "pseudo3D.centroid.y";

const std::string SpatialTemporalDataReader::PSEUDO3D_SPATIAL_ENTITY_TYPE_REGION        = "region";
const std::string SpatialTemporalDataReader::PSEUDO3D_SPATIAL_ENTITY_TYPE_CLUSTER       = "cluster";

const std::string SpatialTemporalDataReader::INPUT_FILES_EXTENSION      = ".xml";
const std::string SpatialTemporalDataReader::INPUT_FILES_SCHEMA_PATH    = "config/verification/spatial-temporal/schema/experiment.xsd";
