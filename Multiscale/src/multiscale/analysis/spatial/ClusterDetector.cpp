#include "multiscale/analysis/spatial/ClusterDetector.hpp"
#include "multiscale/analysis/spatial/DBSCAN.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"
#include "multiscale/util/RGBColourGenerator.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace multiscale::analysis;


ClusterDetector::ClusterDetector(bool debugMode) : Detector(debugMode) {
    this->eps = 0;
    this->minPoints = 0;

    this->avgPileUpDegree = 0;
    this->clusterednessIndex = 0;
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
    if (!detectorSpecificFieldsInitialised) {
        detectorSpecificFieldsInitialised = true;
    }

    this->eps = NumericRangeManipulator::convertFromRange<double, int>(EPS_REAL_MIN, EPS_REAL_MAX, EPS_MIN, EPS_MAX, eps);
}

void ClusterDetector::setMinPoints(int minPoints) {
    if (!detectorSpecificFieldsInitialised) {
        detectorSpecificFieldsInitialised = true;
    }

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

    for (const Entity &entity : entities) {
        dataPoints.push_back(shared_ptr<DataPoint>(new Entity(entity)));
    }

    return dataPoints;
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
    clusterednessIndex = computeClusterednessIndex(clusters);
    avgPileUpDegree = computeAveragePileUpDegree(clusters);
}

double ClusterDetector::computeClusterednessIndex(const vector<Cluster> &clusters) {
    // TODO: Unimplemented method
    return 1.5;
}

double ClusterDetector::computeAveragePileUpDegree(vector<Cluster> &clusters) {
    double averagePileUpDegree = 0;

    for (Cluster &cluster : clusters) {
        averagePileUpDegree += cluster.getPileUpDegree();
    }

    return (clusters.size() == 0) ? 0
                                  : (averagePileUpDegree / clusters.size());
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
