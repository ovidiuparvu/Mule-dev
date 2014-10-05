#include "multiscale/core/Multiscale.hpp"
#include "multiscale/analysis/spatial/factory/CircularMatFactory.hpp"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace multiscale::analysis;


// Main function

int main() {
    CircularMatFactory factory;

    cv::Mat image = factory.createFromViewerImage("data/test/circular.png");

    cv::namedWindow("Test", cv::WINDOW_NORMAL);
    cv::imshow("Test", image);

    std::cout << "Maximum colour bar intensity: "
              << factory.maxColourBarIntensityFromViewerImage("data/test/circular.png")
              << std::endl;

    cv::waitKey(0);

    return multiscale::EXEC_SUCCESS_CODE;
}
