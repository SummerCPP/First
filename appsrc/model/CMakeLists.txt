# project name
PROJECT(testModel)

# requirement of cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# set the directory of executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "E:/test/build/library")


set(OpenCV_LIB_PATH "E:/opencv/opencv/build/x64/v15/lib/")
set(OpenCV_DIR "E:/opencv/opencv/build/")

# find required opencv
FIND_PACKAGE(OpenCV REQUIRED)

# directory of opencv headers
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(./testModel/header)

# name of executable file and path of source file

# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})

# add my library
link_directories(./testModel/library/) 

set(MY_HEADERS "./testModel/header/global.h" "./testModel/header/segimagemodel.h" "./testModel/header/segmanager.h")
add_library(segmodel STATIC  "./testModel/source/segmanager.cpp" "./testModel/source/segimagemodel.cpp" ${MY_HEADERS})
add_executable(test_segmodel "./testModel/source/test_segmodel.cpp" ${MY_HEADERS})
# opencv libraries
target_link_libraries(segmodel ${OpenCV_LIBS})
target_link_libraries(test_segmodel ${OpenCV_LIBS})
target_link_libraries(test_segmodel segmodel)

