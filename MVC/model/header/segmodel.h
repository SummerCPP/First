#ifndef SEGIMAGEMODEL_H
#define SEGIMAGEMODEL_H

#include "../model/header/config.h"
#include "opencv2/highgui/highgui.hpp"
#include <cstring>
;
class segModel {

public :
    segModel();
    ~segModel();

    bool setupModel(const string&);
    bool gsfilter();
    bool gsfilter(double, int);
    cv::Mat getLatestData();
    bool saveModel(const std::string&);

private :
    bool loaded  = false;
    cv::Mat *init_mat ;
    cv::Mat *latest_mat;
    static const std::string algo_list[] = IMG_ALGO_LIST;
    static const int algo_list_num  = IMG_ALGO_N;
};
#endif // SEGIMAGEMODEL_H
