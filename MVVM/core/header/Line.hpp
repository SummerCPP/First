//
//  Line_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/19.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#ifndef Line_filter_hpp
#define Line_filter_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

class Line_filter{
public:
    Line_filter(){}
    ~Line_filter(){}
    Mat LineImage(Mat srcImage);
};
#endif /* Line_filter_hpp */
