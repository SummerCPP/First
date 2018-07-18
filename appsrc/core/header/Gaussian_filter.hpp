//  Gaussian_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/14.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//
//  *高斯滤波器对外接口说明(使用前请先初始化类)
//    Mat GaussianImage( String filepath , double sigma , int iSize);
//    其中filepath为文件路径，sigma为标准差，iSize为高斯模版大小
//    也可以使用如下函数
//    Mat GaussianImage( String filepath );
//    默认sigma为0.25，iSize为3。

#ifndef Gaussian_filter_hpp
#define Gaussian_filter_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <cstring>

using namespace cv;
class Gaussian_filter{
public:
    Gaussian_filter();
    ~Gaussian_filter();
    Mat GaussianImage( String filepath , double sigma , int iSize);
    Mat GaussianImage( Mat img , double sigma , int iSize);
    Mat GaussianImage( String filepath );
    Mat GaussianImage( Mat img);

private:
    double* CreateMuban(int iSize,double sigma);
    Mat operateimage(Mat _img,double*Muban,int iSize);
};

#endif /* Gaussian_filter_hpp */
