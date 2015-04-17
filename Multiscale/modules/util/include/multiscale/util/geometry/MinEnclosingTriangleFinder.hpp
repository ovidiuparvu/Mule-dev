#ifndef MINENCLOSINGTRIANGLEFINDER_HPP
#define MINENCLOSINGTRIANGLEFINDER_HPP

#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale;


namespace multiscale {

    //! Class for computing the minimum area enclosing triangle for a given polygon
    /*!
     * This implementation has a linear complexity (theta(n)) with respect to the number of points
     * defining the convex polygon and is based on the algorithm described in the following paper:
     *
     * J. O’Rourke, A. Aggarwal, S. Maddila, and M. Baldwin, ‘An optimal algorithm for finding minimal
     * enclosing triangles’, Journal of Algorithms, vol. 7, no. 2, pp. 258–269, Jun. 1986.
     */
    class MinEnclosingTriangleFinder {

        private:

            unsigned int validationFlag;        /*!< Validation flag can take the following values:
                                                         - VALIDATION_SIDE_A_TANGENT;
                                                         - VALIDATION_SIDE_B_TANGENT;
                                                         - VALIDATION_SIDES_FLUSH.
                                                 */

            cv::Point2f vertexA;                /*!< Vertex A of the current considered enclosing triangle */
            cv::Point2f vertexB;                /*!< Vertex B of the current considered enclosing triangle */
            cv::Point2f vertexC;                /*!< Vertex C of the current considered enclosing triangle */

            cv::Point2f sideAStartVertex;       /*!< Starting vertex for side A of triangle */
            cv::Point2f sideAEndVertex;         /*!< Ending vertex for side A of triangle */

            cv::Point2f sideBStartVertex;       /*!< Starting vertex for side B of triangle */
            cv::Point2f sideBEndVertex;         /*!< Ending vertex for side B of triangle */

            cv::Point2f sideCStartVertex;       /*!< Starting vertex for side C of triangle */
            cv::Point2f sideCEndVertex;         /*!< Ending vertex for side C of triangle */

            double area;                        /*!< Area of the current considered enclosing triangle */

            unsigned int a;                     /*!< Index of point "a"; see paper for more details */
            unsigned int b;                     /*!< Index of point "b"; see paper for more details */
            unsigned int c;                     /*!< Index of point "c"; see paper for more details */

            unsigned int nrOfPoints;            /*!< Number of points defining the polygon */

            std::vector<cv::Point2f> polygon;   /*!< Polygon for which the minimum area enclosing triangle
                                                     is computed */

        public:

            MinEnclosingTriangleFinder();
            ~MinEnclosingTriangleFinder();

            //! Find the minimum area enclosing triangle for the given 2D point set
            /*!
             * Precondition: Number of points in the set is at least 1.
             *
             * \param points                        Set of points
             * \param minEnclosingTriangle          Minimum area triangle enclosing the given polygon
             */
            double find(const std::vector<cv::Point2f> &points,
                        std::vector<cv::Point2f> &minEnclosingTriangle);

        private:

            //! Find the minimum area enclosing triangle for the given 2D point set
            /*!
             * \param points                        Set of points
             * \param minEnclosingTriangle          Minimum area triangle enclosing the given polygon
             */
            double findMinTriangle(const std::vector<cv::Point2f> &points,
                                   std::vector<cv::Point2f> &minEnclosingTriangle);

            //! Initialisation function for the class
            /*!
             * Initialize the polygon and other class' fields.
             *
             * \param points                Set of points
             * \param minEnclosingTriangle  Minimum area triangle enclosing the given polygon
             */
            void initialize(const std::vector<cv::Point2f> &points,
                            std::vector<cv::Point2f> &minEnclosingTriangle);

            //! Initialize polygon as the convex hull of the given set of points
            /*!
             * \param points Set of points
             */
            void initializeConvexPolygon(const std::vector<cv::Point2f> &points);

