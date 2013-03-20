#ifndef GEOMETRY2D_HPP_
#define GEOMETRY2D_HPP_

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

#define PI                  3.141592
#define MATRIX_START_INDEX  1


namespace multiscale {

    //! Two-dimensional geometric operations
    class Geometry2D {

        public:

            //! Compute the distance between two points
            /*! Compute the Euclidean distance between two points
             * \param a Point a
             * \param b Point b
             */
            static double distanceBtwPoints(const Point &a, const Point &b);

            //! Compute the distance from a point to a line specified by two points
            /*!
             * \param a Point from which the distance is measures
             * \param linePointB One of the points determining the line
             * \param linePointC One of the points determining the line
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
             *\param a1 First point for determining the first line
             *\param b1 Second point for determining the first line
             *\param a2 First point for determining the second line
             *\param b2 Second point for determining the second line
             */
            static void orthogonalLineToAnotherLineEdgePoints(const Point &a1, const Point &b1, Point &a2,
                                                              Point &b2, int nrOfRows, int nrOfCols);

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
             *\param a1 First point for determining the first line
             *\param b1 Second point for determining the first line
             *\param a2 First point for determining the second line
             *\param b2 Second point for determining the second line
             *\param intersection The intersection point, if this point exists
             */
            static bool lineIntersection(const Point &a1, const Point &b1, const Point &a2, const Point &b2, Point &intersection);

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
             *\param a1 First point for determining the first line
             *\param b1 Second point for determining the first line
             *\param a2 First point for determining the second line
             *\param b2 Second point for determining the second line
             *\param intersection The intersection point, if this point exists
             */
            static bool lineSegmentIntersection(const Point &a1, const Point &b1, const Point &a2, const Point &b2, Point &intersection);

            //! Compute the angle between three points
            /*! Compute the angle between the lines determined by
             * points A, B and B, C
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
             *  \param points The set of points
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
            static bool isBetweenCoordinates(int c, int c1, int c2);

            //! Compute sgn(number)
            /*!
             *\param number The number
             */
            static int sgn(int number);

    };

};

#endif
