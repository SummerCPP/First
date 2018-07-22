#ifndef SEG_CONTROLLER_H
#define SEG_CONTROLLER_H

#include "config.h"
#include "segFeature.h"
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

    SegViewModel();
    ~SegViewModel();
    void startup();

public Q_SLOTS:
    void loadImage();
    void undo();
    void saveModel();

    void processImage();

    void algoParameterChanged(segParameter*);
    void algorithmChanged(int);

Q_SIGNALS:
    void imgCh1Changed(const QPixmap&);
    void imgCh2Changed(const QPixmap&);
    void algorithmListInitilaized(const std::string*,int);
    void datareportUpdated(const segFeature);
    void messageChanged(QString);

private:
    int counter = 0 ;
    QPixmap imgCh1;
    QPixmap imgCh2;
    int algorithmMode = IMG_ALGO_0_GSFILTER;
    std::string algorithmList[IMG_ALGO_N];
    int algo_num;
    segParameter *parameter;
    QString message;

    void showDialog(const QString &message);
    void updateView();

    //void adjustDataReport(); //[todo]
    void setMessage(const char*m);
    void setImg2(QPixmap );
    void setImg1(QPixmap );

    void loadAlgorithmList();
    void loadData();
};

#endif
