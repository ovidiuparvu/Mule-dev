#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include "opencv2/imgproc/imgproc.hpp"
#include "multiscale/analysis/spatial/Entity.hpp"
#include "multiscale/analysis/spatial/Shape2D.hpp"
#include "multiscale/analysis/spatial/SpatialCollection2D.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <vector>

using namespace cv;
using namespace std;


namespace multiscale {

    namespace analysis {

        //! Class for representing a cluster of entities in an image
        class Cluster : public SpatialCollection2D {

            private:

                double pileUpDegree;                        /*!< Degree of pile up */

                vector<Point2f> minAreaEnclosingTriangle;   /*!< The minimum area enclosing triangle */

                RotatedRect minAreaEnclosingRect;           /*!< The minimum area enclosing rectangle */

                Point2f minAreaEnclosingCircleCentre;       /*!< The minimum area enclosing circle centre point */
                float minAreaEnclosingCircleRadius;         /*!< The minimum area enclosing circle radius */

                vector<Entity> entities;                    /*!< Entities which belong to this cluster */

            public:

                Cluster();
                ~Cluster();

                //! Add a new entity to the cluster
                void addEntity(const Entity &entity);

                //! Get the degree of pile up
                double getPileUpDegree();

                //! Get the minimum area enclosing triangle
                vector<Point2f> getMinAreaEnclosingTriangle();

                //! Get the minimum area enclosing rectangle
                RotatedRect getMinAreaEnclosingRect();

                //! Get the minimum area enclosing circle centre
                Point2f getMinAreaEnclosingCircleCentre();

                //! Get the minimum area enclosing circle radius
                float getMinAreaEnclosingCircleRadius();

                //! Get the collection of underlying entities
                vector<Entity> getEntities() const;

                //! Get a string representation of all the field names printed in the "toString" method
                static string fieldNamesToString();

            private:

                //! Initialisation function for the class
                void initialise();

                //! Get the collection of entities' centres
                vector<Point2f> getEntitiesCentrePoints();

                //! Get the collection of entities' contour points
                vector<Point2f> getEntitiesContourPoints();

                //! Get the convex hull enclosing the collection of entities' contour points
                vector<Point2f> getEntitiesConvexHull();

                //! Update the values of all measures
                void updateSpatialCollectionSpecificValues() override;

                //! Update the value of the clusteredness degree
                void updateClusterednessDegree();

                //! Update the value of the pile up degree
                void updatePileUpDegree();

                //! Update the value of the area
                void updateArea() override;

                //! Update the value of the perimeter
                void updatePerimeter() override;

                //! Update the point defining the centre of the cluster
                void updateCentrePoint();

                //! Get the measure that the cluster has a triangular shape
                double isTriangularMeasure() override;

                //! Get the measure that the cluster has a rectangular shape
                double isRectangularMeasure() override;

                //! Get the measure that the cluster has a circular shape
                double isCircularMeasure() override;

                //! Get a string representation of all the field values
                string fieldValuesToString() override;

        };

    };

};

#endif
