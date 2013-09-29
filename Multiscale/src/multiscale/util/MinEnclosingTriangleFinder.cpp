#include "multiscale/exception/MinEnclosingTriangleFinderException.hpp"
#include "multiscale/util/MinEnclosingTriangleFinder.hpp"
#include "multiscale/util/Numeric.hpp"

#include <cassert>
#include <iostream>
#include <limits>

using namespace multiscale;


MinEnclosingTriangleFinder::MinEnclosingTriangleFinder() {}

MinEnclosingTriangleFinder::~MinEnclosingTriangleFinder() {}

double MinEnclosingTriangleFinder::find(const vector<Point2f> &points, vector<Point2f> &minEnclosingTriangle) {
    assert(points.size() > 0);

    initialise(points, minEnclosingTriangle);

    if (polygon.size() > 3) {
        return findMinEnclosingTriangle(polygon, minEnclosingTriangle);
    } else {
        return returnMinEnclosingTriangle(polygon, minEnclosingTriangle);
    }
}

void MinEnclosingTriangleFinder::initialise(const vector<Point2f> &points, vector<Point2f> &minEnclosingTriangle) {
    // Clear all points previously stored in the vector
    minEnclosingTriangle.clear();

    initialiseConvexPolygon(points);
}

void MinEnclosingTriangleFinder::initialiseConvexPolygon(const vector<Point2f> &points) {
    polygon.clear();

    convexHull(points, polygon, CONVEX_HULL_CLOCKWISE);
}

double MinEnclosingTriangleFinder::findMinEnclosingTriangle(const vector<Point2f> &polygon,
                                                            vector<Point2f> &minEnclosingTriangle) {
    double minEnclosingTriangleArea = numeric_limits<double>::max();

    initialiseAlgorithmVariables();

    findMinEnclosingTriangle(minEnclosingTriangle, minEnclosingTriangleArea);

    return minEnclosingTriangleArea;
}

double MinEnclosingTriangleFinder::returnMinEnclosingTriangle(const vector<Point2f> &polygon,
                                                              vector<Point2f> &minEnclosingTriangle) {
    int nrOfPolygonPoints = polygon.size();

    for (int i = 0; i < 3; i++) {
        minEnclosingTriangle.push_back(polygon[i % nrOfPolygonPoints]);
    }

    return Geometry2D::areaOfTriangle(minEnclosingTriangle[0], minEnclosingTriangle[1], minEnclosingTriangle[2]);
}

void MinEnclosingTriangleFinder::initialiseAlgorithmVariables() {
    nrOfPoints = polygon.size();

    a = 1;
    b = 2;
    c = 0;
}

void MinEnclosingTriangleFinder::findMinEnclosingTriangle(vector<Point2f> &minEnclosingTriangle,
                                                          double &minEnclosingTriangleArea) {
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

        if (isLocalMinimalTriangle()) {
            updateMinEnclosingTriangle(minEnclosingTriangle, minEnclosingTriangleArea);
        }
    }
}

void MinEnclosingTriangleFinder::advanceBToRightChain() {
    while (Numeric::greaterOrEqual(height(successor(b)), height(b))) {
        advance(b);
    }
}

void MinEnclosingTriangleFinder::moveAIfLowAndBIfHigh() {
    while(height(b) > height(a)) {
        Point2f gammaOfA;

        if ((gamma(a, gammaOfA)) && (intersectsBelow(gammaOfA, b))) {
            advance(b);
        } else {
            advance(a);
        }
    }
}

void MinEnclosingTriangleFinder::searchForBTangency() {
    Point2f gammaOfB;

    while (((gamma(b, gammaOfB)) && (intersectsBelow(gammaOfB, b))) &&
           (Numeric::greaterOrEqual(height(b), height(predecessor(a))))) {
        advance(b);
    }
}

bool MinEnclosingTriangleFinder::isNotBTangency() {
    Point2f gammaOfB;

    if (((gamma(b, gammaOfB)) && (intersectsAbove(gammaOfB, b))) || (height(b) < height(predecessor(a)))) {
        return true;
    }

    return false;
}

