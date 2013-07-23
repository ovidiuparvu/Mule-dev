#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include "opencv2/imgproc/imgproc.hpp"
#include "multiscale/analysis/spatial/Entity.hpp"
#include "multiscale/analysis/spatial/Shape2D.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <vector>

using namespace cv;
using namespace std;

#define STR_TRIANGLE        "triangle"
#define STR_RECTANGLE       "rectangle"
#define STR_CIRCLE          "circle"
#define STR_UNDEFINED       "undefined"

#define OUTPUT_SEPARATOR    ","

#define ERR_UNDEFINED_SHAPE "The shape of the given cluster is undefined."


namespace multiscale {

    namespace analysis {

        //! Class for representing a cluster of entities in an image
        class Cluster {

            private:

                double clusterednessDegree;                 /*!< Degree of clusteredness */
                double pileUpDegree;                        /*!< Degree of pile up */
                double area;                                /*!< Sum of the areas of all entities in the cluster */

                double triangularMeasure;                   /*!< Measure ([0, 1]) indicating that the shape of the cluster is triangular */
                double rectangularMeasure;                  /*!< Measure ([0, 1]) indicating that the shape of the cluster is rectangular */
                double circularMeasure;                     /*!< Measure ([0, 1]) indicating that the shape of the cluster is circular */

                // TODO: Update
                vector<Point2f> minAreaEnclosingTriangle;   /*!< The minimum area enclosing triangle */

                RotatedRect minAreaEnclosingRect;           /*!< The minimum area enclosing rectangle */

                Point2f minAreaEnclosingCircleCentre;       /*!< The minimum area enclosing circle centre point */
                float minAreaEnclosingCircleRadius;         /*!< The minimum area enclosing circle radius */

                Shape2D shape;                              /*!< Shape of the cluster */
                Point2f centre;                             /*!< Point defining the centre of the cluster */
                vector<Entity> entities;                    /*!< Entities which belong to this cluster */

                bool updateFlag;                            /*!< Flag indicating if the field values dependent on the
                                                                 collection of entities need to be updated. This flag is
                                                                 used for lazy evaluation purposes, such that new field
                                                                 values are computed only when required*/

            public:

                Cluster();
                ~Cluster();

                //! Add a new entity to the cluster
                void addEntity(const Entity &entity);

                //! Get the degree of clusteredness
                double getClusterednessDegree();

                //! Get the degree of pile up
                double getPileUpDegree();

                //! Get the area
                double getArea();

                //! Get the shape best fitting the cluster of entities
                Shape2D getShape();

                //! Get the minimum area enclosing triangle
                vector<Point2f> getMinAreaEnclosingTriangle();

                //! Get the minimum area enclosing rectangle
                RotatedRect getMinAreaEnclosingRect();

                //! Get the minimum area enclosing circle centre
                Point2f getMinAreaEnclosingCircleCentre();

                //! Get the minimum area enclosing circle radius
                float getMinAreaEnclosingCircleRadius();

                //! Get the point defining the centre of the entity
                Point2f getCentre();

                //! Get the collection of underlying entities
                vector<Entity> getEntities() const;

                //! Get a string representation of all the field names printed in the "toString" method
                static string fieldNamesToString();

                //! Get a string representation of all the field values
                string toString();


            private:

                //! Initialisation function for the class
                void initialise();

                //! Get the collection of entities' centres
                vector<Point2f> getEntitiesCentrePoints();

                //! Get the collection of entities' contour points
                vector<Point2f> getEntitiesContourPoints();

                //! Update the values of all measures if required
                void updateMeasuresIfRequired();

                //! Update the values of all measures
                void updateMeasures();

                //! Update the value of the clusteredness degree
                void updateClusterednessDegree();

                //! Update the value of the pile up degree
                void updatePileUpDegree();

                //! Update the value of the area
                void updateArea();

                //! Update the shape of the cluster
                void updateShape();

                //! Update the point defining the centre of the cluster
                void updateCentrePoint();

                //! Get probability that the cluster has a triangular shape
                double isTriangularMeasure();

                //! Get probability that the cluster has a rectangular shape
                double isRectangularMeasure();

                //! Get probability that the cluster has a circular shape
                double isCircularMeasure();

                //! Return the shape of the cluster as a string
                string shapeAsString();

        };

    };

};

#endif
