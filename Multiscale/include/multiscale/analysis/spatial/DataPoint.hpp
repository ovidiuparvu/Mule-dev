#ifndef DATAPOINT_HPP_
#define DATAPOINT_HPP_

namespace multiscale {

    namespace analysis {

        class DataPoint {

            public:

                virtual ~DataPoint() {};

                //! Compute the distance between this data point and another one
                virtual double distanceTo(const DataPoint &p) = 0;

        };

    };

};


#endif
