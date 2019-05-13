#ifndef CAMERA_CALIBRATION_H_
#define CAMERA_CALIBRATION_H_

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class CameraCalibration {
    private:
    cv::Size chessboardSize_;
    std::string imageDir_;
    std::vector<std::vector<cv::Point3f> > objectPoints_;
    std::vector<std::vector<cv::Point2f> > imagePoints_;
    void setupCalibration();
    
    public:
    CameraCalibration(cv::Size chessboardSize, std::string imageDir);
    ~CameraCalibration();
    cv::Mat undistort(cv::Mat image);
};

#endif