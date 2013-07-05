#include "multiscale/analysis/spatial/DBSCAN.hpp"

using namespace multiscale::analysis;


double DBSCAN::eps = 0;
unsigned int DBSCAN::minPoints = 0;
int DBSCAN::nrOfDataPoints = 0;
vector<vector<double>> DBSCAN::distanceMatrix;


void DBSCAN::run(const vector<shared_ptr<DataPoint>> &dataPoints, vector<int> clusterIndexes, int &nrOfClusters, double eps,
                 int minPoints) {
    eps = eps;
    minPoints = minPoints;

    nrOfDataPoints = dataPoints.size();

    constructDistanceMatrix(dataPoints);
    runAlgorithm(dataPoints, clusterIndexes, nrOfClusters);
}

void DBSCAN::runAlgorithm(const vector<shared_ptr<DataPoint>> &dataPoints, vector<int> clusterIndexes, int &nrOfClusters) {
    nrOfClusters = 1;

    clusterIndexes.resize(nrOfDataPoints, CLUSTERING_UNCLASSIFIED);

    // Main part of improved DBSCAN algorithm
    for (int i = 0; i < nrOfDataPoints; i++) {
        if (clusterIndexes[i] == CLUSTERING_UNCLASSIFIED) {
            if (expandCoreCluster(clusterIndexes, nrOfClusters, i, nrOfClusters)) {
                nrOfClusters++;
            }
        }
    }

    assignBorderNodesToClusters(clusterIndexes);
}

void DBSCAN::constructDistanceMatrix(const vector<shared_ptr<DataPoint>> &dataPoints) {
    allocateDistanceMatrix();

    for (int i = 0; i < nrOfDataPoints; i++) {
        for (int j = 0; j <= i; j++) {
            distanceMatrix[i][j] = dataPoints[i]->distanceTo(dataPoints[j]);
            distanceMatrix[j][i] = distanceMatrix[i][j];
        }
    }
}

bool DBSCAN::expandCoreCluster(vector<int> clusterIndexes, int &nrOfClusters, int coreDataPointIndex, int clusterId) {
    vector<int> seeds = retrieveNeighbours(coreDataPointIndex);
    unsigned int currentSeedIndex = 0;

    if (seeds.size() < minPoints) {
        // Mark data point as noise
        clusterIndexes[coreDataPointIndex] = CLUSTERING_NOISE;

        return false;
    } else {
        while (currentSeedIndex < seeds.size()) {
            vector<int> neighbours = retrieveNeighbours(currentSeedIndex);

            if (neighbours.size() >= minPoints) {
                // Data point belongs to the same cluster as the given core data point
                clusterIndexes[currentSeedIndex] = clusterId;

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

    for (int i = 0; i < nrOfDataPoints; i++) {
        if (dataPointDistancesToNeighbours[i] < eps) {
            neighbours.push_back(i);
        }
    }

    return neighbours;
}

void DBSCAN::assignBorderNodesToClusters(vector<int> &clusterIndexes) {
    for (int i = 0; i < nrOfDataPoints; i++) {
        if (clusterIndexes[i] == CLUSTERING_BORDER) {
            vector<int> neighbours = retrieveNeighbours(i);
            int closestCoreDataPoint = findClosestCoreDataPoint(neighbours, i);

            clusterIndexes[i] = clusterIndexes[closestCoreDataPoint];
        }
    }
}

int DBSCAN::findClosestCoreDataPoint(const vector<int> &neighbours, int borderDataPointIndex) {
    double minDistance = distanceMatrix[borderDataPointIndex][neighbours[0]];
    int minIndex = 0;

    int nrOfNeighbours = neighbours.size();

    for (int i = 1; i < nrOfNeighbours; i++) {
        if (distanceMatrix[borderDataPointIndex][neighbours[i]] < minDistance) {
            minDistance = distanceMatrix[borderDataPointIndex][neighbours[i]];
            minIndex = i;
        }
    }

    return neighbours[minIndex];
}

void DBSCAN::allocateDistanceMatrix() {
    distanceMatrix.resize(nrOfDataPoints);

    for (int i = 0; i < nrOfDataPoints; i++) {
        distanceMatrix.push_back(vector<double>(nrOfDataPoints, 0));
    }
}
