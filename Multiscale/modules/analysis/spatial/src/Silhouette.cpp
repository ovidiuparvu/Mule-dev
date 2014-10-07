#include "multiscale/analysis/spatial/Silhouette.hpp"
#include "multiscale/exception/IndexOutOfBoundsException.hpp"
#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <algorithm>
#include <limits>

using namespace multiscale;
using namespace multiscale::analysis;


double Silhouette::computeOverallAverageMeasure(const std::vector<Cluster> &clusters) {
    double sumOfMeasures = 0;
    std::size_t nrOfClusters = clusters.size();

    for (std::size_t i = 0; i < nrOfClusters; i++) {
        sumOfMeasures += computeAverageMeasure(i, clusters);
    }

    return (nrOfClusters != 0) ? (sumOfMeasures / nrOfClusters)
                               : 0;
}

double Silhouette::computeAverageMeasure(std::size_t clusterIndex, const std::vector<Cluster> &clusters) {
    validateClusterIndex(clusterIndex, clusters.size());

    double sumOfMeasures = 0;

    std::vector<Entity> entities = clusters[clusterIndex].getEntities();
    std::size_t nrOfEntities = entities.size();

    for (std::size_t i = 0; i < nrOfEntities; i++) {
        sumOfMeasures += computeMeasure(i, clusterIndex, clusters);
    }

    return (nrOfEntities != 0) ? (sumOfMeasures / nrOfEntities)
                               : 0;
}

double Silhouette::computeMeasure(std::size_t entityIndex, std::size_t clusterIndex,
                                  const std::vector<Cluster> &clusters) {
    validateClusterIndex(clusterIndex, clusters.size());
    validateEntityIndex(entityIndex, clusters[clusterIndex].getEntities().size());

    double a = computeAverageDissimilarityWithinCluster(entityIndex, clusterIndex, clusters);
    double b = computeAverageDissimilarityToOtherClusters(entityIndex, clusterIndex, clusters);

    return (
        (Numeric::almostEqual(a, 0) &&
         Numeric::almostEqual(b, 0))
             ? 0
             : (b - a) / (std::max(a, b))
     );
}

double Silhouette::computeAverageDissimilarityWithinCluster(std::size_t entityIndex, std::size_t clusterIndex,
                                                            const std::vector<Cluster> &clusters) {
    double sumOfDistances = 0;

    std::vector<Entity> entities = clusters[clusterIndex].getEntities();
    std::size_t nrOfEntities = entities.size();

    for (std::size_t i = 0; i < nrOfEntities; i++) {
        sumOfDistances += Geometry2D::distanceBtwPoints(
                              entities[entityIndex].getCentre(),
                              entities[i].getCentre()
                          );
    }

    return (nrOfEntities != 0) ? (sumOfDistances / nrOfEntities)
                               : 0;
}

double Silhouette::computeAverageDissimilarityToOtherClusters(std::size_t entityIndex, std::size_t clusterIndex,
                                                              const std::vector<Cluster> &clusters) {
    double minimumDistance = std::numeric_limits<double>::max();
    std::size_t nrOfClusters = clusters.size();

    for (std::size_t i = 0; i < nrOfClusters; i++) {
        if (i != clusterIndex) {
            double distanceToCluster = computeAverageDissimilarityBtwEntityAndCluster(
                                           entityIndex, clusterIndex, i, clusters
                                       );

            if (distanceToCluster < minimumDistance) {
                minimumDistance = distanceToCluster;
            }
        }
    }

    return minimumDistance;
}

double Silhouette::computeAverageDissimilarityBtwEntityAndCluster(std::size_t entityIndex,
                                                                  std::size_t entityClusterIndex,
                                                                  std::size_t clusterIndex,
                                                                  const std::vector<Cluster> &clusters) {
    double sumOfDissimilarities = 0;

    cv::Point2f entityCentrePoint = (clusters[entityClusterIndex].getEntities())[entityIndex].getCentre();
    std::vector<Entity> entities = clusters[clusterIndex].getEntities();
    std::size_t nrOfEntities = entities.size();

    for (std::size_t i = 0; i < nrOfEntities; i++) {
        sumOfDissimilarities += Geometry2D::distanceBtwPoints(entityCentrePoint, entities[i].getCentre());
    }

    return (nrOfEntities != 0) ? (sumOfDissimilarities / nrOfEntities)
                               : 0;
}

void Silhouette::validateClusterIndex(std::size_t clusterIndex, std::size_t totalNrOfClusters) {
    return validateElementIndex(clusterIndex, totalNrOfClusters);
}

void Silhouette::validateEntityIndex(std::size_t entityIndex, std::size_t totalNrOfEntities) {
    return validateElementIndex(entityIndex, totalNrOfEntities);
}

void Silhouette::validateElementIndex(std::size_t elementIndex, std::size_t totalNrOfElements) {
    if ((elementIndex < 0) || (elementIndex >= totalNrOfElements)) {
        MS_throw(IndexOutOfBoundsException, StringManipulator::toString<std::size_t>(elementIndex));
    }
}
