// 用于封装算法参数数据的结构
#ifndef SEGPARAMETER_H
#define SEGPARAMETER_H

#include "config.h"

struct segParameter{
    int algo_mode;
    segParameter(int);
    ~segParameter();
    int getMode();
};

struct segParameter_gsfilter : public segParameter{
    double variance = 0.5; //default parameter
    int kernal_size = 8 ;
    segParameter_gsfilter(double, int, int);
    ~segParameter_gsfilter();
};

struct segParameter_addnoise : public segParameter{
    double variance = 0.5;
    double mu = 0 ;
    int strength = 8 ;
    segParameter_addnoise(double,double,int);
    ~segParameter_addnoise();
};

struct segParameter_shift : public segParameter{
    int direction = D_SOUTH;
    int ofs = 1;
    segParameter_shift(int,int);
    ~segParameter_shift();
};

struct segParameter_fixedvignetting: public segParameter{
    int color;
    segParameter_fixedvignetting(int);
    ~segParameter_fixedvignetting();
};

struct segParameter_fragment: public segParameter{
    int offset;
    segParameter_fragment(int);
    ~segParameter_fragment();
};

#endif // SEGPARAMETER_H
