#ifndef SEG_CONTROLLER_H
#define SEG_CONTROLLER_H

#include "config.h"
// #include "segFeature.h"
#include "segparameter.h"

#include <QObject>
#include <QPixmap>

class segView ;
class segModel;

class QLabel ;
class QFileDialog;
class QScrollArea;


class SegViewModel : public QObject
{
    Q_OBJECT
public:
    segModel * modelManager;
    segView  * view ;
    SegViewModel(bool t= true);
    ~SegViewModel();
    void startup();

public Q_SLOTS:
    void loadImage();
    void undo();
    void stage();
    void saveModel();

    void processImage();

    void algoParameterChanged(segParameter*);
    void algorithmChanged(const QString&);

Q_SIGNALS:
    void imgCh1Changed(const QPixmap&);
    void imgCh2Changed(const QPixmap&);
    void algorithmListInitilaized(const std::string*,int);
    // void datareportUpdated(const segFeature); // [todo]
    void messageChanged(QString);
    void parameterPanelChanged(int);

private:
    int counter = 0 ;
    QPixmap imgCh1;
    QPixmap imgCh2;
    int algorithmMode = IMG_ALGO_0_GSFILTER;
    segParameter *parameter = new segParameter_gsfilter(10,1.5,IMG_ALGO_0_GSFILTER); //default to gsfilter
    std::string algorithmList[IMG_ALGO_N];
    int algo_num;
    QString message;

    void updateView();

    //void adjustDataReport(); //[todo]
    //void adjustStatisticsFeature(); //[todo]
    void setMessage(const char*m);
    void setImg2(QPixmap );
    void setImg1(QPixmap );

    void loadAlgorithmList();
    void loadData();
};

#endif
