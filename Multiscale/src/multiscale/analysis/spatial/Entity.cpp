#include "multiscale/analysis/spatial/Entity.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale::analysis;


Entity::Entity(double pileUpDegree, double area, const Point2f &centre) {
    if (!areValid(pileUpDegree, area, centre))
        throw ERR_INPUT;

    this->pileUpDegree = pileUpDegree;
    this->area = area;
    this->centre = centre;
}

Entity::Entity(const Entity &entity) {
    if (!areValid(entity.pileUpDegree, entity.area, entity.centre))
        throw ERR_INPUT;

    pileUpDegree = entity.pileUpDegree;
    area = entity.area;
    centre = Point2f(entity.centre.x, entity.centre.y);
}

Entity::~Entity() {}

double Entity::getPileUpDegree() const {
    return pileUpDegree;
}

double Entity::getArea() const {
    return area;
}

Point2f Entity::getCentre() const {
    return centre;
}

string Entity::toString() {
    return StringManipulator::toString<double>(pileUpDegree) + OUTPUT_SEPARATOR +
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

bool Entity::areValid(double pileUpDegree, double area, const Point2f &centre) {
    return (
        (pileUpDegree > 0) &&
        (area > 0) &&
        ((centre.x > 0) && (centre.y >0))
    );
}
