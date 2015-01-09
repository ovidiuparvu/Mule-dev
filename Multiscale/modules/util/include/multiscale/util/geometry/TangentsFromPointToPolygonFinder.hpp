#ifndef TANGENTSFROMPOINTTOPOLYGONFINDER_HPP
#define TANGENTSFROMPOINTTOPOLYGONFINDER_HPP

#include "multiscale/util/Geometry2D.hpp"

#include "opencv2/core/core.hpp"

# include <vector>


namespace multiscale {

    //! Class for finding the tangents from a point to a polygon
    template <typename PolygonPointsType, typename ReferencePointType>
    class TangentsFromPointToPolygonFinder {

        private:

            std::vector<cv::Point_<PolygonPointsType>>
                polygon;                                    /*!< The polygon for which the tangents will
                                                                 be computed */
            std::size_t
                nrOfPolygonPoints;                          /*!< The number of points defining the polygon */

            cv::Point_<ReferencePointType>
                referencePoint;                             /*!< The reference point through which the
                                                                 tangents pass */

            std::size_t a;                                  /*!< Index a (0-based) used in the algorithms */
            std::size_t b;                                  /*!< Index b (0-based) used in the algorithms */
            std::size_t c;                                  /*!< Index c (0-based) used in the algorithms */

            bool isEdgeADown;                               /*!< Flag indicating if the edge A is pointing
                                                                 down */
            bool isEdgeAUp;                                 /*!< Flag indicating if the edge A is pointing
                                                                 up */
            bool isEdgeCDown;                               /*!< Flag indicating if the edge C is pointing
                                                                 down */


        public:

            TangentsFromPointToPolygonFinder(const std::vector<cv::Point_<PolygonPointsType>> &polygon,
                                             const cv::Point_<ReferencePointType> &referencePoint)
                                             : referencePoint(referencePoint) {
                initialise(polygon);
            }

            //! Compute the two polygon points through which the left, respectively right tangents pass
            /*! Each of the tangent lines passes through one or more polygon points and the reference point.
             *
             * If the reference point lies inside the convex hull of the provided polygon then
             * the left and right most tangent points are set to (0, 0).
             *
             * If the number of points in the convex hull of the provided polygon is equal to:
             *    + 2, then the left and right most tangent points are the two polygon points;
             *    + 1, then the left and right most tangent points are identical with the polygon point;
             *    + 0, then the left and right most tangent points are set to (0, 0).
             *
             * The employed algorithms are based on the information presented at:
             * http://geomalgorithms.com/a15-_tangents.html (Accessed on: 16.12.2014)
             * However one problem with the algorithms presented at the above website is that
             * they enter an infinite loop whenever a tangent to the polygon does not exist i.e.
             * the tangent contains one of the sides of the polygon rather than a point.
             *
             * \param leftMostTangentPoint  The polygon point through which the left tangent passes
             * \param rightMostTangentPoint The polygon point through which the right tangent passes
             */
            void
            computeTangentsPointsForConvexPolygon(cv::Point_<PolygonPointsType> &leftMostTangentPoint,
                                                  cv::Point_<PolygonPointsType> &rightMostTangentPoint) {
                initialiseAlgorithmVariables();

                computeTangentsPointsWithInitialisedAlgorithmVariables(
                    leftMostTangentPoint, rightMostTangentPoint
                );
            }

        private:

            //! Initialisation function
            /*!
             * \param polygon   The polygon for which the tangents will be computed
             */
            void
            initialise(const std::vector<cv::Point_<PolygonPointsType>> &polygon) {
                initialisePolygon(polygon);
                initialiseAlgorithmVariables();
            }

            //! Initialisation of the polygon
            /*!
             * If the given polygon is concave then its convex hull is considered.
             *
             * \param polygon   The polygon for which the tangents will be computed
             */
            void
            initialisePolygon(const std::vector<cv::Point_<PolygonPointsType>> &polygon) {
                if (Geometry2D::isConvexPolygon(polygon)) {
                    this->polygon = polygon;
                } else {
                    this->polygon = Geometry2D::computeConvexHull(polygon);
                }

                nrOfPolygonPoints = polygon.size();
            }

            //! Initialise the variables employed by the tangent points finding algorithm
            void initialiseAlgorithmVariables() {
                a = 0;
                b = nrOfPolygonPoints;
                c = 0;

                isEdgeADown = false;
                isEdgeAUp   = false;
                isEdgeCDown = false;
            }

            //! Compute the two tangent points assuming the algorithm variables were initialised
            /*!
             * \param leftMostTangentPoint  The polygon point through which the left tangent passes
             * \param rightMostTangentPoint The polygon point through which the right tangent passes
             */
            void
            computeTangentsPointsWithInitialisedAlgorithmVariables(cv::Point_<PolygonPointsType>
                                                                   &leftMostTangentPoint,
                                                                   cv::Point_<PolygonPointsType>
                                                                   &rightMostTangentPoint) {
                if (Geometry2D::isPointInsidePolygon(referencePoint, polygon)) {
                    setTangentPointsCoordinatesZero(leftMostTangentPoint, rightMostTangentPoint);
                } else {
                    computeTangentsPointsWhenReferencePointOutsidePolygon(
                        leftMostTangentPoint,
                        rightMostTangentPoint
                    );
                }
            }

