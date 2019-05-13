cmake_minimum_required(VERSION 3.14)

project(LaneDetectionCpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()
set(SOURCES src/main.cpp
            src/CameraCalibration/Camera-Calibration.cpp
            src/CameraCalibration/Camera-Calibration.hpp)

add_executable(detect_lane ${SOURCES})

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(detect_lane ${OpenCV_LIBS})

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries (detect_lane Eigen3::Eigen)

add_subdirectory(libs/utils)
target_link_libraries (detect_lane utils)