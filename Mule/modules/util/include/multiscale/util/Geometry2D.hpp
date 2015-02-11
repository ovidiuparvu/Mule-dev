#ifndef GEOMETRY2D_HPP
#define GEOMETRY2D_HPP

#include "multiscale/util/Numeric.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


namespace multiscale {

    //! Two-dimensional geometric operations
    class Geometry2D {

        public:

            //! Compute the angle ABC between three points A, B and C
            /*! Compute the angle between the lines determined by
             * points (A, B) and (B, C)
             *
             * \param a cv::Point2f a
             * \param b cv::Point2f b
             * \param c cv::Point2f c
             */
            static double angleBtwPoints(const cv::Point2f &a, const cv::Point2f &b, const cv::Point2f &c);

            //! Get the angle of the line measured from the Ox axis in counterclockwise direction
            /*!
             * The line is specified by points "a" and "b". The value of the angle is expressed in degrees.
             *
             * \param a Point a
             * \param b Point b
             */
            static double angleOfLineWrtOxAxis(const cv::Point2f &a, const cv::Point2f &b);

            //! Check if angle1 lies between angles 2 and 3
            /*!
             * \param angle1 The angle which lies between angle2 and angle3 or not
             * \param angle2 One of the boundary angles
             * \param angle3 The other boundary angle
             */
            static bool isAngleBetween(double angle1, double angle2, double angle3);

            //! Check if the opposite of angle1, ((angle1 + 180) % 360), lies between angles 2 and 3
            /*!
             * \param angle1 The angle for which the opposite angle lies between angle2 and angle3 or not
             * \param angle2 One of the boundary angles
             * \param angle3 The other boundary angle
             */
            static bool isOppositeAngleBetween(double angle1, double angle2, double angle3);

            //! Check if angle1 lies between non reflex angle determined by angles 2 and 3
            /*!
             * \param angle1 The angle which lies between angle2 and angle3 or not
             * \param angle2 One of the boundary angles
             * \param angle3 The other boundary angle
             */
            static bool isAngleBetweenNonReflex(double angle1, double angle2, double angle3);

            //! Check if the opposite of angle1 lies between non reflex angle determined by angles 2 and 3
            /*! Check if the opposite of angle1, ((angle1 + 180) % 360), lies between non reflex angle determined
             *  by angles 2 and 3
             *
             * \param angle1 The angle which lies between angle2 and angle3 or not
             * \param angle2 One of the boundary angles
             * \param angle3 The other boundary angle
             */
            static bool isOppositeAngleBetweenNonReflex(double angle1, double angle2, double angle3);

            //! Return the angle opposite to the given angle
            /*!
             * if (angle < 180) then
             *      return (angle + 180);
             * else
             *      return (angle - 180);
             * endif
             *
             * \param angle Angle
             */
            static double oppositeAngle(double angle);

            //! Compute the slope of the line defined by points "a" and "b"
            /*!
             * Returns true if the slope of the line can be computed and false otherwise.
             *
             * \param a     Point a
             * \param b     Point b
             * \param slope Slope of the line if it is different from (+/-)infinity
             */
            static bool slopeOfLine(const cv::Point2f &a, const cv::Point2f &b, double &slope);

            //! Compute the distance between two points
            /*! Compute the Euclidean distance between two points
             *
             * \param a Point a
             * \param b Point b
             */
            template <typename LhsCoordinateType, typename RhsCoordinateType>
            static double distanceBtwPoints(const cv::Point_<LhsCoordinateType> &a,
                                            const cv::Point_<RhsCoordinateType> &b) {
                double aXCoordinate = static_cast<double>(a.x);
                double aYCoordinate = static_cast<double>(a.y);

                double bXCoordinate = static_cast<double>(b.x);
                double bYCoordinate = static_cast<double>(b.y);

                return (
                    distanceBtwPoints(
                        aXCoordinate,
                        aYCoordinate,
                        bXCoordinate,
                        bYCoordinate
                    )
                );
            }

