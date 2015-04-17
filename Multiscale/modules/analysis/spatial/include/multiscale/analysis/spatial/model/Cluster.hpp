#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include "multiscale/analysis/spatial/model/Entity.hpp"
#include "multiscale/analysis/spatial/model/Shape2D.hpp"
#include "multiscale/analysis/spatial/model/SpatialEntityPseudo3D.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include "opencv2/imgproc/imgproc.hpp"

#include <vector>


namespace multiscale {

    namespace analysis {

        //! Class for representing a cluster of entities in an image
        class Cluster : public SpatialEntityPseudo3D {

            private:

                std::vector<Entity>
                    entities;                       /*!< Entities which belong to this cluster */

            public:

                Cluster();
                ~Cluster();

                //! Add a new entity to the cluster
                void addEntity(const Entity &entity);

                //! Get the minimum area enclosing triangle
                std::vector<cv::Point2f> getMinAreaEnclosingTriangle();

                //! Get the minimum area enclosing rectangle
                cv::RotatedRect getMinAreaEnclosingRect();

                //! Get the minimum area enclosing circle centre
                cv::Point2f getMinAreaEnclosingCircleCentre();

                //! Get the minimum area enclosing circle radius
                float getMinAreaEnclosingCircleRadius();

                //! Get the collection of underlying entities
                std::vector<Entity> getEntities() const;

                //! Get the convex hull enclosing the collection of entities' contour points
                std::vector<cv::Point2f> getEntitiesConvexHull();

                //! Set the values of the origin dependent members
                /*!
                 * \param distanceFromOrigin Distance from the origin
                 * \param angleWrtOrigin     Angle with respect to the origin
                 */
                void setOriginDependentMembers(double distanceFromOrigin, double angleWrtOrigin);

            private:

                //! Initialisation function for the class
                void initialize();

                //! Get the collection of entities' centres
                std::vector<cv::Point2f> getEntitiesCentrePoints();

                //! Get the collection of entities' contour points
                std::vector<cv::Point2f> getEntitiesContourPoints();

                //! Update the value of the clusteredness degree
                void updateClusterednessDegree() override;

                //! Update the value of the pile up degree
                void updateDensity() override;

                //! Update the value of the area
                void updateArea() override;

                //! Update the value of the spatial entity shape
                void updateSpatialEntityShapeArea() override;

                //! Update the value of the perimeter
                void updatePerimeter() override;

                //! Update the point defining the centre of the cluster
                void updateCentrePoint() override;

                //! Get the measure that the cluster has a triangular shape
                double isTriangularMeasure() override;

                //! Get the measure that the cluster has a rectangular shape
                double isRectangularMeasure() override;

                //! Get the measure that the cluster has a circular shape
                double isCircularMeasure() override;

                //! Return the type of the pseudo 3D spatial entity
                SpatialEntityPseudo3DType type() override;

                //! Validate the origin dependent values (i.e. non-negative)
                /*!
                 * \param distanceFromOrigin Distance from the origin
                 * \param angleWrtOrigin     Angle with respect to the origin
                 */
                void validateOriginDependentValues(double distanceFromOrigin, double angleWrtOrigin);

                //! Check if the origin dependent values are valid (i.e. non-negative)
                /*!
                 * \param distanceFromOrigin Distance from the origin
                 * \param angleWrtOrigin     Angle with respect to the origin
                 */
                bool areValidOriginDependentValues(double distanceFromOrigin, double angleWrtOrigin);

            public:

                // Constants
                static const std::string ERR_UNDEFINED_SHAPE;
                static const std::string ERR_ORIGIN_DEPENDENT_VALUES;

        };

    };

};


#endif
