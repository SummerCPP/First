#include "../header/segmodel.h"
#include "../core/header/segcore.hpp"

#include <cstring>
segModel::segModel(){}

segModel::~segModel(){
    printf("Destroy this model");
    delete this->init_mat ;
    delete this->latest_mat ;
}

bool segModel::getStatus(){
    return this->loaded;
}

bool segModel::setupModel(const std::string & filename){
    cv::Mat mat = imread(filename);
    if(mat.empty()){
        return false;
    }else{
        this->init_mat = mat;
        this->latest_mat = mat ;
        this->loaded = true;
        return true;
    }
}

bool segModel::gsfilter(){
    Gaussian_filter *filter = new Gaussian_filter;
    this->latest_mat = filter->GaussianImage(*(this->latest_mat));
}

bool segModel::gsfilter(double delta, window_size){
    Gaussian_filter *filter = new Gaussian_filter;
    filter->latest_mat = filter->GaussianImage(*(this->latest_mat), delta,size);
}

cv::Mat segModel::getLatestData(){
	return *latest_mat; 
}

bool segModel::saveModel(const std::string &filename){
    // unit test
    // do nothing
    printf("saveModel()\n");
    return true;

    // [todo]
    // cv::imwrite(filename, this->latest_mat);
    // return true ;
}

