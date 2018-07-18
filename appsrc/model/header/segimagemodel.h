#ifndef SEGIMAGEMODEL_H
#define SEGIMAGEMODEL_H

#include "segmanager.h"
#include "global.h"
#include "opencv2/highgui/highgui.hpp"

class segImageModel : segManager{
public :
    void updateProcessMode(int processMode);
    void process();
    cv::Mat latestData();
    bool saveModel();
    segImageModel(cv::Mat , int );

private :
    int algoCode;
    int statusFlag = 0;
    cv::Mat * init_mat ;
    cv::Mat * latest_mat;
}
#endif // SEGIMAGEMODEL_H
