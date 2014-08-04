#include "multiscale/verification/spatial-temporal/model/SpatialEntity.hpp"
#include "multiscale/util/Numeric.hpp"
#include "multiscale/util/StringManipulator.hpp"

using namespace multiscale;
using namespace multiscale::verification;


SpatialEntity::SpatialEntity() {
    semanticType = 0;

    clusteredness       = 0;
    density             = 0;
    area                = 0;
    perimeter           = 0;
    distanceFromOrigin  = 0;
    angle               = 0;
    triangleMeasure     = 0;
    rectangleMeasure    = 0;
    circleMeasure       = 0;
    centroidX           = 0;
    centroidY           = 0;
}

unsigned long SpatialEntity::getSemanticType() const {
    return semanticType;
}

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

double SpatialEntity::getAngle() const {
    return angle;
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

void SpatialEntity::setSemanticType(unsigned long semanticType) {
    this->semanticType = semanticType;
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
    validateRealNonNegativeValue(distanceFromOrigin);

    this->distanceFromOrigin = distanceFromOrigin;
}

void SpatialEntity::setAngle(double angle) {
    validateAngleValue(angle);

    this->angle = angle;
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

bool SpatialEntity::operator<(const SpatialEntity &rhsSpatialEntity) const {
    return (
        (this->semanticType                 <   rhsSpatialEntity.semanticType) ||
        (this->clusteredness        <   rhsSpatialEntity.clusteredness) ||
        (this->density              <   rhsSpatialEntity.density) ||
        (this->area                 <   rhsSpatialEntity.area) ||
        (this->perimeter            <   rhsSpatialEntity.perimeter) ||
        (this->distanceFromOrigin   <   rhsSpatialEntity.distanceFromOrigin) ||
        (this->angle                <   rhsSpatialEntity.angle) ||
        (this->triangleMeasure      <   rhsSpatialEntity.triangleMeasure) ||
        (this->rectangleMeasure     <   rhsSpatialEntity.rectangleMeasure) ||
        (this->circleMeasure        <   rhsSpatialEntity.circleMeasure) ||
        (this->centroidX            <   rhsSpatialEntity.centroidX) ||
        (this->centroidY            <   rhsSpatialEntity.centroidY)
    );
}

void SpatialEntity::validateRealNonNegativeValue(double value) {
    if (value < 0) {
        MS_throw_detailed(SpatialTemporalException, ERR_REAL_NON_NEGATIVE_VALUE,
                          StringManipulator::toString<double>(value), ERR_SUFFIX);
    }
}

void SpatialEntity::validateAngleValue(double value) {
    if ((value < 0) || (value > 360)) {
        MS_throw_detailed(SpatialTemporalException, ERR_ANGLE_VALUE,
                          StringManipulator::toString<double>(value), ERR_SUFFIX);
    }
}

void SpatialEntity::validateRealValueBtwZeroAndOne(double value) {
    if ((value < 0) || (value > 1)) {
        MS_throw_detailed(SpatialTemporalException, ERR_REAL_BTW_ZERO_AND_ONE,
                          StringManipulator::toString<double>(value), ERR_SUFFIX);
    }
}


// Constants
const std::string SpatialEntity::ERR_SUFFIX = ").";

const std::string SpatialEntity::ERR_REAL_NON_NEGATIVE_VALUE    = "Please update the values of the spatial measures such that they are all positive (Reported error value: ";
const std::string SpatialEntity::ERR_ANGLE_VALUE                = "Please update the value of the angle such that it is positive (Reported error value: ";
const std::string SpatialEntity::ERR_REAL_BTW_ZERO_AND_ONE      = "Please update the values of the shape (triangular, rectangular, circular) measures such that they are between 0 and 1 (Reported error value: ";
