#include "multiscale/analysis/spatial/detector/ClusterDetector.hpp"
#include "multiscale/analysis/spatial/util/DBSCAN.hpp"
#include "multiscale/analysis/spatial/util/Silhouette.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"
#include "multiscale/util/RGBColourGenerator.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace multiscale::analysis;


ClusterDetector::ClusterDetector(
    unsigned int maxPileupNumber, bool isDebugMode
) : Detector(isDebugMode), maxPileupNumber(maxPileupNumber) {
    this->eps = 0;
    this->minPoints = 0;

    this->avgDensity = 0;
    this->avgClusterednessDegree = 0;

    this->singleEntityIntensity =
        Numeric::division(
            static_cast<double>(INTENSITY_MAX),
            static_cast<double>(maxPileupNumber)
        );
}

ClusterDetector::~ClusterDetector() {}

double ClusterDetector::getEps() {
    return convertEpsValue();
}

int ClusterDetector::getMinPoints() {
    return minPoints;
}

std::vector<Cluster> const &ClusterDetector::getClusters() {
    return clusters;
}

void ClusterDetector::setEps(double eps) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->eps = NumericRangeManipulator::convertFromRange<double, int>(
                    EPS_REAL_MIN, EPS_REAL_MAX, EPS_MIN, EPS_MAX, eps
                );
}

void ClusterDetector::setMinPoints(int minPoints) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->minPoints = minPoints;
}

void ClusterDetector::initialiseDetectorSpecificFields() {
    eps = 1200;
    minPoints = 2;
}

void ClusterDetector::createDetectorSpecificTrackbars() {
    cv::createTrackbar(TRACKBAR_MINPOINTS, WIN_OUTPUT_IMAGE, &minPoints, MIN_POINTS_MAX, nullptr, nullptr);
    cv::createTrackbar(TRACKBAR_EPS, WIN_OUTPUT_IMAGE, &eps, EPS_MAX, nullptr, nullptr);
}

void ClusterDetector::clearPreviousDetectionResults() {
    clusters.clear();
}

std::string ClusterDetector::getDetectorTypeAsString() {
    return DETECTOR_TYPE;
}

void ClusterDetector::processImageAndDetect() {
    std::vector<Entity> entities;

    detectEntitiesInImage(entities);
    detectAndAnalyseClusters(entities, clusters);
}

void ClusterDetector::detectAndAnalyseClusters(const std::vector<Entity> &entities,
                                               std::vector<Cluster> &clusters) {
    std::vector<int> clusterIndexes;
    std::size_t nrOfClusters;

    detectClusters(entities, clusterIndexes, nrOfClusters);
    addEntitiesToClusters(entities, clusterIndexes, nrOfClusters, clusters);
    analyseClusters(clusters);
}

void ClusterDetector::detectClusters(const std::vector<Entity> &entities,
                                     std::vector<int> &clusterIndexes,
                                     std::size_t &nrOfClusters) {
    DBSCAN<Entity>().run(
        flattenEntitiesCollection(entities),
        clusterIndexes,
        nrOfClusters,
        convertEpsValue(),
        getValidMinPointsValue()
    );
}

std::vector<Entity> ClusterDetector::flattenEntitiesCollection(const std::vector<Entity> &entities) {
    std::vector<Entity> flattenedEntities;

    flattenedEntities.insert(flattenedEntities.begin(), entities.begin(), entities.end());

    addPiledUpEntitiesToCollection(entities, flattenedEntities);

    return flattenedEntities;
}

void ClusterDetector::addPiledUpEntitiesToCollection(const std::vector<Entity> &entities,
                                                     std::vector<Entity> &flattenedEntities) {
    for (const Entity &entity : entities) {
        std::size_t nrOfPiledUpEntities = static_cast<std::size_t>(entity.getPileUpDegree());

        // Consider only the above entities (at level 2+)
        for (std::size_t i = 1; i < nrOfPiledUpEntities; i++) {
            flattenedEntities.push_back(entity);
        }
    }
}

