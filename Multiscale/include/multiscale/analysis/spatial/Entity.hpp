#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "multiscale/analysis/spatial/DataPoint.hpp"

#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

using namespace cv;
using namespace std;

#define ERR_INPUT           "Invalid input parameters were provided to the constructor."
#define ERR_DISTANCE        "The distance to an object of a different type cannot be computed."

#define OUTPUT_SEPARATOR    ","


namespace multiscale {

    namespace analysis {

        //! Class for representing an entity in an image (e.g. cell, organism etc.)
        class Entity : public DataPoint {

            private:

                double pileUpDegree;    /*!< Degree of pile up (relevant only if entities can pile up onto each other) */
                double area;            /*!< Area of the entity */

                Point centre;           /*!< Point defining the centre of the entity */

            public:

                Entity(double pileUpDegree, double area, const Point &centre);
                Entity(const Entity &entity);
                ~Entity();

                //! Get the degree of pile up
                double getPileUpDegree() const;

                //! Get the area
                double getArea() const;

                //! Get the point defining the centre of the entity
                Point getCentre() const;

                //! Get a string representation of all the field values
                string toString();

                //! Get the distance between this entity and another one
                double distanceTo(shared_ptr<DataPoint> point);

                //! Get the distance between this entity and another one
                double distanceTo(const Entity &entity);

            private:

                //! Check if the provided degree of pile up, area and centre are valid
                bool areValid(double pileUpDegree, double area, const Point &centre);

        };

    };

};

#endif
