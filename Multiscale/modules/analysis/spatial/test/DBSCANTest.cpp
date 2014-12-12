#include "multiscale/analysis/spatial/util/DBSCAN.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace multiscale;
using namespace multiscale::analysis;


// Class for definig a Euclidean data point
class EuclideanDataPoint : public DataPoint {

    private:
        double x;
        double y;

    public:
        EuclideanDataPoint(double x, double y) : x(x), y(y) {}
        EuclideanDataPoint(const EuclideanDataPoint &point) : x(point.x), y(point.y) {}
        ~EuclideanDataPoint() {};

        double distanceTo(std::shared_ptr<DataPoint> point) override {
            std::shared_ptr<EuclideanDataPoint> ePoint = std::dynamic_pointer_cast<EuclideanDataPoint>(point);

            return Geometry2D::distanceBtwPoints(cv::Point(x, y), cv::Point(ePoint->x, ePoint->y));
        }

};


// Convert std::vector of points to std::vector of std::shared_ptr of points
std::vector<std::shared_ptr<DataPoint>> convertPoints(std::vector<EuclideanDataPoint> &points) {
    std::vector<std::shared_ptr<DataPoint> > dataPoints;

    for (EuclideanDataPoint &point : points) {
        dataPoints.push_back(std::shared_ptr<DataPoint>(new EuclideanDataPoint(point)));
    }

    return dataPoints;
}

// Print the results of the test case
void printResults(const std::vector<int> &clusterIndexes) {
    std::cout << std::endl << "+++ NEW TEST CASE +++" << std::endl << std::endl;

    for (unsigned int i = 0; i < clusterIndexes.size(); i++) {
        std::cout << "cv::Point " << (i + 1) << " belongs to cluster: " << clusterIndexes[i] << std::endl;
    }
}

// Run a test for the given set of points
void runTest(std::vector<EuclideanDataPoint> &points, double eps, int minPoints) {
    std::vector<int> clusterIndexes;
    int nrOfClusters;

    DBSCAN().run(convertPoints(points), clusterIndexes, nrOfClusters, eps, minPoints);

    printResults(clusterIndexes);
}

// TC: Each point in its own cluster
void runTest1() {
    std::vector<EuclideanDataPoint> points;

    for (int i = 0; i < 100; i++) {
        points.push_back(EuclideanDataPoint(i + 1, i + 3));
    }

    runTest(points, 0.5, 1);
}

// TC: Three clusters
void runTest2() {
    std::vector<EuclideanDataPoint> points = {
            EuclideanDataPoint(1, 3),
            EuclideanDataPoint(2, 2),
            EuclideanDataPoint(2, 4),
            EuclideanDataPoint(6, 1),
            EuclideanDataPoint(7, 0),
            EuclideanDataPoint(7, 2),
            EuclideanDataPoint(6, 9),
            EuclideanDataPoint(6, 11),
            EuclideanDataPoint(7, 10)
    };

    runTest(points, 4, 3);
}

// TC: All points in same cluster
void runTest3() {
    std::vector<EuclideanDataPoint> points;

    for (int i = 0; i < 100; i++) {
        points.push_back(EuclideanDataPoint(i + 1, i + 3));
    }

    runTest(points, 10, 7);
}

// TC: No points
void runTest4() {
    std::vector<EuclideanDataPoint> points;

    runTest(points, 10, 7);
}

// TC: All noise points
void runTest5() {
    std::vector<EuclideanDataPoint> points;

    for (int i = 0; i < 100; i++) {
        points.push_back(EuclideanDataPoint(i + 1, i + 3));
    }

    runTest(points, 0.5, 5);
}

// Run the tests
void runTests() {
    runTest1();
    runTest2();
    runTest3();
    runTest4();
    runTest5();
}

// Main function
int main() {
    runTests();

    return EXEC_SUCCESS_CODE;
}
