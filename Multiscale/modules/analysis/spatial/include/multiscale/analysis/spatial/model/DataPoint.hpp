#ifndef DATAPOINT_HPP
#define DATAPOINT_HPP

#include <memory>


namespace multiscale {

    namespace analysis {

        //! Class for representing a data point
        class DataPoint {

            public:

                virtual ~DataPoint() {};

                //! Compute the distance between this data point and another one
                /*!
                 * \param point Data point to which the distance is measured
                 */
                virtual double distanceTo(std::shared_ptr<DataPoint> point) = 0;

        };

    };

};


#endif
