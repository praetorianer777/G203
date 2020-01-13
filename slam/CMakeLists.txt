cmake_minimum_required(VERSION 3.15)
project(slam)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(OpenCV 3.0 QUIET)
#if(NOT OpenCV_FOUND)
#    find_package(OpenCV 2.4.3 QUIET)
#    if(NOT OpenCV_FOUND)
#        message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
#    endif()
#endif()

find_package(Eigen3 3.1.0 REQUIRED)
find_package(Pangolin REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/)
find_package(SFML 2 COMPONENTS audio graphics window system network REQUIRED)

## load in pkg-config support
find_package(PkgConfig)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${EIGEN3_INCLUDE_DIR}
        ${Pangolin_INCLUDE_DIRS}
)

find_library(ENET_LIBRARY
        NAMES enet
        PATHS
        $ENV{ENETDIR}
        /usr/local
        /usr
        PATH_SUFFIXES lib
)

add_executable(slam main.cpp Network.cpp Network.h Argparse.h Slam.cpp Slam.h Control.cpp Control.h PID.cpp PID.h)
target_link_libraries(${PROJECT_NAME}
        ${OpenCV_LIBS}
        ${Pangolin_LIBRARIES}
        ${ENET_LIBRARY}
        ${SFML_LIBRARIES}
        ${PROJECT_SOURCE_DIR}/Thirdparty/DBoW2/lib/libDBoW2.so
        ${PROJECT_SOURCE_DIR}/Thirdparty/g2o/lib/libg2o.so
        ${PROJECT_SOURCE_DIR}/lib/libORB_SLAM2.so
        stdc++fs
)

