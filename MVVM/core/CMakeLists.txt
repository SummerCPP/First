# project name
PROJECT(Gaussian_filter)

# requirement of cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# set the directory of executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Gaussian_filter_SOURCE_DIR}/library/)

set(OpenCV_LIB_PATH "E:/opencv/opencv/build/x64/v15/lib/")
set(OpenCV_DIR "E:/opencv/opencv/build/")

# find required opencv
FIND_PACKAGE(OpenCV REQUIRED)

# directory of opencv headers
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(./core/header)

# name of executable file and path of source file

# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})

# add my library
link_directories(./library/) 

set(MY_HEADERS "./core/header/Gaussian_filter.hpp" "./core/header/segcore.hpp")
add_library(segcore STATIC "./core/source/Gaussian_filter.cpp" ${MY_HEADERS})
add_executable(test_filter "./core/source/test_filter.cpp" ${MY_HEADERS})

target_link_libraries(segcore ${OpenCV_LIBS})
target_link_libraries(test_filter ${OpenCV_LIBS})
target_link_libraries(test_filter segcore)
