#include "../header/segimagemodel.h"
// debug 
//#include "../core/header/segcore.hpp"

segImageModel::segImageModel(cv::Mat mat, int processmode)
{
    this->algoCode = processmode;
    this->init_mat = new cv::Mat(mat);
    this->latest_mat = new cv::Mat(mat) ; //[todo]
}

segImageModel::~segImageModel(){
    printf("Destroy this model");
    delete this->init_mat ;
    delete this->latest_mat ;
}

void segImageModel::updateProcessMode(int processMode){
    // test
    algoCode=processMode;
}

void segImageModel::process(){
    if(algoCode == ALGO_INVALID){
        printf("segImageModel do not have legal algo parameter set \n") ;
        //do nothing
    }else if(algoCode == ALGO_GAUSSIAN_FILTER){
        //unit test
        *(latest_mat) = *(init_mat);

        //real implement
        //Gaussian_filter *filter = new Gaussian_filter();
        //*this->latestData=filter->GaussianImage(*this->latestData());
    }else{
        printf("segImageModel do not have legal algo parameter set \n") ;
        //do nothing
    }
}

cv::Mat segImageModel::getLatestData(){
	return *latest_mat; 
}

bool segImageModel::saveModel(const std::string &filename){
    // unit test
    // do nothing
    printf("saveModel()\n");
    return true;

    // [todo]
    // cv::imwrite(filename, this->latest_mat);
    // return true ;
}
