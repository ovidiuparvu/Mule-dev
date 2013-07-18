#include "multiscale/util/MinimumAreaEnclosingTriangle.hpp"
#include "multiscale/util/Numeric.hpp"

#include <cassert>
#include <iostream>
#include <limits>

using namespace multiscale;


Point2f MinimumAreaEnclosingTriangle::vertexA;
Point2f MinimumAreaEnclosingTriangle::vertexB;
Point2f MinimumAreaEnclosingTriangle::vertexC;

Point2f MinimumAreaEnclosingTriangle::sideAStartVertex;
Point2f MinimumAreaEnclosingTriangle::sideAEndVertex;

Point2f MinimumAreaEnclosingTriangle::sideBStartVertex;
Point2f MinimumAreaEnclosingTriangle::sideBEndVertex;

Point2f MinimumAreaEnclosingTriangle::sideCStartVertex;
Point2f MinimumAreaEnclosingTriangle::sideCEndVertex;

double MinimumAreaEnclosingTriangle::area;

unsigned int MinimumAreaEnclosingTriangle::a;
unsigned int MinimumAreaEnclosingTriangle::b;
unsigned int MinimumAreaEnclosingTriangle::c;

unsigned int MinimumAreaEnclosingTriangle::nrOfPoints;

vector<Point2f> MinimumAreaEnclosingTriangle::polygon;


void MinimumAreaEnclosingTriangle::find(const vector<Point2f> &polygon, vector<Point2f> &minimumAreaEnclosingTriangle,
                                        double &area) {
    // Check if the polygon is convex and is a k-gon with k > 3
    assert(isContourConvex(polygon) && (polygon.size() > 3));

    MinimumAreaEnclosingTriangle::polygon = polygon;
    area = numeric_limits<double>::max();

    // Clear all points previously stored in the vector
    minimumAreaEnclosingTriangle.clear();

    initialise();

    findMinimumAreaEnclosingTriangle(minimumAreaEnclosingTriangle, area);
}

void MinimumAreaEnclosingTriangle::initialise() {
    nrOfPoints = polygon.size();

    a = 1;
    b = 2;
    c = 0;
}

void MinimumAreaEnclosingTriangle::findMinimumAreaEnclosingTriangle(vector<Point2f> &minimumAreaEnclosingTriangle, double &area) {
    for (c = 0; c < nrOfPoints; c++) {
        advanceBToRightChain();
        moveAIfLowAndBIfHigh();
        searchForBTangency();

        updateSidesCA();

        if (isNotBTangency()) {
            updateSidesBA();
        } else {
            updateSideB();
        }

        if (updateTriangleVertices()) {
            updateMinimumAreaEnclosingTriangle(minimumAreaEnclosingTriangle, area);
        }
    }
}

void MinimumAreaEnclosingTriangle::advanceBToRightChain() {
    while (Numeric::greaterOrEqual(height(successor(b)), height(b))) {
        advance(b);
    }
}

void MinimumAreaEnclosingTriangle::moveAIfLowAndBIfHigh() {
    while(height(b) > height(a)) {
        Point2f gammaOfA;

        if ((gamma(a, gammaOfA)) && (intersectsBelow(gammaOfA, b))) {
            advance(b);
        } else {
            advance(a);
        }
    }
}

void MinimumAreaEnclosingTriangle::searchForBTangency() {
    Point2f gammaOfB;

    while (((gamma(b, gammaOfB)) && (intersectsBelow(gammaOfB, b))) &&
           (Numeric::greaterOrEqual(height(b), height(predecessor(a))))) {
        advance(b);
    }
}

bool MinimumAreaEnclosingTriangle::isNotBTangency() {
    Point2f gammaOfB;

    if (gamma(b, gammaOfB)) {
        if ((intersectsAbove(gammaOfB, b)) || (height(b) < height(predecessor(a)))) {
            return true;
        }
    }

    return false;
}

void MinimumAreaEnclosingTriangle::updateSidesCA() {
    sideCStartVertex = polygon[predecessor(c)];
    sideCEndVertex = polygon[c];

    sideAStartVertex = polygon[predecessor(a)];
    sideAEndVertex = polygon[a];
}