            //! Compute the two tangent points assuming the reference point lies outside the polygon
            /*!
             * \param leftMostTangentPoint  The polygon point through which the left tangent passes
             * \param rightMostTangentPoint The polygon point through which the right tangent passes
             */
            void
            computeTangentsPointsWhenReferencePointOutsidePolygon(cv::Point_<PolygonPointsType>
                                                                  &leftMostTangentPoint,
                                                                  cv::Point_<PolygonPointsType>
                                                                  &rightMostTangentPoint) {
                if (nrOfPolygonPoints == 0) {
                    setTangentPointsCoordinatesZero(
                        leftMostTangentPoint,
                        rightMostTangentPoint
                    );
                } else if (nrOfPolygonPoints <= 2) {
                    leftMostTangentPoint  = polygon[0 % nrOfPolygonPoints];
                    rightMostTangentPoint = polygon[1 % nrOfPolygonPoints];
                } else {
                    leftMostTangentPoint  = computeLeftMostTangentPoint();
                    rightMostTangentPoint = computeRightMostTangentPoint();
                }
            }

            //! Compute the left-most polygon tangent point considering the given reference point
            /*! The tangent point is found using a binary search like procedure.
             */
            cv::Point_<PolygonPointsType>
            computeLeftMostTangentPoint() {
                initialiseAlgorithmVariables();

                if (isFirstPolygonPointTheLeftMostTangentPoint()) {
                    return polygon[0];
                } else {
                    return searchForLeftMostTangentPoint();
                }
            }

            //! Compute the right-most polygon tangent point considering the given reference point
            /*! The tangent point is found using a binary search like procedure.
             */
            cv::Point_<PolygonPointsType>
            computeRightMostTangentPoint() {
                initialiseAlgorithmVariables();

                if (isFirstPolygonPointTheRightMostTangentPoint()) {
                    return polygon[0];
                } else {
                    return searchForRightMostTangentPoint();
                }
            }

            //! Check if the first polygon point is the left most tangent point
            bool
            isFirstPolygonPointTheLeftMostTangentPoint() {
                return (
                    !Geometry2D::isToTheRightOfLine(
                        referencePoint,
                        polygon[nrOfPolygonPoints - 1],
                        polygon[0]
                    ) && !Geometry2D::isToTheRightOfLine(
                        referencePoint,
                        polygon[1],
                        polygon[0]
                    )
                );
            }

            //! Check if the first polygon point is the right most tangent point
            bool
            isFirstPolygonPointTheRightMostTangentPoint() {
                return (
                    !Geometry2D::isToTheLeftOfLine(
                        referencePoint,
                        polygon[1],
                        polygon[0]
                    ) && !Geometry2D::isToTheLeftOfLine(
                        referencePoint,
                        polygon[nrOfPolygonPoints - 1],
                        polygon[0]
                    )
                );
            }

            //! Search for the left most tangent point
            cv::Point_<PolygonPointsType>
            searchForLeftMostTangentPoint() {
                for (;;) {
                    updateCValue();
                    updateEdgeCFlag();

                    if (isPointCLeftMostTangentPoint()) {
                        return polygon[c];
                    } else {
                        updateLeftMostTangentPointSubChain();
                    }
                }

                // Line added to avoid "control reaches end of non-void function" warnings
                return cv::Point2f();
            }

            //! Search for the right most tangent point
            cv::Point_<PolygonPointsType>
            searchForRightMostTangentPoint() {
                for (;;) {
                    updateCValue();
                    updateEdgeCFlag();

                    if (isPointCRightMostTangentPoint()) {
                        return polygon[c];
                    } else {
                        updateRightMostTangentPointSubChain();
                    }
                }

                // Line added to avoid "control reaches end of non-void function" warnings
                return cv::Point2f();
            }

            //! Check if the c-th polygon point is the left most tangent point
            bool
            isPointCLeftMostTangentPoint() {
                return (
                    !Geometry2D::isToTheRightOfLine(
                        referencePoint,
                        polygon[predecessor(c, nrOfPolygonPoints)],
                        polygon[c]
                    ) && (
                        !isEdgeCDown
                    )
                );
            }

            //! Check if the c-th polygon point is the right most tangent point
            bool
            isPointCRightMostTangentPoint() {
                return (
                    (
                        isEdgeCDown ||
                        Geometry2D::areCollinear(
                            referencePoint,
                            polygon[successor(c, nrOfPolygonPoints)],
                            polygon[c]
                        )
                    ) && !Geometry2D::isToTheLeftOfLine(
                        referencePoint,
                        polygon[predecessor(c, nrOfPolygonPoints)],
                        polygon[c]
                    )
                );
            }

