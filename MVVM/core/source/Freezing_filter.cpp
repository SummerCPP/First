//
//  Freezing_filter.cpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/22.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#include "Freezing_filter.hpp"

Mat Freezing_filter::FreezingImage( Mat src ){
    Mat img;
    src.copyTo(img);
    int width=src.cols;
    int heigh=src.rows;
    Mat dst(img.size(),CV_8UC3);
    for (int y=0;y<heigh;y++)
    {
        uchar* imgP=img.ptr<uchar>(y);
        uchar* dstP=dst.ptr<uchar>(y);
        for (int x=0;x<width;x++)
        {
            float b0=imgP[3*x];
            float g0=imgP[3*x+1];
            float r0=imgP[3*x+2];
            
            float b = (b0-g0-r0)*3/2;
            float g = (g0-b0-r0)*3/2;
            float r = (r0-g0-b0)*3/2;
            
            r = (r>255 ? 255 : (r<0? -r : r));
            g = (g>255 ? 255 : (g<0? -g : g));
            b = (b>255 ? 255 : (b<0? -b : b));
            // 			r = (r>255 ? 255 : (r<0? 0 : r));
            // 			g = (g>255 ? 255 : (g<0? 0 : g));
            // 			b = (b>255 ? 255 : (b<0? 0 : b));
            dstP[3*x] = (uchar)b;
            dstP[3*x+1] = (uchar)g;
            dstP[3*x+2] = (uchar)r;
        }
    }
    return dst;
}
