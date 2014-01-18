#include "multiscale/analysis/spatial/cluster/SimulationClusterDetector.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/RGBColourGenerator.hpp"

#include <iostream>

using namespace multiscale::analysis;


SimulationClusterDetector::SimulationClusterDetector(unsigned int height, unsigned int width, int maxPileupNumber,
                                                     double maxPileupIntensity, bool debugMode)
                                                    : ClusterDetector(maxPileupNumber, maxPileupIntensity, debugMode) {
    this->height = height;
    this->width = width;

    this->entityHeight = 0;
    this->entityWidth = 0;
}

SimulationClusterDetector::~SimulationClusterDetector() {}

void SimulationClusterDetector::initialiseDetectorSpecificImageDependentFields() {
    this->entityHeight = ((double)image.rows) / height;
    this->entityWidth = ((double)image.cols) / width;

    initialiseThresholdedImage();
}

void SimulationClusterDetector::initialiseThresholdedImage() {
    threshold(image, thresholdedImage, THRESHOLD, THRESHOLD_MAX, THRESH_BINARY);
}

void SimulationClusterDetector::detectEntitiesInImage(vector<Entity> &entities) {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            if (isEntityAtPosition(j, i)) {
                unsigned int pileUpDegree = computePileUpDegreeAtPosition(j, i);
                double area = entityHeight * entityWidth;
                double perimeter = 2 * (entityHeight + entityWidth);
                Point2f centre = getEntityCentrePoint(j, i);
                vector<Point2f> contourPoints = getEntityContourPoints(j, i);

                entities.push_back(Entity(pileUpDegree, area, perimeter, centre, contourPoints));
            }
        }
    }
}

bool SimulationClusterDetector::isEntityAtPosition(int x, int y) {
    Rect mask(x * entityWidth, y * entityHeight, entityWidth, entityHeight);

    Scalar positionMean = mean(thresholdedImage(mask));

    return (positionMean.val[0] > ENTITY_THRESH);
}

Point2f SimulationClusterDetector::getEntityCentrePoint(int x, int y) {
    double xCentre = (x * entityWidth) + (entityWidth / 2);
    double yCentre = (y * entityHeight) + (entityHeight / 2);

    return Point2f(xCentre, yCentre);
}

vector<Point2f> SimulationClusterDetector::getEntityContourPoints(int x, int y) {
    vector<Point2f> contourPoints;

    for (int i = x; i < (x + 2); i++) {
        for (int j = y; j < (y + 2); j++) {
            contourPoints.push_back(Point(i * entityWidth, j * entityHeight));
        }
    }

    return contourPoints;
}

unsigned int SimulationClusterDetector::computePileUpDegreeAtPosition(int x, int y) {
    int xCoordinate = (x * entityWidth) + (entityWidth / 2);
    int yCoordinate = (y * entityHeight) + (entityHeight / 2);

    unsigned char intensityAtPosition = image.at<uchar>(Point(xCoordinate, yCoordinate));

    return static_cast<unsigned int>(round(intensityAtPosition / entityPileupDegree));
}

void SimulationClusterDetector::outputResultsToImage() {
    RNG randomNumberGenerator;

    cvtColor(image, outputImage, CV_GRAY2RGB);

    unsigned int nrOfClusters = clusters.size();

    for (unsigned int i = 0; i < nrOfClusters; i++) {
        // Choose a random colour for the cluster
        Scalar colour = RGBColourGenerator().generate(randomNumberGenerator);

        outputClusterToImage(clusters[i], colour, outputImage);
    }
}

void SimulationClusterDetector::outputClusterToImage(Cluster &cluster, Scalar colour, Mat &image) {
    vector<Entity> entities = cluster.getEntities();

    for (const Entity &entity : entities) {
        circle(image, entity.getCentre(), DATAPOINT_WIDTH, colour, DATAPOINT_THICKNESS);
    }

    outputClusterShape(cluster, colour, image);
}

void SimulationClusterDetector::outputClusterShape(Cluster &cluster, Scalar colour, Mat &image) {
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

void SimulationClusterDetector::outputClusterTriangularShape(Cluster &cluster, Scalar colour, Mat &image) {
    vector<Point2f> trianglePoints = cluster.getMinAreaEnclosingTriangle();

    assert(trianglePoints.size() == 3);

    for (int i = 0; i < 3; i++) {
        line(image, trianglePoints[i], trianglePoints[(i + 1) % 3], colour, DATAPOINT_WIDTH);
    }
}

void SimulationClusterDetector::outputClusterRectangularShape(Cluster &cluster, Scalar colour, Mat &image) {
    Point2f rectanglePoints[4];

    cluster.getMinAreaEnclosingRect().points(rectanglePoints);

    for (int i = 0; i < 4; i++) {
        line(image, rectanglePoints[i], rectanglePoints[(i + 1) % 4], colour, DATAPOINT_WIDTH);
    }
}

void SimulationClusterDetector::outputClusterCircularShape(Cluster &cluster, Scalar colour, Mat &image) {
    Point2f centre = cluster.getMinAreaEnclosingCircleCentre();
    float radius = cluster.getMinAreaEnclosingCircleRadius();

    circle(image, centre, radius, colour, DATAPOINT_WIDTH);
}


// Constants
const int SimulationClusterDetector::THRESHOLD           = 1;
const int SimulationClusterDetector::THRESHOLD_MAX       = 255;

const int SimulationClusterDetector::ENTITY_THRESH       = 200;

const int SimulationClusterDetector::DATAPOINT_WIDTH     = 10;
const int SimulationClusterDetector::DATAPOINT_THICKNESS = -1;
