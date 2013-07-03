#include "multiscale/analysis/spatial/DBSCAN.hpp"

using namespace multiscale::analysis;

void DBSCAN::run(const vector<DataPoint> &dataPoints, vector<int> clusterIndexes, int &nrOfClusters, double eps,
                 int minPoints) {
    DBSCAN::eps = eps;
    DBSCAN::minPoints = minPoints;

    constructDistanceMatrix(dataPoints);
    runAlgorithm(dataPoints, clusterIndexes, nrOfClusters);
}

void DBSCAN::runAlgorithm(const vector<DataPoint> &dataPoints, vector<int> clusterIndexes, int &nrOfClusters) {
    int clusterId = 1;
    int nrOfDataPoints = dataPoints.size();

    clusterIndexes.resize(nrOfDataPoints, CLUSTERING_UNCLASSIFIED);

    // Main part of improved DBSCAN algorithm
    for (int i = 0; i < nrOfEntities; i++) {
        if (clusterIndexes[i] == CLUSTERING_UNCLASSIFIED) {
            if (expandCoreCluster(dataPoints, clusterIndexes, nrOfClusters, i, clusterId)) {
                clusterId++;
            }
        }
    }

    assignBorderNodesToClusters(dataPoints, clusterIndexes);
}

void DBSCAN::constructDistanceMatrix(const vector<DataPoint> &dataPoints) {
    int nrOfDataPoints = dataPoints.size();

    allocateDistanceMatrix(nrOfDataPoints);

    for (int i = 0; i < nrOfDataPoints; i++) {
        for (int j = 0; j <= i; j++) {
            distanceMatrix[i][j] = dataPoints[i].distanceTo(dataPoints[j]);
            distanceMatrix[j][i] = distanceMatrix[i][j];
        }
    }
}

bool DBSCAN::expandCoreCluster(const vector<DataPoint> &dataPoints, vector<int> clusterIndexes,
                               int &nrOfClusters, int coreDataPointIndex, int clusterId) {
    vector<int> seeds = retrieveNeighbours(coreDataPointIndex, dataPoints);
    int currentSeedIndex = 0;

    if (seeds.size() < minPoints) {
        // Mark data point as noise
        clusterIndexes[coreDataPointIndex] = CLUSTERING_NOISE;

        return false;
    } else {
        while (currentSeedIndex < seeds.size()) {
            vector<int> neighbours = retrieveNeighbours(seed, dataPoints);

            if (neighbours.size() >= minPoints) {
                // Data point belongs to the same cluster as the given core data point
                clusterIndexes[seed] = clusterId;

                // TODO: Implement methods
                addUnclassifiedNodesToSeedsList(neighbours, clusterIndexes, seeds);
                labelUnclassifiedNoisyAsBorderNodes(neighbours, clusterIndexes);
            }

            currentSeedIndex++;
        }
    }
}
