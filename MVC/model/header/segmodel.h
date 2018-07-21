#ifndef SEGIMAGEMODEL_H
#define SEGIMAGEMODEL_H

#include "config.h"

#include "opencv2/highgui/highgui.hpp"

#include <cstring>
#include <deque>

class segModel {

public :
    segModel();
    ~segModel();
    std::string algo_list[IMG_ALGO_N];
    const int algo_list_num  = IMG_ALGO_N;

	bool getStatus();
    bool setupModel(const std::string&);
    bool gsfilter();
    bool gsfilter(double, int);
    cv::Mat getLatestData();
    cv::Mat getInitialData();
    bool saveModel(const std::string&);
    bool undo();

private :
    const int MAX_VIRSION_NUM = MAX_HISTORY_NUM;
    bool loaded  = false;
    int counter;
    std::deque<cv::Mat*> history;
    cv::Mat *init_mat ;

    void destroyMats();
};
#endif // SEGIMAGEMODEL_H
