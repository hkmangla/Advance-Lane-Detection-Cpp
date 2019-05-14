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
    std::vector<std::string> imageFiles;
    Utils::globVector(imageDir_, imageFiles);
    for(auto& imageFile: imageFiles) {
        cv::Mat image = cv::imread(imageFile), gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

        bool found = false;
        found = cv::findChessboardCorners (gray, chessboardSize_, corners);

        if (found) {
            objectPoints_.push_back(objectPoint);
            imagePoints_.push_back(corners);
        }
    }
    Utils::saveVector (imagePoints_, "image_points.yml");
    Utils::saveVector (objectPoints_, "object_points.yml");
}

void CameraCalibration::undistort (cv::Mat& image, cv::Mat& outputImage) {

    if (imageSize != image.size()) {
        imageSize = image.size();
        std::vector<cv::Mat> rvecs, tvecs;    
        int flag = 0;
        cv::calibrateCamera(objectPoints_, imagePoints_, imageSize, K, D, rvecs, tvecs, flag);
    }
    
    cv::undistort(image, outputImage, K, D);
}