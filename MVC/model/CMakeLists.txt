# project name
PROJECT(testModel)

# requirement of cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# set the directory of executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "F:/test/build/library")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "F:/test/build/library")


set(OpenCV_LIB_PATH "E:/opencv/opencv/build/x64/v15/lib/")
set(OpenCV_DIR "E:/opencv/opencv/build/")

# find required opencv
FIND_PACKAGE(OpenCV REQUIRED)

# directory of opencv headers
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(./header)


# name of executable file and path of source file

# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})

# add my library
link_directories(./library/) 

set(MY_HEADERS "./header/config.h" "./header/segmodel.h")
add_library(segmodel STATIC  "./source/segmodel.cpp"  ${MY_HEADERS})
set_target_properties(segmodel PROPERTIES LIBRARY_OUTPUT_DIRECTOYR "F:/test/build/library")
add_executable(test_segmodel "./source/test_segmodel.cpp" ${MY_HEADERS})
# opencv libraries
target_link_libraries(segmodel ${OpenCV_LIBS})
target_link_libraries(segmodel gsfilter)
target_link_libraries(test_segmodel ${OpenCV_LIBS})
target_link_libraries(test_segmodel segmodel)

