//
//  Glass_filter.cpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/22.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#include "Glass_filter.hpp"

Mat Glass_filter::GlassImage( Mat img ){
    int width = img.cols;
    int heigh = img.rows;
    RNG rng;
    Mat newImg(img.size(),CV_8UC3);
    for (int y = 0; y < heigh; y++)
    {
        uchar* P0  = img.ptr<uchar>(y);
        uchar* P1  = newImg.ptr<uchar>(y);
        for (int x = 0; x < width; x++)
        {
            int tmp=rng.uniform(0,9);
            P1[3*x]=img.at<uchar>(y-1+tmp/3,3*(x-1+tmp%3));
            P1[3*x+1]=img.at<uchar>(y-1+tmp/3,3*(x-1+tmp%3)+1);
            P1[3*x+2]=img.at<uchar>(y-1+tmp/3,3*(x-1+tmp%3)+2);
        }
        
    }
    return newImg;
}
