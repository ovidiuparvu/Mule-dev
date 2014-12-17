#include "multiscale/analysis/spatial/util/DBSCAN.hpp"

#include <limits>
#include <cassert>

using namespace multiscale::analysis;


DBSCAN::DBSCAN() : eps(0), minPoints(0), nrOfDataPoints(0) {}

DBSCAN::~DBSCAN() {
    distancesMatrix.clear();
    neighboursIndicesMatrix.clear();
}

void DBSCAN::run(const std::vector<std::shared_ptr<DataPoint>> &dataPoints,
                 std::vector<int> &clusterIndexes, int &nrOfClusters,
                 double eps, int minPoints) {
    this->eps       = eps;
    this->minPoints = minPoints;

    nrOfDataPoints  = dataPoints.size();

    constructDistancesMatrix(dataPoints);
    constructNeighboursIndicesMatrix(dataPoints);

    runAlgorithm(dataPoints, clusterIndexes, nrOfClusters);
}

void DBSCAN::runAlgorithm(const std::vector<std::shared_ptr<DataPoint>> &dataPoints,
                          std::vector<int> &clusterIndexes, int &nrOfClusters) {
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

void DBSCAN::constructDistancesMatrix(
    const std::vector<std::shared_ptr<DataPoint>> &dataPoints
) {
    allocateDistancesMatrix();

    for (unsigned int i = 0; i < nrOfDataPoints; i++) {
        for (unsigned int j = 0; j < i; j++) {
            distancesMatrix[i][j] = dataPoints[i]->distanceTo(dataPoints[j]);
            distancesMatrix[j][i] = distancesMatrix[i][j];
        }
    }
}

void DBSCAN::constructNeighboursIndicesMatrix(
    const std::vector<std::shared_ptr<DataPoint>> &dataPoints
) {
    allocateNeighboursIndicesMatrix();

    for (unsigned int i = 0; i < nrOfDataPoints; i++) {
        for (unsigned int j = 0; j <= i; j++) {
            if (distancesMatrix[i][j] < eps) {
                neighboursIndicesMatrix[i].push_back(j);
                neighboursIndicesMatrix[j].push_back(i);
            }
        }
    }
}

bool DBSCAN::expandCoreCluster(std::vector<int> &clusterIndexes, int coreDataPointIndex, int clusterId) {
    std::vector<int> seeds = retrieveNeighbours(coreDataPointIndex);

    if (seeds.size() < minPoints) {
        // Mark data point as noise
        clusterIndexes[coreDataPointIndex] = CLUSTERING_NOISE;

        return false;
    } else {
        std::vector<bool> consideredSeeds = std::vector<bool>(nrOfDataPoints, false);

        // Process the collection of seeds
        processSeeds(
            clusterIndexes,
            clusterId,
            seeds,
            consideredSeeds
        );

        return true;
    }
}

void DBSCAN::processSeeds(std::vector<int> &clusterIndexes, int clusterId,
                          std::vector<int> &seeds, std::vector<bool> &consideredSeeds) {
    std::size_t currentSeedIndex = 0;

    while (currentSeedIndex < seeds.size()) {
        std::vector<int> neighbours = retrieveNeighbours(seeds[currentSeedIndex]);

        if (neighbours.size() >= minPoints) {
            // Assign data point to cluster identified by clusterId
            clusterIndexes[seeds[currentSeedIndex]] = clusterId;

            addUnclassifiedNodesToSeedsList(neighbours, clusterIndexes, seeds, consideredSeeds);
            labelUnclassifiedAndNoiseAsBorder(neighbours, clusterIndexes);
        }

        // Update the list of visited seeds
        consideredSeeds[seeds[currentSeedIndex]] = true;

        currentSeedIndex++;
    }
}

void DBSCAN::addUnclassifiedNodesToSeedsList(const std::vector<int> &neighbours,
                                             const std::vector<int> &clusterIndexes,
                                             std::vector<int> &seeds,
                                             std::vector<bool> &consideredSeeds) {
    for (auto neighbour : neighbours) {
        if (clusterIndexes[neighbour] == CLUSTERING_UNCLASSIFIED) {
            if (consideredSeeds[neighbour] == false) {
                seeds.push_back(neighbour);

                consideredSeeds[neighbour] = true;
            }
        }
    }
}

void DBSCAN::labelUnclassifiedAndNoiseAsBorder(const std::vector<int> &neighbours,
                                               std::vector<int> &clusterIndexes) {
    for (int neighbour : neighbours) {
        if ((clusterIndexes[neighbour] == CLUSTERING_UNCLASSIFIED) ||
            (clusterIndexes[neighbour] == CLUSTERING_NOISE)) {
            clusterIndexes[neighbour] = CLUSTERING_BORDER;
        }
    }
}

std::vector<int> DBSCAN::retrieveNeighbours(int dataPointIndex) {
    return (
        neighboursIndicesMatrix[dataPointIndex]
    );
}

void DBSCAN::assignBorderNodesToClusters(std::vector<int> &clusterIndexes) {
    for (unsigned int i = 0; i < nrOfDataPoints; i++) {
        if (clusterIndexes[i] == CLUSTERING_BORDER) {
            int closestCoreDataPoint = findClosestCoreDataPoint(i, clusterIndexes);

            clusterIndexes[i] = clusterIndexes[closestCoreDataPoint];
        }
    }
}

int DBSCAN::findClosestCoreDataPoint(int borderDataPointIndex,
                                     const std::vector<int> &clusterIndexes) {
    std::vector<int> neighbours = retrieveNeighbours(borderDataPointIndex);

    double  minDistance      = std::numeric_limits<double>::max();
    int     minDistanceIndex = -1;

    for (auto neighbourIndex : neighbours) {
        // Check if the neighbour is a core data point
        if (clusterIndexes[neighbourIndex] > 0) {
            if (distancesMatrix[borderDataPointIndex][neighbourIndex] < minDistance) {
                minDistance = distancesMatrix[borderDataPointIndex][neighbourIndex];
                minDistanceIndex = neighbourIndex;
            }
        }
    }

    return minDistanceIndex;
}

void DBSCAN::allocateDistancesMatrix() {
    distancesMatrix.clear();

    for (unsigned int i = 0; i < nrOfDataPoints; i++) {
        distancesMatrix.push_back(std::vector<double>(nrOfDataPoints, 0));
    }
}

void DBSCAN::allocateNeighboursIndicesMatrix() {
    neighboursIndicesMatrix.clear();

    for (unsigned int i = 0; i < nrOfDataPoints; i++) {
        neighboursIndicesMatrix.push_back(std::vector<int>());
    }
}


// Constants
const int DBSCAN::CLUSTERING_UNCLASSIFIED = -2;
const int DBSCAN::CLUSTERING_BORDER       = -1;
const int DBSCAN::CLUSTERING_NOISE        = 0;
