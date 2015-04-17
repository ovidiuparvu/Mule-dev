#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/geometry/MinEnclosingTriangleFinder.hpp"
#include "multiscale/util/Numeric.hpp"

#include <cassert>
#include <iostream>
#include <limits>

using namespace multiscale;


MinEnclosingTriangleFinder::MinEnclosingTriangleFinder() {
    validationFlag = 0;

    area = 0;

    a = 0;
    b = 0;
    c = 0;

    nrOfPoints = 0;
}

MinEnclosingTriangleFinder::~MinEnclosingTriangleFinder() {}

double MinEnclosingTriangleFinder::find(const std::vector<cv::Point2f> &points,
                                        std::vector<cv::Point2f> &minEnclosingTriangle) {
    if (points.size() == 0) {
        MS_throw(InvalidInputException, ERR_NR_POINTS);

        // Added to overcome warning messages
        throw InvalidInputException(__FILE__, __LINE__, ERR_NR_POINTS);
    } else {
        return findMinTriangle(points, minEnclosingTriangle);
    }
}

double MinEnclosingTriangleFinder::findMinTriangle(const std::vector<cv::Point2f> &points,
                                                   std::vector<cv::Point2f> &minEnclosingTriangle) {
    initialize(points, minEnclosingTriangle);

    if (polygon.size() > 3) {
        return findMinEnclosingTriangle(polygon, minEnclosingTriangle);
    } else {
        return returnMinEnclosingTriangle(polygon, minEnclosingTriangle);
    }
}

void MinEnclosingTriangleFinder::initialize(const std::vector<cv::Point2f> &points,
                                            std::vector<cv::Point2f> &minEnclosingTriangle) {
    // Clear all points previously stored in the std::vector
    minEnclosingTriangle.clear();

    initializeConvexPolygon(points);
}

void MinEnclosingTriangleFinder::initializeConvexPolygon(const std::vector<cv::Point2f> &points) {
    polygon = Geometry2D::computeConvexHull(points, CONVEX_HULL_CLOCKWISE);
}

double MinEnclosingTriangleFinder::findMinEnclosingTriangle(const std::vector<cv::Point2f> &polygon,
                                                            std::vector<cv::Point2f> &minEnclosingTriangle) {
    double minEnclosingTriangleArea = std::numeric_limits<double>::max();

    initializeAlgorithmVariables();

    findMinEnclosingTriangle(minEnclosingTriangle, minEnclosingTriangleArea);

    return minEnclosingTriangleArea;
}

double MinEnclosingTriangleFinder::returnMinEnclosingTriangle(const std::vector<cv::Point2f> &polygon,
                                                              std::vector<cv::Point2f> &minEnclosingTriangle) {
    int nrOfPolygonPoints = polygon.size();

    for (int i = 0; i < 3; i++) {
        minEnclosingTriangle.push_back(polygon[i % nrOfPolygonPoints]);
    }

    return (
        Geometry2D::areaOfTriangle(
            minEnclosingTriangle[0],
            minEnclosingTriangle[1],
            minEnclosingTriangle[2]
        )
    );
}

void MinEnclosingTriangleFinder::initializeAlgorithmVariables() {
    nrOfPoints = polygon.size();

    a = 1;
    b = 2;
    c = 0;
}

void MinEnclosingTriangleFinder::findMinEnclosingTriangle(std::vector<cv::Point2f> &minEnclosingTriangle,
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
        cv::Point2f gammaOfA;

        if ((gamma(a, gammaOfA)) && (intersectsBelow(gammaOfA, b))) {
            advance(b);
        } else {
            advance(a);
        }
    }
}

void MinEnclosingTriangleFinder::searchForBTangency() {
    cv::Point2f gammaOfB;

    while (((gamma(b, gammaOfB)) && (intersectsBelow(gammaOfB, b))) &&
           (Numeric::greaterOrEqual(height(b), height(predecessor(a))))) {
        advance(b);
    }
}