void MinEnclosingTriangleFinder::updateSidesCA() {
    sideCStartVertex = polygon[predecessor(c)];
    sideCEndVertex = polygon[c];

    sideAStartVertex = polygon[predecessor(a)];
    sideAEndVertex = polygon[a];
}

void MinEnclosingTriangleFinder::updateSidesBA() {
    // Side B is flush with edge [b, b-1]
    sideBStartVertex = polygon[predecessor(b)];
    sideBEndVertex = polygon[b];

    // Find middle point of side B
    Point2f sideBMiddlePoint;

    if ((middlePointOfSideB(sideBMiddlePoint)) & (height(sideBMiddlePoint) < height(predecessor(a)))) {
        sideAStartVertex = polygon[predecessor(a)];
        sideAEndVertex = findVertexCOnSideB();

        validationFlag = VALIDATION_SIDE_A_TANGENT;
    } else {
        validationFlag = VALIDATION_SIDES_FLUSH;
    }
}

void MinEnclosingTriangleFinder::updateSideB() {
    if (!gamma(b, sideBStartVertex)) {
        throw MinEnclosingTriangleFinderException(ERR_SIDE_B_GAMMA);
    }

    sideBEndVertex = polygon[b];

    validationFlag = VALIDATION_SIDE_B_TANGENT;
}

bool MinEnclosingTriangleFinder::isLocalMinimalTriangle() {
    if ((!Geometry2D::lineIntersection(sideAStartVertex, sideAEndVertex, sideBStartVertex, sideBEndVertex, vertexC)) ||
        (!Geometry2D::lineIntersection(sideAStartVertex, sideAEndVertex, sideCStartVertex, sideCEndVertex, vertexB)) ||
        (!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideCStartVertex, sideCEndVertex, vertexA))) {
        return false;
    }

    return isValidMinimalTriangle();
}

bool MinEnclosingTriangleFinder::isValidMinimalTriangle() {
    Point2f midpointSideA = Geometry2D::middlePoint(vertexB, vertexC);
    Point2f midpointSideB = Geometry2D::middlePoint(vertexA, vertexC);
    Point2f midpointSideC = Geometry2D::middlePoint(vertexA, vertexB);

    bool sideAValid = (validationFlag == VALIDATION_SIDE_A_TANGENT)
                        ? (Geometry2D::areEqualPoints(midpointSideA, polygon[predecessor(a)]))
                        : (Geometry2D::isPointOnLineSegment(midpointSideA, sideAStartVertex, sideAEndVertex));

    bool sideBValid = (validationFlag == VALIDATION_SIDE_B_TANGENT)
                          ? (Geometry2D::areEqualPoints(midpointSideB, polygon[b]))
                          : (Geometry2D::isPointOnLineSegment(midpointSideB, sideBStartVertex, sideBEndVertex));

    bool sideCValid = Geometry2D::isPointOnLineSegment(midpointSideC, sideCStartVertex, sideCEndVertex);

    return (sideAValid && sideBValid && sideCValid);
}

void MinEnclosingTriangleFinder::updateMinEnclosingTriangle(vector<Point2f> &minEnclosingTriangle, double &minEnclosingTriangleArea) {
    area = Geometry2D::areaOfTriangle(vertexA, vertexB, vertexC);

    if (area < minEnclosingTriangleArea) {
        minEnclosingTriangle.clear();

        minEnclosingTriangle.push_back(vertexA);
        minEnclosingTriangle.push_back(vertexB);
        minEnclosingTriangle.push_back(vertexC);

        minEnclosingTriangleArea = area;
    }
}

bool MinEnclosingTriangleFinder::middlePointOfSideB(Point2f &middlePoint) {
    Point2f vertexA, vertexC;

    if ((!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideCStartVertex, sideCEndVertex, vertexA)) ||
        (!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideAStartVertex, sideAEndVertex, vertexC))) {
        return false;
    }

    middlePoint = Geometry2D::middlePoint(vertexA, vertexC);

    return true;
}

