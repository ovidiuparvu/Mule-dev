#ifndef DATAPOINT_HPP
#define DATAPOINT_HPP

#include <memory>

using namespace std;

namespace multiscale {

    namespace analysis {

        class DataPoint {

            public:

                virtual ~DataPoint() {};

                //! Compute the distance between this data point and another one
                /*!
                 * \param point Data point to which the distance is measured
                 */
                virtual double distanceTo(shared_ptr<DataPoint> point) = 0;

        };

    };

};

#endif
