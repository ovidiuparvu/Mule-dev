#include "multiscale/analysis/spatial/model/Entity.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale::analysis;


Entity::Entity(double pileUpDegree, double area, double perimeter,
               const cv::Point2f &centre, const std::vector<cv::Point2f> &contourPoints) {
    validateInputValues(pileUpDegree, area, perimeter, centre, contourPoints);

    this->pileUpDegree = pileUpDegree;
    this->area = area;
    this->perimeter = perimeter;
    this->centre = centre;
    this->contourPoints = contourPoints;
}

Entity::Entity(const Entity &entity) {
    validateInputValues(entity.pileUpDegree, entity.area, entity.perimeter, entity.centre, entity.contourPoints);

    pileUpDegree = entity.pileUpDegree;
    area = entity.area;
    perimeter = entity.perimeter;
    centre = cv::Point2f(entity.centre.x, entity.centre.y);
    contourPoints = entity.contourPoints;
}

Entity::~Entity() {}

double Entity::getPileUpDegree() const {
    return pileUpDegree;
}

double Entity::getArea() const {
    return area;
}

double Entity::getPerimeter() const {
    return perimeter;
}

cv::Point2f Entity::getCentre() const {
    return centre;
}

std::vector<cv::Point2f> Entity::getContourPoints() const {
    return contourPoints;
}

std::string Entity::toString() {
    // Offset the centre points by (1, 1) in order to use a 1-based indexing
    // which could be potentially more intuitive
    return (
        StringManipulator::toString<double>(pileUpDegree) + OUTPUT_SEPARATOR +
        StringManipulator::toString<double>(centre.x + 1) + OUTPUT_SEPARATOR +
        StringManipulator::toString<double>(centre.y + 1)
   );
}

double Entity::distanceTo(const Entity &entity) const {
    return (
        Geometry2D::distanceBtwPoints(
            centre,
            entity.centre
        )
    );
}

void Entity::validateInputValues(double pileUpDegree, double area, double perimeter,
                                 const cv::Point2f &centre, const std::vector<cv::Point2f> &contourPoints) {
    if (!areValid(pileUpDegree, area, perimeter, centre, contourPoints)) {
        MS_throw(InvalidInputException, ERR_INPUT);
    }
}

bool Entity::areValid(double pileUpDegree, double area, double perimeter,
                      const cv::Point2f &centre, const std::vector<cv::Point2f> &contourPoints) {
    for (const cv::Point2f &point: contourPoints) {
        // Minimum contour points values are (-0.5, -0.5) because
        // the minimum centre point is (0, 0)
        if ((point.x < (-0.5)) || (point.y < (-0.5))) {
            return false;
        }
    }

    return (
        (Numeric::lessOrEqual(0, pileUpDegree)) &&
        (Numeric::lessOrEqual(pileUpDegree, 1)) &&
        (area > 0) &&
        (perimeter > 0) &&
        (
            (Numeric::greaterOrEqual(centre.x, 0)) &&
            (Numeric::greaterOrEqual(centre.y, 0))
        )
    );
}


// Constants
const std::string Entity::ERR_INPUT           = "Invalid input parameters were provided to the constructor.";
const std::string Entity::ERR_DISTANCE        = "The distance to an object of a different type cannot be computed.";

const std::string Entity::OUTPUT_SEPARATOR    = ",";
