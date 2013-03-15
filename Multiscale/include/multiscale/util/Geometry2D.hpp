#ifndef GEOMETRY2D_HPP_
#define GEOMETRY2D_HPP_

using namespace cv;

namespace multiscale {

    //! Class for two-dimensional geometrical operations
    class Geometry2D {

        public:

            //! Compute the distance between two points
            /*! Compute the Euclidean distance between two points
             * \param a Point a
             * \param b Point b
             */
            double computeDistance(Point a, Point b);

            //! Compute the angle between three points
            /* Compute the angle between the lines determined by
             * points A, B and B, C
             * \param a Point a
             * \param b Point b
             * \param c Point c
             */
            double computeAngle(Point a, Point b, Point c);

    };

};

#endif
