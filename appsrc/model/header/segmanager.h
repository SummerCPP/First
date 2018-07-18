#ifndef SEGMODEL_MANAGER_H
#define SEGMODEL_MANAGER_H
#include "global.h"

class segManager{

public:
    static segManager *generate(const string &filepath, int algocode);
    void updateProcessMode(int processMode);
    void process();
    void processStage();
    int  lastestDataLen();
    char* lastestData();
    bool saveModel();
private:
    segManager();
    ~segManager();
}

#endif // SEGMODEL_MANAGER_H
