#ifndef SEG_CONTROLLER_H
#define SEG_CONTROLLER_H

#include <QLabel>


class SegController : public QObject
{
    Q_OBJECT
public:
    SegController(QWidget *parentWidget,QLabel *holder, QLabel *holder_after, QPixmap *init);
    ~SegController();

    void initilizeDataData();

public Q_SLOTS:
    void setTarget();
    void setAlgo(const QString &t);
    void undo();
    void process();
    void saveImage();

private:
    const int ALGO_GAUSSIAN_FILTER = 1;
    const int ALGO_OTHERS = 2;

    //view part, that is the image itself
    QWidget *parentWidget;
    QLabel *holder;
    QLabel *holder_after;
    QPixmap *target;
    int processMode;

    //model part
    SegModel *modelManager;
    int modelFlag = 0;

    //inner functions
    bool loadFile(const QString &filepath); // load file from file system
    bool saveFile(const QString &filepath);
    void initModel(QPixmap*);
    void updateView();
};
#endif
