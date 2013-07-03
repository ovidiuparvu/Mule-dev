#include "multiscale/analysis/spatial/ClusterDetector.hpp"
#include "multiscale/util/RGBColourGenerator.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace multiscale::analysis;


ClusterDetector::ClusterDetector(const Mat &inputImage, const string &outputFilepath, bool debugMode) {
    inputImage.copyTo(image);

    this->outputFilepath = outputFilepath;
    this->debugMode = debugMode;

    initialise();
}

ClusterDetector::~ClusterDetector() {
    image.release();
}

void ClusterDetector::detect() {
    if (!isValidImage())
        throw ERR_INVALID_IMAGE;

    // Initialise the value of eps and minPoints
    initialiseImageDependentMembers();
    detectClusters();
}

void ClusterDetector::initialise() {
    avgClusterednessDegree = 0;
    avgPileUpDegree = 0;

    eps = 0;
    minPoints = 0;
}

void ClusterDetector::detectClusters() {
    vector<Cluster> clusters;

    if (debugMode) {
        detectClustersInDebugMode(clusters);
    } else {
        detectClustersInNormalMode(clusters);
    }
}

void ClusterDetector::detectClustersInDebugMode(vector<Cluster> &clusters) {
    char pressedKey = -1;

    createTrackbars();

    while (pressedKey != KEY_ESC) {
        clusters.clear();

        findClusters(clusters);
        outputClusters(clusters, debugMode);

        pressedKey = waitKey(1);
    }

    outputClusters(regions, !debugMode);
}

void ClusterDetector::detectClustersInNormalMode(vector<Cluster> &clusters) {
    findClusters(clusters);
    outputClusters(clusters, debugMode);
}

void ClusterDetector::findClusters(vector<Cluster> &clusters) {
    vector<Entity> entities;

    detectEntitiesInImage(vector<Entity> &entities);
    detectAndAnalyseClusters(entities, clusters);
}

void ClusterDetector::detectAndAnalyseClusters(const vector<Entity> &entities, vector<Cluster> &clusters) {
    vector<int> clusterIndexes(entities.size(), CLUSTERING_UNCLASSIFIED);
    int nrOfClusters;

    detectClusters(entities, clusterIndexes, nrOfClusters);
    addEntitiesToClusters(entities, clusterIndexes, nrOfClusters, clusters);
    analyseClusters(entities, clusterIndexes, nrOfClusters, clusters);
}

void ClusterDetector::detectClusters(const vector<Entity> &entities, vector<int> &clusterIndexes, int &nrOfClusters) {

}

void ClusterDetector::addEntitiesToClusters(const vector<Entity> &entities, const vector<int> &clusterIndexes,
                                            int nrOfClusters, vector<Cluster> &clusters) {
    int nrOfEntities = entities.size();

    clusters.resize(nrOfClusters);

    for (int i = 0; i < nrOfEntities; i++) {
        clusters[clusterIndexes[i]].push_back(entities[i]);
    }
}

void ClusterDetector::outputClusters(const vector<Cluster> & clusters, bool debugMode) {
    if (debugMode) {
        outputClustersInDebugMode(clusters);
    } else {
        outputClustersAsCsvFile(clusters);
    }
}

void ClusterDetector::displayImage(const Mat& image, const string &windowName) {
    namedWindow( windowName, WINDOW_NORMAL );
    imshow( windowName, image );
}
