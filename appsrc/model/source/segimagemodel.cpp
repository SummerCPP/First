#include "segimagemodel.h"
#include "../core/header/segcore.hpp"

segImageModel::segImageModel(cv::Mat *mat, int processmode){
    this->algoCode = processmode;
    this->init_mat = mat ;
    this->lastest_mat = new cv::Mat(mat) ; //[todo]
}

void segImageModel::updateProcessMode(int processMode){
    this->algoCode=processMode;
}

void segImageModel::process(){
    if(this->algoCode == ALGO_INVALID){
        //do nothing
    }else if(this->algoCode == ALGO_GAUSSIAN_FILTER){
        Gaussian_filter *filter = new Gaussian_filter();
        *this->latestData=filter->GaussianImage(*this->latestData());
    }else{
        //do nothing
    }
}

cv::Mat latestData(){
    return *this->latest_data;
}

bool segImageModel::saveModel(const string filename){
    cv::imwrite(filename, this->latest_mat);
}
