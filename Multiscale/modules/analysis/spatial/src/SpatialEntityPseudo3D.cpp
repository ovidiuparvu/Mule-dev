#include "multiscale/analysis/spatial/SpatialEntityPseudo3D.hpp"

using namespace multiscale::analysis;


SpatialEntityPseudo3D::SpatialEntityPseudo3D() {
    initialise();
}

SpatialEntityPseudo3D::~SpatialEntityPseudo3D() {}

double SpatialEntityPseudo3D::getClusterednessDegree() {
    updateMeasuresIfRequired();

    return clusterednessDegree;
}

double SpatialEntityPseudo3D::getArea() {
    updateMeasuresIfRequired();

    return area;
}

double SpatialEntityPseudo3D::getPerimeter() {
    updateMeasuresIfRequired();

    return perimeter;
}

double SpatialEntityPseudo3D::getDistanceFromOrigin() {
    updateMeasuresIfRequired();

    return distanceFromOrigin;
}

double SpatialEntityPseudo3D::getAngle() {
    updateMeasuresIfRequired();

    return angle;
}

Shape2D SpatialEntityPseudo3D::getShape() {
    updateMeasuresIfRequired();

    return shape;
}

string SpatialEntityPseudo3D::getShapeAsString() {
    return shapeAsString();
}

double SpatialEntityPseudo3D::getTriangularMeasure() {
    return triangularMeasure;
}

double SpatialEntityPseudo3D::getRectangularMeasure() {
    return rectangularMeasure;
}

double SpatialEntityPseudo3D::getCircularMeasure() {
    return circularMeasure;
}

Point2f SpatialEntityPseudo3D::getCentre() {
    updateMeasuresIfRequired();

    return centre;
}

string SpatialEntityPseudo3D::toString() {
    updateMeasuresIfRequired();

    return fieldValuesToString();
}

void SpatialEntityPseudo3D::updateMeasuresIfRequired() {
    if (updateFlag) {
        updateMeasures();
        updateSpatialCollectionSpecificValues();

        updateFlag = false;
    }
}

void SpatialEntityPseudo3D::updateMeasures() {
    updateClusterednessDegree();
    updateArea();
    updatePerimeter();
    updateShape();
    updateCentrePoint();
}

void SpatialEntityPseudo3D::updateShape() {
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

string SpatialEntityPseudo3D::shapeAsString() {
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

vector<Point2f> SpatialEntityPseudo3D::convertPoints(const vector<Point> &points) {
    vector<Point2f> convertedPoints;

    for (const Point &point : points) {
        convertedPoints.push_back(Point2f(point.x, point.y));
    }

    return convertedPoints;
}

void SpatialEntityPseudo3D::initialise() {
    area = 0;
    perimeter = 0;

    triangularMeasure = 0;
    rectangularMeasure = 0;
    circularMeasure = 0;

    shape = Shape2D::Undefined;

    updateFlag = true;
}


// Constants
const string SpatialEntityPseudo3D::STR_TRIANGLE            = "triangular";
const string SpatialEntityPseudo3D::STR_RECTANGLE           = "rectangular";
const string SpatialEntityPseudo3D::STR_CIRCLE              = "circular";
const string SpatialEntityPseudo3D::STR_UNDEFINED           = "undefined";

const string SpatialEntityPseudo3D::OUTPUT_SEPARATOR        = ",";

const string SpatialEntityPseudo3D::ERR_INPUT               = "Invalid input parameters were provided to the constructor.";

const bool SpatialEntityPseudo3D::CONVEX_HULL_CLOCKWISE     = true;