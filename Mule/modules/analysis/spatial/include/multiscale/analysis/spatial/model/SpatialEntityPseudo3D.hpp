#ifndef SpatialEntityPseudo3D_HPP
#define SpatialEntityPseudo3D_HPP

#include "multiscale/analysis/spatial/model/Shape2D.hpp"
#include "multiscale/analysis/spatial/model/SpatialEntityPseudo3DType.hpp"

#include "opencv2/imgproc/imgproc.hpp"


namespace multiscale {

    namespace analysis {

        //! Class for representing a pseudo-3D (explicit 2D + implicit height) object
        class SpatialEntityPseudo3D {

            protected:

                double clusterednessDegree;     /*!< Degree of clusteredness */
                double density;                 /*!< For regions:
                                                     The average intensity of the pixels in the region
                                                     normalised to the interval [0, 1]

                                                     For clusters:
                                                     Degree of pile up */

                double area;                    /*!< Area of the spatial entity */
                double perimeter;               /*!< Perimeter of the spatial entity */

                double distanceFromOrigin;      /*!< Distance from the origin  */
                double angle;                   /*!< Angle of the region wrt the origin */

                double triangularMeasure;       /*!< Measure ([0, 1]) indicating the similarity between the shape
                                                     of the spatial collection and a triangle */
                double rectangularMeasure;      /*!< Measure ([0, 1]) indicating the similarity between the shape
                                                     of the spatial collection and a rectangle */
                double circularMeasure;         /*!< Measure ([0, 1]) indicating the similarity between the shape
                                                     of the spatial collection and a circle */

                double spatialEntityShapeArea;  /*!< The area of the spatial entity considered when
                                                     computing its shape. The difference between the
                                                     shape area and the regular area is that the former
                                                     considers the entities centre points while the latter
                                                     the entities border points */

                Shape2D shape;                  /*!< Shape of the spatial entity */
                cv::Point2f centre;             /*!< Point defining the centre of the spatial entity */

                bool updateFlag;                /*!< Flag indicating if the field values dependent on the
                                                     collection of entities need to be updated. This flag is
                                                     used for lazy evaluation purposes, such that new field
                                                     values are computed only when required */

                std::vector<cv::Point2f>
                    minAreaEnclosingTriangle;       /*!< The minimum area enclosing triangle */

                cv::RotatedRect
                    minAreaEnclosingRect;           /*!< The minimum area enclosing rectangle */

                cv::Point2f
                    minAreaEnclosingCircleCentre;   /*!< The minimum area enclosing circle centre point */
                float
                    minAreaEnclosingCircleRadius;   /*!< The minimum area enclosing circle radius */

            public:

                SpatialEntityPseudo3D();
                virtual ~SpatialEntityPseudo3D();

                //! Get the clusteredness degree
                double getClusterednessDegree();

                //! Get the density
                double getDensity();

                //! Get the area
                double getArea();

                //! Get the perimeter
                double getPerimeter();

                //! Get the distance from the origin
                double getDistanceFromOrigin();

                //! Get the angle
                double getAngle();

                //! Get the shape best fitting the spatial collection
                Shape2D getShape();

                //! Get the shape best fitting the spatial collection as a string
                std::string getShapeAsString();

                //! Get the measure indicating how much the shape of the contour resembles a triangle
                double getTriangularMeasure();

                //! Get the measure indicating how much the shape of the contour resembles a rectangle
                double getRectangularMeasure();

                //! Get the measure indicating how much the shape of the contour resembles a cv::circle
                double getCircularMeasure();

                //! Get the point defining the centre of the entity
                cv::Point2f getCentre();

                //! Get a string representation of all the field names printed in the "toString" method
                static std::string fieldNamesToString();

                //! Get the string representation of all field values
                std::string toString();

                //! Return the type of the pseudo 3D spatial entity as a string
                std::string typeAsString();

            protected:

                //! Update the values of all measures if required
                void updateMeasuresIfRequired();

                //! Update the values of all measures
                void updateMeasures();

                //! Update the value of the clusteredness degree
                virtual void updateClusterednessDegree() = 0;

                //! Update the value of the density
                virtual void updateDensity() = 0;

                //! Update the value of the area
                virtual void updateArea() = 0;

                //! Update the value of the spatial entity shape area
                virtual void updateSpatialEntityShapeArea() = 0;

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

                //! Get the normalised shape measure ([0, 1]) that the spatial entity has a particular shape
                /*! The normalised shape measure is the result of dividing
                 *  spatialEntityShapeArea to shapeArea
                 *
                 * \param shapeArea The area of the shape
                 */
                double normalisedShapeMeasure(double shapeArea);

                //! Return the shape of the cluster as a string
                std::string shapeAsString();

                //! Return the values of the fields as a string
                std::string fieldValuesToString();

                //! Return the type of the pseudo 3D spatial entity
                virtual SpatialEntityPseudo3DType type() = 0;

            private:

                //! Initialisation function for the class
                void initialise();

            protected:

                // Constants
                static const std::string STR_REGION;
                static const std::string STR_CLUSTER;

                static const std::string STR_TRIANGLE;
                static const std::string STR_RECTANGLE;
                static const std::string STR_CIRCLE;
                static const std::string STR_UNDEFINED;

                static const std::string OUTPUT_SEPARATOR;

                static const std::string ERR_INPUT;
                static const std::string ERR_UNDEFINED_TYPE;

                static const bool CONVEX_HULL_CLOCKWISE;

        };

    };

};


#endif