            //! Compute the distance between two points
            /*! Compute the Euclidean distance between two points
             *
             * \param x1 The x-coordinate of the first point
             * \param y1 The y-coordinate of the first point
             * \param x2 The x-coordinate of the second point
             * \param y2 The y-coordinate of the second point
             */
            static double distanceBtwPoints(double x1, double y1, double x2, double y2);

            //! Compute the distance from a point "a" to a line specified by two points "B" and "C"
            /*!
             * Formula used:
             *
             * \f$ distance = \frac{\mid (x_c - x_b)(y_b - y_a) - (x_b - x_a)(y_c - y_b) \mid}{\sqrt{(x_c - x_b)^{2} +
             *                (y_c - y_b)^{2}}} \f$
             *
             * Reference: http://mathworld.wolfram.com/cv::Point-LineDistance2-Dimensional.html
             *
             * \param a             The point from which the distance is measures
             * \param linePointB    One of the points determining the line
             * \param linePointC    One of the points determining the line
             */
            static double distanceFromPointToLine(const cv::Point2f &a, const cv::Point2f &linePointB,
                                                  const cv::Point2f &linePointC);

            //! Get the point in the middle of the segment determined by points "a" and "b"
            /*!
             * \param a Point a
             * \param b Point b
             */
            static cv::Point2f middlePoint(const cv::Point2f &a, const cv::Point2f &b);

            //! Compute the centroid of the provided collection of points
            /*!
             * \param points    The considered collection of points
             */
            template <typename CoordinateType>
            static cv::Point2f centroid(const std::vector<cv::Point_<CoordinateType>> &points) {
                cv::Point2f centroid;

                // Compute the sum of all points coordinates
                for (const auto &point: points) {
                    centroid += cv::Point2f(
                                    static_cast<float>(point.x),
                                    static_cast<float>(point.y)
                                );
                }

                // Divide the coordinates sum by the number of points
                centroid.x /= static_cast<float>(points.size());
                centroid.y /= static_cast<float>(points.size());

                return centroid;
            }

            //! Check if the given point lies inside the polygon
            /*!
             * \param point     The given point
             * \param polygon   The given polygon
             */
            static bool isPointInsidePolygon(const cv::Point2f &point,
                                             const std::vector<cv::Point2f> &polygon);

            //! Check if the provided polygon is convex
            /*!
             * \param polygon   The provided polygon
             */
            static bool isConvexPolygon(const std::vector<cv::Point2f> &polygon);

            //! Compute the convex hull for the provided polygon
            /*!
             * \param polygon                   The provided polygon
             * \param arePointsInClockwiseOrder Flag indicating if the points in the convex hull
             *                                  are sorted in clockwise order
             */
            template <typename CoordinateType>
            static std::vector<cv::Point_<CoordinateType>>
            computeConvexHull(const std::vector<cv::Point_<CoordinateType>> &polygon,
                              bool arePointsInClockwiseOrder = false) {
                std::vector<cv::Point_<CoordinateType>> polygonConvexHull;

                // TODO: Implement method myself to remove dependency between this class
                //       and the OpenCV library
                cv::convexHull(polygon, polygonConvexHull, arePointsInClockwiseOrder);

                return polygonConvexHull;
            }

            //! Compute the polygon points where the tangents from a reference point touch the given polygon
            /*!
             * \param convexPolygon         The considered convex polygon
             * \param referencePoint        The reference point through which the polygon tangents pass
             * \param leftMostTangentPoint  The left most polygon point through which the tangent passes
             * \param rightMostTangentPoint The right most polygon point through which the tangent passes
             */
            static void tangentsFromPointToPolygon(const std::vector<cv::Point2f> &convexPolygon,
                                                   const cv::Point2f &referencePoint,
                                                   cv::Point2f &leftMostTangentPoint,
                                                   cv::Point2f &rightMostTangentPoint);

