#include "multiscale/core/Multiscale.hpp"
#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace multiscale::analysis;


// Main function

int main() {
    RectangularMatFactory factory;

    cv::Mat image = factory.createFromImageFile("data/test/rectangular.png");

    cv::namedWindow("Test", cv::WINDOW_NORMAL);
    cv::imshow("Test", image);

    cv::waitKey(0);

    return multiscale::EXEC_SUCCESS_CODE;
}
