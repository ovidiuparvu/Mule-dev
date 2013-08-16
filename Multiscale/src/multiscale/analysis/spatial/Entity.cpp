#include "multiscale/analysis/spatial/Entity.hpp"
#include "multiscale/exception/EntityException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale::analysis;


Entity::Entity(unsigned int pileUpDegree, double area, double perimeter, const Point2f &centre, const vector<Point2f> &contourPoints) {
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
    centre = Point2f(entity.centre.x, entity.centre.y);
    contourPoints = entity.contourPoints;
}

Entity::~Entity() {}

unsigned int Entity::getPileUpDegree() const {
    return pileUpDegree;
}

double Entity::getArea() const {
    return area;
}

double Entity::getPerimeter() const {
    return perimeter;
}

Point2f Entity::getCentre() const {
    return centre;
}

vector<Point2f> Entity::getContourPoints() const {
    return contourPoints;
}

string Entity::toString() {
    return StringManipulator::toString<unsigned int>(pileUpDegree) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(centre.x) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(centre.y);
}

double Entity::distanceTo(shared_ptr<DataPoint> point) {
    shared_ptr<Entity> entity = dynamic_pointer_cast<Entity>(point);

    return Geometry2D::distanceBtwPoints(centre, entity->centre);
}

double Entity::distanceTo(const Entity &entity) {
    return Geometry2D::distanceBtwPoints(centre, entity.centre);
}

void Entity::validateInputValues(unsigned int pileUpDegree, double area, double perimeter, const Point2f &centre,
                                 const vector<Point2f> &contourPoints) {
    if (!areValid(pileUpDegree, area, perimeter, centre, contourPoints)) {
        throw EntityException(ERR_INPUT);
    }
}

bool Entity::areValid(unsigned int pileUpDegree, double area, double perimeter, const Point2f &centre, const vector<Point2f> &contourPoints) {
    for (const Point2f &point: contourPoints) {
        if ((point.x < 0) || (point.y < 0)) {
            return false;
        }
    }

    return (
        (pileUpDegree > 0) &&
        (area > 0) &&
        (perimeter > 0) &&
        ((Numeric::greaterOrEqual(centre.x, 0)) && (Numeric::greaterOrEqual(centre.y, 0)))
    );
}
