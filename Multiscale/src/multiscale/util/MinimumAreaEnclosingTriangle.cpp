#include "multiscale/util/MinimumAreaEnclosingTriangle.hpp"
#include "multiscale/util/Numeric.hpp"

#include <cassert>
#include <limits>

using namespace multiscale;


Point MinimumAreaEnclosingTriangle::vertexA;
Point MinimumAreaEnclosingTriangle::vertexB;
Point MinimumAreaEnclosingTriangle::vertexC;

Point MinimumAreaEnclosingTriangle::sideAStartVertex;
Point MinimumAreaEnclosingTriangle::sideAEndVertex;

Point MinimumAreaEnclosingTriangle::sideBStartVertex;
Point MinimumAreaEnclosingTriangle::sideBEndVertex;

Point MinimumAreaEnclosingTriangle::sideCStartVertex;
Point MinimumAreaEnclosingTriangle::sideCEndVertex;

double MinimumAreaEnclosingTriangle::area;

unsigned int MinimumAreaEnclosingTriangle::a;
unsigned int MinimumAreaEnclosingTriangle::b;
unsigned int MinimumAreaEnclosingTriangle::c;

unsigned int MinimumAreaEnclosingTriangle::nrOfPoints;

vector<Point> MinimumAreaEnclosingTriangle::polygon;


void MinimumAreaEnclosingTriangle::find(const vector<Point> &polygon, vector<Point> &minimumAreaEnclosingTriangle,
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

void MinimumAreaEnclosingTriangle::findMinimumAreaEnclosingTriangle(vector<Point> &minimumAreaEnclosingTriangle, double &area) {
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

        updateTriangleVertices();
        updateMinimumAreaEnclosingTriangle(minimumAreaEnclosingTriangle, area);
    }
}

void MinimumAreaEnclosingTriangle::advanceBToRightChain() {
    while (height(successor(b)) >= height(b)) {
        advance(b);
    }
}

void MinimumAreaEnclosingTriangle::moveAIfLowAndBIfHigh() {
    while(height(b) > height(a)) {
        Point gammaOfA;

        if ((gamma(a, gammaOfA)) && (intersectsBelow(gammaOfA, b))) {
            advance(b);
        } else {
            advance(a);
        }
    }
}

void MinimumAreaEnclosingTriangle::searchForBTangency() {
    Point gammaOfB;

    while ((gamma(b, gammaOfB)) && (intersectsBelow(gammaOfB, b)) && (height(b) >= height(predecessor(a)))) {
        advance(b);
    }
}

bool MinimumAreaEnclosingTriangle::isNotBTangency() {
    Point gammaOfB;

    if (((gamma(b, gammaOfB)) && (intersectsAbove(gammaOfB, b))) || (height(b) < height(predecessor(a)))) {
        return true;
    } else {
        return false;
    }
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
    Point sideBMiddlePoint = middlePointOfSideB();

    if (height(sideBMiddlePoint) < height(predecessor(a))) {
        sideAStartVertex = polygon[predecessor(a)];
        sideAEndVertex = findVertexCOnSideB();
    }
}

void MinimumAreaEnclosingTriangle::updateSideB() {
    if (!gamma(b, sideBStartVertex))
        throw ERR_SIDE_B_GAMMA;

    sideBEndVertex = polygon[b];
}

void MinimumAreaEnclosingTriangle::updateTriangleVertices() {
    if ((!Geometry2D::lineIntersection(sideAStartVertex, sideAEndVertex, sideBStartVertex, sideBEndVertex, vertexC)) ||
        (!Geometry2D::lineIntersection(sideAStartVertex, sideAEndVertex, sideCStartVertex, sideCEndVertex, vertexB)) ||
        (!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideCStartVertex, sideCEndVertex, vertexA))) {
        throw ERR_TRIANGLE_VERTICES;
    }
}

void MinimumAreaEnclosingTriangle::updateMinimumAreaEnclosingTriangle(vector<Point> &minimumAreaEnclosingTriangle, double &minimumAreaEnclosingTriangleArea) {
    area = Geometry2D::areaOfTriangle(vertexA, vertexB, vertexC);

    if (area < minimumAreaEnclosingTriangleArea) {
        minimumAreaEnclosingTriangle.clear();

        minimumAreaEnclosingTriangle.push_back(vertexA);
        minimumAreaEnclosingTriangle.push_back(vertexB);
        minimumAreaEnclosingTriangle.push_back(vertexC);

        minimumAreaEnclosingTriangleArea = area;
    }
}

Point MinimumAreaEnclosingTriangle::middlePointOfSideB() {
    Point vertexA, vertexC;

    if ((!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideCStartVertex, sideCEndVertex, vertexA)) ||
        (!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideAStartVertex, sideAEndVertex, vertexC))) {
        throw ERR_MIDPOINT_SIDE_B;
    }

    return Geometry2D::middlePoint(vertexA, vertexC);
}

//bool MinimumAreaEnclosingTriangle::intersectsBelow(const Point &gammaPoint, unsigned int polygonPointIndex) {
//    Point polygonPoint = polygon[polygonPointIndex];
//    Point polygonPointPredecessor = polygon[predecessor(polygonPointIndex)];
//    Point polygonPointSuccessor = polygon[successor(polygonPointIndex)];
//
//    double angleOfGammaAndPoint = Geometry2D::angleOfLineWrtOxAxis(gammaPoint, polygonPoint);
//    double angleOfPointAndPredecessor = Geometry2D::angleOfLineWrtOxAxis(polygonPoint, polygonPointPredecessor);
//    double angleOfPointAndSuccessor = Geometry2D::angleOfLineWrtOxAxis(polygonPointSuccessor, polygonPoint);
//
//    if (((angleOfGammaAndPoint < angleOfPointAndSuccessor) || (Numeric::almostEqual(angleOfGammaAndPoint, angleOfPointAndSuccessor))) &&
//        ((angleOfGammaAndPoint > angleOfPointAndPredecessor) || (Numeric::almostEqual(angleOfGammaAndPoint, angleOfPointAndPredecessor))))
//        return ((angleOfGammaAndPoint < angleOfPointAndSuccessor) || (Numeric::almostEqual(angleOfGammaAndPoint, angleOfPointAndPredecessor)));
//
//    return false;
//}

