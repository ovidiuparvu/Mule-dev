#ifndef EUCLIDEANDATAPOINT_HPP
#define EUCLIDEANDATAPOINT_HPP

#include "multiscale/analysis/spatial/DataPoint.hpp"
#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale::analysis;
using namespace multiscale;

class EuclideanDataPoint : public DataPoint {

    private:
        double x;
        double y;

    public:
        EuclideanDataPoint(double x, double y) : x(x), y(y) {}
        EuclideanDataPoint(const EuclideanDataPoint &point) : x(point.x), y(point.y) {}
        ~EuclideanDataPoint() {};

        double distanceTo(shared_ptr<DataPoint> point) override {
            shared_ptr<EuclideanDataPoint> ePoint = dynamic_pointer_cast<EuclideanDataPoint>(point);

            return Geometry2D::distanceBtwPoints(Point(x, y), Point(ePoint->x, ePoint->y));
        }

};

#endif
