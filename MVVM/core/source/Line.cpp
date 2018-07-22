//
//  Line_filter.cpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/19.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#include "Line.hpp"

Mat Line_filter::LineImage(Mat srcImage){
    Mat grayImage;
    Mat edge;
    Mat dstImage;

    //灰度化
    cvtColor(srcImage, grayImage, CV_BGR2GRAY);

    // 设置中值滤波器参数
    medianBlur(grayImage, grayImage, 7);

    // Laplacian边缘检测
    Laplacian(grayImage, edge, CV_8U, 5);

    imshow("La",edge);
    // 对边缘检测结果进行二值化

    threshold(edge, dstImage, 127, 255, THRESH_BINARY_INV);// >127 ? 0:255,用黑色描绘轮廓

    imshow("线条滤镜",dstImage);
    return dstImage;
}
