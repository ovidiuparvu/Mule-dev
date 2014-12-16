#include "multiscale/analysis/spatial/detector/RegionDetector.hpp"
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

TEST(RegionDetector, ZeroImageSize) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(128);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(0, 0));

    // An exception is thrown because 0 x 0 images are invalid
    EXPECT_THROW(detector.detect(inputImage), InvalidInputException);
}

TEST(RegionDetector, SmallImageSize) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(128);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(1, 1) << 0.0);

    // An exception is thrown because 1 x 1 images are invalid
    EXPECT_THROW(detector.detect(inputImage), InvalidInputException);
}

TEST(RegionDetector, NoRegionsDefaultDetectionParameters) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(128);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(4, 4) << 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 0);
}

TEST(RegionDetector, OneRegionDefaultDetectionParameters) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(128);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 255.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionMinimumAlphaValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(128);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 0);
}

TEST(RegionDetector, OneRegionAverageAlphaValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(350);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(128);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionMaximumAlphaValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(1000);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(128);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionMinimumBetaValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(0);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(128);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 0);
}

TEST(RegionDetector, OneRegionAverageBetaValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(128);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 0);
}

TEST(RegionDetector, OneRegionMaximumBetaValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(200);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(128);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionMinimumBlurKernelSizeValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionAverageBlurKernelSizeValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(1000);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 0);
}

TEST(RegionDetector, OneRegionMaximumBlurKernelSizeValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(2000);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 0);
}

TEST(RegionDetector, OneRegionMinimumMorphologicalCloseIterationsValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionAverageMorphologicalCloseIterationsValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(50);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
    EXPECT_TRUE(detectedRegions.back().getArea() > 1);
}

TEST(RegionDetector, OneRegionMaximumMorphologicalCloseIterationsValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(100);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
    EXPECT_TRUE(detectedRegions.back().getArea() > 1);
}

TEST(RegionDetector, OneRegionMinimumEpsilonValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionAverageEpsilonValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(50);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionMaximumEpsilonValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(100);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionMinimumRegionAreaThresh) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionAverageRegionAreaThresh) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(10000);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 0);
}

TEST(RegionDetector, OneRegionMaximumRegionAreaThresh) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(200000);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 0);
}

TEST(RegionDetector, OneRegionMinimumThresholdValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(0);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionAverageThresholdValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(127);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
}

TEST(RegionDetector, OneRegionMaximumThresholdValue) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(255);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 0);
}

TEST(RegionDetector, OneLargeRegion) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 128.0, 128.0, 128.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 128.0, 128.0, 128.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 128.0, 128.0, 128.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 128.0, 128.0, 128.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
    EXPECT_NEAR(detectedRegions.back().getArea(), 12.0, DOUBLE_COMP_ERROR);
}

TEST(RegionDetector, OneLargeRegionWithHole) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(8, 8) << 0.0, 128.0, 128.0, 128.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 128.0, 0.0, 128.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 128.0, 0.0, 128.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 128.0, 128.0, 128.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 1);
    EXPECT_NEAR(detectedRegions.back().getArea(), 10.0, DOUBLE_COMP_ERROR);
}

TEST(RegionDetector, OneTriangularRegion) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(7, 7) << 0.0, 0.0, 0.0, 255.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 255.0, 255.0, 255.0, 0.0, 0.0,
                                                   0.0, 255.0, 255.0, 255.0, 255.0, 255.0, 0.0,                                                             0, 0, 0, 0, 0, 0, 0, 0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.back().getShape() == Shape2D::Triangle);
}

TEST(RegionDetector, OneRectangularRegion) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(7, 7) << 255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.back().getShape() == Shape2D::Rectangle);
}

TEST(RegionDetector, OneCircularRegion) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = cv::Mat::zeros(101, 101, CV_32FC1);

    cv::circle(inputImage, cv::Point(51, 51), 50, cv::Scalar(255), CV_FILLED);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.back().getShape() == Shape2D::Circle);
}

TEST(RegionDetector, OneZeroAngleRegion) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(7, 7) << 0.0, 0.0, 0.0, 255.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_NEAR(detectedRegions.back().getAngle(), 0, DOUBLE_COMP_ERROR);
}

TEST(RegionDetector, OneNinetyAngleRegion) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(15, 15) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0, 255.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                     0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_NEAR(detectedRegions.back().getAngle(), 90, DOUBLE_COMP_ERROR);
}

TEST(RegionDetector, OneBetweenZeroAndOneHundredEightyAngleRegion) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(7, 7) << 0.0, 0.0, 255.0, 255.0, 255.0, 0.0, 0.0,
                                                   0.0, 255.0, 255.0, 255.0, 255.0, 255.0, 0.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(
        (detectedRegions.back().getAngle() >= 0) &&
        (detectedRegions.back().getAngle() <= 180)
    );
}

TEST(RegionDetector, OneMaximumAngleRegion) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(7, 7) << 0.0, 0.0, 255.0, 255.0, 255.0, 0.0, 0.0,
                                                   0.0, 255.0, 255.0, 255.0, 255.0, 255.0, 0.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   255.0, 255.0, 255.0, 255.0, 255.0, 255.0, 255.0,
                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_NEAR(detectedRegions.back().getAngle(), 360, DOUBLE_COMP_ERROR);
}

TEST(RegionDetector, MultipleRegions) {
    // Define the region detector
    RegionDetector detector;

    // Set the spatial analysis parameter values
    detector.setAlpha(0);
    detector.setBeta(100);
    detector.setBlurKernelSize(0);
    detector.setMorphologicalCloseIterations(0);
    detector.setEpsilon(0);
    detector.setRegionAreaThresh(0);
    detector.setThresholdValue(125);

    // Create the input image
    cv::Mat inputImage = (cv::Mat_<float>(4, 4) << 0.0, 0.0, 0.0, 128.0,
                                                   128.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 0.0,
                                                   0.0, 0.0, 0.0, 128.0);

    // Detect regions in the image
    detector.detect(inputImage);

    // Retrieve the collection of detected regions
    std::vector<Region> detectedRegions = detector.getRegions();

    // Test the corresponding condition
    EXPECT_TRUE(detectedRegions.size() == 3);
}


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