            //! Find the minimum area enclosing triangle for the given polygon
            /*!
             * \param polygon                       Polygon of points for which the minimum area enclosing triangle will be  found
             * \param minEnclosingTriangle          Minimum area triangle enclosing the given polygon
             */
            double findMinEnclosingTriangle(const std::vector<cv::Point2f> &polygon,
                                            std::vector<cv::Point2f> &minEnclosingTriangle);

            //! Return the minimum area enclosing triangle in case the given polygon has at most three points
            /*!
             * \param polygon                       Polygon of points for which the minimum area enclosing triangle will be  found
             * \param minEnclosingTriangle          Minimum area triangle enclosing the given polygon
             */
            double returnMinEnclosingTriangle(const std::vector<cv::Point2f> &polygon,
                                              std::vector<cv::Point2f> &minEnclosingTriangle);

            //! Initialisation of the algorithm variables
            void initializeAlgorithmVariables();

            //! Find the minimum area enclosing triangle for the given polygon
            /*!
             * \param minEnclosingTriangle      Minimum area triangle enclosing the given polygon
             * \param minEnclosingTriangleArea  Area of the minimum area enclosing triangle
             */
            void findMinEnclosingTriangle(std::vector<cv::Point2f> &minEnclosingTriangle,
                                          double &minEnclosingTriangleArea);

            //! Advance b to the right chain
            /*!
             * See paper for more details
             */
            void advanceBToRightChain();

            //! Move "a" if it is low and "b" if it is high
            /*!
             * See paper for more details
             */
            void moveAIfLowAndBIfHigh();

            //! Search for the tangency of side B
            /*!
             * See paper for more details
             */
            void searchForBTangency();

            //! Check if tangency for side B was not obtained
            /*!
             * See paper for more details
             */
            bool isNotBTangency();

            //! Update sides A and C
            /*!
             * Side C will have as start and end vertices the polygon points "c" and "c-1"
             * Side A will have as start and end vertices the polygon points "a" and "a-1"
             */
            void updateSidesCA();

            //! Update sides B and possibly A if tangency for side B was not obtained
            /*!
             * See paper for more details
             */
            void updateSidesBA();

            //! Set side B if tangency for side B was obtained
            /*!
             * See paper for more details
             */
            void updateSideB();

            //! Update the triangle vertices after all sides were set and check if a local minimal triangle was found
            /*!
             * See paper for more details
             */
            bool isLocalMinimalTriangle();

            //! Check if the found minimal triangle is valid
            /*!
             * This means that all midpoints of the triangle should touch the polygon
             *
             * See paper for more details
             */
            bool isValidMinimalTriangle();

            //! Update the current minimum area enclosing triangle if the newly obtained one has a smaller area
            /*!
             * \param minEnclosingTriangle      Minimum area triangle enclosing the given polygon
             * \param minEnclosingTriangleArea  Area of the minimum area triangle enclosing the given polygon
             */
            void updateMinEnclosingTriangle(std::vector<cv::Point2f> &minEnclosingTriangle,
                                            double &minEnclosingTriangleArea);

            //! Return the middle point of side B
            bool middlePointOfSideB(cv::Point2f& middlePointOfSideB);

            //! Check if the line determined by gammaPoint and polygon[polygonPointIndex] intersects the polygon below
            /*! Check if the line determined by gammaPoint and polygon[polygonPointIndex] intersects the polygon below
             *  the point polygon[polygonPointIndex]
             *
             * \param gammaPoint Gamma(p)
             * \param polygonPointIndex Index of the polygon point which is considered when determining the line
             */
            bool intersectsBelow(const cv::Point2f &gammaPoint,
                                 unsigned int polygonPointIndex);

            //! Check if the line determined by gammaPoint and polygon[polygonPointIndex] intersects the polygon above
            /*! Check if the line determined by gammaPoint and polygon[polygonPointIndex] intersects the polygon above
             *  the point polygon[polygonPointIndex]
             *
             * \param gammaPoint        Gamma(p)
             * \param polygonPointIndex Index of the polygon point which is considered when determining the line
             */
            bool intersectsAbove(const cv::Point2f &gammaPoint,
                                 unsigned int polygonPointIndex);

