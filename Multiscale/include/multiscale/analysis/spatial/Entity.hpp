#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "multiscale/analysis/spatial/DataPoint.hpp"

#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

using namespace cv;
using namespace std;


namespace multiscale {

    namespace analysis {

        //! Class for representing an entity in an image (e.g. cell, organism etc.)
        class Entity : public DataPoint {

            private:

                unsigned int    pileUpDegree;   /*!< Degree of pile up (relevant only if entities can pile up onto each other) */
                double          area;           /*!< Area of the entity */
                double          perimeter;      /*!< Perimeter of the entity */

                Point2f centre;                 /*!< Point defining the centre of the entity */
                vector<Point2f> contourPoints;  /*!< Set of points defining the contour of the entity */

            public:

                Entity(unsigned int pileUpDegree, double area, double perimeter, const Point2f &centre, const vector<Point2f> &contourPoints);
                Entity(const Entity &entity);
                ~Entity();

                //! Get the degree of pile up
                unsigned int getPileUpDegree() const;

                //! Get the area
                double getArea() const;

                //! Get the perimeter
                double getPerimeter() const;

                //! Get the point defining the centre of the entity
                Point2f getCentre() const;

                //! Get the set of points defining the contour of the entity
                vector<Point2f> getContourPoints() const;

                //! Get a string representation of all the field values
                string toString();

                //! Get the distance between this entity and another one
                double distanceTo(shared_ptr<DataPoint> point) override;

                //! Get the distance between this entity and another one
                double distanceTo(const Entity &entity);



            private:

                // Validate the input values
                /*!
                 * \param pileUpDegree  Degree of pile up
                 * \param area          Area
                 * \param perimeter     Perimeter
                 * \param centre        Centre of the entity
                 * \param contourPoints Points defining the contour of the entity
                 */
                void validateInputValues(unsigned int pileUpDegree, double area, double perimeter, const Point2f &centre,
                                         const vector<Point2f> &contourPoints);

                //! Check if the provided degree of pile up, area, centre and contour points are valid
                /*!
                * \param pileUpDegree   Degree of pile up
                * \param area           Area
                * \param perimeter      Perimeter
                * \param centre         Centre of the entity
                * \param contourPoints  Points defining the contour of the entity
                */
                bool areValid(unsigned int pileUpDegree, double area, double perimeter, const Point2f &centre, const vector<Point2f> &contourPoints);

            private:

                // Constants
                static const string ERR_INPUT;
                static const string ERR_DISTANCE;

                static const string OUTPUT_SEPARATOR;

        };

    };

};

#endif
