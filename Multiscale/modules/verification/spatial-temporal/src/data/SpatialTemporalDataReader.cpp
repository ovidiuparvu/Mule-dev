#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/RuntimeException.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/Filesystem.hpp"
#include "multiscale/util/XmlValidator.hpp"
#include "multiscale/verification/spatial-temporal/data/SpatialTemporalDataReader.hpp"
#include "multiscale/verification/spatial-temporal/model/Cluster.hpp"
#include "multiscale/verification/spatial-temporal/model/Region.hpp"

#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

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
    updateInputFilesSets();
}

SpatialTemporalTrace SpatialTemporalDataReader::getNextSpatialTemporalTrace() {
    if (!hasNext()) {
        MS_throw(RuntimeException, ERR_NO_VALID_INPUT_FILES_REMAINING);
    }

    return generateSpatialTemporalTrace();
}

SpatialTemporalTrace SpatialTemporalDataReader::getNextSpatialTemporalTrace(std::string &tracePath) {
    if (!hasNext()) {
        MS_throw(RuntimeException, ERR_NO_VALID_INPUT_FILES_REMAINING);
    }

    return generateSpatialTemporalTrace(tracePath);
}

void SpatialTemporalDataReader::initialise(const std::string &folderPath) {
    validateFolderPath(folderPath);

    this->folderPath = folderPath;

    initialise();
}

void SpatialTemporalDataReader::initialise() {
    clearInputFilesSets();
    updateInputFilesSets();
}

void SpatialTemporalDataReader::clearInputFilesSets() {
    processedInputFiles.clear();
    unprocessedInputFiles.clear();
}

bool SpatialTemporalDataReader::hasValidNext() {
    auto it = unprocessedInputFiles.begin();

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
    std::string inputFilepath = getRandomValidUnprocessedInputFilepath();
    SpatialTemporalTrace trace = constructSpatialTemporalTrace(inputFilepath);

    // Add the file to the list of processed files
    processedInputFiles.insert(inputFilepath);

    return trace;
}

SpatialTemporalTrace SpatialTemporalDataReader::generateSpatialTemporalTrace(std::string &tracePath) {
    tracePath = getRandomValidUnprocessedInputFilepath();
    SpatialTemporalTrace trace = constructSpatialTemporalTrace(tracePath);

    // Add the file to the list of processed files
    processedInputFiles.insert(tracePath);

    return trace;
}

SpatialTemporalTrace SpatialTemporalDataReader::constructSpatialTemporalTrace(const std::string &inputFilepath) {
    pt::ptree propertyTree;

    read_xml(inputFilepath, propertyTree, pt::xml_parser::trim_whitespace);

    return constructSpatialTemporalTrace(propertyTree);
}

SpatialTemporalTrace SpatialTemporalDataReader::constructSpatialTemporalTrace(const pt::ptree &tree) {
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
    std::shared_ptr<SpatialEntity>  spatialEntity;
    SubsetSpecificType              spatialEntityType;

    createDerivedSpatialEntity(spatialEntityTree, spatialEntity, spatialEntityType);
    setSpatialEntityValues(spatialEntityTree, spatialEntity);

    timePoint.addSpatialEntity(spatialEntity, spatialEntityType);
}

void SpatialTemporalDataReader::createDerivedSpatialEntity(const pt::ptree &spatialEntityTree,
                                                           std::shared_ptr<SpatialEntity> &spatialEntity,
                                                           SubsetSpecificType &spatialEntityType) {
    std::string spatialEntityTypeLabel = spatialEntityTree.get<std::string>(LABEL_SPATIAL_ENTITY_PSEUDO3D_TYPE);

    if (spatialEntityTypeLabel.compare("cluster") == 0) {
        spatialEntity       = std::make_shared<Cluster>();
        spatialEntityType   = SubsetSpecificType::Clusters;
    } else if (spatialEntityTypeLabel.compare("region") == 0) {
        spatialEntity       = std::make_shared<Region>();
        spatialEntityType   = SubsetSpecificType::Regions;
    } else {
        MS_throw(UnexpectedBehaviourException, ERR_UNDEFINED_SPATIAL_ENTITY_TYPE);
    }
}

void SpatialTemporalDataReader::setSpatialEntityValues(const pt::ptree &spatialEntityTree,
                                                       const std::shared_ptr<SpatialEntity> &spatialEntity) {
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Clusteredness,
                                          spatialEntityTree.get<double>("pseudo3D.clusteredness"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Density,
                                          spatialEntityTree.get<double>("pseudo3D.density"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Area,
                                          spatialEntityTree.get<double>("pseudo3D.area"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Perimeter,
                                          spatialEntityTree.get<double>("pseudo3D.perimeter"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::DistanceFromOrigin,
                                          spatialEntityTree.get<double>("pseudo3D.distanceFromOrigin"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::Angle,
                                          spatialEntityTree.get<double>("pseudo3D.angle"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::TriangleMeasure,
                                          spatialEntityTree.get<double>("pseudo3D.triangleMeasure"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::RectangleMeasure,
                                          spatialEntityTree.get<double>("pseudo3D.rectangleMeasure"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::CircleMeasure,
                                          spatialEntityTree.get<double>("pseudo3D.circleMeasure"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::CentroidX,
                                          spatialEntityTree.get<double>("pseudo3D.centroid.x"));
    spatialEntity->setSpatialMeasureValue(SpatialMeasureType::CentroidY,
                                          spatialEntityTree.get<double>("pseudo3D.centroid.y"));
}

std::string SpatialTemporalDataReader::getFirstValidUnprocessedInputFilepath() {
    if (!hasNext()) {
        MS_throw(RuntimeException, ERR_NO_VALID_INPUT_FILES_REMAINING);
    }

    // Obtain the valid unprocessed input file
    auto it = unprocessedInputFiles.begin();
    std::string validUnprocessedFile = (*it);

    // Remove it from the list of unprocessed files
    unprocessedInputFiles.erase(it);

    return validUnprocessedFile;
}

std::string SpatialTemporalDataReader::getRandomValidUnprocessedInputFilepath() {
    if (!hasNext()) {
        MS_throw(RuntimeException, ERR_NO_VALID_INPUT_FILES_REMAINING);
    }

    // Obtain an iterator to the beginning of the collection
    auto it = unprocessedInputFiles.begin();

    // Advance the iterator for a valid random number of positions
    std::advance(it, std::rand() % unprocessedInputFiles.size());

    // Obtain the valid unprocessed input file
    std::string validUnprocessedFile = (*it);

    // Remove it from the list of unprocessed files
    unprocessedInputFiles.erase(it);

    return validUnprocessedFile;
}

void SpatialTemporalDataReader::updateInputFilesSets() {
    std::vector<std::string> filesInFolder = getFilesInFolder();

    for (const std::string &file : filesInFolder) {
        if (processedInputFiles.find(file) == processedInputFiles.end()) {
            // Since this is a set each element will be added only if the set does not contain the element already
            unprocessedInputFiles.insert(file);
        }
    }
}

std::vector<std::string> SpatialTemporalDataReader::getFilesInFolder() {
    return Filesystem::getFilesInFolder(folderPath, INPUT_FILES_EXTENSION);
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

const std::string SpatialTemporalDataReader::INPUT_FILES_EXTENSION      = ".xml";
const std::string SpatialTemporalDataReader::INPUT_FILES_SCHEMA_PATH    = "/home/ovidiu/Repositories/git/multiscale/Multiscale/config/verification/spatial-temporal/schema/MSTML_L1V1.xsd";