bool MinEnclosingTriangleFinder::isNotBTangency() {
    cv::Point2f gammaOfB;

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
    cv::Point2f sideBMiddlePoint;

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
        MS_throw(UnexpectedBehaviourException, ERR_SIDE_B_GAMMA);
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
    cv::Point2f midpointSideA = Geometry2D::middlePoint(vertexB, vertexC);
    cv::Point2f midpointSideB = Geometry2D::middlePoint(vertexA, vertexC);
    cv::Point2f midpointSideC = Geometry2D::middlePoint(vertexA, vertexB);

    bool sideAValid = (validationFlag == VALIDATION_SIDE_A_TANGENT)
                        ? (Geometry2D::areEqualPoints(midpointSideA, polygon[predecessor(a)]))
                        : (Geometry2D::isPointOnLineSegment(midpointSideA, sideAStartVertex, sideAEndVertex));

    bool sideBValid = (validationFlag == VALIDATION_SIDE_B_TANGENT)
                          ? (Geometry2D::areEqualPoints(midpointSideB, polygon[b]))
                          : (Geometry2D::isPointOnLineSegment(midpointSideB, sideBStartVertex, sideBEndVertex));

    bool sideCValid = Geometry2D::isPointOnLineSegment(midpointSideC, sideCStartVertex, sideCEndVertex);

    return (sideAValid && sideBValid && sideCValid);
}

void MinEnclosingTriangleFinder::updateMinEnclosingTriangle(std::vector<cv::Point2f> &minEnclosingTriangle,
                                                            double &minEnclosingTriangleArea) {
    area = Geometry2D::areaOfTriangle(vertexA, vertexB, vertexC);

    if (area < minEnclosingTriangleArea) {
        minEnclosingTriangle.clear();

        minEnclosingTriangle.push_back(vertexA);
        minEnclosingTriangle.push_back(vertexB);
        minEnclosingTriangle.push_back(vertexC);

        minEnclosingTriangleArea = area;
    }
}

bool MinEnclosingTriangleFinder::middlePointOfSideB(cv::Point2f &middlePoint) {
    cv::Point2f vertexA, vertexC;

    if ((!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideCStartVertex, sideCEndVertex, vertexA)) ||
        (!Geometry2D::lineIntersection(sideBStartVertex, sideBEndVertex, sideAStartVertex, sideAEndVertex, vertexC))) {
        return false;
    }

    middlePoint = Geometry2D::middlePoint(vertexA, vertexC);

    return true;
}

bool MinEnclosingTriangleFinder::intersectsBelow(const cv::Point2f &gammaPoint, unsigned int polygonPointIndex) {
    double angleOfGammaAndPoint = Geometry2D::angleOfLineWrtOxAxis(polygon[polygonPointIndex], gammaPoint);

    return (intersects(angleOfGammaAndPoint, polygonPointIndex) == INTERSECTS_BELOW);
}

bool MinEnclosingTriangleFinder::intersectsAbove(const cv::Point2f &gammaPoint, unsigned int polygonPointIndex) {
    double angleOfGammaAndPoint = Geometry2D::angleOfLineWrtOxAxis(gammaPoint, polygon[polygonPointIndex]);

    return (intersects(angleOfGammaAndPoint, polygonPointIndex) == INTERSECTS_ABOVE);
}

unsigned int MinEnclosingTriangleFinder::intersects(double angleOfGammaAndPoint, unsigned int polygonPointIndex) {
    double angleOfPointAndPredecessor = Geometry2D::angleOfLineWrtOxAxis(polygon[predecessor(polygonPointIndex)],
                                                                         polygon[polygonPointIndex]);
    double angleOfPointAndSuccessor = Geometry2D::angleOfLineWrtOxAxis(polygon[successor(polygonPointIndex)],
                                                                       polygon[polygonPointIndex]);
    double angleOfFlushEdge = Geometry2D::angleOfLineWrtOxAxis(polygon[predecessor(c)], polygon[c]);

    if (isFlushAngleBetweenPredecessorAndSuccessor(angleOfFlushEdge, angleOfPointAndPredecessor,
                                                   angleOfPointAndSuccessor)) {
        if ((isGammaAngleBetween(angleOfGammaAndPoint, angleOfPointAndPredecessor, angleOfFlushEdge)) ||
            (almostEqual(angleOfGammaAndPoint, angleOfPointAndPredecessor))) {
            return intersectsAboveOrBelow(predecessor(polygonPointIndex), polygonPointIndex);
        } else if ((isGammaAngleBetween(angleOfGammaAndPoint, angleOfPointAndSuccessor, angleOfFlushEdge)) ||
                  (almostEqual(angleOfGammaAndPoint, angleOfPointAndSuccessor))) {
            return intersectsAboveOrBelow(successor(polygonPointIndex), polygonPointIndex);
        }
    } else {
        if ((
                isGammaAngleBetween(angleOfGammaAndPoint, angleOfPointAndPredecessor, angleOfPointAndSuccessor)
            ) || (
                (isGammaAngleEqualTo(angleOfGammaAndPoint, angleOfPointAndPredecessor)) &&
                (!isGammaAngleEqualTo(angleOfGammaAndPoint, angleOfFlushEdge))
            ) || (
                (isGammaAngleEqualTo(angleOfGammaAndPoint, angleOfPointAndSuccessor)) &&
                (!isGammaAngleEqualTo(angleOfGammaAndPoint, angleOfFlushEdge))
            )) {
            return INTERSECTS_BELOW;
        }
    }

    return INTERSECTS_CRITICAL;
}

