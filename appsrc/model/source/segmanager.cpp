#include "global.h"
#include "segmanager.h"
#include "segimagemodel.h"

static segManager* segManager::generate(const string &filepath, int algocode){
    cv::Mat *init_data = cv::imread(filepath);
    if(init_data ->empty()){
        if(processmode == ALGO_GAUSSIAN_FILTER){
            return new segImageModel(init_data, processmode);
        }else{
            return new segImageModel(init_data, processmode);
        }
    }
    return NULL;
}
