//
//  main.cpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/14.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#include "Gaussian_filter.hpp"

int main(int argc, char** argv) {
    Gaussian_filter test;
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", test.GaussianImage("/Users/Jeanne/test/1.png", 1, 3));
    waitKey(0);
    return 0;
}
