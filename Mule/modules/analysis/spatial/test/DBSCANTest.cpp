#include "multiscale/analysis/spatial/util/DBSCAN.hpp"
#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale;
using namespace multiscale::analysis;
using namespace multiscaletest;


// Class for definig a Euclidean data point
class EuclideanDataPoint {

    private:
        double x;
        double y;

    public:
        EuclideanDataPoint(double x, double y) : x(x), y(y) {}
        EuclideanDataPoint(const EuclideanDataPoint &point) : x(point.x), y(point.y) {}
        ~EuclideanDataPoint() {};

        double distanceTo(const EuclideanDataPoint &point) const {
            return (
                Geometry2D::distanceBtwPoints(
                    cv::Point(x, y),
                    cv::Point(point.x, point.y)
                )
            );
        }

};


///////////////////////////////////////////////////////////////////////////////
//
// Tests
//
///////////////////////////////////////////////////////////////////////////////

TEST(DBSCAN, EachPointInItsOwnCluster) {
    std::vector<EuclideanDataPoint> points;

    // Create collection of points
    for (std::size_t i = 0; i < 100; i++) {
        points.push_back(EuclideanDataPoint(i + 1, i + 3));
    }

    std::vector<int> clusterIndexes;
    std::size_t nrOfClusters;

    // Run DBSCAN
    DBSCAN<EuclideanDataPoint>().run(points, clusterIndexes, nrOfClusters, 0.5, 1);

    // Test the corresponding condition(s)
    // Add one to account for the noise cluster
    EXPECT_TRUE(nrOfClusters == (points.size() + 1));

    for (int i = 0; i < 100; i++) {
        EXPECT_TRUE(clusterIndexes[i] == i + 1);
    }
}

TEST(DBSCAN, ThreeClusters) {
    // Create collection of points
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

    std::vector<int> clusterIndexes;
    std::size_t nrOfClusters;

    // Run DBSCAN
    DBSCAN<EuclideanDataPoint>().run(points, clusterIndexes, nrOfClusters, 4, 3);

    // Test the corresponding condition(s)
    // Add one to account for the noise cluster
    EXPECT_TRUE(nrOfClusters == (3 + 1));

    EXPECT_TRUE(clusterIndexes[0] == 1);
    EXPECT_TRUE(clusterIndexes[1] == 1);
    EXPECT_TRUE(clusterIndexes[2] == 1);
    EXPECT_TRUE(clusterIndexes[3] == 2);
    EXPECT_TRUE(clusterIndexes[4] == 2);
    EXPECT_TRUE(clusterIndexes[5] == 2);
    EXPECT_TRUE(clusterIndexes[6] == 3);
    EXPECT_TRUE(clusterIndexes[7] == 3);
    EXPECT_TRUE(clusterIndexes[8] == 3);
}

TEST(DBSCAN, AllPointsInSameCluster) {
    std::vector<EuclideanDataPoint> points;

    // Create collection of points
    for (std::size_t i = 0; i < 100; i++) {
        points.push_back(EuclideanDataPoint(i + 1, i + 3));
    }

    std::vector<int> clusterIndexes;
    std::size_t nrOfClusters;

    // Run DBSCAN
    DBSCAN<EuclideanDataPoint>().run(points, clusterIndexes, nrOfClusters, 10, 7);

    // Test the corresponding condition(s)
    // Add one to account for the noise cluster
    EXPECT_TRUE(nrOfClusters == (1 + 1));

    for (std::size_t i = 0; i < 100; i++) {
        EXPECT_TRUE(clusterIndexes[i] == 1);
    }
}

TEST(DBSCAN, NoPoints) {
    std::vector<EuclideanDataPoint> points;

    std::vector<int> clusterIndexes;
    std::size_t nrOfClusters;

    // Run DBSCAN
    DBSCAN<EuclideanDataPoint>().run(points, clusterIndexes, nrOfClusters, 10, 7);

    // Test the corresponding condition(s)
    // Add one to account for the noise cluster
    EXPECT_TRUE(nrOfClusters == (0 + 1));
}

TEST(DBSCAN, AllPointsInNoiseCluster) {
    std::vector<EuclideanDataPoint> points;

    // Create collection of points
    for (std::size_t i = 0; i < 100; i++) {
        points.push_back(EuclideanDataPoint(i + 1, i + 3));
    }

    std::vector<int> clusterIndexes;
    std::size_t nrOfClusters;

    // Run DBSCAN
    DBSCAN<EuclideanDataPoint>().run(points, clusterIndexes, nrOfClusters, 0.5, 5);

    // Test the corresponding condition(s)
    // Add one to account for the noise cluster
    EXPECT_TRUE(nrOfClusters == (0 + 1));

    for (std::size_t i = 0; i < 100; i++) {
        EXPECT_TRUE(clusterIndexes[i] == 0);
    }
}


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