void ClusterDetector::addEntitiesToClusters(const std::vector<Entity> &entities,
                                            const std::vector<int> &clusterIndexes,
                                            std::size_t nrOfClusters,
                                            std::vector<Cluster> &clusters) {
    if (nrOfClusters > 1) {
        std::size_t nrOfEntities = entities.size();

        // The "noise" cluster will be ignored
        clusters.resize(nrOfClusters - 1);

        for (std::size_t i = 0; i < nrOfEntities; i++) {
            // If the entity does not belong to the "noise" cluster
            if (clusterIndexes[i] > 0) {
                clusters[clusterIndexes[i] - 1].addEntity(entities[i]);
            }
        }
    }
}

void ClusterDetector::analyseClusters(std::vector<Cluster> &clusters) {
    analyseClustersOriginDependentValues(clusters);

    avgClusterednessDegree = computeClusterednessIndex(clusters);
    avgDensity = computeAveragePileUpDegree(clusters);
}

void ClusterDetector::analyseClustersOriginDependentValues(std::vector<Cluster> &clusters) {
    for (Cluster &cluster : clusters) {
        std::vector<cv::Point2f> convexHull = cluster.getEntitiesConvexHull();

        if (convexHull.size() > 0) {
            updateClusterOriginDependentValues(cluster, convexHull);
        }
    }
}

void ClusterDetector::updateClusterOriginDependentValues(Cluster &cluster,
                                                         const std::vector<cv::Point2f>
                                                         &clusterConvexHull) {
    double distance = computeDistanceFromOrigin(clusterConvexHull);
    double angle = computePolygonAngle(clusterConvexHull);

    cluster.setOriginDependentMembers(distance, angle);
}

double ClusterDetector::computeClusterednessIndex(const std::vector<Cluster> &clusters) {
    return (clusters.size() > 0) ? Silhouette::computeOverallAverageMeasure(clusters)
                                 : 0;
}

double ClusterDetector::computeAveragePileUpDegree(std::vector<Cluster> &clusters) {
    double averagePileUpDegree = 0;

    for (Cluster &cluster : clusters) {
        averagePileUpDegree += cluster.getDensity();
    }

    return (
        Numeric::division(
            averagePileUpDegree,
            clusters.size()
        )
    );
}

std::vector<std::shared_ptr<SpatialEntityPseudo3D>> ClusterDetector::getCollectionOfSpatialEntityPseudo3D() {
    std::vector<std::shared_ptr<SpatialEntityPseudo3D>> convertedClusters;

    for (Cluster &cluster : clusters) {
        convertedClusters.push_back(std::shared_ptr<SpatialEntityPseudo3D>(new Cluster(cluster)));
    }

    return convertedClusters;
}

double ClusterDetector::convertEpsValue() {
    return (
        NumericRangeManipulator::convertFromRange<int, double>(
            EPS_MIN, EPS_MAX, EPS_REAL_MIN, EPS_REAL_MAX, eps
        )
    );
}

int ClusterDetector::getValidMinPointsValue() {
    return (
        (minPoints > 0) ? minPoints
                        : 1
    );
}


// Constants
const std::string ClusterDetector::DETECTOR_TYPE = "Clusters";

const std::string ClusterDetector::TRACKBAR_EPS         = "Eps (Multiplied by 10)";
const std::string ClusterDetector::TRACKBAR_MINPOINTS   = "Minimum number of points";

const int ClusterDetector::MIN_POINTS_MIN    = 0;
const int ClusterDetector::MIN_POINTS_MAX    = 100;

const int ClusterDetector::EPS_MIN           = 0;
const int ClusterDetector::EPS_MAX           = 10000;
const int ClusterDetector::EPS_REAL_MIN      = 0;
const int ClusterDetector::EPS_REAL_MAX      = 1000;
