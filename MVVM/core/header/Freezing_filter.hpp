//
//  Freezing_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/22.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#ifndef Freezing_filter_hpp
#define Freezing_filter_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

class Freezing_filter{
public:
    Freezing_filter(){};
    ~Freezing_filter(){};
    Mat FreezingImage( Mat src );
};

#endif /* Freezing_filter_hpp */
