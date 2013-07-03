#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

using namespace cv;
using namespace std;

#define ERR_INPUT "Invalid input parameters were provided to the constructor."


namespace multiscale {

    namespace analysis {

        //! Class for representing an entity in an image (e.g. cell, organism etc.)
        class Entity {

            private:

                double pileUpDegree;    /*!< Degree of pile up (relevant only if entities can pile up onto each other) */
                double area;            /*!< Area of the entity */

                Point centre;           /*!< Point defining the centre of the entity */

            public:

                Entity(double pileUpDegree, double area, const Point &centre);
                ~Entity();

                //! Get the degree of pile up
                double getPileUpDegree() const;

                //! Get the area
                double getArea() const;

                //! Get the point defining the centre of the entity
                Point getCentre() const;

                //! Get a string representation of all the field values
                string toString();

            private:

                //! Check if the provided degree of pile up, area and centre are valid
                bool areValid(double pileUpDegree, double area, const Point &centre);

        };

    };

};

#endif