void MinimumAreaEnclosingTriangle::updateSidesBA() {
    // Side B is flush with edge [b b-1]
    sideBStartVertex = polygon[predecessor(b)];
    sideBEndVertex = polygon[b];

    // Find middle point of side B
    Point2f sideBMiddlePoint;

    if ((middlePointOfSideB(sideBMiddlePoint)) & (height(sideBMiddlePoint) < height(predecessor(a)))) {
        sideAStartVertex = polygon[predecessor(a)];

        cout << "Here";

        sideAEndVertex = findVertexCOnSideB();
    }
}

void MinimumAreaEnclosingTriangle::updateSideB() {
    if (!gamma(b, sideBStartVertex))
        throw ERR_SIDE_B_GAMMA;

    sideBEndVertex = polygon[b];
}

bool MinimumAreaEnclosingTriangle::updateTriangleVertices() {
    if ((!Geometry2D::lineIntersection(sideAStartVertex, sideAEndVertex, sideBStartVertex, sideBEndVertex, vertexC)) ||
        (!Geometry2D::lineIntersection(sideAStartVertex, sideAEndVertex, sideCStartVertex, sideCEndVertex, vertexB)) ||
        (!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideCStartVertex, sideCEndVertex, vertexA))) {
        return false;
    }

    return true;
}

bool MinimumAreaEnclosingTriangle::isValidMinimalTriangle() {
    Point2f midpointSideA = Geometry2D::middlePoint(vertexB, vertexC);
    Point2f midpointSideB = Geometry2D::middlePoint(vertexA, vertexC);
    Point2f midpointSideC = Geometry2D::middlePoint(vertexA, vertexB);

    bool sideAValid = ((Geometry2D::isPointOnLineSegment(midpointSideA, sideAStartVertex, sideAEndVertex)) ||
                       (Geometry2D::areEqualPoints(midpointSideA, polygon[predecessor(a)])));
    bool sideBValid = ((Geometry2D::isPointOnLineSegment(midpointSideB, sideBStartVertex, sideBEndVertex)) ||
                       (Geometry2D::areEqualPoints(midpointSideB, polygon[b])));
    bool sideCValid = Geometry2D::isPointOnLineSegment(midpointSideC, sideCStartVertex, sideCEndVertex);

    return (sideAValid && sideBValid && sideCValid);
}

void MinimumAreaEnclosingTriangle::updateMinimumAreaEnclosingTriangle(vector<Point2f> &minimumAreaEnclosingTriangle, double &minimumAreaEnclosingTriangleArea) {
    area = Geometry2D::areaOfTriangle(vertexA, vertexB, vertexC);

    if (area < minimumAreaEnclosingTriangleArea) {
        minimumAreaEnclosingTriangle.clear();

        minimumAreaEnclosingTriangle.push_back(vertexA);
        minimumAreaEnclosingTriangle.push_back(vertexB);
        minimumAreaEnclosingTriangle.push_back(vertexC);

        minimumAreaEnclosingTriangleArea = area;
    }
}

bool MinimumAreaEnclosingTriangle::middlePointOfSideB(Point2f &middlePoint) {
    Point2f vertexA, vertexC;

    if ((!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideCStartVertex, sideCEndVertex, vertexA)) ||
        (!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideAStartVertex, sideAEndVertex, vertexC))) {
        return false;
    }

    middlePoint = Geometry2D::middlePoint(vertexA, vertexC);

    return true;
}

bool MinimumAreaEnclosingTriangle::intersectsBelow(const Point2f &gammaPoint, unsigned int polygonPointIndex) {
   return (intersects(gammaPoint, polygonPointIndex) == INTERSECTS_BELOW);
}

bool MinimumAreaEnclosingTriangle::intersectsAbove(const Point2f &gammaPoint, unsigned int polygonPointIndex) {
    return (intersects(gammaPoint, polygonPointIndex) == INTERSECTS_ABOVE);
}

