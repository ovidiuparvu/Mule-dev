#ifndef GEOMETRY2D_HPP_
#define GEOMETRY2D_HPP_

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

#define PI                  3.14159265358979323846264338327950288419716939937510
#define MATRIX_START_INDEX  1


namespace multiscale {

    //! Two-dimensional geometric operations
    class Geometry2D {

        public:

            //! Get the angle of the line measured from the Ox axis in counterclockwise direction
            /*!
             * The line is specified by points "a" and "b". The value of the angle is expressed in radians.
             *
             * \param a Point a
             * \param b Point b
             */
            static double angleOfLineWrtOxAxis(const Point &a, const Point &b);

            //! Compute the slope of the line defined by points "a" and "b"
            /*!
             * \param a Point a
             * \param b Point b
             * \param slope Slope of the line if it is different from (+/-)infinity
             */
            static bool slopeOfLine(const Point &a, const Point &b, double &slope);

            //! Compute the distance between two points
            /*! Compute the Euclidean distance between two points
             *
             * \param a Point a
             * \param b Point b
             */
            static double distanceBtwPoints(const Point &a, const Point &b);

            //! Compute the distance from a point "a" to a line specified by two points "B" and "C"
            /*!
             * \param a             Point from which the distance is measures
             * \param linePointB    One of the points determining the line
             * \param linePointC    One of the points determining the line
             */
            static double distanceFromPointToLine(const Point &a, const Point &linePointB, const Point &linePointC);

            //! Get the point in the middle of the segment determined by points "a" and "b"
            /*!
             * \param a Point a
             * \param b Point b
             */
            static Point middlePoint(const Point &a, const Point &b);

            //! Find the points which are on the edge and on the line orthogonal to the line defined by 2 given points
            /*!
             * \param a1        First point for determining the first line
             * \param b1        Second point for determining the first line
             * \param a2        First point for determining the second line
             * \param b2        Second point for determining the second line
             * \param nrOfRows  Maximum number of rows in the considered matrix
             * \param nrOfCols  Maximum number of columns in the considered matrix
             */
            static void orthogonalLineToAnotherLineEdgePoints(const Point &a1, const Point &b1, Point &a2,
                                                              Point &b2, int nrOfRows, int nrOfCols);

            //! Get the values of "a", "b" and "c" of the line equation ax + by + c = 0 knowing that point "p" and "q" are on the line
            /*!
             * a = q.y - p.y
             * b = p.x - q.x
             * c = - (p.x * a) - (p.y * b)
             *
             * \param p Point p
             * \param q Point q
             * \param a Parameter "a" from the line equation
             * \param b Parameter "b" from the line equation
             * \param c Parameter "c" from the line equation
             */
            static void lineEquationDeterminedByPoints(const Point &p, const Point &q, double &a, double &b, double &c);

            //! Determine the intersection point of two lines, if this point exists
            /*! Two lines intersect if they are not parallel (Parallel lines intersect at
             * +/- infinity, but we do not consider this case here).
             *
             * The lines are specified by a pair of points each. If they intersect, then
             * the function returns true, else it returns false.
             *
             * Lines are specified in the following form:
             *      A1x + B1x = C1
             *      A2x + B2x = C2
             *
             * If det (= A1xB2 - A2xB1) == 0, then lines are parallel
             *                                else they intersect
             *
             * If they intersect, then let us denote the intersection point with P(x, y) where:
             *      x = (C1xB2 - C2xB1) / (det)
             *      y = (C2xA1 - C1xA2) / (det)
             *
             * \param a1 First point for determining the first line
             * \param b1 Second point for determining the first line
             * \param a2 First point for determining the second line
             * \param b2 Second point for determining the second line
             * \param intersection The intersection point, if this point exists
             */
            static bool lineIntersection(const Point &a1, const Point &b1, const Point &a2, const Point &b2, Point &intersection);