bool MinimumAreaEnclosingTriangle::intersectsBelow(const Point &gammaPoint, unsigned int polygonPointIndex) {
    Point point = polygon[polygonPointIndex];
    Point predecessor = polygon[MinimumAreaEnclosingTriangle::predecessor(polygonPointIndex)];
    Point successor = polygon[MinimumAreaEnclosingTriangle::successor(polygonPointIndex)];

    double angleOfGammaAndPoint = Geometry2D::angleOfLineWrtOxAxis(gammaPoint, point);
    double angleOfPointAndPredecessor = Geometry2D::angleOfLineWrtOxAxis(point, predecessor);
    double angleOfPointAndSuccessor = Geometry2D::angleOfLineWrtOxAxis(successor, point);

    return intersectsBelow(predecessor, point, successor, angleOfGammaAndPoint, angleOfPointAndPredecessor, angleOfPointAndSuccessor);
}

bool MinimumAreaEnclosingTriangle::intersectsBelow(const Point &predecessor, const Point &point, const Point &succesor,
                                                   double angleOfGammaAndPoint, double angleOfPointAndPredecessor,
                                                   double angleOfPointAndSuccessor) {
    if (predecessor.y <= point.y) {
        if (succesor.y <= point.y) {
            return ((Numeric::greaterOrEqual(angleOfGammaAndPoint, angleOfPointAndPredecessor)) && (Numeric::lessOrEqual(angleOfGammaAndPoint, angleOfPointAndSuccessor)));
        } else {
            return (Numeric::greaterOrEqual(angleOfGammaAndPoint, angleOfPointAndPredecessor));
        }
    } else {
        if (succesor.y <= point.y) {
            return (Numeric::lessOrEqual(angleOfGammaAndPoint, angleOfPointAndSuccessor));
        } else {
            return false;
        }
    }
}

bool MinimumAreaEnclosingTriangle::intersectsAbove(const Point &gammaPoint, unsigned int polygonPointIndex) {
    Point point = polygon[polygonPointIndex];
    Point predecessor = polygon[MinimumAreaEnclosingTriangle::predecessor(polygonPointIndex)];
    Point successor = polygon[MinimumAreaEnclosingTriangle::successor(polygonPointIndex)];

    double angleOfGammaAndPoint = Geometry2D::angleOfLineWrtOxAxis(gammaPoint, point);
    double angleOfPointAndPredecessor = Geometry2D::angleOfLineWrtOxAxis(point, predecessor);
    double angleOfPointAndSuccessor = Geometry2D::angleOfLineWrtOxAxis(successor, point);

    return intersectsAbove(predecessor, point, successor, angleOfGammaAndPoint, angleOfPointAndPredecessor, angleOfPointAndSuccessor);
}

bool MinimumAreaEnclosingTriangle::intersectsAbove(const Point &predecessor, const Point &point, const Point &succesor,
                                                   double angleOfGammaAndPoint, double angleOfPointAndPredecessor,
                                                   double angleOfPointAndSuccessor) {
    if (predecessor.y <= point.y) {
        if (succesor.y <= point.y) {
            return false;
        } else {
            return (Numeric::lessOrEqual(angleOfGammaAndPoint, angleOfPointAndSuccessor));
        }
    } else {
        if (succesor.y <= point.y) {
            return (Numeric::greaterOrEqual(angleOfGammaAndPoint, angleOfPointAndPredecessor));
        } else {
            return ((Numeric::greaterOrEqual(angleOfGammaAndPoint, angleOfPointAndPredecessor)) && (Numeric::lessOrEqual(angleOfGammaAndPoint, angleOfPointAndSuccessor)));
        }
    }
}

double MinimumAreaEnclosingTriangle::height(unsigned int polygonPointIndex) {
    Point pointC = polygon[c];
    Point pointCPredecessor = polygon[predecessor(c)];

    Point polygonPoint = polygon[polygonPointIndex];

    return Geometry2D::distanceFromPointToLine(polygonPoint, pointC, pointCPredecessor);
}

double MinimumAreaEnclosingTriangle::height(const Point &polygonPoint) {
    Point pointC = polygon[c];
    Point pointCPredecessor = polygon[predecessor(c)];

    return Geometry2D::distanceFromPointToLine(polygonPoint, pointC, pointCPredecessor);
}

bool MinimumAreaEnclosingTriangle::gamma(unsigned int polygonPointIndex, Point &gammaPoint) {
    Point intersectionPoint1, intersectionPoint2;

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

Point MinimumAreaEnclosingTriangle::findVertexCOnSideB() {
    Point intersectionPoint1, intersectionPoint2;

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

bool MinimumAreaEnclosingTriangle::findGammaIntersectionPoints(unsigned int polygonPointIndex, const Point &side1StartVertex,
                                                               const Point &side1EndVertex, const Point &side2StartVertex,
                                                               const Point &side2EndVertex, Point &intersectionPoint1,
                                                               Point &intersectionPoint2) {
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

vector<double> MinimumAreaEnclosingTriangle::lineEquationParameters(const Point &p, const Point &q) {
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
