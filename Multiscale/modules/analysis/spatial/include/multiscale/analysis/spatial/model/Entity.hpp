#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "opencv2/imgproc/imgproc.hpp"

#include <vector>


namespace multiscale {

    namespace analysis {

        //! Class for representing an entity in an image (e.g. cell, organism etc.)
        class Entity {

            private:

                double
                    pileUpDegree;   /*!< Degree of pile up (relevant only if entities can pile up onto each other) */
                double
                    area;           /*!< Area of the entity */
                double
                    perimeter;      /*!< Perimeter of the entity */

                cv::Point2f
                    centre;         /*!< Point defining the centre of the entity */
                std::vector<cv::Point2f>
                    contourPoints;  /*!< Set of points defining the contour of the entity */

            public:

                Entity(double pileUpDegree, double area, double perimeter,
                       const cv::Point2f &centre, const std::vector<cv::Point2f> &contourPoints);
                Entity(const Entity &entity);
                ~Entity();

                //! Get the degree of pile up
                double getPileUpDegree() const;

                //! Get the area
                double getArea() const;

                //! Get the perimeter
                double getPerimeter() const;

                //! Get the point defining the centre of the entity
                cv::Point2f getCentre() const;

                //! Get the set of points defining the contour of the entity
                std::vector<cv::Point2f> getContourPoints() const;

                //! Get a string representation of all the field values
                std::string toString();

                //! Get the distance between this entity and another one
                double distanceTo(const Entity &entity) const;

            private:

                // Validate the input values
                /*!
                 * \param pileUpDegree  Degree of pile up
                 * \param area          Area
                 * \param perimeter     Perimeter
                 * \param centre        Centre of the entity
                 * \param contourPoints Points defining the contour of the entity
                 */
                void validateInputValues(double pileUpDegree, double area, double perimeter,
                                         const cv::Point2f &centre, const std::vector<cv::Point2f> &contourPoints);

                //! Check if the provided degree of pile up, area, centre and contour points are valid
                /*!
                * \param pileUpDegree   Degree of pile up
                * \param area           Area
                * \param perimeter      Perimeter
                * \param centre         Centre of the entity
                * \param contourPoints  Points defining the contour of the entity
                */
                bool areValid(double pileUpDegree, double area, double perimeter,
                              const cv::Point2f &centre, const std::vector<cv::Point2f> &contourPoints);

            private:

                // Constants
                static const std::string ERR_INPUT;
                static const std::string ERR_DISTANCE;

                static const std::string OUTPUT_SEPARATOR;

        };

    };

};


#endif
