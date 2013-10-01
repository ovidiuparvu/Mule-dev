#include "multiscale/analysis/spatial/MatFactory.hpp"
#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <fstream>
#include <iostream>


using namespace multiscale::analysis;
using namespace std;

const string WIN_ORIGINAL_IMAGE  = "Original image";
const string WIN_PROCESSED_IMAGE = "Processed image";
const string WIN_EDGES_IN_IMAGE  = "Edges in image";
const string WIN_CONTOURS        = "Contours";
const string WIN_POLYGONS        = "Polygons";

const string TRACKBAR_ALPHA              = "Alpha";
const string TRACKBAR_BETA               = "Beta";
const string TRACKBAR_KERNEL             = "Gaussian blur kernel size";
const string TRACKBAR_MORPH              = "Morphological open, number of iterations";
const string TRACKBAR_CANNY              = "Canny lower threshold";
const string TRACKBAR_EPSILON            = "Epsilon";
const string TRACKBAR_SECTOR_AREA_THRESH = "Sector area threshold";
const string TRACKBAR_THRESHOLD          = "Threshold value";

const bool USE_CANNY_L2           = true;
const bool CONTOUR_AREA_ORIENTED  = false;

const double ALPHA_REAL_MIN       = 1.0;
const double ALPHA_REAL_MAX       = 3.0;
const int BETA_REAL_MIN           = -100;
const int BETA_REAL_MAX           = 100;

const int ALPHA_MAX               = 1000;
const int BETA_MAX                = 200;
const int KERNEL_MAX              = 100;
const int ITER_MAX                = 100;
const int CANNY_THRESH_MAX        = 100;
const int EPSILON_MAX             = 100;
const int SECTOR_AREA_THRESH_MAX  = 500;
const int THRESHOLD_MAX           = 255;

const int KEY_ESC           = 27;
const int IMAGE_MIN_INDEX   = 1;

const double PI = 3.141592;

// Global variables

int alpha                           = 750;
int beta                            = 0;
int blurKernelSize                  = 1;
int morphologicalCloseIterations    = 2;
int cannyThresholdRatio             = 3;
int cannyLowerThreshold             = 50;
int cannyAppertureSize              = 3;
int epsilon                         = 1;
int sectorAreaThresh                = 140;
int thresholdValue                  = 50;

Point origin(30, 30);

// Display the image

void displayImage(const Mat &image, const string &windowName) {
    namedWindow( windowName, WINDOW_NORMAL );
    imshow( windowName, image );
}

// Display trackbars for changing the image

void createTrackbars() {
    namedWindow( WIN_PROCESSED_IMAGE, WINDOW_NORMAL);

    createTrackbar(TRACKBAR_ALPHA, WIN_PROCESSED_IMAGE, &alpha, ALPHA_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_BETA, WIN_PROCESSED_IMAGE, &beta, BETA_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_KERNEL, WIN_PROCESSED_IMAGE, &blurKernelSize, KERNEL_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_MORPH, WIN_PROCESSED_IMAGE, &morphologicalCloseIterations, ITER_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_CANNY, WIN_PROCESSED_IMAGE, &cannyLowerThreshold, CANNY_THRESH_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_EPSILON, WIN_PROCESSED_IMAGE, &epsilon, EPSILON_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_SECTOR_AREA_THRESH, WIN_PROCESSED_IMAGE, &sectorAreaThresh, SECTOR_AREA_THRESH_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_THRESHOLD, WIN_PROCESSED_IMAGE, &thresholdValue, SECTOR_AREA_THRESH_MAX, nullptr, nullptr);
}

// Convert alpha from the range [0, ALPHA_MAX] to [1.0, 3.0]

double convertAlpha(int alpha) {
    return 1.0 + (((double) alpha) / (ALPHA_MAX)) * (3.0 - 1.0);
}

// Convert beta from the range [0, 1000] to [-100, 100]

int convertBeta(int beta) {
    return (-100) + ((double)(beta) / (BETA_MAX)) * (100 - (-100));
}

// Convert the integer to an odd number

