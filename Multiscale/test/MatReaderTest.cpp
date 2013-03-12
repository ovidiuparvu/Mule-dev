#include "multiscale/analysis/spatial/MatFactory.hpp"
#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <fstream>

using namespace multiscale::analysis;
using namespace std;

int main() {
    MatFactory* factory = new RectangularMatFactory();

    Mat originalImage = factory->create("test/input/phase_variation_in_space4_61x61_trace4_101.in");

    namedWindow( "Original image", WINDOW_NORMAL );
    imshow( "Original image", originalImage );

    waitKey();

    originalImage.release();

    return 0;
}
