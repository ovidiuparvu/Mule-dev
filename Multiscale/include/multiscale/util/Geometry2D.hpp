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
            static double distanceBtwPoints(Point a, Point b);

            //! Compute the angle between three points
            /*! Compute the angle between the lines determined by
             * points A, B and B, C
             * \param a Point a
             * \param b Point b
             * \param c Point c
             */
            static double angleBtwPoints(Point a, Point b, Point c);

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
            static bool isPointOnEdge(Point p, int nrOfRows, int nrOfCols);

    };

};

#endif