            //! Determine the intersection point of two lines, if this point exists
            /*! Two lines intersect if they are not parallel (Parallel lines intersect at
             * +/- infinity, but we do not consider this case here).
             *
             * The lines are specified in the following form:
             *      A1x + B1x = C1
             *      A2x + B2x = C2
             *
             * If det (= A1xB2 - A2xB1) == 0, then lines are parallel
             *                                else they intersect
             *
             * If they intersect, then let us denote the intersection point with P(x, y) where:
             *      x = (C1xB2 - C2xB1) / (det)
             *      y = (C2xA1 - C1xA2) / (det)
             *
             * \param a1 A1
             * \param b1 B1
             * \param c1 C1
             * \param a2 A2
             * \param b2 B2
             * \param c2 C2
             * \param intersection The intersection point, if this point exists
             */
            static bool lineIntersection(double a1, double b1, double c1, double a2, double b2, double c2, Point &intersection);

            //! Determine the intersection point of two line segments, if this point exists
            /*! Find the intersection point of the lines, if this point exists. Let us assume that
             * this point exists and let us denote it with P(x, y). Then, in order for the point to be
             * the intersection of the segments and not of the lines, we have to verify the following
             * conditions:
             *  1. min(a1.x, b1.x) <= x <= max(a1.x, b1.x) -- x coordinate is valid for first line segment
             *  2. min(a2.x, b2.x) <= x <= max(a2.x, b2.x) -- x coordinate is valid for second line segment
             *  3. min(a1.y, b1.y) <= y <= max(a1.y, b1.y) -- y coordinate is valid for first line segment
             *  4. min(a2.y, b2.y) <= y <= max(a2.y, b2.y) -- y coordinate is valid for second line segment
             *
             * \param a1            First point for determining the first line
             * \param b1            Second point for determining the first line
             * \param a2            First point for determining the second line
             * \param b2            Second point for determining the second line
             * \param intersection  The intersection point, if this point exists
             */
            static bool lineSegmentIntersection(const Point &a1, const Point &b1, const Point &a2, const Point &b2, Point &intersection);

            //! Determine if a line and a circle intersect and return the intersection points if they exist
            /*!
             * We translate all the points such that the circle origin coincides with the origin of the
             * coordinate system. When returning the results, the intersection points are inverse translated.
             *
             * \param a                     First point for determining the line
             * \param b                     Second point for determining the line
             * \param circleOrigin          Origin of the circle
             * \param radius                Radius of the circle
             * \param intersectionPoints    The intersection points between the circle and the line
             */
            static bool lineCircleIntersection(Point a, Point b, const Point &circleOrigin,
                                               double radius, vector<Point2f> &intersectionPoints);

            //! Determine if a line segment and a circle intersect and return the intersection points if they exist
            /*!
             * We translate all the points such that the circle origin coincides with the origin of the
             * coordinate system. When returning the results, the intersection points are inverse translated.
             *
             * \param a                     First point for determining the line
             * \param b                     Second point for determining the line
             * \param circleOrigin          Origin of the circle
             * \param radius                Radius of the circle
             * \param intersectionPoints    The intersection points between the circle and the line
             */
            static bool lineSegmentCircleIntersection(const Point &a, const Point &b, const Point &circleOrigin,
                                                      double radius, vector<Point2f> &intersectionPoints);

            //! Compute the angle between three points
            /*! Compute the angle between the lines determined by
             * points A, B and B, C
             *
             * \param a Point a
             * \param b Point b
             * \param c Point c
             */
            static double angleBtwPoints(const Point &a, const Point &b, const Point &c);