            //! Find the points which are on the edge and on the line orthogonal to the line defined by 2 given points
            /*!
             * \param a1        First point for determining the first line
             * \param b1        Second point for determining the first line
             * \param a2        First point for determining the second line
             * \param b2        Second point for determining the second line
             * \param nrOfRows  Maximum number of rows in the considered matrix
             * \param nrOfCols  Maximum number of columns in the considered matrix
             */
            static void orthogonalLineToAnotherLineEdgePoints(const cv::Point &a1, const cv::Point &b1,
                                                              cv::Point &a2, cv::Point &b2, int nrOfRows,
                                                              int nrOfCols);

            //! Compute on which side of the line (A, B) the given point P lies
            /*! The function returns:
             *      <0, if P lies to the left of (A, B)
             *       0, if P lies on the line (A, B)
             *      >0, if P lies to the right of (A, B)
             *
             * \param point             The considered point P
             * \param lineStartPointA   The line start point A
             * \param lineEndPointB     The line end point B
             */
            static double sideOfLine(const cv::Point2f &point, const cv::Point2f &lineStartPointA,
                                     const cv::Point2f &lineEndPointB);

            //! Check if the point P lies to the right of line (A, B)
            /*!
             * \param point             The considered point P
             * \param lineStartPointA   The line start point A
             * \param lineEndPointB     The line end point B
             */
            static bool isToTheRightOfLine(const cv::Point2f &point, const cv::Point2f &lineStartPointA,
                                           const cv::Point2f &lineEndPointB);

            //! Check if the point P lies to the left of line (A, B)
            /*!
             * \param point             The considered point P
             * \param lineStartPointA   The line start point A
             * \param lineEndPointB     The line end point B
             */
            static bool isToTheLeftOfLine(const cv::Point2f &point, const cv::Point2f &lineStartPointA,
                                          const cv::Point2f &lineEndPointB);

            //! Check if p1 and p2 are on the same side of the line determined by points a and b
            /*!
             * \param p1    Point p1
             * \param p2    Point p2
             * \param a     First point for determining line
             * \param b     Second point for determining line
             */
            static bool areOnTheSameSideOfLine(const cv::Point2f &p1, const cv::Point2f &p2,
                                               const cv::Point2f &a, const cv::Point2f &b);

            //! Get the values of "a", "b" and "c" of the line equation ax + by + c = 0
            /*! Get the values of "a", "b" and "c" of the line equation ax + by + c = 0
             *  knowing that point "p" and "q" are on the line
             *
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
            static void lineEquationDeterminedByPoints(const cv::Point2f &p, const cv::Point2f &q,
                                                       double &a, double &b, double &c);

            //! Check if two lines are identical
            /*!
             * Lines are be specified in the following form:
             *      A1x + B1x = C1
             *      A2x + B2x = C2
             *
             * If (A1/A2) == (B1/B2) == (C1/C2), then the lines are identical
             *                                   else they are not
             *
             * \param a1 A1
             * \param b1 B1
             * \param c1 C1
             * \param a2 A2
             * \param b2 B2
             * \param c2 C2
             */
            static bool areIdenticalLines(double a1, double b1, double c1, double a2, double b2, double c2);

            //! Check if two lines are identical
            /*!
             * The lines are specified by a pair of points each. If they are identical, then
             * the function returns true, else it returns false.
             *
             * Lines can be specified in the following form:
             *      A1x + B1x = C1
             *      A2x + B2x = C2
             *
             * If (A1/A2) == (B1/B2) == (C1/C2), then the lines are identical
             *                                   else they are not
             *
             * \param a1 First point for determining the first line
             * \param b1 Second point for determining the first line
             * \param a2 First point for determining the second line
             * \param b2 Second point for determining the second line
             */
            static bool areIdenticalLines(const cv::Point2f &a1, const cv::Point2f &b1,
                                          const cv::Point2f &a2, const cv::Point2f &b2);

