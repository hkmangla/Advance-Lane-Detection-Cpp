cmake_minimum_required(VERSION 3.14)

project(LaneDetectionCpp)

set(CMAKE_CXX_STANDARD 14)

if (UNIX)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
    add_definitions(-DCMAKEMACROSAMPLE="${CMAKE_SYSTEM_NAME}")
elseif (WIN32)
    message("This is windows system")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(detect_lane ./src/Camera-Calibration.cpp)