unsigned int MinimumAreaEnclosingTriangle::intersects(const Point2f &gammaPoint, unsigned int polygonPointIndex) {
    double angleOfGammaAndPoint = Geometry2D::angleOfLineWrtOxAxis(polygon[polygonPointIndex], gammaPoint);
    double angleOfPointAndPredecessor = Geometry2D::angleOfLineWrtOxAxis(polygon[predecessor(polygonPointIndex)], polygon[polygonPointIndex]);
    double angleOfPointAndSuccessor = Geometry2D::angleOfLineWrtOxAxis(polygon[successor(polygonPointIndex)], polygon[polygonPointIndex]);
    double angleOfFlushEdge = Geometry2D::angleOfLineWrtOxAxis(polygon[predecessor(c)], polygon[c]);

    if (isFlushAngleBetweenPredecessorAndSuccessor(angleOfFlushEdge, angleOfPointAndPredecessor, angleOfPointAndSuccessor)) {
        if ((isGammaAngleBetween(angleOfGammaAndPoint, angleOfPointAndPredecessor, angleOfFlushEdge)) ||
            (Numeric::almostEqual(angleOfGammaAndPoint, angleOfPointAndPredecessor))) {
            return intersectsAboveOrBelow(predecessor(polygonPointIndex), polygonPointIndex);
        } else if ((isGammaAngleBetween(angleOfGammaAndPoint, angleOfPointAndSuccessor, angleOfFlushEdge)) ||
                  (Numeric::almostEqual(angleOfGammaAndPoint, angleOfPointAndSuccessor))) {
            return intersectsAboveOrBelow(successor(polygonPointIndex), polygonPointIndex);
        }
    } else {

        if ((isGammaAngleBetween(angleOfGammaAndPoint, angleOfPointAndPredecessor, angleOfPointAndSuccessor)) ||
            ((isGammaAngleEqualTo(angleOfGammaAndPoint, angleOfPointAndPredecessor)) && (!isGammaAngleEqualTo(angleOfGammaAndPoint, angleOfFlushEdge))) ||
            ((isGammaAngleEqualTo(angleOfGammaAndPoint, angleOfPointAndSuccessor)) && (!isGammaAngleEqualTo(angleOfGammaAndPoint, angleOfFlushEdge)))) {
            return INTERSECTS_BELOW;
        }
    }

    return INTERSECTS_CRITICAL;
}

unsigned int MinimumAreaEnclosingTriangle::intersectsAboveOrBelow(unsigned int successorOrPredecessorIndex, unsigned int pointIndex) {
    if (height(successorOrPredecessorIndex) > height(pointIndex)) {
        return INTERSECTS_ABOVE;
    } else {
        return INTERSECTS_BELOW;
    }
}

bool MinimumAreaEnclosingTriangle::isFlushAngleBetweenPredecessorAndSuccessor(double &angleFlushEdge, double anglePredecessor,
                                                                              double angleSuccessor) {
    if (Geometry2D::isAngleBetweenNonReflex(angleFlushEdge, anglePredecessor, angleSuccessor)) {
        return true;
    } else if (Geometry2D::isOppositeAngleBetweenNonReflex(angleFlushEdge, anglePredecessor, angleSuccessor)) {
        angleFlushEdge = Geometry2D::oppositeAngle(angleFlushEdge);

        return true;
    }

    return false;
}

bool MinimumAreaEnclosingTriangle::isGammaAngleBetween(double &gammaAngle, double angle1, double angle2) {
    if (Geometry2D::isAngleBetweenNonReflex(gammaAngle, angle1, angle2)) {
        return true;
    } else if (Geometry2D::isOppositeAngleBetweenNonReflex(gammaAngle, angle1, angle2)) {
        gammaAngle = Geometry2D::oppositeAngle(gammaAngle);

        return true;
    }

    return false;
}

bool MinimumAreaEnclosingTriangle::isGammaAngleEqualTo(double &gammaAngle, double angle) {
    if (Numeric::almostEqual(gammaAngle, angle)) {
        return true;
    } else if (Numeric::almostEqual(Geometry2D::oppositeAngle(gammaAngle), angle)){
        gammaAngle = Geometry2D::oppositeAngle(gammaAngle);

        return true;
    }

    return false;
}

double MinimumAreaEnclosingTriangle::height(unsigned int polygonPointIndex) {
    Point2f pointC = polygon[c];
    Point2f pointCPredecessor = polygon[predecessor(c)];

    Point2f polygonPoint = polygon[polygonPointIndex];

    return Geometry2D::distanceFromPointToLine(polygonPoint, pointC, pointCPredecessor);
}

double MinimumAreaEnclosingTriangle::height(const Point2f &polygonPoint) {
    Point2f pointC = polygon[c];
    Point2f pointCPredecessor = polygon[predecessor(c)];

    return Geometry2D::distanceFromPointToLine(polygonPoint, pointC, pointCPredecessor);
}

