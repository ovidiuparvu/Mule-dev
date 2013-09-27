#ifndef REGION_HPP_
#define REGION_HPP_

#include "multiscale/analysis/spatial/SpatialCollection2D.hpp"

#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

using namespace cv;
using namespace std;

#define CONTOUR_ORIENTED    false
#define CONTOUR_CLOSED      true


namespace multiscale {

    namespace analysis {

        //! Class for representing a region
        class Region : public SpatialCollection2D {

            private:

                double density;             /*!< The average intensity of the pixels in the region
                                                 normalised to the interval [0, 1] */

                double distanceFromOrigin;  /*!< Distance from the origin  */
                double angle;               /*!< Angle of the region wrt the origin */

                vector<Point> polygon;      /*!< Polygon defining the region */

            public:
                
                Region(double clusterednessDegree, double density, double distanceFromOrigin,
                       double angleWrtOrigin, const vector<Point> &polygon);
                ~Region();

                //! Get the density
                double getDensity();

                //! Get the distance from the origin
                double getDistanceFromOrigin();

                //! Get the angle
                double getAngle();

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
                 * \param distanceFromOrigin    The distance from the origin
                 * \param angleWrtOrigin        The angle computed wrt to the origin
                 * \param polygon               The polygon
                 */
                void validateInputValues(double clusterednessDegree, double density, double distanceFromOrigin,
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
                 * \param distanceFromOrigin    The distance from the origin
                 * \param angleWrtOrigin        The angle computed wrt to the origin
                 * \param polygon               The polygon
                 */
                bool areValidInputValues(double clusterednessDegree, double density, double distanceFromOrigin,
                                         double angleWrtOrigin, const vector<Point> &polygon);

                //! Update the value of all class specific measures
                void updateSpatialCollectionSpecificValues() override;

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

        };

    };

};

#endif
