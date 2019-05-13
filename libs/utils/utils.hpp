#ifndef _UTILS_H_
#define _UTILS_H_
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

namespace Utils {
    std::vector<std::string> globVector (const std::string& pattern);
    
    template<typename T>
    void saveVector(std::vector<T>& vec, const std::string& filename) {
        cv::FileStorage storage(filename, cv::FileStorage::WRITE);
        storage << "img" << vec;
        storage.release(); 
    }

    template<typename T>
    void loadVector(std::vector<T>& vec, const std::string& filename) {
        cv::FileStorage storage(filename, cv::FileStorage::READ);
        storage["img"] >> vec;
        storage.release(); 
    }
}

#endif
