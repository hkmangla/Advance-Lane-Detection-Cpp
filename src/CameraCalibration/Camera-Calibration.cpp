#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "../../libs/utils/utils.hpp"
#include "Camera-Calibration.hpp"

CameraCalibration::CameraCalibration (cv::Size chessboardSize, std::string imageDir) {
    chessboardSize_ = chessboardSize;
    imageDir_ = imageDir;
    setupCalibration();
}
CameraCalibration::~CameraCalibration() {}

void CameraCalibration::setupCalibration () {
    Utils::loadVector(imagePoints_, "image_points.yml");
    Utils::loadVector(objectPoints_, "object_points.yml");

    if (imagePoints_.size() != 0) {
        std::cout << "Using saved file for calibration" << std::endl;
        return;
    }
    std::vector<cv::Point3f> objectPoint;
    for (int i=0; i<chessboardSize_.height; i++) {
        for (int j=0; j<chessboardSize_.width; j++) {
            objectPoint.push_back(cv::Point3f(j, i, 0));
        }
    }

    std::vector<cv::Point2f> corners;
    std::vector<std::string> imageFiles = Utils::globVector(imageDir_);
    for(auto& imageFile: imageFiles) {
        cv::Mat image = cv::imread(imageFile), gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

        bool found = false;
        found = cv::findChessboardCorners (gray, chessboardSize_, corners);

        if (found) {
            objectPoints_.push_back(objectPoint);
            imagePoints_.push_back(corners);
            cv::drawChessboardCorners (gray, chessboardSize_, corners, found);
        }
    }
    Utils::saveVector (imagePoints_, "image_points.yml");
    Utils::saveVector (objectPoints_, "object_points.yml");
}

cv::Mat CameraCalibration::undistort (cv::Mat image) {
    cv:: Mat K, D;
    std::vector<cv::Mat> rvecs, tvecs;    
    int flag = 0;

    cv::Mat undistort_image;
    cv::calibrateCamera(objectPoints_, imagePoints_, image.size(), K, D, rvecs, tvecs, flag);
    cv::undistort(image, undistort_image, K, D);

    return undistort_image;
}