#include <opencv2/opencv.hpp>
#include "CameraCalibration/Camera-Calibration.hpp"

int main(int argc, char** argv )
{ 
    CameraCalibration cameraCalibration = CameraCalibration(cv::Size(9, 6), "../assets/camera_cal/*");
    cv::Mat image = cv::imread("../assets/camera_cal/calibration17.jpg");
    cv::namedWindow("image");
    cv::imshow("image", image);
    cv::waitKey(0);
    cv::Mat outImage;
    cameraCalibration.undistort(image, outImage);
    cv::namedWindow("image");
    cv::imshow("image", outImage);
    cv::waitKey(0);
    return 0;
}