            //! Narrow the side chain in which the search for the left most tangent point continues
            void
            updateLeftMostTangentPointSubChain() {
                updateEdgeADownFlag();

                if (isEdgeADown) {
                    updateLeftMostTangentPointSubChainEdgeADown();

                } else {
                    updateLeftMostTangentPointSubChainEdgeAUp();
                }
            }

            //! Narrow the side chain in which the search for the right most tangent point continues
            void
            updateRightMostTangentPointSubChain() {
                updateEdgeAUpFlag();

                if (isEdgeAUp) {
                    updateRightMostTangentPointSubChainEdgeAUp();
                } else {
                    updateRightMostTangentPointSubChainEdgeADown();
                }
            }

            //! Narrow the side chain in which the search for the left most tangent point continues if edge A is down
            void
            updateLeftMostTangentPointSubChainEdgeADown() {
                if (!isEdgeCDown) {
                    b = c;
                } else {
                    if (isPointABelowPointC()) {
                        b = c;
                    } else {
                        a = c;
                    }
                }
            }

            //! Narrow the side chain in which the search for the right most tangent point continues if edge A is down
            void
            updateRightMostTangentPointSubChainEdgeADown() {
                if (!isEdgeCDown) {
                    a = c;
                } else {
                    if (isPointABelowPointC()) {
                        b = c;
                    } else {
                        a = c;
                    }
                }
            }

            //! Narrow the side chain in which the search for the left most tangent point continues if edge A is up
            void
            updateLeftMostTangentPointSubChainEdgeAUp() {
                if (isEdgeCDown) {
                    a = c;
                } else {
                    if (isPointAAbovePointC()) {
                        b = c;
                    } else {
                        a = c;
                    }
                }
            }

            //! Narrow the side chain in which the search for the right most tangent point continues if edge A is up
            void
            updateRightMostTangentPointSubChainEdgeAUp() {
                if (isEdgeCDown) {
                    b = c;
                } else {
                    if (isPointAAbovePointC()) {
                        b = c;
                    } else {
                        a = c;
                    }
                }
            }

            //! Check if point A is below point C
            bool
            isPointABelowPointC() {
                return (
                    Geometry2D::isToTheRightOfLine(
                        referencePoint,
                        polygon[a],
                        polygon[c]
                    )
                );
            }

            //! Check if point A is above point C
            bool
            isPointAAbovePointC() {
                return (
                    Geometry2D::isToTheLeftOfLine(
                        referencePoint,
                        polygon[a],
                        polygon[c]
                    )
                );
            }

            //! Set the value of index c as half of the sum of indices a and b
            void
            updateCValue() {
                c = (a + b) / 2;
            }

            //! Update the edge C related flag
            void
            updateEdgeCFlag() {
                isEdgeCDown = Geometry2D::isToTheRightOfLine(
                                  referencePoint,
                                  polygon[successor(c, nrOfPolygonPoints)],
                                  polygon[c]
                              );
            }

            //! Update the edge A up flag
            void
            updateEdgeAUpFlag() {
                isEdgeAUp = Geometry2D::isToTheLeftOfLine(
                                referencePoint,
                                polygon[successor(a, nrOfPolygonPoints)],
                                polygon[a]
                            );
            }

            //! Update the edge A down flag
            void
            updateEdgeADownFlag() {
                isEdgeADown = Geometry2D::isToTheRightOfLine(
                                  referencePoint,
                                  polygon[successor(a, nrOfPolygonPoints)],
                                  polygon[a]
                              );
            }

            //! Set the coordinates of the tangent points to zero
            void
            setTangentPointsCoordinatesZero(cv::Point_<PolygonPointsType> &leftMostTangentPoint,
                                            cv::Point_<PolygonPointsType> &rightMostTangentPoint) {
                leftMostTangentPoint.x = 0;
                leftMostTangentPoint.y = 0;

                rightMostTangentPoint.x = 0;
                rightMostTangentPoint.y = 0;
            }

            //! Return the predecessor of the provided index
            /*!
             * \param currentIndex  The current index (0-based)
             * \param nrOfIndices   The total number of indices
             */
            std::size_t
            predecessor(std::size_t currentIndex, std::size_t nrOfIndices) {
                return (
                    (currentIndex == 0)
                        ? (nrOfIndices - 1)
                        : (currentIndex - 1)
                );
            }

            //! Return the successor of the provided index
            /*!
             * \param currentIndex  The current index (0-based)
             * \param nrOfIndices   The total number of indices
             */
            std::size_t
            successor(std::size_t currentIndex, std::size_t nrOfIndices) {
                return (
                    (currentIndex + 1) % nrOfIndices
                );
            }

    };

};

#endif
