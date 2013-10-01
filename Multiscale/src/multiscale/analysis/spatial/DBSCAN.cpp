#include "multiscale/analysis/spatial/DBSCAN.hpp"

#include <limits>
#include <cassert>

using namespace multiscale::analysis;


DBSCAN::DBSCAN() {}

DBSCAN::~DBSCAN() {
    distanceMatrix.clear();
}

void DBSCAN::run(const vector<shared_ptr<DataPoint>> &dataPoints, vector<int> &clusterIndexes, int &nrOfClusters, double eps,
                 int minPoints) {
    this->eps = eps;
    this->minPoints = minPoints;

    nrOfDataPoints = dataPoints.size();

    constructDistanceMatrix(dataPoints);
    runAlgorithm(dataPoints, clusterIndexes, nrOfClusters);
}

void DBSCAN::runAlgorithm(const vector<shared_ptr<DataPoint>> &dataPoints, vector<int> &clusterIndexes, int &nrOfClusters) {
    nrOfClusters = 1;

    // Mark all points as unclassified
    clusterIndexes.resize(nrOfDataPoints, CLUSTERING_UNCLASSIFIED);

    // Main part of improved DBSCAN algorithm
    for (unsigned int i = 0; i < nrOfDataPoints; i++) {
        if (clusterIndexes[i] == CLUSTERING_UNCLASSIFIED) {
            if (expandCoreCluster(clusterIndexes, i, nrOfClusters)) {
                nrOfClusters++;
            }
        }
    }

    assignBorderNodesToClusters(clusterIndexes);
}

void DBSCAN::constructDistanceMatrix(const vector<shared_ptr<DataPoint>> &dataPoints) {
    allocateDistanceMatrix();

    assert(distanceMatrix.size() == nrOfDataPoints);

    for (unsigned int i = 0; i < nrOfDataPoints; i++) {
        for (unsigned int j = 0; j < i; j++) {
            distanceMatrix[i][j] = dataPoints[i]->distanceTo(dataPoints[j]);
            distanceMatrix[j][i] = distanceMatrix[i][j];
        }
    }
}

bool DBSCAN::expandCoreCluster(vector<int> &clusterIndexes, int coreDataPointIndex, int clusterId) {
    vector<int> seeds = retrieveNeighbours(coreDataPointIndex);
    unsigned int currentSeedIndex = 0;

    if (seeds.size() < minPoints) {
        // Mark data point as noise
        clusterIndexes[coreDataPointIndex] = CLUSTERING_NOISE;

        return false;
    } else {
        while (currentSeedIndex < seeds.size()) {
            vector<int> neighbours = retrieveNeighbours(seeds[currentSeedIndex]);

            if (neighbours.size() >= minPoints) {
                // Assign data point to cluster identified by clusterId
                clusterIndexes[seeds[currentSeedIndex]] = clusterId;

                addUnclassifiedNodesToSeedsList(neighbours, clusterIndexes, seeds);
                labelUnclassifiedAndNoiseAsBorder(neighbours, clusterIndexes);
            }

            currentSeedIndex++;
        }

        return true;
    }
}

void DBSCAN::addUnclassifiedNodesToSeedsList(const vector<int> &neighbours, const vector<int> &clusterIndexes,
                                             vector<int> &seeds) {
    for (int neighbour : neighbours) {
        if (clusterIndexes[neighbour] == CLUSTERING_UNCLASSIFIED) {
            seeds.push_back(neighbour);
        }
    }
}

void DBSCAN::labelUnclassifiedAndNoiseAsBorder(const vector<int> &neighbours, vector<int> &clusterIndexes) {
    for (int neighbour : neighbours) {
        if ((clusterIndexes[neighbour] == CLUSTERING_UNCLASSIFIED) ||
            (clusterIndexes[neighbour] == CLUSTERING_NOISE)) {
            clusterIndexes[neighbour] = CLUSTERING_BORDER;
        }
    }
}

vector<int> DBSCAN::retrieveNeighbours(int dataPointIndex) {
    vector<double> dataPointDistancesToNeighbours = distanceMatrix[dataPointIndex];
    vector<int> neighbours;

    // Check for all neighbours including the point itself
    for (unsigned int i = 0; i < nrOfDataPoints; i++) {
        if (dataPointDistancesToNeighbours[i] < eps) {
            neighbours.push_back(i);
        }
    }

    return neighbours;
}

void DBSCAN::assignBorderNodesToClusters(vector<int> &clusterIndexes) {
    for (unsigned int i = 0; i < nrOfDataPoints; i++) {
        if (clusterIndexes[i] == CLUSTERING_BORDER) {
            vector<int> neighbours = retrieveNeighbours(i);
            int closestCoreDataPoint = findClosestCoreDataPoint(neighbours, i, clusterIndexes);

            clusterIndexes[i] = clusterIndexes[closestCoreDataPoint];
        }
    }
}

int DBSCAN::findClosestCoreDataPoint(const vector<int> &neighbours, int borderDataPointIndex,
                                     const vector<int> &clusterIndexes) {
    double minDistance = numeric_limits<double>::max();
    int minIndex = -1;

    int nrOfNeighbours = neighbours.size();

    for (int i = 0; i < nrOfNeighbours; i++) {
        // Check if the neighbour is a core data point
        if (clusterIndexes[neighbours[i]] > 0) {
            if (distanceMatrix[borderDataPointIndex][neighbours[i]] < minDistance) {
                minDistance = distanceMatrix[borderDataPointIndex][neighbours[i]];
                minIndex = i;
            }
        }
    }

    return neighbours[minIndex];
}

void DBSCAN::allocateDistanceMatrix() {
    distanceMatrix.clear();

    for (unsigned int i = 0; i < nrOfDataPoints; i++) {
        distanceMatrix.push_back(vector<double>(nrOfDataPoints, 0));
    }
}


// Constants
const int DBSCAN::CLUSTERING_UNCLASSIFIED = -2;
const int DBSCAN::CLUSTERING_BORDER       = -1;
const int DBSCAN::CLUSTERING_NOISE        = 0;
