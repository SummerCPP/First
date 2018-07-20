#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
class Gaussian_filter {
public:
	Gaussian_filter() {};
	~Gaussian_filter() {};
	Mat GaussianImage(Mat image, double sigma, int iSize);
	Mat GaussianImage(Mat image);
private:
	double* CreateMuban(int iSize, double sigma);
	Mat operateimage(Mat _img, double*Muban, int iSize);
};