#ifndef SPATIALENTITY_HPP
#define SPATIALENTITY_HPP

#include "multiscale/verification/spatial-temporal/exception/SpatialTemporalException.hpp"

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing a pseudo-3D spatial entity
        class SpatialEntity {

            protected:

                double clusteredness;       /*!< The clusteredness of the spatial entity */
                double density;             /*!< The density of the spatial entity */
                double area;                /*!< The area of the spatial entity */
                double perimeter;           /*!< The perimeter of the spatial entity */
                double distanceFromOrigin;  /*!< The distance of the spatial entity from the centre of the discretised space */
                double angle;               /*!< The angle described by the spatial entity with respect to the centre of the discretised space expressed in degrees */
                double triangleMeasure;     /*!< The measure indicating how triangular the shape of the spatial entity is */
                double rectangleMeasure;    /*!< The measure indicating how rectangular the shape of the spatial entity is */
                double circleMeasure;       /*!< The measure indicating how circular the shape of the spatial entity is */
                double centroidX;           /*!< The x-coordinate of the centroid of the spatial entity */
                double centroidY;           /*!< The y-coordinate of the centroid of the spatial entity */

            public:

                SpatialEntity();
                virtual ~SpatialEntity() {};

                //! Get the degree of clusteredness
                double getClusteredness() const;

                //! Get the density
                double getDensity() const;

                //! Get the value of the area
                double getArea() const;

                //! Get the value of the perimeter
                double getPerimeter() const;

                //! Get the distance from the centre of the discretised space
                double getDistanceFromOrigin() const;

                //! Get the value of the angle in degrees
                double getAngle() const;

                //! Get the triangle measure
                double getTriangleMeasure() const;

                //! Get the rectangle measure
                double getRectangleMeasure() const;

                //! Get the circle measure
                double getCircleMeasure() const;

                //! Get the x-coordinate of the centroid
                double getCentroidX() const;

                //! Get the y-coordinate of the centroid
                double getCentroidY() const;

                //! Set the value of the clusteredness
                /*!
                 *  \param clusteredness The value of the clusteredness
                 */
                void setClusteredness(double clusteredness);

                //! Set the value of the density
                /*!
                 * \param density The value of the density
                 */
                void setDensity(double density);

                //! Set the value of the area
                /*!
                 *  \param area The value of the area
                 */
                void setArea(double area);

                //! Set the value of the perimeter
                /*!
                 * \param perimeter The value of the perimeter
                 */
                void setPerimeter(double perimeter);

                //! Set the value of the distance from the origin (i.e. centre of the discretised space)
                /*!
                 * \param distanceFromOrigin    The value of the distance from the origin (i.e. centre of the discretised space)
                 */
                void setDistanceFromOrigin(double distanceFromOrigin);

                //! Set the value of the angle in degrees
                /*!
                 *  \param angle  The value of the angle in degrees
                 */
                void setAngle(double angle);

                //! Set the value of the triangle measure
                /*!
                 * \param triangleMeasure The value of the triangle measure
                 */
                void setTriangleMeasure(double triangleMeasure);

                //! Set the value of the rectangle measure
                /*!
                 * \param rectangleMeasure The value of the rectangle measure
                 */
                void setRectangleMeasure(double rectangleMeasure);

                //! Set the value of the circle measure
                /*!
                 * \param circleMeasure The value of the circle measure
                 */
                void setCircleMeasure(double circleMeasure);

                //! Set the value of the x-coordinate of the centroid
                /*!
                 * \param centroidX The value of the x-coordinate of the centroid
                 */
                void setCentroidX(double centroidX);

                //! Set the value of the y-coordinate of the centroid
                /*!
                 * \param centroidY The value of the y-coordinate of the centroid
                 */
                void setCentroidY(double centroidY);

                //! Overload the "<" operator for spatial entities
                /*! In this implementation spatial entity se1 is smaller than spatial entity se2 (se1 < se2)
                 * if at least one of the fields in se1 < the corresponding field in se2
                 *
                 * \param rhsSpatialEntity  The spatial entity lying on the right hand side of the comparison operator
                 */
                bool operator<(const SpatialEntity &rhsSpatialEntity) const;

            private:

                //! Check if the provided value is a real non-negative value and throw an exception if it is not
                /*!
                 * \param value The value to be checked
                 */
                void validateRealNonNegativeValue(double value);

                //! Check if the provided value is between 0 and 360 and throw an exception if it is not
                /*!
                 * \param value The value to be checked
                 */
                void validateAngleValue(double value);

                //! Check if the provided value is a real number between 0 and 1 and throw an exception if it is not
                /*!
                 * \param value The value to be checked
                 */
                void validateRealValueBtwZeroAndOne(double value);


                // Constants
                static const std::string ERR_SUFFIX;

                static const std::string ERR_REAL_NON_NEGATIVE_VALUE;
                static const std::string ERR_ANGLE_VALUE;
                static const std::string ERR_REAL_BTW_ZERO_AND_ONE;

        };

    };

};

#endif
