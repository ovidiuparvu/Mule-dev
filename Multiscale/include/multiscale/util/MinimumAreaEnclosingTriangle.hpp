#ifndef MINIMUMAREAENCLOSINGTRIANGLE_HPP
#define MINIMUMAREAENCLOSINGTRIANGLE_HPP

#include "multiscale/util/Geometry2D.hpp"

using namespace cv;
using namespace multiscale;

namespace multiscale {

    //! Class for computing the minimum area enclosing triangle for a given polygon
    /*!
     * This implementation has a linear complexity (theta(n)) with respect to the number of points
     * defining the polygon and is based on the algorithm described in the following paper:
     *
     * J. O’Rourke, A. Aggarwal, S. Maddila, and M. Baldwin, ‘An optimal algorithm for finding minimal
     * enclosing triangles’, Journal of Algorithms, vol. 7, no. 2, pp. 258–269, Jun. 1986.
     */
    class MinimumAreaEnclosingTriangle {

        private:

            static Point vertexA;               /*!< Vertex A of the current considered enclosing triangle */
            static Point vertexB;               /*!< Vertex B of the current considered enclosing triangle */
            static Point vertexC;               /*!< Vertex C of the current considered enclosing triangle */

            static Point sideAStartVertex;      /*!< Starting vertex for side A of triangle */
            static Point sideAEndVertex;        /*!< Ending vertex for side A of triangle */

            static Point sideBStartVertex;      /*!< Starting vertex for side B of triangle */
            static Point sideBEndVertex;        /*!< Ending vertex for side B of triangle */

            static Point sideCStartVertex;      /*!< Starting vertex for side C of triangle */
            static Point sideCEndVertex;        /*!< Ending vertex for side C of triangle */

            static double area;                 /*!< Area of the current considered enclosing triangle */

            static unsigned int a;              /*!< Index of point "a"; see paper for more details */
            static unsigned int b;              /*!< Index of point "b"; see paper for more details */
            static unsigned int c;              /*!< Index of point "c"; see paper for more details */

            static vector<Point> polygon;       /*!< Polygon for which the minimum area enclosing triangle is computed */

        public:

            //! Find the minimum area enclosing triangle for the given polygon
            /*!
             * \param polygon                       Polygon of points for which the minimum area enclosing triangle will be  found
             * \param minimumAreaEnclosingTriangle  Minimum area triangle enclosing the given polygon
             * \param area                          Area of the minimum area enclosing triangle
             */
            static void find(const vector<Point> &polygon, vector<Point> &minimumAreaEnclosingTriangle, double &area);

        private:

            //! Find the minimum area enclosing triangle for the given polygon
            /*!
             * \param polygon                       Polygon of points for which the minimum area enclosing triangle will be  found
             * \param minimumAreaEnclosingTriangle  Minimum area triangle enclosing the given polygon
             * \param area                          Area of the minimum area enclosing triangle
             */
            static void findMinimumAreaEnclosingTriangle(const vector<Point> &polygon, vector<Point> &minimumAreaEnclosingTriangle,
                                                         double &area);

            //! Initialisation function for the class
            static void initialise();

            //! Advance b to the right chain
            /*!
             * See paper for more details
             */
            static void advanceBToRightChain();

            //! Move "a" if it is low and "b" if it is high
            /*!
            * See paper for more details
            */
            static void moveAIfLowAndBIfHigh();

            //! Search for the tangency of side B
            /*!
            * See paper for more details
            */
            static void searchForBTangency();

            //! Check if tangency for side B was not obtained
            /*!
            * See paper for more details
            */
            static bool isNotBTangency();

            //! Update sides B and possibly A if tangency for side B was not obtained
            /*!
            * See paper for more details
            */
            static void updateSides();

            //! Set side B if tangency for side B was obtained
            /*!
            * See paper for more details
            */
            static void updateSideB();

            //! Update the triangle vertices after all sides were set
            /*!
            * See paper for more details
            */
            static void updateTriangleVertices();

            //! Update the current minimum area enclosing triangle if the new obtained one has a smaller area
            /*!
            * See paper for more details
            */
            static void updateMinimumAreaEnclosingTriangle();

    };

};

#endif