            //! Check if/where the line determined by gammaPoint and polygon[polygonPointIndex] intersects the polygon
            /*!
             * \param angleOfGammaAndPoint  Angle between gammaPoint and polygon[polygonPointIndex]
             * \param polygonPointIndex     Index of the polygon point which is considered when determining the line
             */
            unsigned int intersects(double angleOfGammaAndPoint,
                                    unsigned int polygonPointIndex);

            //! If (gamma(x) x) intersects P between successorOrPredecessorIndex and pointIntex is it above/below?
            /*!
             * \param successorOrPredecessorIndex Index of the successor or predecessor
             * \param pointIndex                  Index of the point x in the polygon
             */
            unsigned int intersectsAboveOrBelow(unsigned int successorOrPredecessorIndex,
                                                unsigned int pointIndex);

            //! Check if the flush edge (opposite) angle lies between the predecessor and successor angle
            /*!
             * \param angleFlushEdge    Angle of the flush edge
             * \param anglePredecessor  Angle of the predecessor
             * \param angleSuccessor    Angle of the successor
             */
            bool isFlushAngleBetweenPredecessorAndSuccessor(double &angleFlushEdge,
                                                            double anglePredecessor,
                                                            double angleSuccessor);

            //! Check if the angle of the line (gamma(p) p) or its opposite angle lie between angle1 and angle2
            /*!
             * \param gammaAngle    Angle of the line (gamma(p) p)
             * \param angle1        One of the boundary angles
             * \param angle2        Another boundary angle
             */
            bool isGammaAngleBetween(double &gammaAngle, double angle1, double angle2);

            //! Check if the angle of the line (gamma(p) p) or its opposite angle is equal to the given angle
            /*!
             * \param gammaAngle    Angle of the line (gamma(p) p)
             * \param angle         Angle to compare against
             */
            bool isGammaAngleEqualTo(double &gammaAngle, double angle);

            //! Compute the height of the point specified by the given index
            /*!
             * See paper for more details
             *
             * \param polygonPointIndex Index of the polygon point
             */
            double height(unsigned int polygonPointIndex);

            //! Compute the height of the point
            /*!
             * See paper for more details
             *
             * \param polygonPoint Polygon point
             */
            double height(const cv::Point2f &polygonPoint);

            //! Find gamma for a given point "p" specified by its index
            /*!
             * The function returns true if gamma exists i.e. if lines (a a-1) and (x y) intersect
             * and false otherwise. In case the two lines intersect in point intersectionPoint, gamma is computed.
             *
             * Considering that line (x y) is a line parallel to (c c-1) and that the distance between the lines
             * is equal to 2 * height(p), we can have two possible (x y) lines.
             *
             * Therefore, we will compute two intersection points between the lines (x y) and (a a-1) and take the
             * point which is closest to point polygon[a].
             *
             * See paper and formula for distance from point to a line for more details
             *
             * \param polygonPointIndex Index of the polygon point
             * \param gammaPoint        cv::Point2f gamma(polygon[polygonPointIndex])
             */
            bool gamma(unsigned int polygonPointIndex, cv::Point2f &gammaPoint);

            //! Find vertex C which lies on side B at a distance = 2 * height(a-1) from side C
            /*!
             * Considering that line (x y) is a line parallel to (c c-1) and that the distance between the lines is
             * equal to 2 * height(a-1), we can have two possible (x y) lines.
             *
             * Therefore, we will compute two intersection points between the lines (x y) and (b b-1) and take the
             * point which is closest to point polygon[b].
             *
             * See paper and formula for distance from point to a line for more details
             */
            cv::Point2f findVertexCOnSideB();

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
            bool findGammaIntersectionPoints(unsigned int polygonPointIndex,
                                             const cv::Point2f &side1StartVertex,
                                             const cv::Point2f &side1EndVertex,
                                             const cv::Point2f &side2StartVertex,
                                             const cv::Point2f &side2EndVertex,
                                             cv::Point2f &intersectionPoint1,
                                             cv::Point2f &intersectionPoint2);