int convertToOdd(int number) {
    return ((number % 2) == 0) ? number + IMAGE_MIN_INDEX
                               : number;
}

// Change the contrast and the brightness of the image

void changeContrastAndBrightness(const Mat &originalImage, Mat &processedImage) {
    originalImage.convertTo(processedImage, -1, convertAlpha(alpha), convertBeta(beta));
}

// Smooth out the differences in the image

void smoothImage(Mat &image) {
    if (blurKernelSize != 0) {
        blurKernelSize = convertToOdd(blurKernelSize);

        GaussianBlur(image, image, Size(blurKernelSize, blurKernelSize), 0);
    }
}

// Apply the morphological open filter to the image

void morphologicalClose(Mat &image) {
    morphologyEx(image, image, MORPH_CLOSE, Mat(), Point(-1, -1), morphologicalCloseIterations);
}

/* Detect the edges in the image using Canny, apply dilate to fill gaps between edge segments
   and display the result
 */

void detectEdges(const Mat &processedImage, Mat &edges) {
    Canny(processedImage, edges, cannyLowerThreshold, cannyLowerThreshold * cannyThresholdRatio, cannyAppertureSize, USE_CANNY_L2);
    dilate(processedImage, processedImage, Mat());

    displayImage(edges, WIN_EDGES_IN_IMAGE);
}

// Apply the threshold filter to the image

void thresholdImage(const Mat &image, Mat &thresholdedImage) {
    threshold(image, thresholdedImage, thresholdValue, THRESHOLD_MAX, THRESH_BINARY);
}

// Check if the area of the contour's bounding box < "sector area threshold"

bool isValidBoundingBox(const vector<Point> &contour) {
    RotatedRect boundingBox = minAreaRect(contour);
    double area = boundingBox.size.width * boundingBox.size.height;

    return (area >= sectorAreaThresh);
}

// Get the distance between 2 points

