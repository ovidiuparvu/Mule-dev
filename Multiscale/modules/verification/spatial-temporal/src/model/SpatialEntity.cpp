#include "multiscale/verification/spatial-temporal/model/SpatialEntity.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"

using namespace multiscale;
using namespace multiscale::verification;


double SpatialEntity::getClusteredness() const {
    return clusteredness;
}

double SpatialEntity::getDensity() const {
    return density;
}

double SpatialEntity::getArea() const {
    return area;
}

double SpatialEntity::getPerimeter() const {
    return perimeter;
}

double SpatialEntity::getDistanceFromOrigin() const {
    return distanceFromOrigin;
}

double SpatialEntity::getAngleDegrees() const {
    return angleDegrees;
}

double SpatialEntity::getTriangleMeasure() const {
    return triangleMeasure;
}

double SpatialEntity::getRectangleMeasure() const {
    return rectangleMeasure;
}

double SpatialEntity::getCircleMeasure() const {
    return circleMeasure;
}

double SpatialEntity::getCentroidX() const {
    return centroidX;
}

double SpatialEntity::getCentroidY() const {
    return centroidY;
}

void SpatialEntity::setClusteredness(double clusteredness) {
    validateRealNonNegativeValue(clusteredness);

    this->clusteredness = clusteredness;
}

void SpatialEntity::setDensity(double density) {
    validateRealNonNegativeValue(density);

    this->density = density;
}

void SpatialEntity::setArea(double area) {
    validateRealNonNegativeValue(area);

    this->area = area;
}

void SpatialEntity::setPerimeter(double perimeter) {
    validateRealNonNegativeValue(perimeter);

    this->perimeter = perimeter;
}

void SpatialEntity::setDistanceFromOrigin(double distanceFromOrigin) {
    validateRealNonNegativeValue(distanceFromOrigin
            );

    this->distanceFromOrigin = distanceFromOrigin;
}

void SpatialEntity::setAngleDegrees(double angleDegrees) {
    validateAngleDegreesValue(angleDegrees);

    this->angleDegrees = angleDegrees;
}

void SpatialEntity::setTriangleMeasure(double triangleMeasure) {
    validateRealValueBtwZeroAndOne(triangleMeasure);

    this->triangleMeasure = triangleMeasure;
}

void SpatialEntity::setRectangleMeasure(double rectangleMeasure) {
    validateRealValueBtwZeroAndOne(rectangleMeasure);

    this->rectangleMeasure = rectangleMeasure;
}

void SpatialEntity::setCircleMeasure(double circleMeasure) {
    validateRealValueBtwZeroAndOne(circleMeasure);

    this->circleMeasure = circleMeasure;
}

void SpatialEntity::setCentroidX(double centroidX) {
    validateRealNonNegativeValue(centroidX);

    this->centroidX = centroidX;
}

void SpatialEntity::setCentroidY(double centroidY) {
    validateRealNonNegativeValue(centroidY);

    this->centroidY = centroidY;
}

void SpatialEntity::validateRealNonNegativeValue(double value) {
    if (Numeric::lessOrEqual(value, 0)) {
        MS_throw(InvalidInputException, constructErrorMessage(ERR_REAL_NON_NEGATIVE_VALUE, value));
    }
}

void SpatialEntity::validateAngleDegreesValue(double value) {
    if ((Numeric::lessOrEqual(value, 0)) || (Numeric::greaterOrEqual(value, 360))) {
        MS_throw(InvalidInputException, constructErrorMessage(ERR_ANGLE_VALUE, value));
    }
}

void SpatialEntity::validateRealValueBtwZeroAndOne(double value) {
    if ((Numeric::lessOrEqual(value, 0)) || (Numeric::greaterOrEqual(value, 1))) {
        MS_throw(InvalidInputException, constructErrorMessage(ERR_REAL_BTW_ZERO_AND_ONE, value));
    }
}

std::string SpatialEntity::constructErrorMessage(const string &errorMessage, double errorValue) {
    return (errorMessage + StringManipulator::toString<double>(errorValue) + ERR_SUFFIX);
}


// Constants
const std::string SpatialEntity::ERR_SUFFIX = ").";

const std::string SpatialEntity::ERR_REAL_NON_NEGATIVE_VALUE    = "Please update the values of the spatial measures such that they are all positive (Reported error value: ";
const std::string SpatialEntity::ERR_ANGLE_VALUE                = "Please update the value of the angle such that it is positive (Reported error value: ";
const std::string SpatialEntity::ERR_REAL_BTW_ZERO_AND_ONE      = "Please update the values of the shape (triangular, rectangular, circular) measures such that they are between 0 and 1 (Reported error value: ";
