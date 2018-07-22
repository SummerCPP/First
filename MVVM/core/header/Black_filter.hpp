//
//  Black_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/22.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#ifndef Black_filter_hpp
#define Black_filter_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
using namespace cv;
class Black_filter{
public:
    Black_filter(){};
    ~Black_filter(){};
    Mat BlackImage( Mat img );
};

#endif /* Black_filter_hpp */
