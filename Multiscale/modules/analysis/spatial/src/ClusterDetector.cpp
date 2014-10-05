#include "multiscale/analysis/spatial/ClusterDetector.hpp"
#include "multiscale/analysis/spatial/DBSCAN.hpp"
#include "multiscale/analysis/spatial/Silhouette.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"
#include "multiscale/util/RGBColourGenerator.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace multiscale::analysis;


ClusterDetector::ClusterDetector(int maxPileupNumber, double maxPileupIntensity, bool debugMode)
                                 : Detector(debugMode) {
    this->eps = 0;
    this->minPoints = 0;

    this->avgDensity = 0;
    this->avgClusterednessDegree = 0;

    this->entityPileupDegree = (maxPileupIntensity / maxPileupNumber);
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
    std::vector<int> clusterIndexes(entities.size(), DBSCAN::CLUSTERING_UNCLASSIFIED);
    int nrOfClusters;

    detectClusters(entities, clusterIndexes, nrOfClusters);
    addEntitiesToClusters(entities, clusterIndexes, nrOfClusters, clusters);
    analyseClusters(clusters);
}

void ClusterDetector::detectClusters(const std::vector<Entity> &entities, std::vector<int> &clusterIndexes,
                                     int &nrOfClusters) {
    DBSCAN().run(
        convertEntities(entities),
        clusterIndexes,
        nrOfClusters,
        convertEpsValue(),
        getValidMinPointsValue()
    );
}

std::vector<std::shared_ptr<DataPoint>> ClusterDetector::convertEntities(const std::vector<Entity> &entities) {
    std::vector<std::shared_ptr<DataPoint>> dataPoints;

    convertNonPiledUpEntities(entities, dataPoints);
    convertPiledUpEntities(entities, dataPoints);

    return dataPoints;
}

void ClusterDetector::convertNonPiledUpEntities(const std::vector<Entity> &entities,
                                                std::vector<std::shared_ptr<DataPoint> > &dataPoints) {
    for (const Entity &entity : entities) {
        dataPoints.push_back(std::shared_ptr<DataPoint>(new Entity(entity)));
    }
}

void ClusterDetector::convertPiledUpEntities(const std::vector<Entity> &entities,
                                             std::vector<std::shared_ptr<DataPoint> > &dataPoints) {
    for (const Entity &entity : entities) {
        int nrOfPiledUpEntities = entity.getPileUpDegree();

        // Consider only the above entities (at level 2+)
        for (int i = 1; i < nrOfPiledUpEntities; i++) {
            dataPoints.push_back(std::shared_ptr<DataPoint>(new Entity(entity)));
        }
    }
}

void ClusterDetector::addEntitiesToClusters(const std::vector<Entity> &entities,
                                            const std::vector<int> &clusterIndexes,
                                            int nrOfClusters,
                                            std::vector<Cluster> &clusters) {
    if (nrOfClusters > 1) {
        int nrOfEntities = entities.size();

        // The "noise" cluster will be ignored
        clusters.resize(nrOfClusters - 1);

        for (int i = 0; i < nrOfEntities; i++) {
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
        std::vector<cv::Point> convexHull = getClusterConvexHull(cluster);

        if (convexHull.size() > 0) {
            updateClusterOriginDependentValues(cluster, convexHull);
        }
    }
}

void ClusterDetector::updateClusterOriginDependentValues(Cluster &cluster,
                                                         const std::vector<cv::Point> &clusterConvexHull) {
    unsigned int minDistancePointIndex = Geometry2D::minimumDistancePointIndex(clusterConvexHull, origin);

    double distance = Geometry2D::distanceBtwPoints(clusterConvexHull[minDistancePointIndex], origin);
    double angle = polygonAngle(clusterConvexHull, minDistancePointIndex);

    cluster.setOriginDependentMembers(distance, angle);
}

std::vector<cv::Point> ClusterDetector::getClusterConvexHull(Cluster &cluster) {
    std::vector<cv::Point> clusterConvexHull;

    std::vector<cv::Point2f> entitiesConvexHull = cluster.getEntitiesConvexHull();

    cv::Mat(entitiesConvexHull).copyTo(clusterConvexHull);

    return clusterConvexHull;
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

    unsigned int nrOfClusters = clusters.size();

    return (nrOfClusters == 0) ? 0
                               : (averagePileUpDegree / nrOfClusters);
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
    return (minPoints > 0) ? minPoints
                           : 1;
}


// Constants
const std::string ClusterDetector::DETECTOR_TYPE = "Clusters";

const std::string ClusterDetector::TRACKBAR_EPS           = "Eps (Multiplied by 10)";
const std::string ClusterDetector::TRACKBAR_MINPOINTS     = "Minimum number of points";

const int ClusterDetector::MIN_POINTS_MIN    = 0;
const int ClusterDetector::MIN_POINTS_MAX    = 100;

const int ClusterDetector::EPS_MIN           = 0;
const int ClusterDetector::EPS_MAX           = 10000;
const int ClusterDetector::EPS_REAL_MIN      = 0;
const int ClusterDetector::EPS_REAL_MAX      = 1000;
