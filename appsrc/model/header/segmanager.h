#ifndef SEGMODEL_MANAGER_H
#define SEGMODEL_MANAGER_H
#include "global.h"
#include "opencv2/highgui/highgui.hpp"
#include <cstring>

class segManager{
public:
    static segManager *generate(const std::string &filepath, int algocode);
    static void destroy(segManager*);

    virtual void updateProcessMode(int processMode)=0;
    virtual void process()=0;
    virtual cv::Mat getLatestData()=0;
	virtual bool saveModel(const std::string &filepath)=0;
    segManager();
    ~segManager();
}

#endif // SEGMODEL_MANAGER_H