            //! Determine the intersection point of two lines, if this point exists
            /*! Two lines intersect if they are not parallel (Parallel lines intersect at
             * +/- infinity, but we do not consider this case here).
             *
             * The lines are specified by a pair of points each. If they intersect, then
             * the function returns true, else it returns false.
             *
             * Lines can be specified in the following form:
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
            static bool lineIntersection(const cv::Point2f &a1, const cv::Point2f &b1, const cv::Point2f &a2,
                                         const cv::Point2f &b2, cv::Point2f &intersection);

            //! Determine the intersection point of two lines, if this point exists
            /*! Two lines intersect if they are not parallel (Parallel lines intersect at
             * +/- infinity, but we do not consider this case here).
             *
             * The lines are specified by a pair of points each. If they intersect, then
             * the function returns true, else it returns false.
             *
             * Lines can be specified in the following form:
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
            static bool lineIntersection(const cv::Point &a1, const cv::Point &b1, const cv::Point &a2,
                                         const cv::Point &b2, cv::Point &intersection);

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
            static bool lineIntersection(double a1, double b1, double c1, double a2, double b2,
                                         double c2, cv::Point2f &intersection);

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
            static bool lineSegmentIntersection(const cv::Point &a1, const cv::Point &b1, const cv::Point &a2,
                                                const cv::Point &b2, cv::Point &intersection);

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
            static bool lineCircleIntersection(cv::Point2f a, cv::Point2f b, const cv::Point2f &circleOrigin,
                                               double radius, std::vector<cv::Point2f> &intersectionPoints);

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
            static bool lineSegmentCircleIntersection(const cv::Point2f &a, const cv::Point2f &b,
                                                      const cv::Point2f &circleOrigin, double radius,
                                                      std::vector<cv::Point2f> &intersectionPoints);

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
            static std::vector<cv::Point2f> findPointsOnEdge(const std::vector<cv::Point2f> &points,
                                                             unsigned int nrOfRows,
                                                             unsigned int nrOfCols);

            //! Get the index of the point which is the closest to the origin
            /*! Get the index of the point P from the given set of points, such that
             *  for any point A from the set of points dist(A, origin) >= dist(P, origin).
             *
             * \param points The set of points
             * \param origin The origin
             */
            static unsigned int minimumDistancePointIndex(const std::vector<cv::Point> &points,
                                                          const cv::Point2f &origin);

            //! Get the index of the point which is the closest to the origin
            /*! Get the index of the point P from the given set of points, such that
             *  for any point A from the set of points dist(A, origin) >= dist(P, origin).
             *
             * \param points The set of points
             * \param origin The origin
             */
            template <typename PointCoordinateType>
            static unsigned int minimumDistancePointIndex(const std::vector<cv::Point_<PointCoordinateType>> &points,
                                                          const cv::Point2f &origin) {
                double  minDistance             = std::numeric_limits<int>::max();
                int     minDistancePointIndex   = -1;

                double      distance    = 0.0;
                std::size_t nrOfPoints  = points.size();

                for (std::size_t i = 0; i < nrOfPoints; i++) {
                    distance = distanceBtwPoints(points[i], origin);

                    if (distance < minDistance) {
                        minDistance = distance;

                        minDistancePointIndex = i;
                    }
                }

                return minDistancePointIndex;
            }

            //! Check if one point lies between two other points
            /*!
             * \param point             Point lying possibly outside the line segment
             * \param lineSegmentStart  First point determining the line segment
             * \param lineSegmentEnd    Second point determining the line segment
             */
            static bool isPointOnLineSegment(const cv::Point2f &point, const cv::Point2f &lineSegmentStart,
                                             const cv::Point2f &lineSegmentEnd);

            //! Check if points point1 and point2 are equal or not
            /*!
             * \param point1 One point
             * \param point2 The other point
             */
            static bool areEqualPoints(const cv::Point2f &point1, const cv::Point2f &point2);

