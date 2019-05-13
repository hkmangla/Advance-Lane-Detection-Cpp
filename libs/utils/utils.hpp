#ifndef _UTILS_H_
#define _UTILS_H_
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <iterator>

class Utils {
    public:
    static std::vector<std::string> globVector(const std::string&);
    
    template<typename T>
    static void saveVector(std::vector<T>& vec, const std::string& filename) {
        cv::FileStorage storage(filename, cv::FileStorage::WRITE);
        storage << "img" << vec;
        storage.release(); 
    }

    template<typename T>
    static void loadVector(std::vector<T>& vec, const std::string& filename) {
        cv::FileStorage storage(filename, cv::FileStorage::READ);
        storage["img"] >> vec;
        storage.release(); 
    }
};
#endif
