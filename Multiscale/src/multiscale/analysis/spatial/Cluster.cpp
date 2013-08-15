#include "multiscale/analysis/spatial/CircularityMeasure.hpp"
#include "multiscale/analysis/spatial/Cluster.hpp"
#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/util/MinimumAreaEnclosingTriangle.hpp"
#include "multiscale/util/StringManipulator.hpp"

using namespace multiscale::analysis;


Cluster::Cluster() {
    initialise();
}

Cluster::~Cluster() {}

void Cluster::addEntity(const Entity &entity) {
    entities.push_back(entity);

    updateFlag = true;
}

double Cluster::getClusterednessDegree() {
    updateMeasuresIfRequired();

    return clusterednessDegree;
}

double Cluster::getPileUpDegree() {
    updateMeasuresIfRequired();

    return pileUpDegree;
}

vector<Point2f> Cluster::getMinAreaEnclosingTriangle() {
    updateMeasuresIfRequired();

    return minAreaEnclosingTriangle;
}

RotatedRect Cluster::getMinAreaEnclosingRect() {
    updateMeasuresIfRequired();

    return minAreaEnclosingRect;
}

Point2f Cluster::getMinAreaEnclosingCircleCentre() {
    updateMeasuresIfRequired();

    return minAreaEnclosingCircleCentre;
}

float Cluster::getMinAreaEnclosingCircleRadius() {
    updateMeasuresIfRequired();

    return minAreaEnclosingCircleRadius;
}

vector<Entity> Cluster::getEntities() const {
    return entities;
}

string Cluster::fieldNamesToString() {
    return "Clusteredness degree,Pile up degree,Number of entities (ignoring pileup),Area,Perimeter,Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)";
}

void Cluster::initialise() {
    this->clusterednessDegree = 0;
    this->pileUpDegree = 0;

    this->minAreaEnclosingCircleRadius = 0;

    minAreaEnclosingTriangle.clear();
    entities.clear();
}

vector<Point2f> Cluster::getEntitiesCentrePoints() {
    vector<Point2f> centrePoints;

    for (const Entity& entity : entities) {
        centrePoints.push_back(entity.getCentre());
    }

    return centrePoints;
}

vector<Point2f> Cluster::getEntitiesContourPoints() {
    vector<Point2f> contourPoints;

    for (const Entity& entity : entities) {
        vector<Point2f> entityContourPoints = entity.getContourPoints();

        contourPoints.insert(contourPoints.begin(), entityContourPoints.begin(), entityContourPoints.end());
    }

    return contourPoints;
}

vector<Point2f> Cluster::getEntitiesConvexHull() {
    vector<Point2f> entitiesContourPoints = getEntitiesContourPoints();

    vector<Point2f> entitiesConvexHull;

    convexHull(entitiesContourPoints, entitiesConvexHull, true, true);

    return entitiesConvexHull;
}

void Cluster::updateSpatialCollectionSpecificValues() {
    if (entities.size() > 0) {
        updatePileUpDegree();
        updateClusterednessDegree();
    }
}

void Cluster::updateClusterednessDegree() {
    clusterednessDegree = 0;

    for (Entity &e1 : entities) {
        double avgDistance = 0;

        for (Entity &e2 : entities) {
            avgDistance += e1.distanceTo(e2);
        }

        clusterednessDegree += (entities.size() == 1) ? 0
                                                      : avgDistance / (entities.size() - 1);
    }

    clusterednessDegree /= (entities.size());
}

void Cluster::updatePileUpDegree() {
    pileUpDegree = 0;

    for (const Entity &entity : entities) {
        pileUpDegree += entity.getPileUpDegree();
    }

    pileUpDegree /= (entities.size());
}

void Cluster::updateArea() {
    area = 0;

    for (const Entity &entity : entities) {
        area += entity.getArea();
    }
}

void Cluster::updatePerimeter() {
    vector<Point2f> entitiesConvexHull = getEntitiesConvexHull();

    perimeter = arcLength(entitiesConvexHull, true);
}

void Cluster::updateCentrePoint() {
    centre *= 0;

    for (const Entity &entity : entities) {
        centre += entity.getCentre();
    }

    centre.x /= entities.size();
    centre.y /= entities.size();
}

double Cluster::isTriangularMeasure() {
    vector<Point2f> entitiesContourPoints = getEntitiesContourPoints();
    vector<Point2f> contourConvexHull;
    double triangleArea = 0;

    convexHull(entitiesContourPoints, contourConvexHull, true, true);

    MinimumAreaEnclosingTriangle::find(contourConvexHull, minAreaEnclosingTriangle, triangleArea);

    return (triangleArea == 0) ? 0
                               : (area / triangleArea);
}

double Cluster::isRectangularMeasure() {
    vector<Point2f> entitiesContourPoints = getEntitiesContourPoints();

    minAreaEnclosingRect = minAreaRect(entitiesContourPoints);

    // Compute the area of the minimum area enclosing rectangle
    double rectangleArea = minAreaEnclosingRect.size.height * minAreaEnclosingRect.size.width;

    return (rectangleArea == 0) ? 0
                                : (area / rectangleArea);
}

double Cluster::isCircularMeasure() {
    vector<Point2f> entitiesContourPoints = getEntitiesContourPoints();

    minEnclosingCircle(entitiesContourPoints, minAreaEnclosingCircleCentre, minAreaEnclosingCircleRadius);

    return CircularityMeasure::compute(entitiesContourPoints);
}

string Cluster::fieldValuesToString() {
    return StringManipulator::toString<double>(clusterednessDegree) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(pileUpDegree) + OUTPUT_SEPARATOR +
           StringManipulator::toString<unsigned int>(entities.size()) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(area) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(perimeter) + OUTPUT_SEPARATOR +
           shapeAsString() + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(triangularMeasure) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(rectangularMeasure) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(circularMeasure) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(centre.x) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(centre.y);
}
