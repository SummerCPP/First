//
//  Black_filter.cpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/22.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#include "Black_filter.hpp"

Mat Black_filter::BlackImage( Mat img ){
    int width = img.cols;
    int heigh = img.rows;
    RNG rng;
    Mat newImg(img.size(),CV_8UC3);
    for (int y = 0; y<heigh; y++)
    {
        uchar* P0  = img.ptr<uchar>(y);
        uchar* P1  = newImg.ptr<uchar>(y);
        for (int x = 0; x<width; x++)
        {
            float B=P0[3*x];
            float G=P0[3*x+1];
            float R=P0[3*x+2];
            float newB=abs(B-G+B+R)*G/256;
            float newG=abs(B-G+B+R)*R/256;
            float newR=abs(G-B+G+R)*R/256;
            if(newB<0)newB=0;
            if(newB>255)newB=255;
            if(newG<0)newG=0;
            if(newG>255)newG=255;
            if(newR<0)newR=0;
            if(newR>255)newR=255;
            P1[3*x] = (uchar)newB;
            P1[3*x+1] = (uchar)newG;
            P1[3*x+2] = (uchar)newR;
        }
        
    }
    Mat gray;
    cvtColor(newImg,gray,CV_BGR2GRAY);
    normalize(gray,gray,255,0,CV_MINMAX);
    return gray;
}