unsigned int MinEnclosingTriangleFinder::intersectsAboveOrBelow(unsigned int successorOrPredecessorIndex,
                                                                unsigned int pointIndex) {
    if (height(successorOrPredecessorIndex) > height(pointIndex)) {
        return INTERSECTS_ABOVE;
    } else {
        return INTERSECTS_BELOW;
    }
}

bool MinEnclosingTriangleFinder::isFlushAngleBetweenPredecessorAndSuccessor(double &angleFlushEdge,
                                                                            double anglePredecessor,
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
    return (almostEqual(gammaAngle, angle));
}

double MinEnclosingTriangleFinder::height(unsigned int polygonPointIndex) {
    cv::Point2f pointC = polygon[c];
    cv::Point2f pointCPredecessor = polygon[predecessor(c)];

    cv::Point2f polygonPoint = polygon[polygonPointIndex];

    return Geometry2D::distanceFromPointToLine(polygonPoint, pointC, pointCPredecessor);
}

double MinEnclosingTriangleFinder::height(const cv::Point2f &polygonPoint) {
    cv::Point2f pointC = polygon[c];
    cv::Point2f pointCPredecessor = polygon[predecessor(c)];

    return Geometry2D::distanceFromPointToLine(polygonPoint, pointC, pointCPredecessor);
}

bool MinEnclosingTriangleFinder::gamma(unsigned int polygonPointIndex, cv::Point2f &gammaPoint) {
    cv::Point2f intersectionPoint1, intersectionPoint2;

    // Get intersection points if they exist
    if (!findGammaIntersectionPoints(polygonPointIndex, polygon[a], polygon[predecessor(a)], polygon[c],
                                     polygon[predecessor(c)], intersectionPoint1, intersectionPoint2)) {
        return false;
    }

    // Select the point which is on the same side of line C as the polygon
    if (Geometry2D::areOnTheSameSideOfLine(intersectionPoint1, polygon[successor(c)],
                                           polygon[c], polygon[predecessor(c)])) {
        gammaPoint = intersectionPoint1;
    } else {
        gammaPoint = intersectionPoint2;
    }

    return true;
}

cv::Point2f MinEnclosingTriangleFinder::findVertexCOnSideB() {
    cv::Point2f intersectionPoint1, intersectionPoint2;

    // Get intersection points if they exist
    if (!findGammaIntersectionPoints(predecessor(a), sideBStartVertex, sideBEndVertex, sideCStartVertex,
                                     sideCEndVertex, intersectionPoint1, intersectionPoint2)) {
        MS_throw(UnexpectedBehaviourException, ERR_VERTEX_C_ON_SIDE_B);
    }

    // Select the point which is on the same side of line C as the polygon
    if (Geometry2D::areOnTheSameSideOfLine(intersectionPoint1, polygon[successor(c)],
                                           polygon[c], polygon[predecessor(c)])) {
        return intersectionPoint1;
    } else {
        return intersectionPoint2;
    }
}

