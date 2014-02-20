#include "multiscale/analysis/spatial/SpatialEntityPseudo3D.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/Numeric.hpp"

using namespace multiscale::analysis;


SpatialEntityPseudo3D::SpatialEntityPseudo3D() {
    initialise();
}

SpatialEntityPseudo3D::~SpatialEntityPseudo3D() {}

double SpatialEntityPseudo3D::getClusterednessDegree() {
    updateMeasuresIfRequired();

    return clusterednessDegree;
}

double SpatialEntityPseudo3D::getDensity() {
    updateMeasuresIfRequired();

    return density;
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

string SpatialEntityPseudo3D::fieldNamesToString() {
    return "Clusteredness degree,Density,Area,Perimeter,Distance from origin,Angle(degrees),Shape,Triangle measure,Rectangle measure,Circle measure,Centre (x-coord),Centre (y-coord)";
}

string SpatialEntityPseudo3D::toString() {
    updateMeasuresIfRequired();

    return fieldValuesToString();
}

string SpatialEntityPseudo3D::typeAsString() {
    SpatialEntityPseudo3DType spatialEntityType = type();

    switch (spatialEntityType) {
    case SpatialEntityPseudo3DType::Region:
        return STR_REGION;
        break;

    case SpatialEntityPseudo3DType::Cluster:
        return STR_CLUSTER;
        break;

    default:
        MS_throw(UnexpectedBehaviourException, ERR_UNDEFINED_TYPE);
        break;
    }

    // Statement not executed but added to overcome warning message
    return STR_UNDEFINED;
}

void SpatialEntityPseudo3D::updateMeasuresIfRequired() {
    if (updateFlag) {
        updateMeasures();

        updateFlag = false;
    }
}

void SpatialEntityPseudo3D::updateMeasures() {
    updateClusterednessDegree();
    updateDensity();
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

double SpatialEntityPseudo3D::normalisedShapeMeasure(double shapeArea) {
    if (Numeric::almostEqual(shapeArea, 0)) {
        return 0;
    } else if (Numeric::almostEqual(shapeArea, 1)) {
        return 1;
    } else {
        return (area / shapeArea);
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

string SpatialEntityPseudo3D::fieldValuesToString() {
    stringstream strStream;

    strStream << clusterednessDegree << OUTPUT_SEPARATOR
              << density << OUTPUT_SEPARATOR
              << area << OUTPUT_SEPARATOR
              << perimeter << OUTPUT_SEPARATOR
              << distanceFromOrigin << OUTPUT_SEPARATOR
              << angle << OUTPUT_SEPARATOR
              << shapeAsString() << OUTPUT_SEPARATOR
              << triangularMeasure << OUTPUT_SEPARATOR
              << rectangularMeasure << OUTPUT_SEPARATOR
              << circularMeasure << OUTPUT_SEPARATOR
              << centre.x << OUTPUT_SEPARATOR
              << centre.y;

    return strStream.str();
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
const string SpatialEntityPseudo3D::STR_REGION  = "region";
const string SpatialEntityPseudo3D::STR_CLUSTER = "cluster";

const string SpatialEntityPseudo3D::STR_TRIANGLE    = "triangular";
const string SpatialEntityPseudo3D::STR_RECTANGLE   = "rectangular";
const string SpatialEntityPseudo3D::STR_CIRCLE      = "circular";
const string SpatialEntityPseudo3D::STR_UNDEFINED   = "undefined";

const string SpatialEntityPseudo3D::OUTPUT_SEPARATOR    = ",";

const string SpatialEntityPseudo3D::ERR_INPUT           = "Invalid input parameters were provided to the constructor.";
const string SpatialEntityPseudo3D::ERR_UNDEFINED_TYPE  = "Pseudo 3D spatial entity of undefined type encountered.";

const bool SpatialEntityPseudo3D::CONVEX_HULL_CLOCKWISE = true;
