add_library(Gaussian_filter ./header/Gaussian_filter.hpp ./source/Gassian_filter.cpp)
add_executable(test_Gaussian_filter ./header/Gaussian_filter.hpp ./test/test_Gaussian_filter.cpp)
target_link_libraries(test_Gaussian_filter Caussian_filter)
