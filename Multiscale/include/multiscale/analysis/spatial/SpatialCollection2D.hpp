#ifndef SPATIALCOLLECTION2D_HPP_
#define SPATIALCOLLECTION2D_HPP_

#include "multiscale/analysis/spatial/Shape2D.hpp"

#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

#define STR_TRIANGLE            "triangle"
#define STR_RECTANGLE           "rectangle"
#define STR_CIRCLE              "circle"
#define STR_UNDEFINED           "undefined"

#define OUTPUT_SEPARATOR        ","

#define ERR_INPUT               "Invalid input parameters were provided to the constructor."
#define ERR_UNDEFINED_SHAPE     "The shape of the given cluster is undefined."

#define CONVEX_HULL_CLOCKWISE   true


namespace multiscale {

    namespace analysis {

        //! Class for representing a collection of objects in 2D space
        class SpatialCollection2D {

            protected:

                double clusterednessDegree;     /*!< Degree of clusteredness */

                double area;                    /*!< Area of the spatial collection */
                double perimeter;               /*!< Perimeter of the spatial collection */

                double triangularMeasure;       /*!< Measure ([0, 1]) indicating that the shape of the spatial collection is triangular */
                double rectangularMeasure;      /*!< Measure ([0, 1]) indicating that the shape of the spatial collection is rectangular */
                double circularMeasure;         /*!< Measure ([0, 1]) indicating that the shape of the spatial collection is circular */

                Shape2D shape;                  /*!< Shape of the spatial collection */
                Point2f centre;                 /*!< Point defining the centre of the spatial collection */

                bool updateFlag;                /*!< Flag indicating if the field values dependent on the
                                                     collection of entities need to be updated. This flag is
                                                     used for lazy evaluation purposes, such that new field
                                                     values are computed only when required*/

            public:

                SpatialCollection2D();
                virtual ~SpatialCollection2D();

                //! Get the clusteredness degree
                double getClusterednessDegree();

                //! Get the area
                double getArea();

                //! Get the perimeter
                double getPerimeter();

                //! Get the shape best fitting the spatial collection
                Shape2D getShape();

                //! Get the point defining the centre of the entity
                Point2f getCentre();

                //! Get the string representation of all field values
                string toString();

            protected:

                //! Update the values of all measures if required
                void updateMeasuresIfRequired();

                //! Update the values of all measures
                void updateMeasures();

                //! Update the values of all measures specific to the derived classes
                virtual void updateSpatialCollectionSpecificValues() = 0;

                //! Update the value of the area
                virtual void updateArea() = 0;

                //! Update the value of the perimeter
                virtual void updatePerimeter() = 0;

                //! Update the shape of the cluster
                void updateShape();

                //! Update the point defining the centre of the cluster
                virtual void updateCentrePoint() = 0;

                //! Get the measure that the cluster has a triangular shape
                virtual double isTriangularMeasure() = 0;

                //! Get the measure that the cluster has a rectangular shape
                virtual double isRectangularMeasure() = 0;

                //! Get the measure that the cluster has a circular shape
                virtual double isCircularMeasure() = 0;

                //! Return the shape of the cluster as a string
                string shapeAsString();

                //! Return the values of the fields as a string
                virtual string fieldValuesToString() = 0;

                //! Convert the collection of points from type Point to type Point2f
                /*!
                 * \param points Collection of points
                 */
                vector<Point2f> convertPoints(const vector<Point> &points);

            private:

                //! Initialisation function for the class
                void initialise();

        };

    };

};

#endif
