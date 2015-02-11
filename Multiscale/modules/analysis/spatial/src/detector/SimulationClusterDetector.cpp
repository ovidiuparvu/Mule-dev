#include "multiscale/analysis/spatial/detector/SimulationClusterDetector.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/RGBColourGenerator.hpp"

#include <iostream>

using namespace multiscale::analysis;


SimulationClusterDetector::SimulationClusterDetector(
    unsigned int height, unsigned int width,
    unsigned int maxPileupNumber, bool isDebugMode
) : ClusterDetector(maxPileupNumber, isDebugMode) {
    this->height = height;
    this->width = width;

    this->entityHeight = 0;
    this->entityWidth = 0;
}

SimulationClusterDetector::~SimulationClusterDetector() {}

void SimulationClusterDetector::initialiseDetectorSpecificImageDependentFields() {
    this->entityHeight = Numeric::division(
                             static_cast<double>(image.rows),
                             static_cast<double>(height)
                         );
    this->entityWidth = Numeric::division(
                            static_cast<double>(image.cols),
                            static_cast<double>(width)
                        );

    initialiseThresholdedImage();
}

void SimulationClusterDetector::initialiseThresholdedImage() {
    cv::threshold(image, thresholdedImage, THRESHOLD, THRESHOLD_MAX, cv::THRESH_BINARY);
}

void SimulationClusterDetector::detectEntitiesInImage(std::vector<Entity> &entities) {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            if (isEntityAtPosition(j, i)) {
                double pileUpDegree = computePileUpDegreeAtPosition(j, i);
                double area         = entityHeight * entityWidth;
                double perimeter    = 2 * (entityHeight + entityWidth);
                cv::Point2f centre  = computeEntityCentrePoint(j, i);

                std::vector<cv::Point2f> contourPoints = computeEntityContourPoints(j, i);

                entities.push_back(
                    Entity(
                        pileUpDegree,
                        area,
                        perimeter,
                        centre,
                        contourPoints
                    )
                );
            }
        }
    }
}

bool SimulationClusterDetector::isEntityAtPosition(int x, int y) {
    cv::Rect mask(x * entityWidth, y * entityHeight, entityWidth, entityHeight);

    cv::Scalar positionMean = cv::mean(thresholdedImage(mask));

    return (positionMean.val[0] > ENTITY_THRESH);
}

cv::Point2f SimulationClusterDetector::computeEntityCentrePoint(int x, int y) {
    double xCentre = (static_cast<double>(x) * entityWidth) + (entityWidth / 2.0) - (0.5);
    double yCentre = (static_cast<double>(y) * entityHeight) + (entityHeight / 2.0) - (0.5);

    return cv::Point2f(xCentre, yCentre);
}

std::vector<cv::Point2f> SimulationClusterDetector::computeEntityContourPoints(int x, int y) {
    std::vector<cv::Point2f> contourPoints;

    for (int i = x; i < (x + 2); i++) {
        for (int j = y; j < (y + 2); j++) {
            contourPoints.push_back(
                cv::Point2f(
                    (i * entityWidth) - (0.5),
                    (j * entityHeight) - (0.5)
                )
            );
        }
    }

    return contourPoints;
}

double SimulationClusterDetector::computePileUpDegreeAtPosition(int x, int y) {
    int xCoordinate = static_cast<int>((x * entityWidth) + (entityWidth / 2));
    int yCoordinate = static_cast<int>((y * entityHeight) + (entityHeight / 2));

    float intensityAtPosition = image.at<float>(cv::Point(xCoordinate, yCoordinate));

    unsigned int nrOfPiledUpEntities = static_cast<unsigned int>(
                                           std::round(
                                               Numeric::division(
                                                   intensityAtPosition,
                                                   singleEntityIntensity
                                               )
                                           )
                                        );

    return (
        Numeric::division(
            static_cast<double>(nrOfPiledUpEntities),
            maxPileupNumber
        )
    );
}

void SimulationClusterDetector::outputResultsToImage() {
    cv::RNG randomNumberGenerator;

    // Convert the floating point initial image to a unsigned char output image
    image.convertTo(outputImage, CV_8UC1);

    // Convert the temporary grayscale output image to coloured
    cvtColor(outputImage, outputImage, CV_GRAY2BGR);

    unsigned int nrOfClusters = clusters.size();

    for (unsigned int i = 0; i < nrOfClusters; i++) {
        // Choose a random colour for the cluster
        cv::Scalar colour = RGBColourGenerator().generate(randomNumberGenerator);

        outputClusterToImage(clusters[i], colour, outputImage);
    }
}

void SimulationClusterDetector::outputClusterToImage(Cluster &cluster, cv::Scalar colour, cv::Mat &image) {
    std::vector<Entity> entities = cluster.getEntities();

    for (const Entity &entity : entities) {
        cv::circle(image, entity.getCentre(), DATAPOINT_WIDTH, colour, DATAPOINT_THICKNESS);
    }

    outputClusterShape(cluster, colour, image);
}

void SimulationClusterDetector::outputClusterShape(Cluster &cluster, cv::Scalar colour, cv::Mat &image) {
    Shape2D shape = cluster.getShape();

    switch (shape) {
    case Shape2D::Triangle:
        outputClusterTriangularShape(cluster, colour, image);
        break;

    case Shape2D::Rectangle:
        outputClusterRectangularShape(cluster, colour, image);
        break;

    case Shape2D::Circle:
        outputClusterCircularShape(cluster, colour, image);
        break;

    default:
        MS_throw(UnexpectedBehaviourException, Cluster::ERR_UNDEFINED_SHAPE);
        break;
    }
}

void SimulationClusterDetector::outputClusterTriangularShape(Cluster &cluster, cv::Scalar colour, cv::Mat &image) {
    std::vector<cv::Point2f> trianglePoints = cluster.getMinAreaEnclosingTriangle();

    assert(trianglePoints.size() == 3);

    for (int i = 0; i < 3; i++) {
        cv::line(image, trianglePoints[i], trianglePoints[(i + 1) % 3], colour, DATAPOINT_WIDTH);
    }
}

void SimulationClusterDetector::outputClusterRectangularShape(Cluster &cluster, cv::Scalar colour, cv::Mat &image) {
    cv::Point2f rectanglePoints[4];

    cluster.getMinAreaEnclosingRect().points(rectanglePoints);

    for (int i = 0; i < 4; i++) {
        cv::line(image, rectanglePoints[i], rectanglePoints[(i + 1) % 4], colour, DATAPOINT_WIDTH);
    }
}

void SimulationClusterDetector::outputClusterCircularShape(Cluster &cluster, cv::Scalar colour, cv::Mat &image) {
    cv::Point2f centre = cluster.getMinAreaEnclosingCircleCentre();
    float radius = cluster.getMinAreaEnclosingCircleRadius();

    cv::circle(image, centre, radius, colour, DATAPOINT_WIDTH);
}


// Constants
const int SimulationClusterDetector::THRESHOLD           = 1;
const int SimulationClusterDetector::THRESHOLD_MAX       = 255;

const int SimulationClusterDetector::ENTITY_THRESH       = 200;

const int SimulationClusterDetector::DATAPOINT_WIDTH     = 1;
const int SimulationClusterDetector::DATAPOINT_THICKNESS = -1;