bool MinEnclosingTriangleFinder::findGammaIntersectionPoints(unsigned int polygonPointIndex,
                                                             const cv::Point2f &side1StartVertex,
                                                             const cv::Point2f &side1EndVertex,
                                                             const cv::Point2f &side2StartVertex,
                                                             const cv::Point2f &side2EndVertex,
                                                             cv::Point2f &intersectionPoint1,
                                                             cv::Point2f &intersectionPoint2) {
    std::vector<double> side1Params = lineEquationParameters(side1StartVertex, side1EndVertex);
    std::vector<double> side2Params = lineEquationParameters(side2StartVertex, side2EndVertex);

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

bool MinEnclosingTriangleFinder::areIdenticalLines(const std::vector<double> &side1Params,
                                                   const std::vector<double> &side2Params,
                                                   double sideCExtraParam) {
    return (
        (Geometry2D::areIdenticalLines(side1Params[0], side1Params[1], -(side1Params[2]),
                                       side2Params[0], side2Params[1], -(side2Params[2]) - sideCExtraParam)) ||
        (Geometry2D::areIdenticalLines(side1Params[0], side1Params[1], -(side1Params[2]),
                                       side2Params[0], side2Params[1], -(side2Params[2]) + sideCExtraParam))
    );
}

bool MinEnclosingTriangleFinder::areIntersectingLines(const std::vector<double> &side1Params,
                                                      const std::vector<double> &side2Params,
                                                      double sideCExtraParam,
                                                      cv::Point2f &intersectionPoint1,
                                                      cv::Point2f &intersectionPoint2) {
    return (
        (Geometry2D::lineIntersection(side1Params[0], side1Params[1], -(side1Params[2]),
                                      side2Params[0], side2Params[1], -(side2Params[2]) - sideCExtraParam,
                                      intersectionPoint1)) &&
        (Geometry2D::lineIntersection(side1Params[0], side1Params[1], -(side1Params[2]),
                                      side2Params[0], side2Params[1], -(side2Params[2]) + sideCExtraParam,
                                      intersectionPoint2))
    );
}

std::vector<double> MinEnclosingTriangleFinder::lineEquationParameters(const cv::Point2f &p,
                                                                       const cv::Point2f &q) {
    std::vector<double> lineEquationParameters;
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

bool MinEnclosingTriangleFinder::almostEqual(float lhsNumber, float rhsNumber) {
    return (
        (std::fabs(lhsNumber - rhsNumber) <=
        (EPSILON * std::max(1.0f, std::max(std::fabs(lhsNumber), std::fabs(rhsNumber)))))
    );
}


// Constants
const float MinEnclosingTriangleFinder::EPSILON = 1E-5;

const bool MinEnclosingTriangleFinder::CONVEX_HULL_CLOCKWISE = true;

const unsigned int MinEnclosingTriangleFinder::INTERSECTS_BELOW      = 1;
const unsigned int MinEnclosingTriangleFinder::INTERSECTS_ABOVE      = 2;
const unsigned int MinEnclosingTriangleFinder::INTERSECTS_CRITICAL   = 3;
const unsigned int MinEnclosingTriangleFinder::INTERSECTS_LIMIT      = 4;

const std::string MinEnclosingTriangleFinder::ERR_NR_POINTS           = "The number of 2D points in the input std::vector should be greater than 0.";
const std::string MinEnclosingTriangleFinder::ERR_MIDPOINT_SIDE_B     = "The position of the middle point of side B could not be determined.";
const std::string MinEnclosingTriangleFinder::ERR_SIDE_B_GAMMA        = "The position of side B could not be determined, because gamma(b) could not be computed.";
const std::string MinEnclosingTriangleFinder::ERR_VERTEX_C_ON_SIDE_B  = "The position of the vertex C on side B could not be determined, because the considered lines do not intersect.";
const std::string MinEnclosingTriangleFinder::ERR_TRIANGLE_VERTICES   = "The position of the triangle vertices could not be determined, because the sides of the triangle do not intersect.";

const unsigned int MinEnclosingTriangleFinder::VALIDATION_SIDE_A_TANGENT   = 0;
const unsigned int MinEnclosingTriangleFinder::VALIDATION_SIDE_B_TANGENT   = 1;
const unsigned int MinEnclosingTriangleFinder::VALIDATION_SIDES_FLUSH      = 2;
