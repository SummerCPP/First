#ifndef SEGIMAGEMODEL_H
#define SEGIMAGEMODEL_H

#include "segmanager.h"
#include "opencv2/highgui/highgui.hpp"


;
class segImageModel : public segManager {

public :
    segImageModel(cv::Mat , int );
    ~segImageModel();

    void updateProcessMode(int processMode);
    void process();
    cv::Mat getLatestData();
    bool saveModel(const std::string&);

private :
    int algoCode;
    int statusFlag = 0;
    cv::Mat *init_mat ;
    cv::Mat *latest_mat;
};
#endif // SEGIMAGEMODEL_H
