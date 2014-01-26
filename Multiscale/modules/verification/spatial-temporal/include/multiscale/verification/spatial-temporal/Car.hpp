#ifndef CAR_HPP
#define CAR_HPP

#include <boost/fusion/adapted/adt/adapt_adt.hpp>
#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <string>

using namespace std;


namespace multiscale {

    namespace verification {

        // Class for representing a car
        class Car {

            private:

                double speed;
                int seats;

            public:

                Car() : speed(0), seats(0) {}
                Car(double speed, int seats) : speed(speed), seats(seats) {}

                int const &getSeats() const {
                    return seats;
                }

                void setSeats(int seats) {
                    this->seats = seats;
                }

                double getSpeed() const {
                    return speed;
                }

                void setSpeed(double speed) {
                    this->speed = speed;
                }

        };

    };

};


// Adapt the Car class to a Boost Fusion data type
BOOST_FUSION_ADAPT_ADT(
    multiscale::verification::Car,
    (double, double, obj.getSpeed(), obj.setSpeed(val))
    (int, int, obj.getSeats(), obj.setSeats(val))
)

#endif
