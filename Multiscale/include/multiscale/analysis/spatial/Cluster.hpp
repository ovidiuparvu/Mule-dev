#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include "opencv2/imgproc/imgproc.hpp"
#include "multiscale/analysis/spatial/Entity.hpp"
#include "multiscale/analysis/spatial/Shape2D.hpp"

#include <vector>

using namespace cv;
using namespace std;

#define PI                  3.141592

#define STR_TRIANGLE        "triangle"
#define STR_RECTANGLE       "rectangle"
#define STR_CIRCLE          "circle"

#define ERR_UNDEFINED_SHAPE "The shape of the given cluster is undefined."


namespace multiscale {

    namespace analysis {

        //! Class for representing a cluster of entities in an image
        class Cluster {

            private:

                double clusterednessDegree;             /*!< Degree of clusteredness */
                double pileUpDegree;                    /*!< Degree of pile up */
                double area;                            /*!< Sum of the areas of all entities in the cluster */

                double triangularProbability;           /*!< Probability that the shape of the cluster is triangular */
                double rectangularProbability;          /*!< Probability that the shape of the cluster is rectangular */
                double circularProbability;             /*!< Probability that the shape of the cluster is circular */

                RotatedRect minAreaEnclosingRect;       /*!< The minimum area enclosing rectangle */

                Point2f minAreaEnclosingCircleCentre;   /*!< The minimum area enclosing circle centre point */
                float minAreaEnclosingCircleRadius;     /*!< The minimum area enclosing circle radius */

                vector<Point> minAreaEnclosingTriangle; /*!< The minimum area enclosing triangle */

                Shape2D shape;                          /*!< Shape of the cluster */
                Point centre;                           /*!< Point defining the centre of the cluster */
                vector<Entity> entities;                /*!< Entities which belong to this cluster */

                bool updateFlag;                        /*!< Flag indicating if the field values dependent on the collection of entities needs to be updated */

            public:

                Cluster();
                ~Cluster();

                //! Add a new entity to the cluster
                void addEntity(const Entity &entity);

                //! Get the degree of clusteredness
                double getClusterednessDegree() const;

                //! Get the degree of pile up
                double getPileUpDegree() const;

                //! Get the area
                double getArea() const;

                //! Get the shape best fitting the cluster of entities
                Shape2D getShape() const;

                //! Get the point defining the centre of the entity
                double getCentre() const;

                //! Get a string representation of all the field values
                string toString();


            private:

                //! Initialisation function for the class
                void initialise();

                //! Get the collection of entities' centres
                vector<Point> getEntitiesCentrePoints();

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
                double isTriangularProbability();

                //! Get probability that the cluster has a rectangular shape
                double isRectangularProbability();

                //! Get probability that the cluster has a circular shape
                double isCircularProbability();

                //! Return the shape of the cluster as a string
                string shapeAsString();

        };

    };

};

#endif
