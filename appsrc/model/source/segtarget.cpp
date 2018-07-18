#include "segtarget.h"
#include "global.h"
#include "segimagemodel.h"

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

static segTarget* segTarget::generate(const char*filepath, int processmode){
    cv::Mat *init_data = cv::imread(filepath);
    if(init_data ->empty()){
        return NULL;
    }
    segTarget *newtarget;
        if(processmode == ALGO_GAUSSIAN_FILTER){
            newtarget = new segImageModel(init_data, processmode);
        }else{
            newtarget = new segImageModel(init_data, processmode);
        }
    }
}
