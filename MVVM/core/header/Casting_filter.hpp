//
//  Casting_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/22.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#ifndef Casting_filter_hpp
#define Casting_filter_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

class Casting_filter{
public:
    Casting_filter(){};
    ~Casting_filter(){};
    Mat CastingImage( Mat img );
};

#endif /* Casting_filter_hpp */
