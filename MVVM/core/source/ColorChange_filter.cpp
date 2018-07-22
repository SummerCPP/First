//
//  ColorChange_filter.cpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/22.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#include "ColorChange_filter.hpp"

Mat ColorChange_filter::ColorChangeImage( Mat src , int Color ){
    int width = src.cols;
    int heigh = src.rows;
    Mat gray;
    Mat imgColor;
    Mat display(heigh*3,width*4,CV_8UC3);
    cvtColor(src,gray,CV_BGR2GRAY);
    applyColorMap(gray,imgColor,Color);
    return imgColor;
}

