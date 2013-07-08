#include "multiscale/analysis/spatial/cluster/SimulationClusterDetector.hpp"
#include "multiscale/util/RGBColourGenerator.hpp"

#include <iostream>

using namespace multiscale::analysis;


SimulationClusterDetector::SimulationClusterDetector(const Mat &inputImage, const string &outputFilepath,
                                                     unsigned int height, unsigned int width, bool debugMode)
                                                    : ClusterDetector(inputImage, outputFilepath, debugMode) {
    this->height = height;
    this->width = width;

    this->entityHeight = inputImage.rows / height;
    this->entityWidth = inputImage.cols / width;

    initialiseThresholdedImage();
}

SimulationClusterDetector::~SimulationClusterDetector() {}

void SimulationClusterDetector::initialiseThresholdedImage() {
    threshold(image, thresholdedImage, THRESHOLD, THRESHOLD_MAX, THRESH_BINARY);
}

void SimulationClusterDetector::detectEntitiesInImage(vector<Entity> &entities) {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            if (isEntityAtPosition(j, i)) {
                double pileUpDegree = computePileUpDegreeAtPosition(j, i);
                double area = entityHeight * entityWidth;

                double xCentre = (j * entityWidth) + (entityWidth / 2);
                double yCentre = (i * entityHeight) + (entityHeight / 2);

                Point centre(xCentre, yCentre);

                entities.push_back(Entity(pileUpDegree, area, centre));
            }
        }
    }
}

bool SimulationClusterDetector::isEntityAtPosition(int x, int y) {
    Rect mask(x * entityWidth, y * entityHeight, entityWidth, entityHeight);

    Scalar positionMean = mean(thresholdedImage(mask));

    return (positionMean.val[0] > ENTITY_THRESH);
}

double SimulationClusterDetector::computePileUpDegreeAtPosition(int x, int y) {
    Rect mask(x * entityWidth, y * entityHeight, entityWidth, entityHeight);

    Scalar positionMean = mean(image(mask));

    return positionMean.val[0];
}

void SimulationClusterDetector::outputClustersInDebugMode(vector<Cluster> &clusters) {
    RNG randomNumberGenerator;

    cvtColor(image, outputImage, CV_GRAY2RGB);

    unsigned int nrOfClusters = clusters.size();

    // Skipping the noise cluster which will be displayed as it already is in the original image
    for (unsigned int i = 1; i < nrOfClusters; i++) {
        // Choose a random colour for the cluster
        Scalar colour = RGBColourGenerator::generate(randomNumberGenerator);

        outputClusterInDebugMode(clusters[i], colour, outputImage);
    }

    displayImage(outputImage, WIN_OUTPUT_IMAGE);
}

void SimulationClusterDetector::outputClusterInDebugMode(Cluster &cluster, Scalar colour, Mat &image) {
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
        throw ERR_UNDEFINED_SHAPE;
        break;
    }
}

void SimulationClusterDetector::outputClusterTriangularShape(Cluster &cluster, Scalar colour, Mat &image) {
    vector<Point> trianglePoints = cluster.getMinAreaEnclosingTriangle();

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

void SimulationClusterDetector::processSaveRequest() {
    imwrite(outputFilepath + IMG_EXTENSION, outputImage);

    cout << MSG_IMG_SAVED << endl;
}
