#include "global.h"
#include "segmanager.h"
#include "segimagemodel.h"

#include <cstring>
#include <string.h>
#include <iostream>
#include "..\header\segmanager.h"

segManager* segManager::generate(const std::string &filepath, int algocode){
	std::cout << "debug!"; 
	cv::Mat init_data = cv::imread(filepath);
    if(!init_data.empty()){
        if(algocode== ALGO_GAUSSIAN_FILTER){
            return new segImageModel(init_data, algocode);
        }else{
            return new segImageModel(init_data, algocode);
        }
	}
	else {
		std::cout << "can not read image!\n from " << filepath << std::endl; 
	}
    return NULL;
}

void segManager::destroy(segManager* done){
    //[0] test
    //do nothing
}

segManager::segManager()
{
}

segManager::~segManager()
{
}
