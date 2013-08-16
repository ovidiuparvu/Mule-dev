#include "multiscale/analysis/spatial/Silhouette.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <algorithm>
#include <limits>

using namespace multiscale;
using namespace multiscale::analysis;


double Silhouette::computeOverallAverageMeasure(const vector<Cluster> &clusters) {
    assert(clusters.size() > 0);

    double sumOfMeasures = 0;
    unsigned int nrOfClusters = clusters.size();

    // Ignore the noise cluster (i = 1)
    for (unsigned int i = 1; i < nrOfClusters; i++) {
        sumOfMeasures += computeAverageMeasure(i, clusters);
    }

    return (nrOfClusters != 0) ? (sumOfMeasures / nrOfClusters)
                               : 0;
}

double Silhouette::computeAverageMeasure(unsigned int clusterIndex, const vector<Cluster> &clusters) {
    assert((clusterIndex > 0) && (clusterIndex < clusters.size()));

    double sumOfMeasures = 0;

    vector<Entity> entities = clusters[clusterIndex].getEntities();
    unsigned int nrOfEntities = entities.size();

    for (unsigned int i = 0; i < nrOfEntities; i++) {
        sumOfMeasures += computeMeasure(i, clusterIndex, clusters);
    }

    return (nrOfEntities != 0) ? (sumOfMeasures / nrOfEntities)
                               : 0;
}

double Silhouette::computeMeasure(unsigned int entityIndex, unsigned int clusterIndex, const vector<Cluster> &clusters) {
    assert((clusterIndex > 0) && (clusterIndex < clusters.size()) && (entityIndex < clusters[clusterIndex].getEntities().size()));

    double a = computeAverageDissimilarityWithinCluster(entityIndex, clusterIndex, clusters);
    double b = computeAverageDissimilarityToOtherClusters(entityIndex, clusterIndex, clusters);

    return ((a != 0) || (b != 0)) ? (b - a) / (max(a, b))
                                  : 1;
}

double Silhouette::computeAverageDissimilarityWithinCluster(unsigned int entityIndex, unsigned int clusterIndex, const vector<Cluster> &clusters) {
    double sumOfDistances = 0;

    vector<Entity> entities = clusters[clusterIndex].getEntities();
    unsigned int nrOfEntities = entities.size();

    for (unsigned int i = 0; i < nrOfEntities; i++) {
        sumOfDistances += Geometry2D::distanceBtwPoints(entities[entityIndex].getCentre(), entities[i].getCentre());
    }

    return (nrOfEntities != 0) ? (sumOfDistances / nrOfEntities)
                               : 0;
}

double Silhouette::computeAverageDissimilarityToOtherClusters(unsigned int entityIndex, unsigned int clusterIndex, const vector<Cluster> &clusters) {
    double minimumDistance = numeric_limits<double>::max();
    unsigned int nrOfClusters = clusters.size();

    // Ignore the noise cluster (i = 1)
    for (unsigned int i = 1; i < nrOfClusters; i++) {
        if (i != clusterIndex) {
            double distanceToCluster = computeAverageDissimilarityBtwEntityAndCluster(entityIndex, clusterIndex, i, clusters);

            if (distanceToCluster < minimumDistance) {
                minimumDistance = distanceToCluster;
            }
        }
    }

    return minimumDistance;
}

double Silhouette::computeAverageDissimilarityBtwEntityAndCluster(unsigned int entityIndex, unsigned int entityClusterIndex,
                                                                  unsigned int clusterIndex, const vector<Cluster> &clusters) {
    double sumOfDissimilarities = 0;

    Point2f entityCentrePoint = (clusters[entityClusterIndex].getEntities())[entityIndex].getCentre();
    vector<Entity> entities = clusters[clusterIndex].getEntities();
    unsigned int nrOfEntities = entities.size();

    for (unsigned int i = 0; i < nrOfEntities; i++) {
        sumOfDissimilarities += Geometry2D::distanceBtwPoints(entityCentrePoint, entities[i].getCentre());
    }

    return (nrOfEntities != 0) ? (sumOfDissimilarities / nrOfEntities)
                               : 0;
}

