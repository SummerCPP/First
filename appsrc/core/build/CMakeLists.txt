# project name
PROJECT(Gaussian_filter)

# requirement of cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

# set the directory of executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Gaussian_filter_SOURCE_DIR}/bin)

# find required opencv
FIND_PACKAGE(OpenCV REQUIRED)
# directory of opencv headers
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
# name of executable file and path of source file
 add_executable(Gaussian_filter src/main.cpp)
# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})
# opencv libraries
target_link_libraries(Gaussian_filter ${OpenCV_LIBS})