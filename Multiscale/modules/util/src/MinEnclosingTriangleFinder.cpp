#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/exception/UnexpectedBehaviourException.hpp"
#include "multiscale/util/MinEnclosingTriangleFinder.hpp"
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

double MinEnclosingTriangleFinder::find(const vector<Point2f> &points, vector<Point2f> &minEnclosingTriangle) {
    if (points.size() == 0) {
        MS_throw(InvalidInputException, ERR_NR_POINTS);

        // Added to overcome warning messages
        throw InvalidInputException(__FILE__, __LINE__, ERR_NR_POINTS);
    } else {
        return findMinTriangle(points, minEnclosingTriangle);
    }
}

double MinEnclosingTriangleFinder::findMinTriangle(const vector<Point2f> &points, vector<Point2f> &minEnclosingTriangle) {
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


























//------------------------------------------------------------------------------
// Minimum enclosing triangle algorithm implementation
//------------------------------------------------------------------------------

void MinEnclosingTriangleFinder::findMinEnclosingTriangle(vector<Point2f> &minEnclosingTriangle,
                                                          double &minEnclosingTriangleArea) {
    for (c = 0; c < nrOfPoints; c++) {
        // Function introduced just for visualisation purposes
        showProgress();

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

        // Function introduced just for visualisation purposes
        showProgress();
    }
}

void MinEnclosingTriangleFinder::moveAIfLowAndBIfHigh() {
    while(height(b) > height(a)) {
        Point2f gammaOfA;

        if ((gamma(a, gammaOfA)) && (intersectsBelow(gammaOfA, b))) {
            // Function introduced just for visualisation purposes
            showProgress(true, false, false, gammaOfA.x, gammaOfA.y);

            advance(b);
        } else {
            // Function introduced just for visualisation purposes
            showProgress(true, false, false, gammaOfA.x, gammaOfA.y);

            advance(a);
        }

        // Function introduced just for visualisation purposes
        showProgress(true, false, false, gammaOfA.x, gammaOfA.y);
    }
}

void MinEnclosingTriangleFinder::searchForBTangency() {
    Point2f gammaOfB;

    while (((gamma(b, gammaOfB)) && (intersectsBelow(gammaOfB, b))) &&
           (Numeric::greaterOrEqual(height(b), height(predecessor(a))))) {
        // Function introduced just for visualisation purposes
        showProgress(false, true, false, gammaOfB.x, gammaOfB.y);

        advance(b);

        // Function introduced just for visualisation purposes
        showProgress(false, true, false, gammaOfB.x, gammaOfB.y);
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

    // Function introduced just for visualisation purposes
    showProgress(false, false, true, 0, 0);

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
        MS_throw(UnexpectedBehaviourException, ERR_VERTEX_C_ON_SIDE_B);
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

void MinEnclosingTriangleFinder::showProgress(bool isGammaOfA, bool isGammaOfB, bool isTriangle, double x, double y) {
    const int OFFSET = 10;

    Mat progressImage(Size(1600, 1600), CV_32FC4);
    Mat flippedImage(Size(1600, 1600), CV_32FC4);

    progressImage = Scalar(255, 255, 255, 255);

    // Display the polygon
    for (unsigned int i = 0; i < polygon.size(); i++) {
        line(progressImage, polygon[i], polygon[(i + 1) % polygon.size()], Scalar(0, 0, 0), 30);
    }

    // Write the coordinates for gamma of a
    if (isGammaOfA) {
        line(progressImage, Point2f(x, y), polygon[a], Scalar(128, 128, 0), 30);
        circle(progressImage, Point2f(x, y), 1, Scalar(128, 128, 0), 60);
    }

    // Write the coordinates for gamma of b
    if (isGammaOfB) {
        line(progressImage, Point2f(x, y), polygon[b], Scalar(0, 128, 128), 30);
        circle(progressImage, Point2f(x, y), 1, Scalar(0, 128, 128), 60);
    }

    // Draw points a, b, c
    circle(progressImage, polygon[a], 1, Scalar(0, 0, 255), 60);
    circle(progressImage, polygon[b], 1, Scalar(0, 255, 0), 60);
    circle(progressImage, polygon[c], 1, Scalar(255, 0, 0), 60);

    // Draw the triangle and write the positions of A, B, C
    if (isTriangle) {
        line(progressImage, vertexA, vertexB, Scalar(128, 0, 128), 30, 8);
        line(progressImage, vertexB, vertexC, Scalar(128, 0, 128), 30, 8);
        line(progressImage, vertexC, vertexA, Scalar(128, 0, 128), 30, 8);
    }

    // Flip the image
    flip(progressImage, flippedImage, 0);

    // Write the coordinates for gamma of a
    if (isGammaOfA) {
        circle(flippedImage, Point(30, 1532), 1, Scalar(255, 255, 0), 30);

        putText(flippedImage, "  Gamma(a) = P(" + StringManipulator::toString<double>(x) + ", " + StringManipulator::toString<double>(y) + ")", Point(20, 1550), FONT_HERSHEY_PLAIN, 4, Scalar::all(0), 3, 9);
    }

    // Write the coordinates for gamma of b
    if (isGammaOfB) {
        circle(flippedImage, Point(30, 1532), 1, Scalar(0, 255, 255), 30);

        putText(flippedImage, "  Gamma(b) = P(" + StringManipulator::toString<double>(x) + ", " + StringManipulator::toString<double>(y) + ")", Point(20, 1550), FONT_HERSHEY_PLAIN, 4, Scalar::all(0), 3, 9);
    }

    // Draw the triangle and write the positions of A, B, C
    if (isTriangle) {
        putText(flippedImage, "Triangle vertices: ", Point(850, 1370), FONT_HERSHEY_PLAIN, 4, Scalar::all(0), 3, 9);
        putText(flippedImage, "A(" + StringManipulator::toString<float>(vertexA.x) + ", " + StringManipulator::toString<float>(vertexA.y) + ")", Point(850, 1450), FONT_HERSHEY_PLAIN, 4, Scalar::all(0), 3, 9);
        putText(flippedImage, "B(" + StringManipulator::toString<float>(vertexB.x) + ", " + StringManipulator::toString<float>(vertexB.y) + ")", Point(850, 1500), FONT_HERSHEY_PLAIN, 4, Scalar::all(0), 3, 9);
        putText(flippedImage, "C(" + StringManipulator::toString<float>(vertexC.x) + ", " + StringManipulator::toString<float>(vertexC.y) + ")", Point(850, 1550), FONT_HERSHEY_PLAIN, 4, Scalar::all(0), 3, 9);
    }

    // Write the values of the indices a, b, c
    putText(flippedImage, "  a = " + StringManipulator::toString<unsigned int>(a), Point(20, OFFSET + 120), FONT_HERSHEY_PLAIN, 4, Scalar::all(0), 3, 9);
    putText(flippedImage, "  b = " + StringManipulator::toString<unsigned int>(b), Point(20, OFFSET + 170), FONT_HERSHEY_PLAIN, 4, Scalar::all(0), 3, 9);
    putText(flippedImage, "  c = " + StringManipulator::toString<unsigned int>(c), Point(20, OFFSET + 220), FONT_HERSHEY_PLAIN, 4, Scalar::all(0), 3, 9);

    // Place colours indicating positions of points
    circle(flippedImage, Point(30, OFFSET + 102), 1, Scalar(0, 0, 255), 30);
    circle(flippedImage, Point(30, OFFSET + 152), 1, Scalar(0, 255, 0), 30);
    circle(flippedImage, Point(30, OFFSET + 202), 1, Scalar(255, 0, 0), 30);

    namedWindow("Execution progress", WINDOW_NORMAL);
    setWindowProperty( "Execution progress", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN );
    imshow("Execution progress", flippedImage);

    waitKey(2000);
}


// Constants
const bool MinEnclosingTriangleFinder::CONVEX_HULL_CLOCKWISE = true;

const unsigned int MinEnclosingTriangleFinder::INTERSECTS_BELOW      = 1;
const unsigned int MinEnclosingTriangleFinder::INTERSECTS_ABOVE      = 2;
const unsigned int MinEnclosingTriangleFinder::INTERSECTS_CRITICAL   = 3;
const unsigned int MinEnclosingTriangleFinder::INTERSECTS_LIMIT      = 4;

const string MinEnclosingTriangleFinder::ERR_NR_POINTS           = "The number of 2D points in the input vector should be greater than 0.";
const string MinEnclosingTriangleFinder::ERR_MIDPOINT_SIDE_B     = "The position of the middle point of side B could not be determined.";
const string MinEnclosingTriangleFinder::ERR_SIDE_B_GAMMA        = "The position of side B could not be determined, because gamma(b) could not be computed.";
const string MinEnclosingTriangleFinder::ERR_VERTEX_C_ON_SIDE_B  = "The position of the vertex C on side B could not be determined, because the considered lines do not intersect.";
const string MinEnclosingTriangleFinder::ERR_TRIANGLE_VERTICES   = "The position of the triangle vertices could not be determined, because the sides of the triangle do not intersect.";

const unsigned int MinEnclosingTriangleFinder::VALIDATION_SIDE_A_TANGENT   = 0;
const unsigned int MinEnclosingTriangleFinder::VALIDATION_SIDE_B_TANGENT   = 1;
const unsigned int MinEnclosingTriangleFinder::VALIDATION_SIDES_FLUSH      = 2;
