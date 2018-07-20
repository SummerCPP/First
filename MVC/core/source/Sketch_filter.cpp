//
//  Sketch_filter.cpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/19.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#include "Sketch_filter.hpp"

Mat Sketch_filter::SketchImage(Mat srcImage){
    Mat gray0,gray1;
    //去色，灰度化
    cvtColor(srcImage,gray0,CV_BGR2GRAY);
    
    //反色
    addWeighted(gray0,-1,NULL,0,255,gray1);
    
    //高斯模糊,高斯核的Size与最后的效果有关
    GaussianBlur(gray1,gray1,Size(11,11),0);
    
    //融合：颜色减淡
    Mat dstImage(gray1.size(),CV_8UC1);
    
    for (int y=0; y<srcImage.rows; y++)
    {
        uchar* P0  = gray0.ptr<uchar>(y);
        uchar* P1  = gray1.ptr<uchar>(y);
        uchar* P  = dstImage.ptr<uchar>(y);
        for (int x=0; x<srcImage.cols; x++)
        {
            int tmp0=P0[x];
            int tmp1=P1[x];
            P[x] =(uchar) min((tmp0+(tmp0*tmp1)/(256-tmp1)),255);
        }
    }
    
    return dstImage;
}
