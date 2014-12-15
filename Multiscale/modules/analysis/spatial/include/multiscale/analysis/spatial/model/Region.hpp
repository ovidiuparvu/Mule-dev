#ifndef REGION_HPP
#define REGION_HPP

#include "multiscale/analysis/spatial/model/SpatialEntityPseudo3D.hpp"

#include "opencv2/imgproc/imgproc.hpp"

#include <vector>


namespace multiscale {

    namespace analysis {

        //! Class for representing a region
        class Region : public SpatialEntityPseudo3D {

            private:

                std::vector<cv::Point>
                    outerBorderPolygon;   /*!< Polygon defining the outer border of the region */
                std::vector<std::vector<cv::Point> >
                    innerBorderPolygons;  /*!< Polygon defining the inner borders of the region */

            public:
                
                Region(double density, double distanceFromOrigin, double angleWrtOrigin,
                       const std::vector<cv::Point> &outerBorderPolygon,
                       const std::vector<std::vector<cv::Point> > &innerBorderPolygons);
                ~Region();

                //! Get the polygon defining the outer border of the region
                const std::vector<cv::Point>& getOuterBorderPolygon() const;

                //! Get the polygons defining the inner borders of the region
                const std::vector<std::vector<cv::Point> > &getInnerBorderPolygons() const;

            private:

                //! Validate the input values
                /*!
                 * Validation rules:
                 *  0 < density
                 *  0 < distanceFromOrigin
                 *  0 <= angleWrtOrigin <= 360
                 *
                 *  For each polygon point p:
                 *      0 <= p.x
                 *      0 <= p.y
                 *
                 * \param density               The density of the region
                 * \param distanceFromOrigin    The distance from the origin
                 * \param angleWrtOrigin        The angle computed wrt to the origin
                 * \param outerBorderPolygon    The polygon defining the outer border of the region
                 * \param innerBorderPolygons   The polygon defining the inner borders of the region
                 */
                void validateInputValues(double density, double distanceFromOrigin, double angleWrtOrigin,
                                         const std::vector<cv::Point> &outerBorderPolygon,
                                         const std::vector<std::vector<cv::Point> > &innerBorderPolygons);

                //! Check if the input values are valid or not
                /*!
                 * Validation rules:
                 *  0 < density
                 *  0 < distanceFromOrigin
                 *  0 <= angleWrtOrigin <= 360
                 *
                 *  For each polygon point p:
                 *      0 <= p.x
                 *      0 <= p.y
                 *
                 * \param density               The density of the region
                 * \param distanceFromOrigin    The distance from the origin
                 * \param angleWrtOrigin        The angle computed wrt to the origin
                 * \param outerBorderPolygon    The polygon defining the outer border of the region
                 * \param innerBorderPolygons   The polygon defining the inner borders of the region
                 */
                bool areValidInputValues(double density, double distanceFromOrigin, double angleWrtOrigin,
                                         const std::vector<cv::Point> &outerBorderPolygon,
                                         const std::vector<std::vector<cv::Point> > &innerBorderPolygons);

                //! Check if the given input outer/inner border polygons are valid
                /*!
                 *  For each polygon p and each point a:
                 *      0 <= p.a.x
                 *      0 <= p.a.y
                 *
                 * \param outerBorderPolygon    The polygon defining the outer border of the region
                 * \param innerBorderPolygons   The polygon defining the inner borders of the region
                 */
                bool areValidInputPolygons(const std::vector<cv::Point> &outerBorderPolygon,
                                           const std::vector<std::vector<cv::Point> > &innerBorderPolygons);

                //! Check if the given input polygons are valid
                /*!
                 *  For each polygon p and each point a:
                 *      0 <= p.a.x
                 *      0 <= p.a.y
                 *
                 *  \param polygons The given collection of polygons
                 */
                bool areValidInputPolygons(const std::vector<std::vector<cv::Point> > &polygons);

                //! Check if the given input polygons are valid
                /*!
                 *  For each polygon point p:
                 *      0 <= p.x
                 *      0 <= p.y
                 *
                 *  \param polygon The given polygon
                 */
                bool isValidInputPolygon(const std::vector<cv::Point> &polygon);

                //! Update the value of the clusteredness degree
                void updateClusterednessDegree() override;

                //! Compute the value of the clusteredness degree if the outer border of the region is defined
                double computeClusterednessDegreeIfOuterBorderDefined();

                //! Update the value of the density
                void updateDensity() override;

                //! Update the area
                void updateArea() override;

                //! Update the spatial entity shape area
                void updateSpatialEntityShapeArea() override;

                //! Compute the value of the area if the outer border of the region is defined
                double computeAreaIfOuterBoderDefined();

                //! Compute the value of the spatial entity shape area if the outer border of the region is defined
                double computeSpatialEntityShapeAreaIfOuterBoderDefined();

                //! Update the perimeter
                void updatePerimeter() override;

                //! Get the measure that the cluster has a triangular shape
                double isTriangularMeasure() override;

                //! Get the measure that the cluster has a rectangular shape
                double isRectangularMeasure() override;

                //! Get the measure that the cluster has a circular shape
                double isCircularMeasure() override;

                //! Update the centre of the region
                void updateCentrePoint() override;

                //! Update the centre of the region in case the region is defined by a single point
                void updateCentrePointWhenRegionDefinedBySinglePoint();

                //! Update the centre of the region in case the region is defined by multiple points
                void updateCentrePointWhenRegionDefinedByMultiplePoints();

                //! Return the type of the pseudo 3D spatial entity
                SpatialEntityPseudo3DType type() override;

            private:

                // Constants
                static const bool CONTOUR_ORIENTED;
                static const bool CONTOUR_CLOSED;

        };

    };

};


#endif
