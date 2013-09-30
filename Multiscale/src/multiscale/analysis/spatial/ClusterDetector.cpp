#include "multiscale/analysis/spatial/ClusterDetector.hpp"
#include "multiscale/analysis/spatial/DBSCAN.hpp"
#include "multiscale/analysis/spatial/Silhouette.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"
#include "multiscale/util/RGBColourGenerator.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace multiscale::analysis;


ClusterDetector::ClusterDetector(int maxPileupNumber, double maxPileupIntensity, bool debugMode) : Detector(debugMode) {
    this->eps = 0;
    this->minPoints = 0;

    this->avgPileUpDegree = 0;
    this->clusterednessIndex = 0;

    this->entityPileupDegree = (maxPileupIntensity / maxPileupNumber);
}

ClusterDetector::~ClusterDetector() {}

double ClusterDetector::getEps() {
    return convertEpsValue();
}

int ClusterDetector::getMinPoints() {
    return minPoints;
}

vector<Cluster> const &ClusterDetector::getClusters() {
    return clusters;
}

void ClusterDetector::setEps(double eps) {
    setDetectorSpecificFieldsInitialisationFlag();

    this->eps = NumericRangeManipulator::convertFromRange<double, int>(EPS_REAL_MIN, EPS_REAL_MAX, EPS_MIN, EPS_MAX, eps);
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
    createTrackbar(TRACKBAR_MINPOINTS, WIN_OUTPUT_IMAGE, &minPoints, MIN_POINTS_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_EPS, WIN_OUTPUT_IMAGE, &eps, EPS_MAX, nullptr, nullptr);
}

void ClusterDetector::clearPreviousDetectionResults() {
    clusters.clear();
}

void ClusterDetector::processImageAndDetect() {
    vector<Entity> entities;

    detectEntitiesInImage(entities);
    detectAndAnalyseClusters(entities, clusters);
}

void ClusterDetector::detectAndAnalyseClusters(const vector<Entity> &entities, vector<Cluster> &clusters) {
    vector<int> clusterIndexes(entities.size(), CLUSTERING_UNCLASSIFIED);
    int nrOfClusters;

    detectClusters(entities, clusterIndexes, nrOfClusters);
    addEntitiesToClusters(entities, clusterIndexes, nrOfClusters, clusters);
    analyseClusters(clusters);
}

void ClusterDetector::detectClusters(const vector<Entity> &entities, vector<int> &clusterIndexes, int &nrOfClusters) {
    DBSCAN::run(convertEntities(entities), clusterIndexes, nrOfClusters, convertEpsValue(), getValidMinPointsValue());
}

vector<shared_ptr<DataPoint>> ClusterDetector::convertEntities(const vector<Entity> &entities) {
    vector<shared_ptr<DataPoint>> dataPoints;

    convertNonPiledUpEntities(entities, dataPoints);
    convertPiledUpEntities(entities, dataPoints);

    return dataPoints;
}

void ClusterDetector::convertNonPiledUpEntities(const vector<Entity> &entities, vector<shared_ptr<DataPoint> > &dataPoints) {
    for (const Entity &entity : entities) {
        dataPoints.push_back(shared_ptr<DataPoint>(new Entity(entity)));
    }
}

void ClusterDetector::convertPiledUpEntities(const vector<Entity> &entities, vector<shared_ptr<DataPoint> > &dataPoints) {
    for (const Entity &entity : entities) {
        int nrOfPiledUpEntities = entity.getPileUpDegree();

        // Consider only the above entities (at level 2+)
        for (int i = 1; i < nrOfPiledUpEntities; i++) {
            dataPoints.push_back(shared_ptr<DataPoint>(new Entity(entity)));
        }
    }
}

void ClusterDetector::addEntitiesToClusters(const vector<Entity> &entities, const vector<int> &clusterIndexes,
                                            int nrOfClusters, vector<Cluster> &clusters) {
    int nrOfEntities = entities.size();

    clusters.resize(nrOfClusters);

    for (int i = 0; i < nrOfEntities; i++) {
        clusters[clusterIndexes[i]].addEntity(entities[i]);
    }
}

void ClusterDetector::analyseClusters(vector<Cluster> &clusters) {
    analyseClustersOriginDependentValues(clusters);

    clusterednessIndex = computeClusterednessIndex(clusters);
    avgPileUpDegree = computeAveragePileUpDegree(clusters);
}

void ClusterDetector::analyseClustersOriginDependentValues(vector<Cluster> &clusters) {
    for (Cluster &cluster : clusters) {
        vector<Point> convexHull = getClusterConvexHull(cluster);

        if (convexHull.size() > 0) {
            updateClusterOriginDependentValues(cluster, convexHull);
        }
    }
}

void ClusterDetector::updateClusterOriginDependentValues(Cluster &cluster, const vector<Point> &clusterConvexHull) {
    unsigned int minDistancePointIndex = Geometry2D::minimumDistancePointIndex(clusterConvexHull, origin);

    double distance = Geometry2D::distanceBtwPoints(clusterConvexHull[minDistancePointIndex], origin);
    double angle = polygonAngle(clusterConvexHull, minDistancePointIndex);

    cluster.setOriginDependentMembers(distance, angle);
}

vector<Point> ClusterDetector::getClusterConvexHull(Cluster &cluster) {
    vector<Point> clusterConvexHull;

    vector<Point2f> entitiesConvexHull = cluster.getEntitiesConvexHull();

    Mat(entitiesConvexHull).copyTo(clusterConvexHull);

    return clusterConvexHull;
}

double ClusterDetector::computeClusterednessIndex(const vector<Cluster> &clusters) {
    return Silhouette::computeOverallAverageMeasure(clusters);
}

double ClusterDetector::computeAveragePileUpDegree(vector<Cluster> &clusters) {
    double averagePileUpDegree = 0;

    for (Cluster &cluster : clusters) {
        averagePileUpDegree += cluster.getPileUpDegree();
    }

    unsigned int nrOfClusters = (clusters[0].getEntities().size() == 0)
                                    ? (clusters.size() - 1)
                                    : clusters.size();

    return (nrOfClusters == 0) ? 0
                               : (averagePileUpDegree / nrOfClusters);
}

void ClusterDetector::outputResultsToCsvFile(ofstream &fout) {
    fout << Cluster::fieldNamesToString() << endl;

    for (Cluster &cluster : clusters) {
        fout << cluster.toString() << endl;
    }

    // Add an empty line between the cluster data and the averaged data
    fout << endl;

    fout << OUTPUT_CLUSTEREDNESS << clusterednessIndex << endl
         << OUTPUT_PILE_UP << avgPileUpDegree << endl;
}

double ClusterDetector::convertEpsValue() {
    return NumericRangeManipulator::convertFromRange<int, double>(EPS_MIN, EPS_MAX, EPS_REAL_MIN, EPS_REAL_MAX, eps);
}

int ClusterDetector::getValidMinPointsValue() {
    return (minPoints > 0) ? minPoints
                           : 1;
}
