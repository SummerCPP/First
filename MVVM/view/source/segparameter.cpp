#include "config.h"
#include "segparameter.h"

segParameter::segParameter(int setmode){
    this->algo_mode = setmode;
}
segParameter::~segParameter(){}

int segParameter::getMode(){
    return this->algo_mode;
}

segParameter_gsfilter::segParameter_gsfilter(double var, int sz, int mode): segParameter(mode), kernal_size(sz), variance(var){}
segParameter_addnoise::segParameter_addnoise(double mu, double delta, int s): segParameter(IMG_ALGO_1_ADD_NOISE), mu(mu), variance(delta){}
segParameter_fixedvignetting::segParameter_fixedvignetting(int color): segParameter(IMG_ALGO_6_FIXED_VIGNETTING), color(color){}
segParameter_fragment::segParameter_fragment(int ofs):segParameter(IMG_ALGO_7_FRAGMENT), offset(ofs){}
segParameter_shift::segParameter_shift(int d, int l):segParameter(IMG_ALGO_2_SHIFTER), direction(d), ofs(l){}

segParameter_gsfilter::~segParameter_gsfilter(){}
segParameter_addnoise::~segParameter_addnoise(){}
segParameter_fixedvignetting::~segParameter_fixedvignetting(){}
segParameter_fragment::~segParameter_fragment(){}
segParameter_shift::~segParameter_shift(){}