bool MinEnclosingTriangleFinder::intersectsBelow(const Point2f &gammaPoint, unsigned int polygonPointIndex) {
    double angleOfGammaAndPoint = Geometry2D::angleOfLineWrtOxAxis(polygon[polygonPointIndex], gammaPoint);

    return (intersects(angleOfGammaAndPoint, polygonPointIndex) == INTERSECTS_BELOW);
}

bool MinEnclosingTriangleFinder::intersectsAbove(const Point2f &gammaPoint, unsigned int polygonPointIndex) {
    double angleOfGammaAndPoint = Geometry2D::angleOfLineWrtOxAxis(gammaPoint, polygon[polygonPointIndex]);

    return (intersects(angleOfGammaAndPoint, polygonPointIndex) == INTERSECTS_ABOVE);
}

unsigned int MinEnclosingTriangleFinder::intersects(double angleOfGammaAndPoint, unsigned int polygonPointIndex) {
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

unsigned int MinEnclosingTriangleFinder::intersectsAboveOrBelow(unsigned int successorOrPredecessorIndex, unsigned int pointIndex) {
    if (height(successorOrPredecessorIndex) > height(pointIndex)) {
        return INTERSECTS_ABOVE;
    } else {
        return INTERSECTS_BELOW;
    }
}

bool MinEnclosingTriangleFinder::isFlushAngleBetweenPredecessorAndSuccessor(double &angleFlushEdge, double anglePredecessor,
                                                                            double angleSuccessor) {
    if (Geometry2D::isAngleBetweenNonReflex(angleFlushEdge, anglePredecessor, angleSuccessor)) {
        return true;
    } else if (Geometry2D::isOppositeAngleBetweenNonReflex(angleFlushEdge, anglePredecessor, angleSuccessor)) {
        angleFlushEdge = Geometry2D::oppositeAngle(angleFlushEdge);

        return true;
    }

    return false;
}

bool MinEnclosingTriangleFinder::isGammaAngleBetween(double &gammaAngle, double angle1, double angle2) {
    return (Geometry2D::isAngleBetweenNonReflex(gammaAngle, angle1, angle2));
}

bool MinEnclosingTriangleFinder::isGammaAngleEqualTo(double &gammaAngle, double angle) {
    return (Numeric::almostEqual(gammaAngle, angle));
}

double MinEnclosingTriangleFinder::height(unsigned int polygonPointIndex) {
    Point2f pointC = polygon[c];
    Point2f pointCPredecessor = polygon[predecessor(c)];

    Point2f polygonPoint = polygon[polygonPointIndex];

    return Geometry2D::distanceFromPointToLine(polygonPoint, pointC, pointCPredecessor);
}

double MinEnclosingTriangleFinder::height(const Point2f &polygonPoint) {
    Point2f pointC = polygon[c];
    Point2f pointCPredecessor = polygon[predecessor(c)];

    return Geometry2D::distanceFromPointToLine(polygonPoint, pointC, pointCPredecessor);
}

bool MinEnclosingTriangleFinder::gamma(unsigned int polygonPointIndex, Point2f &gammaPoint) {
    Point2f intersectionPoint1, intersectionPoint2;

    // Get intersection points if they exist
    if (!findGammaIntersectionPoints(polygonPointIndex, polygon[a], polygon[predecessor(a)], polygon[c],
                                     polygon[predecessor(c)], intersectionPoint1, intersectionPoint2)) {
        return false;
    }

    // Select the point which is on the same side of line C as the polygon
    if (Geometry2D::areOnTheSameSideOfLine(intersectionPoint1, polygon[successor(c)], polygon[c], polygon[predecessor(c)])) {
        gammaPoint = intersectionPoint1;
    } else {
        gammaPoint = intersectionPoint2;
    }

    return true;
}

Point2f MinEnclosingTriangleFinder::findVertexCOnSideB() {
    Point2f intersectionPoint1, intersectionPoint2;

    // Get intersection points if they exist
    if (!findGammaIntersectionPoints(predecessor(a), sideBStartVertex, sideBEndVertex, sideCStartVertex, sideCEndVertex,
                                     intersectionPoint1, intersectionPoint2)) {
        throw MinEnclosingTriangleFinderException(ERR_VERTEX_C_ON_SIDE_B);
    }

    // Select the point which is on the same side of line C as the polygon
    if (Geometry2D::areOnTheSameSideOfLine(intersectionPoint1, polygon[successor(c)], polygon[c], polygon[predecessor(c)])) {
        return intersectionPoint1;
    } else {
        return intersectionPoint2;
    }
}

bool MinEnclosingTriangleFinder::findGammaIntersectionPoints(unsigned int polygonPointIndex, const Point2f &side1StartVertex,
                                                             const Point2f &side1EndVertex, const Point2f &side2StartVertex,
                                                             const Point2f &side2EndVertex, Point2f &intersectionPoint1,
                                                             Point2f &intersectionPoint2) {
    vector<double> side1Params = lineEquationParameters(side1StartVertex, side1EndVertex);
    vector<double> side2Params = lineEquationParameters(side2StartVertex, side2EndVertex);

    // Compute side C extra parameter using the formula for distance from a point to a line
    double polygonPointHeight = height(polygonPointIndex);
    double distanceFormulaDenominator = sqrt((side2Params[0] * side2Params[0]) + (side2Params[1] * side2Params[1]));
    double sideCExtraParam = 2 * polygonPointHeight * distanceFormulaDenominator;

    // Get intersection points if they exist or if lines are identical
    if (!areIntersectingLines(side1Params, side2Params, sideCExtraParam, intersectionPoint1, intersectionPoint2)) {
        return false;
    } else if (areIdenticalLines(side1Params, side2Params, sideCExtraParam)) {
        intersectionPoint1 = side1StartVertex;
        intersectionPoint2 = side1EndVertex;
    }

    return true;
}

bool MinEnclosingTriangleFinder::areIdenticalLines(const vector<double> &side1Params, const vector<double> &side2Params,
                                                   double sideCExtraParam) {
    return (
        (Geometry2D::areIdenticalLines(side1Params[0], side1Params[1], -(side1Params[2]),
                                       side2Params[0], side2Params[1], -(side2Params[2]) - sideCExtraParam)) ||
        (Geometry2D::areIdenticalLines(side1Params[0], side1Params[1], -(side1Params[2]),
                                       side2Params[0], side2Params[1], -(side2Params[2]) + sideCExtraParam))
    );
}

bool MinEnclosingTriangleFinder::areIntersectingLines(const vector<double> &side1Params, const vector<double> &side2Params, double sideCExtraParam,
                                                      Point2f &intersectionPoint1, Point2f &intersectionPoint2) {
    return (
        (Geometry2D::lineIntersection(side1Params[0], side1Params[1], -(side1Params[2]),
                                      side2Params[0], side2Params[1], -(side2Params[2]) - sideCExtraParam,
                                      intersectionPoint1)) &&
        (Geometry2D::lineIntersection(side1Params[0], side1Params[1], -(side1Params[2]),
                                      side2Params[0], side2Params[1], -(side2Params[2]) + sideCExtraParam,
                                      intersectionPoint2))
    );
}

vector<double> MinEnclosingTriangleFinder::lineEquationParameters(const Point2f &p, const Point2f &q) {
    vector<double> lineEquationParameters;
    double a, b, c;

    Geometry2D::lineEquationDeterminedByPoints(p, q, a, b, c);

    lineEquationParameters.push_back(a);
    lineEquationParameters.push_back(b);
    lineEquationParameters.push_back(c);

    return lineEquationParameters;
}

void MinEnclosingTriangleFinder::advance(unsigned int &index) {
    index = successor(index);
}

unsigned int MinEnclosingTriangleFinder::successor(unsigned int index) {
    return ((index + 1) % nrOfPoints);
}

unsigned int MinEnclosingTriangleFinder::predecessor(unsigned int index) {
    return (index == 0) ? (nrOfPoints - 1)
                        : (index - 1);
}