bool MinimumAreaEnclosingTriangle::gamma(unsigned int polygonPointIndex, Point2f &gammaPoint) {
    Point2f intersectionPoint1, intersectionPoint2;

    // Get intersection points if they exist
    if (!findGammaIntersectionPoints(polygonPointIndex, polygon[a], polygon[predecessor(a)], polygon[c],
                                     polygon[predecessor(c)], intersectionPoint1, intersectionPoint2)) {
        return false;
    }

    // Select the point which is closer to polygon[a]
    double distanceToIntersectionPoint1 = Geometry2D::distanceBtwPoints(intersectionPoint1, polygon[a]);
    double distanceToIntersectionPoint2 = Geometry2D::distanceBtwPoints(intersectionPoint2, polygon[a]);

    if (distanceToIntersectionPoint1 < distanceToIntersectionPoint2) {
        gammaPoint = intersectionPoint1;
    } else {
        gammaPoint = intersectionPoint2;
    }

    return true;
}

Point2f MinimumAreaEnclosingTriangle::findVertexCOnSideB() {
    Point2f intersectionPoint1, intersectionPoint2;

    // Get intersection points if they exist
    if (!findGammaIntersectionPoints(predecessor(a), sideBStartVertex, sideBEndVertex, sideCStartVertex, sideCEndVertex,
                                     intersectionPoint1, intersectionPoint2)) {
        throw ERR_VERTEX_C_ON_SIDE_B;
    }

    // Select the point which is closer to polygon[b]
    double distanceToIntersectionPoint1 = Geometry2D::distanceBtwPoints(intersectionPoint1, polygon[b]);
    double distanceToIntersectionPoint2 = Geometry2D::distanceBtwPoints(intersectionPoint2, polygon[b]);

    if (distanceToIntersectionPoint1 < distanceToIntersectionPoint2) {
        return intersectionPoint1;
    } else {
        return intersectionPoint2;
    }
}

bool MinimumAreaEnclosingTriangle::findGammaIntersectionPoints(unsigned int polygonPointIndex, const Point2f &side1StartVertex,
                                                               const Point2f &side1EndVertex, const Point2f &side2StartVertex,
                                                               const Point2f &side2EndVertex, Point2f &intersectionPoint1,
                                                               Point2f &intersectionPoint2) {
    vector<double> side1Params = lineEquationParameters(side1StartVertex, side1EndVertex);
    vector<double> side2Params = lineEquationParameters(side2StartVertex, side2EndVertex);

    // Compute side C extra parameter using the formula for distance from a point to a line
    double polygonPointHeight = height(polygonPointIndex);
    double distanceFormulaDenominator = sqrt((side2Params[0] * side2Params[0]) + (side2Params[1] * side2Params[1]));
    double sideCExtraParam = 2 * polygonPointHeight * distanceFormulaDenominator;

    // Get intersection points if they exist
    if ((!Geometry2D::lineIntersection(side1Params[0], side1Params[1], -(side1Params[2]),
                                       side2Params[0], side2Params[1], -(side2Params[2]) - sideCExtraParam,
                                       intersectionPoint1)) ||
        (!Geometry2D::lineIntersection(side1Params[0], side1Params[1], -(side1Params[2]),
                                       side2Params[0], side2Params[1], -(side2Params[2]) + sideCExtraParam,
                                       intersectionPoint2))) {
        return false;
    }

    return true;
}

vector<double> MinimumAreaEnclosingTriangle::lineEquationParameters(const Point2f &p, const Point2f &q) {
    vector<double> lineEquationParameters;
    double a, b, c;

    Geometry2D::lineEquationDeterminedByPoints(p, q, a, b, c);

    lineEquationParameters.push_back(a);
    lineEquationParameters.push_back(b);
    lineEquationParameters.push_back(c);

    return lineEquationParameters;
}

void MinimumAreaEnclosingTriangle::advance(unsigned int &index) {
    index = successor(index);
}

unsigned int MinimumAreaEnclosingTriangle::successor(unsigned int index) {
    return ((index + 1) % nrOfPoints);
}

unsigned int MinimumAreaEnclosingTriangle::predecessor(unsigned int index) {
    return (index == 0) ? (nrOfPoints - 1)
                        : (index - 1);
}
