#include "multiscale/analysis/spatial/RegionDetector.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"
#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale::analysis;

RegionDetector::RegionDetector(const string &inputFilepath, const string &outputFilepath, bool debugMode) {
    this->inputFilepath = inputFilepath;
    this->outputFilepath = outputFilepath;
    this->isDebugMode = debugMode;

    initialiseVisionMembers();
}

RegionDetector::~RegionDetector() {}

void RegionDetector::detect() {
    MatFactory* factory = new RectangularMatFactory();

    Mat originalImage = factory->create(inputFilepath);

    delete factory;

    // Initialise the number of rows and columns and the origin
    initialiseImageDependentMembers(originalImage);

    detectRegions(originalImage);
}

void RegionDetector::initialiseVisionMembers() {
    alpha = 750;
    beta = 0;
    blurKernelSize = 1;
    morphologicalCloseIterations = 2;
    epsilon = 1;
    regionAreaThresh = 140;
    thresholdValue = 50;
}

void RegionDetector::initialiseImageDependentMembers(const Mat &image) {
    nrOfRows = image.rows;
    nrOfCols = image.cols;

    int originX = (nrOfRows + 1) / 2;
    int originY = (nrOfCols + 1) / 2;

    origin = Point(originX, originY);
}

void RegionDetector::createTrackbars() {
    namedWindow( WIN_PROCESSED_IMAGE, WINDOW_NORMAL);

    createTrackbar(TRACKBAR_ALPHA, WIN_PROCESSED_IMAGE, &alpha, ALPHA_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_BETA, WIN_PROCESSED_IMAGE, &beta, BETA_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_KERNEL, WIN_PROCESSED_IMAGE, &blurKernelSize, KERNEL_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_MORPH, WIN_PROCESSED_IMAGE, &morphologicalCloseIterations, ITER_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_CANNY, WIN_PROCESSED_IMAGE, &cannyLowerThreshold, CANNY_THRESH_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_EPSILON, WIN_PROCESSED_IMAGE, &epsilon, EPSILON_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_SECTOR_AREA_THRESH, WIN_PROCESSED_IMAGE, &regionAreaThresh, SECTOR_AREA_THRESH_MAX, nullptr, nullptr);
    createTrackbar(TRACKBAR_THRESHOLD, WIN_PROCESSED_IMAGE, &thresholdValue, SECTOR_AREA_THRESH_MAX, nullptr, nullptr);
}

void RegionDetector::detectRegions(const Mat &image) {
    vector<Region> regions;

    if (isDebugMode) {
        detectRegionsInDebugMode(image, regions);
    } else {
        detectRegionsInNormalMode(image, regions);
    }
}

void RegionDetector::detectRegionsInDebugMode(const Mat& image, vector<Region> &regions) {
    int pressedKey = 0;

    createTrackbars();

    while (pressedKey != KEY_ESC) {
        regions.clear();

        processImage(image, regions);
        outputRegions(image, regions);

        pressedKey = cvWaitKey(1);
    }
}

void RegionDetector::detectRegionsInNormalMode(const Mat& image, vector<Region> &regions) {
    processImage(image, regions);
    outputRegions(image, regions);
}

void RegionDetector::processImage(const Mat &image, vector<Region> &regions) {
    Mat processedImage, thresholdedImage;

    changeContrastAndBrightness(image, processedImage);
    morphologicalClose(processedImage);
    thresholdImage(processedImage, thresholdedImage);
    findRegions(thresholdedImage, regions);
}

void RegionDetector::changeContrastAndBrightness(const Mat &originalImage, Mat &processedImage) {
    originalImage.convertTo(processedImage, -1, convertAlpha(alpha), convertBeta(beta));
}

void RegionDetector::smoothImage(Mat &image) {
    if (blurKernelSize % 2) {
        GaussianBlur(image, image, Size(blurKernelSize, blurKernelSize), 0);
    } else {
        GaussianBlur(image, image, Size(blurKernelSize + 1, blurKernelSize + 1), 0);
    }
}