            //! Find the subset of points from the given set of points which lie on the edge
            /*!
             *  A point "p" is considered to be on the edge if:
             *      ((p.x == 1) && (p.y > 1) && (p.y < nrOfCols)) OR
             *      ((p.x == nrOfRows) && (p.y > 1) && (p.y < nrOfCols)) OR
             *      ((p.y == 1) && (p.x > 1) && (p.x < nrOfRows)) OR
             *      ((p.y == nrOfCols) && (p.x > 1) && (p.x < nrOfRows))
             *
             *  \param points   The set of points
             *  \param nrOfRows The number of rows
             *  \param nrOfCols The number of columns
             */
            static vector<Point> findPointsOnEdge(const vector<Point> &points, unsigned int nrOfRows, unsigned int nrOfCols);

            //! Get the index of the point which is the closest to the origin
            /*! Get the index of the point P from the given set of points, such that
             *  for any point A from the set of points dist(A, origin) >= dist(P, origin).
             *
             * \param points The set of points
             * \param origin The origin
             */
            static unsigned int minimumDistancePointIndex(const vector<Point> &points, const Point &origin);

            //! Compute the area of a triangle defined by three points
            /*!
             * The area is computed using the determinant method.
             * An example is presented at http://demonstrations.wolfram.com/TheAreaOfATriangleUsingADeterminant/
             * (Last access: 10.07.2013)
             *
             * \param a Point a
             * \param b Point b
             * \param c Point c
             */
            static double areaOfTriangle(const Point2f &a, const Point2f &b, const Point2f &c);

        private:

            //! Check if the given point is on the edge
            /*!
             *  A point "p" is considered to be on the edge if:
             *      ((p.x == 1) && (p.y > 1) && (p.y < nrOfCols)) OR
             *      ((p.x == nrOfRows) && (p.y > 1) && (p.y < nrOfCols)) OR
             *      ((p.y == 1) && (p.x > 1) && (p.x < nrOfRows)) OR
             *      ((p.y == nrOfCols) && (p.x > 1) && (p.x < nrOfRows))
             *
             *  \param p Point p
             *  \param nrOfRows The number of rows
             *  \param nrOfCols The number of columns
             */
            static bool isPointOnEdge(const Point &p, int nrOfRows, int nrOfCols);

            //! Check if the coordinate c lies between c1 and c2
            /*!
             * \param c Coordinate c
             * \param c1 Coordinate c1
             * \param c2 Coordinate c2
             */
            template <typename T, typename U>
            static bool isBetweenCoordinates(T c, U c1, U c2);

            //! Compute sgn(number)
            /*!
             *\param number The number
             */
            static int sgn(int number);

            //! Translate a point by the given values
            /*!
             * \param point The point
             * \param translation Translation values
             */
            static void translate(Point &point, const Point &translation);

            //! Inverse translate a point by the given values
            /*!
             * \param point The point
             * \param translation Translation values
             */
            static void inverseTranslate(Point2f &point, const Point &translation);

            //! Treat the case when the line and circle intersect in two points
            /*!
             * \param circleOrigin          Origin of the circle
             * \param A                     y2 - y1
             * \param B                     x1 - x2
             * \param C                     A*x1 + B*y1
             * \param delta                 (4 * B^2 * C^2) - (4 * (A^2 + B^2) * (C^2 - (R^2 * A^2)))
             * \param intersectionPoints    Intersection points
             */
            static void lineCircleTwoIntersectionPoints(const Point &circleOrigin, double A, double B,
                                                        double C, double delta, vector<Point2f> &intersectionPoints);

            //! Treat the case when the line and circle intersect in one point
            /*!
             * \param circleOrigin          Origin of the circle
             * \param A                     y2 - y1
             * \param B                     x1 - x2
             * \param C                     A*x1 + B*y1
             * \param delta                 (4 * B^2 * C^2) - (4 * (A^2 + B^2) * (C^2 - (R^2 * A^2)))
             * \param intersectionPoints    Intersection points
             */
            static void lineCircleOneIntersectionPoint(const Point &circleOrigin, double A, double B,
                                                       double C, double delta, vector<Point2f> &intersectionPoints);

    };

};

#endif
