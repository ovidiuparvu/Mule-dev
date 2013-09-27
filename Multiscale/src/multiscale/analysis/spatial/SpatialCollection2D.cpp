#include "multiscale/analysis/spatial/SpatialCollection2D.hpp"

using namespace multiscale::analysis;


SpatialCollection2D::SpatialCollection2D() {
    initialise();
}

SpatialCollection2D::~SpatialCollection2D() {}

double SpatialCollection2D::getClusterednessDegree() {
    updateMeasuresIfRequired();

    return clusterednessDegree;
}

double SpatialCollection2D::getArea() {
    updateMeasuresIfRequired();

    return area;
}

double SpatialCollection2D::getPerimeter() {
    updateMeasuresIfRequired();

    return perimeter;
}

Shape2D SpatialCollection2D::getShape() {
    updateMeasuresIfRequired();

    return shape;
}

Point2f SpatialCollection2D::getCentre() {
    updateMeasuresIfRequired();

    return centre;
}

string SpatialCollection2D::toString() {
    updateMeasuresIfRequired();

    return fieldValuesToString();
}

void SpatialCollection2D::updateMeasuresIfRequired() {
    if (updateFlag) {
        updateMeasures();
        updateSpatialCollectionSpecificValues();

        updateFlag = false;
    }
}

void SpatialCollection2D::updateMeasures() {
    updateClusterednessDegree();
    updateArea();
    updatePerimeter();
    updateShape();
    updateCentrePoint();
}

void SpatialCollection2D::updateShape() {
    triangularMeasure = isTriangularMeasure();
    rectangularMeasure = isRectangularMeasure();
    circularMeasure = isCircularMeasure();

    if (triangularMeasure < rectangularMeasure) {
        if (rectangularMeasure > circularMeasure) {
            shape = Shape2D::Rectangle;
        } else {
            shape = Shape2D::Circle;
        }
    } else {
        if (triangularMeasure > circularMeasure) {
            shape = Shape2D::Triangle;
        } else {
            shape = Shape2D::Circle;
        }
    }
}

string SpatialCollection2D::shapeAsString() {
    switch (shape) {
        case Shape2D::Triangle:
            return STR_TRIANGLE;
            break;

        case Shape2D::Rectangle:
            return STR_RECTANGLE;
            break;

        case Shape2D::Circle:
            return STR_CIRCLE;
            break;

        case Shape2D::Undefined:
            // There are no entities in this cluster
            break;
    }

    return STR_UNDEFINED;
}

vector<Point2f> SpatialCollection2D::convertPoints(const vector<Point> &points) {
    vector<Point2f> convertedPoints;

    for (const Point &point : points) {
        convertedPoints.push_back(Point2f(point.x, point.y));
    }

    return convertedPoints;
}

void SpatialCollection2D::initialise() {
    area = 0;
    perimeter = 0;

    triangularMeasure = 0;
    rectangularMeasure = 0;
    circularMeasure = 0;

    shape = Shape2D::Undefined;

    updateFlag = true;
}
