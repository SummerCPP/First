//
//  ColorChange_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/22.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#ifndef ColorChange_filter_hpp
#define ColorChange_filter_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

enum COLORMAP
{
    COLORMAP_AUTUMN = 0,
    COLORMAP_BONE = 1,
    COLORMAP_JET = 2,
    COLORMAP_WINTER = 3,
    COLORMAP_RAINBOW = 4,
    COLORMAP_OCEAN = 5,
    COLORMAP_SUMMER = 6,
    COLORMAP_SPRING = 7,
    COLORMAP_COOL = 8,
    COLORMAP_HSV = 9,
    COLORMAP_PINK = 10,
    COLORMAP_HOT = 11
};

class ColorChange_filter{
public:
    ColorChange_filter(){};
    ~ColorChange_filter(){};
    Mat ColorChangeImage( Mat src , int Color );
};
#endif /* ColorChange_filter_hpp */