            //! Check if the given lines are identical or not
            /*!
             * The lines are specified as:
             *      ax + by + c = 0
             *  OR
             *      ax + by + c (+/-) sideCExtraParam = 0
             *
             * \param side1Params       Vector containing the values of a, b and c for side 1
             * \param side2Params       Vector containing the values of a, b and c for side 2
             * \param sideCExtraParam   Extra parameter for the flush edge C
             */
            bool areIdenticalLines(const std::vector<double> &side1Params,
                                   const std::vector<double> &side2Params,
                                   double sideCExtraParam);

            //! Check if the given lines intersect or not. If the lines intersect find their intersection points.
            /*!
             * The lines are specified as:
             *      ax + by + c = 0
             *  OR
             *      ax + by + c (+/-) sideCExtraParam = 0
             *
             * \param side1Params           Vector containing the values of a, b and c for side 1
             * \param side2Params           Vector containing the values of a, b and c for side 2
             * \param sideCExtraParam       Extra parameter for the flush edge C
             * \param intersectionPoint1    The first intersection point, if it exists
             * \param intersectionPoint2    The second intersection point, if it exists
             */
            bool areIntersectingLines(const std::vector<double> &side1Params,
                                      const std::vector<double> &side2Params,
                                      double sideCExtraParam,
                                      cv::Point2f &intersectionPoint1,
                                      cv::Point2f &intersectionPoint2);

            //! Get the line equation parameters "a", "b" and "c" for the line determined by points "p" and "q"
            /*!
             * The equation of the line is considered in the general form:
             * ax + by + c = 0
             *
             * \param p One point for defining the equation of the line
             * \param q Second point for defining the equation of the line
             */
            std::vector<double> lineEquationParameters(const cv::Point2f& p, const cv::Point2f &q);

            //! Advance the given index with one position
            /*!
             * \param index Index of the point
             */
            void advance(unsigned int &index);

            //! Return the succesor of the provided point index
            /*!
             * The succesor of the last polygon point is the first polygon point
             * (circular referencing)
             *
             * \param index Index of the point
             */
            unsigned int successor(unsigned int index);

            //! Return the predecessor of the provided point index
            /*!
             * The predecessor of the first polygon point is the last polygon point
             * (circular referencing)
             *
             * \param index Index of the point
             */
            unsigned int predecessor(unsigned int index);

            //! Check if the provided real numbers are "almost" equal
            /*! The expression for determining if two real numbers x and y are equal is:
             *  (Abs(x - y) <= EPSILON * Max(1.0f, Abs(x), Abs(y))).
             *
             *  \param lhsNumber    The left hand side real number
             *  \param rhsNumber    The right hand side real number
             */
            bool almostEqual(float lhsNumber, float rhsNumber);

        private:

            // Constants
            static const float EPSILON;

            static const bool CONVEX_HULL_CLOCKWISE;

            static const unsigned int INTERSECTS_BELOW;
            static const unsigned int INTERSECTS_ABOVE;
            static const unsigned int INTERSECTS_CRITICAL;
            static const unsigned int INTERSECTS_LIMIT;

            static const std::string ERR_NR_POINTS;
            static const std::string ERR_MIDPOINT_SIDE_B;
            static const std::string ERR_SIDE_B_GAMMA;
            static const std::string ERR_VERTEX_C_ON_SIDE_B;
            static const std::string ERR_TRIANGLE_VERTICES;

            static const unsigned int VALIDATION_SIDE_A_TANGENT;
            static const unsigned int VALIDATION_SIDE_B_TANGENT;
            static const unsigned int VALIDATION_SIDES_FLUSH;

    };

};


#endif
