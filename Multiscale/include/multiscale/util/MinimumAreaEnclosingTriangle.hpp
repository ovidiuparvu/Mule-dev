#ifndef MINIMUMAREAENCLOSINGTRIANGLE_HPP
#define MINIMUMAREAENCLOSINGTRIANGLE_HPP

#include "multiscale/util/Geometry2D.hpp"

using namespace cv;
using namespace multiscale;

#define ERR_MIDPOINT_SIDE_B     "The position of the middle point of side B could not be determined."
#define ERR_SIDE_B_GAMMA        "The position of side B could not be determined, because gamma(b) could not be computed."
#define ERR_VERTEX_C_ON_SIDE_B  "The position of the vertex C on side B could not be determined, because the considered lines do not intersect."
#define ERR_TRIANGLE_VERTICES   "The position of the triangle vertices could not be determined, because the sides of the triangle do not intersect."


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

            static unsigned int nrOfPoints;     /*!< Number of points defining the polygon */

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

            //! Initialisation function for the class
            static void initialise();

            //! Find the minimum area enclosing triangle for the given polygon
            /*!
             * \param minimumAreaEnclosingTriangle  Minimum area triangle enclosing the given polygon
             * \param area                          Area of the minimum area enclosing triangle
             */
            static void findMinimumAreaEnclosingTriangle(vector<Point> &minimumAreaEnclosingTriangle, double &area);

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

            //! Update sides A and C
            /*!
             * Side C will have as start and end vertices the polygon points "c" and "c-1"
             * Side A will have as start and end vertices the polygon points "a" and "a-1"
             */
            static void updateSidesCA();

            //! Update sides B and possibly A if tangency for side B was not obtained
            /*!
             * See paper for more details
             */
            static void updateSidesBA();

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

            //! Update the current minimum area enclosing triangle if the newly obtained one has a smaller area
            /*!
             * \param minimumAreaEnclosingTriangle      Minimum area triangle enclosing the given polygon
             * \param minimumAreaEnclosingTriangleArea  Area of the minimum area triangle enclosing the given polygon
             */
            static void updateMinimumAreaEnclosingTriangle(vector<Point> &minimumAreaEnclosingTriangle, double &minimumAreaEnclosingTriangleArea);

            //! Return the middle point of side B
            static Point middlePointOfSideB();

            //! Check if the line determined by gammaPoint and polygon[polygonPointIndex] intersects the polygon below the point polygon[polygonPointIndex]
            /*!
             * \param gammaPoint Gamma(p)
             * \param polygonPointIndex Index of the polygon point which is considered when determining the line
             */
            static bool intersectsBelow(const Point &gammaPoint, unsigned int polygonPointIndex);

            //! Check if the line determined by gammaPoint and polygon[polygonPointIndex] intersects the polygon below the point polygon[polygonPointIndex]
            /*!
             * \param predecessor                   Predecessor of polygon[polygonPointIndex]
             * \param point                         polygon[polygonPointIndex]
             * \param successor                     Successor of polygon[polygonPointIndex]
             * \param angleOfGammaAndPoint          Angle of line determined by gamma point and polygon[polygonPointIndex]
             * \param angleOfPointAndPredecessor    Angle of line determined by polygon[polygonPointIndex] and its predecessor
             * \param angleOfPointAndSuccessor      Angle of line determined by polygon[polygonPointIndex] and its successor
             */
            static bool intersectsBelow(const Point &predecessor, const Point &point, const Point &succesor,
                                        double angleOfGammaAndPoint, double angleOfPointAndPredecessor,
                                        double angleOfPointAndSuccessor);

            //! Check if the line determined by gammaPoint and polygon[polygonPointIndex] intersects the polygon above the point polygon[polygonPointIndex]
            /*!
             * \param gammaPoint Gamma(p)
             * \param polygonPointIndex Index of the polygon point which is considered when determining the line
             */
            static bool intersectsAbove(const Point &gammaPoint, unsigned int polygonPointIndex);

            //! Check if the line determined by gammaPoint and polygon[polygonPointIndex] intersects the polygon above the point polygon[polygonPointIndex]
            /*!
             * \param predecessor                   Predecessor of polygon[polygonPointIndex]
             * \param point                         polygon[polygonPointIndex]
             * \param successor                     Successor of polygon[polygonPointIndex]
             * \param angleOfGammaAndPoint          Angle of line determined by gamma point and polygon[polygonPointIndex]
             * \param angleOfPointAndPredecessor    Angle of line determined by polygon[polygonPointIndex] and its predecessor
             * \param angleOfPointAndSuccessor      Angle of line determined by polygon[polygonPointIndex] and its successor
             */
            static bool intersectsAbove(const Point &predecessor, const Point &point, const Point &succesor,
                                        double angleOfGammaAndPoint, double angleOfPointAndPredecessor,
                                        double angleOfPointAndSuccessor);

            //! Compute the height of the point specified by the given index
            /*!
             * See paper for more details
             *
             * \param polygonPointIndex Index of the polygon point
             */
            static double height(unsigned int polygonPointIndex);

            //! Compute the height of the point
            /*!
             * See paper for more details
             *
             * \param polygonPoint Polygon point
             */
            static double height(const Point &polygonPoint);

            //! Find gamma for a given point "p" specified by its index
            /*!
             * The function returns true if gamma exists i.e. if lines (a a-1) and (x y) intersect
             * and false otherwise. In case the two lines intersect in point intersectionPoint, gamma is computed.
             *
             * Considering that line (x y) is a line parallel to (c c-1) and that the distance between the lines is equal
             * to 2 * height(p), we can have two possible (x y) lines.
             *
             * Therefore, we will compute two intersection points between the lines (x y) and (a a-1) and take the
             * point which is closest to point polygon[a].
             *
             * See paper and formula for distance from point to a line for more details
             *
             * \param polygonPointIndex Index of the polygon point
             * \param gammaPoint        Point gamma(polygon[polygonPointIndex])
             */
            static bool gamma(unsigned int polygonPointIndex, Point &gammaPoint);

            //! Find vertex C which lies on side B at a distance = 2 * height(a-1) from side C
            /*!
             * Considering that line (x y) is a line parallel to (c c-1) and that the distance between the lines is equal
             * to 2 * height(a-1), we can have two possible (x y) lines.
             *
             * Therefore, we will compute two intersection points between the lines (x y) and (b b-1) and take the
             * point which is closest to point polygon[b].
             *
             * See paper and formula for distance from point to a line for more details
             */
            static Point findVertexCOnSideB();

            //! Find the intersection points to compute gamma(point)
            /*!
             * \param polygonPointIndex     Index of the polygon point for which the distance is known
             * \param side1StartVertex      Start vertex for side 1
             * \param side1EndVertex        End vertex for side 1
             * \param side2StartVertex      Start vertex for side 2
             * \param side2EndVertex        End vertex for side 2
             * \param intersectionPoint1    First intersection point between one pair of lines
             * \param intersectionPoint2    Second intersection point between another pair of lines
             */
            static bool findGammaIntersectionPoints(unsigned int polygonPointIndex, const Point &side1StartVertex,
                                                    const Point &side1EndVertex, const Point &side2StartVertex,
                                                    const Point &side2EndVertex, Point &intersectionPoint1,
                                                    Point &intersectionPoint2);

            //! Get the line equation parameters "a", "b" and "c" for the line determined by points "p" and "q"
            /*!
             * The equation of the line is considered in the general form:
             * ax + by + c = 0
             *
             * \param p One point for defining the equation of the line
             * \param q Second point for defining the equation of the line
             */
            static vector<double> lineEquationParameters(const Point& p, const Point &q);

            //! Advance the given index with one position
            /*!
             * \param index Index of the point
             */
            static void advance(unsigned int &index);

            //! Return the succesor of the provided point index
            /*!
             * The succesor of the last polygon point is the first polygon point
             * (circular referencing)
             *
             * \param index Index of the point
             */
            static unsigned int successor(unsigned int index);

            //! Return the predecessor of the provided point index
            /*!
             * The predecessor of the first polygon point is the last polygon point
             * (circular referencing)
             *
             * \param index Index of the point
             */
            static unsigned int predecessor(unsigned int index);

    };

};

#endif
