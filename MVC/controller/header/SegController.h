#ifndef SEG_CONTROLLER_H
#define SEG_CONTROLLER_H

#include <QObject>
#include <QLabel>
#include <QFileDialog>
#include <QObject>
#include <QScrollArea>

class segView ;
class segModel;
class SegController : public QObject
{
    Q_OBJECT
public:
    segModel *modelManager;
    segView * view ;

    SegController();
    ~SegController();
    void startup();

public Q_SLOTS:
    void selectTarget();
    void undo();
    void saveModel();
    void algo_gsfilter(double,int);
    void algo_others(double);

signals:
    void processFinished(const QPixmap&) ; // [todo]
    void algorithmListUpdated(const std::string*,int);
    void statisticsUpdated(const QString&);
    void modelLoaded(const QPixmap&, const QPixmap&, const QString&);

private:

    void updateView();
    void initModelView();
    void showDialog(const QString &message);

};

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);

#endif
