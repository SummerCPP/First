//
//  Gaussian_filter.cpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/14.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#include "Gaussian_filter.hpp"

double* Gaussian_filter::CreateMuban(int iSize,double sigma)
{
    double *gauss=new double[iSize];
    int radius=(iSize-1)/2;
    double MySigma=2*sigma*sigma;
    double value=0;
    for (int i = 0; i <iSize; i++)
    {
        gauss[i]=exp(-(i-radius)*(i-radius)/MySigma);
        value=value+gauss[i];
    }
    for (int i = 0; i < iSize; i++)
    {
        gauss[i]=gauss[i]/value;
    }
    return gauss;
}

Mat Gaussian_filter::operateimage(Mat _img,double*Muban,int iSize)
{
    Mat img=_img;
    Mat img1=_img;
    Mat img2=_img;
    int radius=(iSize-1)/2;
    int r=0;
    int g=0;
    int b=0;
    for (int i = (iSize+1)/2; i < img.rows-(iSize+1)/2; i++)
    {
        for (int j = (iSize+1)/2; j <img.cols-(iSize+1)/2; j++)
        {
            for (int k = 0; k < iSize; k++)
            {
                b=b+(img.at<Vec3b>(i,j-radius+k)[0])*Muban[k];
                g=g+(img.at<Vec3b>(i,j-radius+k)[1])*Muban[k];
                r=r+(img.at<Vec3b>(i,j-radius+k)[2])*Muban[k];
            }
            img1.at<Vec3b>(i,j)=Vec3b(b,g,r);
            b=0;
            g=0;
            r=0;
        }
    }
    
    for (int i = (iSize+1)/2; i < img1.cols-(iSize+1)/2; i++)
    {
        for (int j = (iSize+1)/2; j <img1.rows-(iSize+1)/2; j++)
        {
            for (int k = 0; k < iSize; k++)
            {
                b=b+(img1.at<Vec3b>(j-radius+k,i)[0])*Muban[k];
                g=g+(img1.at<Vec3b>(j-radius+k,i)[1])*Muban[k];
                r=r+(img1.at<Vec3b>(j-radius+k,i)[2])*Muban[k];
            }
            img2.at<Vec3b>(j,i)=Vec3b(b,g,r);
            b=0;
            g=0;
            r=0;
        }
    }
    return img2;
}

Mat Gaussian_filter::GaussianImage( String filepath , double sigma , int iSize){
    Mat image = imread(filepath);
    double *Muban = CreateMuban(iSize,sigma);
    return operateimage(image, Muban, iSize);
}

Mat Gaussian_filter::GaussianImage( String filepath ){
    return GaussianImage(filepath, 0.25, 3);
}

Gaussian_filter(){}
~Gaussian_filter(){}
