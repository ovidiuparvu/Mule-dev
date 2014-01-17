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

                double density;             /*!< The average intensity of the pixels in the region
                                                 normalised to the interval [0, 1] */

                vector<Point> polygon;      /*!< Polygon defining the region */

            public:
                
                Region(double clusterednessDegree, double density, double area, double distanceFromOrigin,
                       double angleWrtOrigin, const vector<Point> &polygon);
                ~Region();

                //! Get the density
                double getDensity();

                //! Get the polygon defining the region
                const vector<Point>& getPolygon();

                //! Get a string representation of all the field names except polygon
                static string fieldNamesToString();

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
                 * \param polygon               The polygon
                 */
                void validateInputValues(double clusterednessDegree, double density, double area, double distanceFromOrigin,
                                         double angleWrtOrigin, const vector<Point> &polygon);

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
                 * \param polygon               The polygon
                 */
                bool areValidInputValues(double clusterednessDegree, double density, double area, double distanceFromOrigin,
                                         double angleWrtOrigin, const vector<Point> &polygon);

                //! Update the value of all class specific measures
                void updateSpatialCollectionSpecificValues() override;

                //! Update the value of the clusteredness degree
                void updateClusterednessDegree() override;

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

                //! Get a string representation of all the field values except polygon
                string fieldValuesToString() override;

            private:

                // Constants
                static const bool CONTOUR_ORIENTED;
                static const bool CONTOUR_CLOSED;

        };

    };

};

#endif
