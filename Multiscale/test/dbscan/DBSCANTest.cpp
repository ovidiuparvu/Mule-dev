#include "multiscale/analysis/spatial/DBSCAN.hpp"
#include "EuclideanDataPoint.hpp"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace multiscale::analysis;
using namespace std;


// Convert vector of points to vector of shared_ptr of points
vector<shared_ptr<DataPoint>> convertPoints(vector<EuclideanDataPoint> &points) {
    vector<shared_ptr<DataPoint> > dataPoints;

    for (EuclideanDataPoint &point : points) {
        dataPoints.push_back(shared_ptr<DataPoint>(new EuclideanDataPoint(point)));
    }

    return dataPoints;
}

// Print the results of the test case
void printResults(const vector<int> &clusterIndexes) {
    cout << endl << "+++ NEW TEST CASE +++" << endl << endl;

    for (unsigned int i = 0; i < clusterIndexes.size(); i++) {
        cout << "Point " << (i + 1) << " belongs to cluster: " << clusterIndexes[i] << endl;
    }
}

// Run a test for the given set of points
void runTest(vector<EuclideanDataPoint> &points, double eps, int minPoints) {
    vector<int> clusterIndexes;
    int nrOfClusters;

    DBSCAN::run(convertPoints(points), clusterIndexes, nrOfClusters, eps, minPoints);

    printResults(clusterIndexes);
}

// TC: Each point in its own cluster
void runTest1() {
    vector<EuclideanDataPoint> points;

    for (int i = 0; i < 100; i++) {
        points.push_back(EuclideanDataPoint(i + 1, i + 3));
    }

    runTest(points, 0.5, 1);
}

// TC: Three clusters
void runTest2() {
    vector<EuclideanDataPoint> points = {
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
    vector<EuclideanDataPoint> points;

    for (int i = 0; i < 100; i++) {
        points.push_back(EuclideanDataPoint(i + 1, i + 3));
    }

    runTest(points, 10, 7);
}

// TC: No points
void runTest4() {
    vector<EuclideanDataPoint> points;

    runTest(points, 10, 7);
}

// TC: All noise points
void runTest5() {
    vector<EuclideanDataPoint> points;

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

    return 0;
}