#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/util/Geometry2D.hpp"

#include <ctime>
#include <iostream>

using namespace multiscale;


const std::string WINDOW_NAME  = "Tangents from point to polygon";

const int KEY_ESC = 27;

const int RADIUS                    = 1;
const int LINE_THICKNESS            = 10;
const int NR_RAND_POLYGONS          = 50;
const int MAX_POLYGON_POINTS        = 100;
const int POLYGON_POINT_RAND_X_MAX  = 500;
const int POLYGON_POINT_RAND_Y_MAX  = 500;

const double POINT_IN_TRIANGLE_THRESH = 1E-4;

const cv::Point origin = cv::Point(0, 0);


// Generate a new random set of 2D points
std::vector<cv::Point2f> generateRandomSetOf2DPoints(int nrOfPoints) {
    std::vector<cv::Point2f> points;

    for (int i = 0; i < nrOfPoints; i++) {
        points.push_back(
            cv::Point(
                (rand() % POLYGON_POINT_RAND_X_MAX) + POLYGON_POINT_RAND_X_MAX,
                (rand() % POLYGON_POINT_RAND_Y_MAX) + POLYGON_POINT_RAND_Y_MAX
            )
        );
    }

    return points;
}

// Output the results for the minimum area enclosing triangle
void outputTangentsAndPolygon(const std::vector<cv::Point2f> &polygon,
                              const cv::Point &leftMostTangentPoint,
                              const cv::Point &rightMostTangentPoint) {
    cv::Mat image = cv::Mat::zeros(POLYGON_POINT_RAND_X_MAX * 3, POLYGON_POINT_RAND_Y_MAX * 3, CV_32FC3);

    // Draw polygon
    for (unsigned int i = 0; i < polygon.size(); i++) {
        cv::line(
            image, polygon[i], polygon[(i + 1) % polygon.size()],
            cv::Scalar(0, 255, 255), LINE_THICKNESS
        );
    }

    // Draw tangents
    cv::line(image, leftMostTangentPoint, origin, cv::Scalar(255, 0, 255), LINE_THICKNESS);
    cv::line(image, rightMostTangentPoint, origin, cv::Scalar(255, 0, 255), LINE_THICKNESS);

    cv::namedWindow(WINDOW_NAME, cv::WINDOW_NORMAL);
    cv::imshow(WINDOW_NAME, image);
}

// Find tangents from a fixed point to the given polygon
void findTangentsForRandomPolygon(const std::vector<cv::Point2f> &polygon) {
    cv::Point2f leftMostTangentPoint;
    cv::Point2f rightMostTangentPoint;

    // Find the tangent points
    Geometry2D::tangentsFromPointToPolygon(
        polygon,
        origin,
        leftMostTangentPoint,
        rightMostTangentPoint
    );

    // Display the tangents and the polygon
    outputTangentsAndPolygon(polygon, leftMostTangentPoint, rightMostTangentPoint);
}

// Generate a random number of points between 2 and MAX_POLYGON_POINTS
int generateRandomNumberOfPoints() {
    int nrOfPoints = rand() % MAX_POLYGON_POINTS;

    return (
        (nrOfPoints < 2)
            ? 2
            : nrOfPoints
    );
}

// Find tangents from fixed point to randomly generated polygons
void findTangentsForRandomPolygons() {
    std::vector<cv::Point2f> randomPolygon;

    char key = 0;

    // Initialize the seed - milliseconds is enough as this program is not to be run in parallel
    srand(time(0));

    while (key != KEY_ESC) {
        int nrOfPoints = generateRandomNumberOfPoints();

        // Generate points
        std::vector<cv::Point2f> points = generateRandomSetOf2DPoints(nrOfPoints);

        // Construct a polygon from the points
        randomPolygon = Geometry2D::computeConvexHull(points);

        // Find tangents to the polygon
        findTangentsForRandomPolygon(randomPolygon);

        key = cv::waitKey();
    }
}

// Find tangents from fixed point to randomly generated lines (i.e. polygons comprising only 2 points)
void findTangentsForRandomLines() {
    std::vector<cv::Point2f> randomPolygon;

    char key = 0;

    // Initialize the seed - milliseconds is enough as this program is not to be run in parallel
    srand(time(0));

    while (key != KEY_ESC) {
        // Generate points
        std::vector<cv::Point2f> points = generateRandomSetOf2DPoints(2);

        // Construct a polygon from the points
        randomPolygon = Geometry2D::computeConvexHull(points);

        // Find tangents to the polygon
        findTangentsForRandomPolygon(randomPolygon);

        key = cv::waitKey();
    }
}

// Find tangents from a fixed point to different polygons
void findTangentsFromPointToPolygons() {
    // Uncomment if interested in random lines
    // findTangentsForRandomLines();

    findTangentsForRandomPolygons();
}

// Main function
int main(int argc, char** argv) {
    try {
        findTangentsFromPointToPolygons();
    } catch (const std::exception &ex) {
        ExceptionHandler::printDetailedErrorMessage(ex);
    }

    return EXEC_SUCCESS_CODE;
}