double distanceBtwPoints(Point a, Point b) {
    double xDiff = a.x - b.x;
    double yDiff = a.y - b.y;

    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

// Get the index of the point which is the closest to the origin

int minimumDistancePointIndex(const vector<Point> &contour, const Point &origin) {
    double minDistance = numeric_limits<int>::max();
    double distance;
    int nrOfPoints = contour.size();
    int minimumDistancePointIndex = -IMAGE_MIN_INDEX;

    for (int i = 0; i < nrOfPoints; i++) {
        distance = distanceBtwPoints(contour[i], origin);

        if (distance < minDistance) {
            minDistance = distance;

            minimumDistancePointIndex = i;
        }
    }

    return minimumDistancePointIndex;
}

// Get the angle between 3 points

double angleBtwPoints(Point a, Point b, Point c) {
    Point2f ab(b.x - a.x, b.y - a.y);
    Point2f cb(b.x - c.x, b.y - c.y);

    double dotProduct   = (ab.x * cb.x + ab.y * cb.y);
    double crossProduct = (ab.x * cb.y - ab.y * cb.x);

    double alpha = atan2(crossProduct, dotProduct);

    return abs(((alpha * 180) / PI));
}

// Check if a point is on the edge

bool isOnEdge(Point p, int nrOfRows, int nrOfCols) {
    return (
              ((p.x == IMAGE_MIN_INDEX) && (p.y > IMAGE_MIN_INDEX) && (p.y < nrOfCols)) ||
              ((p.x == nrOfRows) && (p.y > IMAGE_MIN_INDEX) && (p.y < nrOfCols)) ||
              ((p.y == IMAGE_MIN_INDEX) && (p.x > IMAGE_MIN_INDEX) && (p.x < nrOfRows)) ||
              ((p.y == nrOfCols) && (p.x > IMAGE_MIN_INDEX) && (p.x < nrOfRows))
           );
}

// Find the points on the edge of the image

vector<Point> findPointsOnEdge(const vector<Point> &sector, int nrOfRows, int nrOfCols) {
    vector<Point> pointsOnEdge;

    for (Point p : sector) {
        if (isOnEdge(p, nrOfRows, nrOfCols)) {
            pointsOnEdge.push_back(p);
        }
    }

    return pointsOnEdge;
}

/* Get the angle of the sector by considering it to be equal to the
 * angle between the closest point to the origin and the points on the edges
 */
double sectorAngle(const vector<Point> &sector, int closestPointIndex, int nrOfRows, int nrOfCols) {
    Point closestPoint = sector[closestPointIndex];
    vector<Point> edgePoints = findPointsOnEdge(sector, nrOfRows, nrOfCols);

    // Consider that there are no more than 2 points on the edge
    return angleBtwPoints(edgePoints[0], closestPoint, edgePoints[1]);
}

// Print the details regarding the polygon

void printPolygonInformation(double area, double distance, double angle) {
    cout << "Area: " << area
         << ", distance: " << distance
         << ", angle: " << angle
         << endl;
}


// Display the required information about the contour
void displayPolygonInformation(const vector<Point> &polygon, int nrOfRows, int nrOfCols) {
    int minDistancePointIndex = minimumDistancePointIndex(polygon, origin);

    double area = contourArea(polygon, CONTOUR_AREA_ORIENTED);
    double distance = distanceBtwPoints(polygon[minDistancePointIndex], origin);
    double angle = sectorAngle(polygon, minDistancePointIndex, nrOfRows, nrOfCols);

    printPolygonInformation(area, distance, angle);
}

// Draw the points which define the polygon

void drawPolygonPoints(const vector<Point> &polygon, Mat &image) {
    for (auto point : polygon) {
        circle(image, point, IMAGE_MIN_INDEX, Scalar(0, 0, 0), 2, 8);
    }
}

// Find and display the contours

void findAndDisplayContours(const Mat &image, const Mat &originalImage) {
    Mat contoursImage = Mat::zeros(image.size(), CV_8UC1);
    Mat modifiedImage = Mat::zeros(image.rows + 2, image.cols + 2, image.type());
    Mat polygonsImage = Mat::zeros(originalImage.rows + 2, originalImage.cols + 2, originalImage.type());
    vector<vector<Point> > contours;

    image.copyTo(modifiedImage(Rect(IMAGE_MIN_INDEX, IMAGE_MIN_INDEX, image.cols, image.rows)));
    originalImage.copyTo(polygonsImage(Rect(IMAGE_MIN_INDEX, IMAGE_MIN_INDEX, originalImage.cols, originalImage.rows)));

    findContours(modifiedImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    for(unsigned int i = 0; i < contours.size(); i++ ) {
        if (!isValidBoundingBox(contours[i]))
            continue;

        // Obtain the approximated polygon and draw it
        vector<Point> approxCurve;

        approxPolyDP( contours[i], approxCurve, epsilon, true);
        polylines(polygonsImage, approxCurve, true, Scalar( 255, 255, 255));

        // Display information about the polygon
        displayPolygonInformation(approxCurve, originalImage.rows, originalImage.cols);
    }

    displayImage(polygonsImage(Rect(1, 1, originalImage.cols, originalImage.rows)), WIN_POLYGONS);
}

// Process the image and detect regions

void processImage(const Mat &originalImage, Mat &processedImage) {
    Mat thresholdedImage;

    changeContrastAndBrightness(originalImage, processedImage);
    morphologicalClose(processedImage);
    thresholdImage(processedImage, thresholdedImage);
    findAndDisplayContours(thresholdedImage, originalImage);
}

// Find the regions in the image

void findRegionsInImage(const Mat &image) {
    Mat processedImage = Mat::zeros(image.size(), image.type());
    int pressedKey = 0;

    createTrackbars();

    while (pressedKey != KEY_ESC) {
        processImage(image, processedImage);
        displayImage(processedImage, WIN_PROCESSED_IMAGE);

        pressedKey = cvWaitKey(10000);
    }
}

// Main function

int main() {
    MatFactory* factory = new RectangularMatFactory();

    Mat originalImage = factory->create("test/input/phase_variation_in_space4_61x61_trace4_101.in");

    delete factory;

    displayImage(originalImage, WIN_ORIGINAL_IMAGE);
    findRegionsInImage(originalImage);

    return 0;
}
