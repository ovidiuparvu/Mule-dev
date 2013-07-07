#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace multiscale::analysis;
using namespace std;

// Main function

int main() {
    RectangularMatFactory factory;

    Mat image = factory.createFromViewerImage("test/input/rectangular.png");

    namedWindow("Test", WINDOW_NORMAL);
    imshow("Test", image);

    waitKey(0);

    return 0;
}