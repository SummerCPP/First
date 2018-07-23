#ifndef SEGIMAGEMODEL_H
#define SEGIMAGEMODEL_H

#include "config.h"

#include <cstring>
#include <deque>

#include "opencv2/highgui/highgui.hpp"

class segModel {

public :
    segModel();
    ~segModel();
    std::string algo_list[IMG_ALGO_N];
    const int algo_list_num  = IMG_ALGO_N;

	bool getStatus();
    bool setupModel(const std::string&);
    cv::Mat getLatestData();
    cv::Mat getInitialData();
    bool saveModel(const std::string&);
    bool undo();
    void updateHistory(cv::Mat&);

    //功能
    bool gsfilter();
    bool gsfilter(double,int);
    bool addnoise(double, double, int);
    bool shift(int, int);
    bool colorchange();
    bool oldimage();
    bool oldmovieimage();
    bool fixedvignetting(int );
    bool fragment();
    bool fragmentlomo();
    bool oldpaperimage();

private :
    //模型数据
    const int MAX_VIRSION_NUM = MAX_HISTORY_NUM;
    bool loaded  = false;
    int  counter = 0 ;
    std::deque<cv::Mat*> history;
    cv::Mat *init_mat ;

    void destroyMats();
};

#endif // SEGIMAGEMODEL_H
