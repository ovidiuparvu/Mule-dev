#ifndef REGION_HPP
#define REGION_HPP

#include "multiscale/analysis/spatial/SpatialEntityPseudo3D.hpp"

#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

using namespace cv;
using namespace std;


namespace multiscale {

    namespace analysis {

        //! Class for representing a region
        class Region : public SpatialEntityPseudo3D {

            private:

                vector<Point>           outerBorderPolygon;   /*!< Polygon defining the outer border of the region */
                vector<vector<Point> >  innerBorderPolygons;  /*!< Polygon defining the inner borders of the region */

            public:
                
                Region(double clusterednessDegree, double density, double area,
                       double distanceFromOrigin, double angleWrtOrigin,
                       const vector<Point> &outerBorderPolygon);
                ~Region();

                //! Get the polygon defining the region
                const vector<Point>& getOuterBorderPolygon();

            private:

                //! Validate the input values
                /*!
                 * Validation rules:
                 *  0 < clusterednessDegree
                 *  0 < density
                 *  0 < distanceFromOrigin
                 *  0 <= angleWrtOrigin <= 360
                 *
                 *  For each polygon point p:
                 *      0 <= p.x
                 *      0 <= p.y
                 *
                 * \param clusterednessDegree   The clusteredness degree of the region
                 * \param density               The density of the region
                 * \param area                  The area of the region considering holes
                 * \param distanceFromOrigin    The distance from the origin
                 * \param angleWrtOrigin        The angle computed wrt to the origin
                 * \param outerBorderPolygon    The polygon defining the outer border of the region
                 */
                void validateInputValues(double clusterednessDegree, double density, double area,
                                         double distanceFromOrigin, double angleWrtOrigin,
                                         const vector<Point> &outerBorderPolygon);

                //! Check if the input values are valid or not
                /*!
                 * Validation rules:
                 *  0 < clusterednessDegree
                 *  0 < density
                 *  0 < distanceFromOrigin
                 *  0 <= angleWrtOrigin <= 360
                 *
                 *  For each polygon point p:
                 *      0 <= p.x
                 *      0 <= p.y
                 *
                 * \param clusterednessDegree   The clusteredness degree of the region
                 * \param density               The density of the region
                 * \param area                  The area of the region considering holes
                 * \param distanceFromOrigin    The distance from the origin
                 * \param angleWrtOrigin        The angle computed wrt to the origin
                 * \param outerBorderPolygon    The polygon defining the outer border of the region
                 */
                bool areValidInputValues(double clusterednessDegree, double density, double area,
                                         double distanceFromOrigin, double angleWrtOrigin,
                                         const vector<Point> &outerBorderPolygon);

                //! Check if the given input polygons are valid
                /*!
                 *  For each polygon point p:
                 *      0 <= p.x
                 *      0 <= p.y
                 *
                 *  \param polygon
                 */
                bool areValidInputPolygons(const vector<Point> &polygon);

                //! Check if the given input polygons are valid
                /*!
                 *  For each polygon point p:
                 *      0 <= p.x
                 *      0 <= p.y
                 *
                 *  \param polygon
                 */
                bool isValidInputPolygon(const vector<Point> &polygon);

                //! Update the value of the clusteredness degree
                void updateClusterednessDegree() override;

                //! Update the value of the density
                void updateDensity() override;

                //! Update the area
                void updateArea() override;

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
