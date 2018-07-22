//
//  Glass_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/22.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#ifndef Glass_filter_hpp
#define Glass_filter_hpp

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace cv;

class Glass_filter{
public:
    Glass_filter(){};
    ~Glass_filter(){};
    Mat GlassImage( Mat img );
};

#endif /* Glass_filter_hpp */