            //! Check if the three points are collinear
            /*!
             * \param point1 The first point
             * \param point2 The second point
             * \param point3 The third point
             */
            static bool areCollinear(const cv::Point2f &point1, const cv::Point2f &point2,
                                     const cv::Point2f &point3);

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
            static double areaOfTriangle(const cv::Point2f &a, const cv::Point2f &b, const cv::Point2f &c);

            //! Convert the coordinates from integers to floating point for the given points collection
            /*!
             * \param pointsCollection  The given collection of points
             */
            template <typename SourceCoordinateType, typename DestinationCoordinateType>
            static std::vector<cv::Point_<DestinationCoordinateType>>
            convertPoints(const std::vector<cv::Point_<SourceCoordinateType>> &pointsCollection) {
                std::vector<cv::Point_<DestinationCoordinateType>> convertedPoints;

                for (const auto &point : pointsCollection) {
                    convertedPoints.push_back(
                        cv::Point_<DestinationCoordinateType>(
                            static_cast<DestinationCoordinateType>(point.x),
                            static_cast<DestinationCoordinateType>(point.y)
                        )
                    );
                }

                return convertedPoints;
            }

        private:

            //! Check if the given point is on the edge
            /*!
             *  A point "p" is considered to be on the edge if:
             *      ((p.x == 0) && (p.y >= 1) && (p.y <= nrOfCols)) OR
             *      ((p.x == nrOfRows) && (p.y >= 1) && (p.y <= nrOfCols)) OR
             *      ((p.y == 0) && (p.x >= 1) && (p.x <= nrOfRows)) OR
             *      ((p.y == nrOfCols) && (p.x >= 1) && (p.x <= nrOfRows))
             *
             *  \param p        The point p
             *  \param nrOfRows The number of rows
             *  \param nrOfCols The number of columns
             */
            static bool isPointOnEdge(const cv::Point2f &p, int nrOfRows, int nrOfCols);

            //! Check if the coordinate c lies between c1 and c2
            /*!
             * \param c  Coordinate c
             * \param c1 Coordinate c1
             * \param c2 Coordinate c2
             */
            template <typename T, typename U>
            static bool isBetweenCoordinates(T c, U c1, U c2);

            //! Translate a point by the given values
            /*!
             * \param point         The point
             * \param translation   Translation values
             */
            static void translate(cv::Point2f &point, const cv::Point2f &translation);

            //! Inverse translate a point by the given values
            /*!
             * \param point         The point
             * \param translation   Translation values
             */
            static void inverseTranslate(cv::Point2f &point, const cv::Point2f &translation);

            //! Treat the case when the line and circle intersect in two points
            /*!
             * \param circleOrigin          Origin of the circle
             * \param A                     y2 - y1
             * \param B                     x1 - x2
             * \param C                     A*x1 + B*y1
             * \param delta                 (4 * B^2 * C^2) - (4 * (A^2 + B^2) * (C^2 - (R^2 * A^2)))
             * \param intersectionPoints    Intersection points
             */
            static void lineCircleTwoIntersectionPoints(const cv::Point2f &circleOrigin, double A,
                                                        double B, double C, double delta,
                                                        std::vector<cv::Point2f> &intersectionPoints);

            //! Treat the case when the line and circle intersect in one point
            /*!
             * \param circleOrigin          Origin of the circle
             * \param A                     y2 - y1
             * \param B                     x1 - x2
             * \param C                     A*x1 + B*y1
             * \param delta                 (4 * B^2 * C^2) - (4 * (A^2 + B^2) * (C^2 - (R^2 * A^2)))
             * \param intersectionPoints    Intersection points
             */
            static void lineCircleOneIntersectionPoint(const cv::Point2f &circleOrigin,
                                                       double A, double B, double C, double delta,
                                                       std::vector<cv::Point2f> &intersectionPoints);

        public:

            // Constants
            static const double PI;
            static const int MATRIX_START_INDEX;

    };

};


#endif
