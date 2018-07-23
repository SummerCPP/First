#pragma once
//
//  OldMovie_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/20.
//
//  可用滤镜7个
//	包含:1.<怀旧电影滤镜>OldMovieImage
//		 2.<怀旧滤镜>ColorChange
//		 3.<旧照片滤镜>OldImage
//		 4.<旧笔记滤镜>OldPaperImage
//		 5.<碎片滤镜>FragmentImage
//		 6.<边框滤镜>FixedVignetting
//		 7.<碎片LOMO滤镜>FragmentLomoImage
//	两个可用功能:
//		 1.图片添加高斯噪点 ddNoise(Mat img, double mu, double sigma, int k) //推荐参数(0,0.1,64)/(0,0.5,64)
//		 2.移动图片 shift(Mat imge, int dir, int offset)	//dir方向参考ENUM Direction，Offset为偏移量推荐5

#ifndef OldMovie_filter_h
#define OldMovie_filter_h
#include <stdio.h>
#include <cstdlib>
#include <math.h>
;
#include<opencv2/highgui/highgui.hpp>
;
using namespace cv;

enum color{
	BLACK_BACK, WHITE_BACK
};
enum Direction{
	Up, Down, Right, Left
};

class OldMovie_filter {
public:
    OldMovie_filter()  {}
    ~OldMovie_filter() {}
	
	double generateGaussianNoise(double mu, double sigma);//生成随机高斯噪点
	Mat AddNoise(Mat img, double mu, double sigma, int k);//图片添加高斯噪点
	Mat shift(Mat imge, int dir, int offset);//移动图像(FRAGMENT内置函数)

    Mat ColorChage(Mat img);    //生成怀旧色图像
    Mat OldImage(Mat img);      //生成怀旧色+噪点图像
    Mat OldMovieImage(Mat img); //生成怀旧色+噪点+暗边图像
	Mat FixedVignetting(Mat img, int color);//生成添加白色毛边或黑色毛边图像
	Mat FragmentImage(Mat imge, int Offset);//生成碎片模糊图像
    Mat FragmentImage(Mat imge);            //缺参碎片模糊图像
    Mat FragmentLomoImage(Mat img);         //生成碎片模糊+暗边效果图像
    Mat OldPaperImage(Mat img);  //生成怀旧色+噪点+白边图像
};
#endif // !OldMovie_filter_h

