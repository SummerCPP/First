#ifndef SEG_CONTROLLER_H
#define SEG_CONTROLLER_H

#include <QLabel>
#include <QFileDialog>
#include <QObject>
#include <QScrollArea>

#include "../model/header/segmodel.h"
#include "../view/header/segview.h"

class SegController : public QObject
{
    Q_OBJECT
public:
    SegController(SegView*);
    ~SegController();

public Q_SLOTS:
    void selectTarget();
    void undo();
    void processImage();
    void saveModel();
    void algo_gsfilter(double,int);

signals:
    void processFinished(const QPixmap&) ; // [todo]
    void algorithmListUpdated(const string*,int);
    void statisticsUpdated(const QString&);
    void modelLoaded(const QPixmap&, const QPixelmap&, const QString&);

private:
    //view
    SegView *view;

    //model
    segModel *modelManager;

    //inner functions
    bool loadFile(const QString &filepath); // load file from file system
    bool saveFile(const QString &filepath);
    bool initModel(const QString &);
    void updateView();

    void setView(const QString& );
    void setView(QPixmap pixmap1, QPixmap pixmap2);
    void setView(QPixmap pixmap1, QPixmap pixmap2, const QString& stat);
    void showDialog(const QString &message);

};

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);

#endif
