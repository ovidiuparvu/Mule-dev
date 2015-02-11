#include "multiscale/analysis/spatial/util/Silhouette.hpp"
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

    return (Numeric::division(sumOfMeasures, nrOfClusters));
}

double Silhouette::computeAverageMeasure(std::size_t clusterIndex, const std::vector<Cluster> &clusters) {
    validateClusterIndex(clusterIndex, clusters.size());

    double sumOfMeasures = 0;

    std::vector<Entity> entities = clusters[clusterIndex].getEntities();
    std::size_t nrOfEntities = entities.size();

    for (std::size_t i = 0; i < nrOfEntities; i++) {
        sumOfMeasures += computeMeasure(i, clusterIndex, clusters);
    }

    return (Numeric::division(sumOfMeasures, nrOfEntities));
}

double Silhouette::computeMeasure(std::size_t entityIndex, std::size_t clusterIndex,
                                  const std::vector<Cluster> &clusters) {
    validateClusterIndex(clusterIndex, clusters.size());
    validateEntityIndex(entityIndex, clusters[clusterIndex].getEntities().size());

    double a = computeAverageDissimilarityWithinCluster(entityIndex, clusterIndex, clusters);
    double b = computeAverageDissimilarityToOtherClusters(entityIndex, clusterIndex, clusters);

    return (
        Numeric::division(
            (b - a),
            std::max(a, b)
        )
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

    return (Numeric::division(sumOfDistances, nrOfEntities));
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

    return (Numeric::division(sumOfDissimilarities, nrOfEntities));
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
