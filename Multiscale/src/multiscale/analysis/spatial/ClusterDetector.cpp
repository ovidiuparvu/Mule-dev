#include "multiscale/analysis/spatial/ClusterDetector.hpp"
#include "multiscale/analysis/spatial/DBSCAN.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"
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
    initialiseClusteringValues();
    detectClusters();
}

void ClusterDetector::initialise() {
    clusterednessIndex = 0;
    avgPileUpDegree = 0;
}

void ClusterDetector::initialiseClusteringValues() {
    eps = 5000;
    minPoints = 2;
}

bool ClusterDetector::isValidImage() {
    return ((image.type() == CV_8UC1) && (image.dims == 2) && (image.rows > 1) && (image.cols > 1));
}

void ClusterDetector::createTrackbars() {
    namedWindow( WIN_OUTPUT_IMAGE, WINDOW_NORMAL);
    setWindowProperty( WIN_OUTPUT_IMAGE, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN );

    createTrackbar(TRACKBAR_MINPOINTS, WIN_OUTPUT_IMAGE, &minPoints, MIN_POINTS_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_EPS, WIN_OUTPUT_IMAGE, &eps, EPS_MAX, nullptr, nullptr);
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

        processPressedKeyRequest(pressedKey);
    }

    outputClusters(clusters, !debugMode);
}

void ClusterDetector::detectClustersInNormalMode(vector<Cluster> &clusters) {
    findClusters(clusters);
    outputClusters(clusters, debugMode);
}

void ClusterDetector::findClusters(vector<Cluster> &clusters) {
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
    DBSCAN::run(convertEntities(entities), clusterIndexes, nrOfClusters, convertEpsValue(), minPoints);
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

void ClusterDetector::outputClusters(vector<Cluster> & clusters, bool debugMode) {
    if (debugMode) {
        outputClustersInDebugMode(clusters);
    } else {
        outputClustersAsCsvFile(clusters);
    }
}

void ClusterDetector::outputClustersAsCsvFile(vector<Cluster> &clusters) {
    ofstream fout(outputFilepath + OUTPUT_EXTENSION, ios_base::trunc);

    if (!fout.is_open())
        throw ERR_OUTPUT_FILE;

    outputClustersAsCsvFile(clusters, fout);

    fout.close();
}

void ClusterDetector::outputClustersAsCsvFile(vector<Cluster> &clusters, ofstream &fout) {
    for (Cluster &cluster : clusters) {
        fout << cluster.toString() << endl;
    }

    fout << endl;

    fout << OUTPUT_CLUSTEREDNESS << clusterednessIndex
         << OUTPUT_PILE_UP << avgPileUpDegree
         << endl;
}

void ClusterDetector::processPressedKeyRequest(char &pressedKey) {
    pressedKey = waitKey(1);

    if (pressedKey == KEY_SAVE) {
        processSaveRequest();
    }
}

void ClusterDetector::displayImage(const Mat& image, const string &windowName) {
    namedWindow( windowName, WINDOW_NORMAL );
    imshow( windowName, image );
}

double ClusterDetector::convertEpsValue() {
    return NumericRangeManipulator::convertFromRange<int, double>(EPS_MIN, EPS_MAX, EPS_REAL_MIN, EPS_REAL_MAX, eps);
}