void RegionDetector::morphologicalClose(Mat &image) {
    morphologyEx(image, image, MORPH_CLOSE, Mat(), Point(-1, -1), morphologicalCloseIterations);
}

void RegionDetector::thresholdImage(const Mat &image, Mat &thresholdedImage) {
    threshold(image, thresholdedImage, thresholdValue, THRESHOLD_MAX, THRESH_BINARY);
}

void RegionDetector::findRegions(const Mat &image, vector<Region> &regions) {
    vector<vector<Point> > contours = findContoursInImage(image);

    int nrOfContours = contours.size();

    for(unsigned int i = 0; i < nrOfContours; i++ ) {
        if (!isValidRegion(contours[i]))
            continue;

        // Obtain the approximated polygon and draw it
        vector<Point> approxPolygon;

        approxPolyDP( contours[i], approxPolygon, epsilon, true );

        // Display information about the polygon
        regions.push_back(createRegionFromPolygon(approxPolygon));
    }
}

vector<vector<Point> > RegionDetector::findContoursInImage(const Mat &image) {
    Mat modifiedImage = Mat::zeros(image.rows + 2, image.cols + 2, image.type());
    vector<vector<Point> > contours;

    image.copyTo(modifiedImage(Rect(1, 1, image.cols, image.rows)));

    findContours(modifiedImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    return contours;
}

Region RegionDetector::createRegionFromPolygon(const vector<Point> &polygon) {
    unsigned int minDistancePointIndex = Geometry2D::minimumDistancePointIndex(polygon, origin);

    double area = contourArea(polygon, CONTOUR_AREA_ORIENTED);
    double distance = Geometry2D::distanceBtwPoints(polygon[minDistancePointIndex], origin);
    double angle = regionAngle(polygon, minDistancePointIndex);

    return Region(area, distance, angle, polygon);
}

// TODO: Change this method with the one considering the actual area?

bool RegionDetector::isValidRegion(const vector<Point> &polygon) {
    RotatedRect boundingBox = minAreaRect(polygon);
    double area = boundingBox.size.width * boundingBox.size.height;

    return (area >= regionAreaThresh);
}

double RegionDetector::regionAngle(const vector<Point> &polygon, unsigned int closestPointIndex) {
    Point closestPoint = polygon[closestPointIndex];
    vector<Point> edgePoints = Geometry2D::findPointsOnEdge(polygon, nrOfRows, nrOfCols);

    // Consider that there are no more than 2 points on the edge
    // TODO: Consider cases in which there are more than 2 points on the edge - take the ones farthest apart
    return Geometry2D::angleBtwPoints(edgePoints[0], closestPoint, edgePoints[1]);
}

void RegionDetector::outputRegions(const Mat &image, const vector<Region> &regions) {
    if (isDebugMode) {
        outputRegionsInDebugMode(image, regions);
    } else {
        outputRegionsAsPlainTextFile(regions);
    }
}

void RegionDetector::outputRegionsAsXMLFile(const vector<Region> &regions) {
    // TODO: Implement
}

void RegionDetector::outputRegionsAsPlainTextFile(const vector<Region> &regions) {
    // TODO: Implement
}

void RegionDetector::outputRegionsInDebugMode(const Mat &image, const vector<Region> &regions) {
    Mat outputImage = image.clone();

    for (const auto &region : regions) {
        polylines(outputImage, region.getPolygon(), true, Scalar(INTENSITY_MAX, INTENSITY_MAX, INTENSITY_MAX));
    }

    displayImage(outputImage, WIN_PROCESSED_IMAGE);
}

void RegionDetector::displayImage(const Mat& image, const string &windowName) {
    namedWindow( windowName, WINDOW_NORMAL );
    imshow( windowName, image );
}

double RegionDetector::convertAlpha(int alpha) {
    return NumericRangeManipulator::convertFromRange<int, double>(0, ALPHA_MAX, ALPHA_REAL_MIN, ALPHA_REAL_MAX, alpha);
}

int RegionDetector::convertBeta(int beta) {
    return NumericRangeManipulator::convertFromRange<int, int>(0, BETA_MAX, BETA_REAL_MIN, BETA_REAL_MAX, beta);
}
