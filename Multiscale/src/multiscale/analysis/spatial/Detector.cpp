#include "multiscale/analysis/spatial/Detector.hpp"

#include <iostream>

using namespace multiscale::analysis;
using namespace std;


Detector::Detector(bool debugMode) {
    this->debugMode = debugMode;

    this->detectMethodCalled = false;
    this->detectorSpecificFieldsInitialised = false;
}

Detector::~Detector() {
    image.release();
    outputImage.release();
}

void Detector::detect(const Mat &inputImage) {
    if (!isValidInputImage(inputImage))
        throw ERR_INVALID_IMAGE;

    inputImage.copyTo(image);

    initialise();
    detect();
}

void Detector::outputResults(const string &outputFilepath) {
    if (detectMethodCalled) {
        this->outputFilepath = outputFilepath;

        outputResultsToFile();
    } else {
        printOutputErrorMessage();
    }
}

void Detector::initialise() {
    initialiseImageDependentFields();
    initialiseDetectorSpecificFieldsIfNotSet();
}

void Detector::initialiseDetectorSpecificFieldsIfNotSet() {
    if (!detectorSpecificFieldsInitialised) {
        initialiseDetectorSpecificFields();

        detectorSpecificFieldsInitialised = true;
    }
}

bool Detector::isValidInputImage(const Mat &inputImage) {
    return ((inputImage.type() == CV_8UC1) && (inputImage.dims == 2) && (inputImage.rows > 1) && (inputImage.cols > 1));
}

void Detector::detect() {
    detectMethodCalled = true;

    if (debugMode) {
        detectInDebugMode();
    } else {
        detectInReleaseMode();
    }
}

void Detector::detectInDebugMode() {
    char pressedKey = -1;

    createTrackbars();

    while (pressedKey != KEY_ESC) {
        clearPreviousDetectionResults();

        processImageAndDetect();
        displayResultsInWindow();

        processPressedKeyRequest(pressedKey);
    }
}

void Detector::detectInReleaseMode() {
    clearPreviousDetectionResults();
    processImageAndDetect();
}

void Detector::displayResultsInWindow() {
    outputResultsToImage();
    displayImage(outputImage, WIN_OUTPUT_IMAGE);
}

void Detector::outputResultsToFile() {
    outputResultsToCsvFile();

    outputResultsToImage();
    storeOutputImageOnDisk();
}

void Detector::storeOutputImageOnDisk() {
    if (outputImage.data) {
        imwrite(outputFilepath + IMG_EXTENSION, outputImage);
    }
}

void Detector::outputResultsToCsvFile() {
    ofstream fout(outputFilepath + OUTPUT_EXTENSION, ios_base::trunc);

    if (!fout.is_open())
        throw ERR_OUTPUT_FILE;

    outputResultsToCsvFile(fout);

    fout.close();
}

void Detector::createTrackbars() {
    createTrackbarsWindow();
    createDetectorSpecificTrackbars();
}

void Detector::createTrackbarsWindow() {
    namedWindow( WIN_OUTPUT_IMAGE, WINDOW_NORMAL);
    setWindowProperty( WIN_OUTPUT_IMAGE, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN );
}

void Detector::processPressedKeyRequest(char &pressedKey) {
    pressedKey = waitKey(1);

    // Additional processing can be added here in the future
}

void Detector::displayImage(const Mat &image, const string &windowName) {
    namedWindow( windowName, WINDOW_NORMAL );
    imshow( windowName, image );
}

void Detector::printOutputErrorMessage() {
    cout << ERR_OUTPUT_WITHOUT_DETECT << endl;
}
