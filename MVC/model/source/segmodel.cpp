#include "segmodel.h"
#include "segcore.h"
#include <cstring>
#include <iostream>

segModel::segModel(){
    //supported algorithms
    algo_list[0] = std::string(GS_FILTER);
    algo_list[1] = std::string(INFO_HIDING);
    algo_list[2] = std::string(ALGO_OTHERS);
    //history deque
}

segModel::~segModel(){
    destroyMats();
}

void segModel::destroyMats(){
    if(getStatus()){
        std::cout << "this is valid " << std::endl;
        init_mat->release();
        while(!this->history.empty()){
            cv::Mat &temp = *history.front();
            history.pop_front();
            temp.release();
        }
        this->counter = 0 ;
    }
}

bool segModel::getStatus(){
    return this->loaded;
}

bool segModel::setupModel(const std::string & filename){
    cv::Mat mat = cv::imread(filename,3);
    if(mat.empty()){
		// debug 
        // std::cout << "cv::imread can not load image" << std::endl;
        std::cout << filename << std::endl ;
        return false;
    }else{
        destroyMats();
        this->init_mat = new cv::Mat(mat.clone());
        this->history.push_front(new cv::Mat(mat));
        this->counter = 1;
        this->loaded = true;
        return true;
    }
}

bool segModel::gsfilter(){
	if (!getStatus()) {
		return false;
	}
    Gaussian_filter *filter = new Gaussian_filter;
    cv::Mat temp = history.front()->clone();
    temp = filter->GaussianImage(temp);
	if (temp.empty())
		return false; 	
    else {
        this->counter ++;
        if(this->counter > this->MAX_VIRSION_NUM){
            this->history.pop_back();
            this->history.push_front(new cv::Mat(temp));
            this->counter--;
        }else{
            this->history.push_front(new cv::Mat(temp));
        }
        return true;
    }
}

bool segModel::gsfilter(double delta, int window_size){
	if (!getStatus()) {
		return false;
	}
    std::cout << "gs " << delta << " " << window_size << std::endl;
	Gaussian_filter *filter = new Gaussian_filter;
    cv::Mat temp = this->getLatestData().clone();
    temp = filter->GaussianImage(temp, delta, window_size);
	if (temp.empty())
		return false;
    else {
        this->counter ++;
        if(this->counter > this->MAX_VIRSION_NUM){
            this->history.pop_back();
            this->history.push_front(new cv::Mat(temp));
            this->counter--;
        }else{
            this->history.push_front(new cv::Mat(temp));
        }
        return true;
    }
}

cv::Mat segModel::getLatestData(){
    std::cout <<" total : " << counter ;
    if(getStatus()){
        cv::Mat *temp = this->history.front();
        if(!temp) return cv::Mat();
        return *temp ;
    }
}

cv::Mat segModel::getInitialData(){
    return *history.back();
}

bool segModel::saveModel(const std::string &filename) {
	if (getStatus()) {
        cv::imwrite(filename, this->getLatestData());
		return true;
	}
	else {
		return false; 
	}
}

bool segModel::undo(){
    if(getStatus() && counter > 1){
        this->history.pop_front();
        counter--;
    }else{
        std::cout << "something wrong ! " << counter << std::endl ;
        return false;
    }
    return true;
}
