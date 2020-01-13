cmake_minimum_required(VERSION 3.7)
project(g203)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
)

find_package(OpenCV 4.0 QUIET)
if(NOT OpenCV_FOUND)
    find_package(OpenCV 2.4.3 QUIET)
    if(NOT OpenCV_FOUND)
        message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
    endif()
endif()
find_library(ENET_LIBRARY
        NAMES enet
        PATHS
        $ENV{ENETDIR}
        /usr/local
        /usr
        PATH_SUFFIXES lib
        )
find_library(wiringPi_LIB wiringPi)

add_executable(g203 main.cpp G203.cpp Network.cpp parts/Camera.cpp parts/Motor.cpp)

target_link_libraries(g203
        ${wiringPi_LIB}
        pthread
        ${ENET_LIBRARY}
        ${OpenCV_LIBS}
)