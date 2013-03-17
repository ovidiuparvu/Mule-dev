#ifndef GEOMETRY2D_HPP_
#define GEOMETRY2D_HPP_

using namespace cv;
using namespace std;


namespace multiscale {

    //! Two-dimensional geometric operations
    class Geometry2D {

        private:

            const int MATRIX_START_INDEX = 1;
            const double PI = 3.141592;

        public:

            //! Compute the distance between two points
            /*! Compute the Euclidean distance between two points
             * \param a Point a
             * \param b Point b
             */
            double computeDistance(Point a, Point b);

            //! Compute the angle between three points
            /*! Compute the angle between the lines determined by
             * points A, B and B, C
             * \param a Point a
             * \param b Point b
             * \param c Point c
             */
            double computeAngle(Point a, Point b, Point c);

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
            vector<Point> findPointsOnEdge(const vector<Point> &points, unsigned int nrOfRows, unsigned int nrOfCols);

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
            bool isPointOnEdge(Point p, int nrOfRows, int nrOfCols);

    };

};

#endif
