#include "segmodel.h"
#include "segcore.hpp"

#include <cstring>
#include <iostream>

segModel::segModel(){
    //系统支持的算法
    algo_list[ IMG_ALGO_0_GSFILTER ] = std::string(N0_GS_FILTER         );
    algo_list[ IMG_ALGO_1_ADD_NOISE ] = std::string(N1_ADD_NOISE         );
    algo_list[ IMG_ALGO_2_SHIFTER ] = std::string(N2_SHIFTER           );
    algo_list[ IMG_ALGO_3_COLOR_CHAGE ] = std::string(N3_COLOR_CHANGE      );
    algo_list[ IMG_ALGO_4_OLD_IMAGE ] = std::string(N4_OLD_IMAGE         );
    algo_list[ IMG_ALGO_5_OLD_MOVIE ] = std::string(N5_OLD_MOVIE_FILTER  );
    algo_list[ IMG_ALGO_6_FIXED_VIGNETTING ] = std::string(N6_FIXEDVIGNETTING   );
    algo_list[ IMG_ALGO_7_FRAGMENT ] = std::string(N7_FRAGMENT          );
    algo_list[ IMG_ALGO_8_FRAGMENT_LOMO ] = std::string(N8_FRAGMEN_MONO      );
    algo_list[ IMG_ALGO_9_OLD_PAPER ] = std::string(N9_OLDPAPER          );
}

segModel::~segModel(){
    destroyMats();
}

void segModel::destroyMats(){
    if(getStatus()){
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

void segModel::updateHistory(cv::Mat &temp){
    this->counter ++;
    if(this->counter > this->MAX_VIRSION_NUM){
        this->history.pop_back();
        this->history.push_front(new cv::Mat(temp));
        this->counter--;
    }else{
        //[debug] imwrite("F:/test/test3.jpg", temp);
        this->history.push_front(new cv::Mat(temp));
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
        updateHistory(temp);
        return true;
    }
}

bool segModel::addnoise(double mu, double delta, int s){
    if (!getStatus()) {
        return false;
    }
    OldMovie_filter filter;
    cv::Mat temp = history.front()->clone();
    temp =  filter.AddNoise(temp,mu,delta,s);
    if (temp.empty()){
        temp.release();
        return false;
    }
    else {
        updateHistory(temp);
        return true;
    }
}

bool segModel::shift(int a, int b){
    if (!getStatus()) {
        return false;
    }
    OldMovie_filter filter ;
    cv::Mat temp = history.front()->clone();
    temp = filter.shift(temp, a, b);
    if (temp.empty()){
        temp.release();
        return false;
    }
    else {
        updateHistory(temp);
        return true;
    }
}

bool segModel::colorchange(){
    if (!getStatus()) {
        return false;
    }
    OldMovie_filter filter ;
    cv::Mat temp = history.front()->clone();
    temp = filter.ColorChage(temp);
    if (temp.empty()){
        temp.release();
        return false;
    }
    else {
        updateHistory(temp);
        return true;
    }
}

bool segModel::oldimage(){
    if (!getStatus()) {
        std::cout <<"old image wrong!" << std::endl;
        return false;
    }
    OldMovie_filter filter ;
    cv::Mat temp = history.front()->clone();
    temp = filter.OldImage(temp);
    if (temp.empty()){
        temp.release();
        return false;
    }
    else {
        updateHistory(temp);
        return true;
    }
}

bool segModel::oldmovieimage(){
    if (!getStatus()) {
        return false;
    }
    OldMovie_filter filter ;
    cv::Mat temp = history.front()->clone();
    temp = filter.OldMovieImage(temp);
    if (temp.empty()){
        temp.release();
        return false;
    }
    else {
        updateHistory(temp);
        return true;
    }
}

bool segModel::fixedvignetting(int color){
    if (!getStatus()) {
        return false;
    }
    OldMovie_filter filter ;
    cv::Mat temp = history.front()->clone();
    temp = filter.FixedVignetting(temp, color);
    if (temp.empty()){
        temp.release();
        return false;
    }
    else {
        updateHistory(temp);
        return true;
    }
}

bool segModel::fragment(int ofs){
    if (!getStatus()) {
        return false;
    }
    OldMovie_filter filter ;
    cv::Mat temp = history.front()->clone();
    temp = filter.FragmentImage(temp, ofs);
    if (temp.empty()){
        temp.release();
        return false;
    }
    else {
        updateHistory(temp);
        return true;
    }
}

bool segModel::fragmentlomo(){
    if (!getStatus()) {
        return false;
    }
    OldMovie_filter filter ;
    cv::Mat temp = history.front()->clone();
    temp = filter.FragmentLomoImage(temp);
    if (temp.empty()){
        temp.release();
        return false;
    }
    else {
        updateHistory(temp);
        return true;
    }
}

bool segModel::oldpaperimage(){
    if (!getStatus()) {
        return false;
    }
    OldMovie_filter filter ;
    cv::Mat temp = history.front()->clone();
    temp = filter.OldPaperImage(temp);
    if (temp.empty()){
        temp.release();
        return false;
    }
    else {
        updateHistory(temp);
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
    if (temp.empty()){
        temp.release();
		return false;
    }
    else {
        updateHistory(temp);
        return true;
    }
}

cv::Mat segModel::getLatestData(){
    if(getStatus()){
        cv::Mat *temp = this->history.front();
        if(!temp) return cv::Mat();
        return *temp ;
    }
    cv::Mat mat;
    return mat;
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
        return false;
    }
    return true;
}

bool segModel::stage(){
    if(getStatus()){
        while(this->history.size()>1){
            this->history.pop_back();
        }
    }else{
        return false;
    }
    return true;
}

