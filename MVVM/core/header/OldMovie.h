#pragma once
//
//  OldMovie_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/20.
//
//  �����˾�7��
//	����:1.<���ɵ�Ӱ�˾�>OldMovieImage
//		 2.<�����˾�>ColorChange
//		 3.<����Ƭ�˾�>OldImage
//		 4.<�ɱʼ��˾�>OldPaperImage
//		 5.<��Ƭ�˾�>FragmentImage
//		 6.<�߿��˾�>FixedVignetting
//		 7.<��ƬLOMO�˾�>FragmentLomoImage
//	�������ù���:
//		 1.ͼƬ��Ӹ�˹��� ddNoise(Mat img, double mu, double sigma, int k) //�Ƽ�����(0,0.1,64)/(0,0.5,64)
//		 2.�ƶ�ͼƬ shift(Mat imge, int dir, int offset)	//dir����ο�ENUM Direction��OffsetΪƫ�����Ƽ�5

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
	
	double generateGaussianNoise(double mu, double sigma);//���������˹���
	Mat AddNoise(Mat img, double mu, double sigma, int k);//ͼƬ��Ӹ�˹���
	Mat shift(Mat imge, int dir, int offset);//�ƶ�ͼ��(FRAGMENT���ú���)

    Mat ColorChage(Mat img);    //���ɻ���ɫͼ��
    Mat OldImage(Mat img);      //���ɻ���ɫ+���ͼ��
    Mat OldMovieImage(Mat img); //���ɻ���ɫ+���+����ͼ��
	Mat FixedVignetting(Mat img, int color);//������Ӱ�ɫë�߻��ɫë��ͼ��
	Mat FragmentImage(Mat imge, int Offset);//������Ƭģ��ͼ��
    Mat FragmentImage(Mat imge);            //ȱ����Ƭģ��ͼ��
    Mat FragmentLomoImage(Mat img);         //������Ƭģ��+����Ч��ͼ��
    Mat OldPaperImage(Mat img);  //���ɻ���ɫ+���+�ױ�ͼ��
};
#endif // !OldMovie_filter_h

