#include "multiscale/analysis/spatial/detector/SimulationClusterDetector.hpp"
#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/InvalidInputException.hpp"

using namespace multiscale;
using namespace multiscale::analysis;
using namespace multiscaletest;

const double DOUBLE_COMP_ERROR = 1E-6;


///////////////////////////////////////////////////////////////////////////////
//
// Tests
//
///////////////////////////////////////////////////////////////////////////////

TEST(ClusterDetector, ZeroImageSize) {
    // Define the cluster detector
    SimulationClusterDetector detector(0, 0, 1);

    // Set the spatial analysis parameter values
    detector.setEps(1.0);
    detector.setMinPoints(1);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(0, 0));

    // An exception is thrown because 0 x 0 images are invalid
    EXPECT_THROW(detector.detect(inputImage), InvalidInputException);
}

TEST(ClusterDetector, SmallImageSize) {
    // Define the cluster detector
    SimulationClusterDetector detector(1, 1, 1);

    // Set the spatial analysis parameter values
    detector.setEps(1.0);
    detector.setMinPoints(1);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(1, 1) << 0.0);

    // An exception is thrown because 1 x 1 images are invalid
    EXPECT_THROW(detector.detect(inputImage), InvalidInputException);
}

TEST(ClusterDetector, NoClustersDefaultDetectionParameters) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(1.0);
    detector.setMinPoints(1);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 0);
}


TEST(ClusterDetector, OneClusterDefaultDetectionParameters) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(1.0);
    detector.setMinPoints(1);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 4);
}

TEST(ClusterDetector, OneClusterMinEps) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(0.0);
    detector.setMinPoints(1);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 0);
}

TEST(ClusterDetector, OneClusterAverageEps) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(15);
    detector.setMinPoints(2);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 1);
    EXPECT_NEAR(detectedClusters.back().getArea(), 3, DOUBLE_COMP_ERROR);
}

TEST(ClusterDetector, OneClusterMaximumEps) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(1000);
    detector.setMinPoints(2);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 1);
    EXPECT_NEAR(detectedClusters.back().getArea(), 5, DOUBLE_COMP_ERROR);
}

TEST(ClusterDetector, OneClusterMinMinNrOfPoints) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(1.0);
    detector.setMinPoints(0);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 4);
}

TEST(ClusterDetector, OneClusterAverageMinNrOfPoints) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(1.0);
    detector.setMinPoints(50);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 0);
}

TEST(ClusterDetector, OneClusterMaximumMinNrOfPoints) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(1.0);
    detector.setMinPoints(100);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 0);
}

TEST(ClusterDetector, OneLargeCluster) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(15);
    detector.setMinPoints(1);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 1);
    EXPECT_TRUE(detectedClusters.back().getClusterednessDegree() > 0.24);
}

TEST(ClusterDetector, OneLargeClusterWithHole) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(15);
    detector.setMinPoints(1);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 1);
    EXPECT_TRUE(detectedClusters.back().getClusterednessDegree() < 0.20);
}

TEST(ClusterDetector, OneTriangularCluster) {
    // Define the cluster detector
    SimulationClusterDetector detector(7, 7, 1);

    // Set the spatial analysis parameter values
    detector.setEps(15);
    detector.setMinPoints(1);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(7, 7) << 0.0, 0.0, 0.0, 255.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 255.0, 255.0, 0.0, 0.0,
                                                   0.0, 255.0, 255.0, 255.0, 255.0, 255.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 1);
    EXPECT_TRUE(detectedClusters.back().getShape() == Shape2D::Triangle);
}

TEST(ClusterDetector, OneRectangularCluster) {
    // Define the cluster detector
    SimulationClusterDetector detector(7, 7, 1);

    // Set the spatial analysis parameter values
    detector.setEps(15);
    detector.setMinPoints(1);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(7, 7) << 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 0.0, 255.0, 255.0, 255.0, 0.0, 0.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 1);
    EXPECT_TRUE(detectedClusters.back().getShape() == Shape2D::Rectangle);
}

TEST(ClusterDetector, OneCircularCluster) {
    // Define the cluster detector
    SimulationClusterDetector detector(101, 101, 1);

    // Set the spatial analysis parameter values
    detector.setEps(1.0);
    detector.setMinPoints(1);

    // Create the input image
    cv::Mat inputImage = cv::Mat::zeros(101, 101, CV_32FC1);

    cv::circle(inputImage, cv::Point(51, 51), 40, cv::Scalar(255), CV_FILLED);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.back().getShape() == Shape2D::Circle);
}

TEST(ClusterDetector, MultipleClusters) {
    // Define the cluster detector
    SimulationClusterDetector detector(8, 8, 1);

    // Set the spatial analysis parameter values
    detector.setEps(1.5);
    detector.setMinPoints(0);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 255.0, 0.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 255.0, 0.0, 255.0,
                                                   255.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0,
                                                   255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0);

    // Detect clusters in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected clusters
    std::vector<Cluster> detectedClusters = detector.getClusters();

    // Test the corresponding condition
    EXPECT_TRUE(detectedClusters.size() == 3);
}


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}