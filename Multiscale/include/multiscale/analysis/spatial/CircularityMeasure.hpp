#ifndef CIRCULARITYMEASURE_HPP_
#define CIRCULARITYMEASURE_HPP_

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <vector>

using namespace cv;
using namespace std;


namespace multiscale {

    namespace analysis {

        class CircularityMeasure {

            public:

                //! Compute circularity measure for the given collection of points
                /*!
                 * The circularity measure is equal to the standard circularity measure described in the
                 * following paper:
                 *
                 * Joviša Žunić, Kaoru Hirota, Paul L. Rosin, A Hu moment invariant as a shape circularity measure,
                 * Pattern Recognition, Volume 43, Issue 1, January 2010, Pages 47-57, ISSN 0031-3203,
                 * http://dx.doi.org/10.1016/j.patcog.2009.06.017.
                 */
                static double compute(const vector<Point2f> &points);

        };

    };

};

#endif
