#include "../model/header/global.h"
#include "SegController.h"
#include "segmodel.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QScreen>
#include <QImageReader>
#include <QImageWriter>
#include <QGuiApplication>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTranslator>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//the view for this application is simply an image
SegController::SegController(QWidget *parentwidget, QLabel *holder, QLabel *holder_after, QLabel *holder_stat)
{
    this->holder = holder ;
    this->holder_after = holder_after;
    this->holder_stat = holder_stat;
    this->parentWidget = parentwidget;
    this->initModel("F:/test/02.jpg"); //this will create a new model manager
}

bool SegController::initModel(const QString&filePath){
    //destroy old model manager
    if(this->modelManager) {
        segManager::destroy(this->modelManager);
    }
    //create a new model manager
    //[1] let model manager initialize itself, according to the mode of system
    if(this->modelManager = segManager::generate(filePath.toUtf8().constData(), processMode)){
       updateView();
       return true;
    }else{
        return false;
    }

}

//change target image
void SegController::setTarget(){
    QFileDialog dialog(this->parentWidget, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    if(dialog.exec() == QDialog::Accepted){
        initModel(dialog.selectedFiles().first());
    }else{
        return ;
    }
}

//set when Combobox is reset
void SegController::setAlgo(const QString &algo){
    if(algo.compare(new QString("GaussianFilter"))){
        processMode = ALGO_GAUSSIAN_FILTER ;
    }else{
        processMode = ALGO_OTHERS ;
    }
    this->modelManager->updateProcessMode(processMode);
}

void SegController::undo(){
   //[TODO]
}

void SegController::process(){
    this->modelManager->process();
    updateView();
}

void SegController::saveModel()
{
    // debug save model
    QFileDialog dialog(parentWidget, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);
    if(dialog.exec() == QDialog::Accepted){
        this->modelManager->saveModel(dialog.selectedFiles().first().toUtf8().constData());
    }
}


//retrieve more info from data model
void SegController::updateView(){
    if(!this->modelManager){
        showDialog("System Error! System has null model manager");return ;
    }
    cv::Mat ch1 = modelManager->getLatestData();
    cv::Mat ch2 = modelManager->getLatestData();
    QString newstat("hello, world!");
    if(ch2.empty()){
        showDialog("System Error :: Get Null Lastest Data from model.");
        return ;
    }
    QImage *qtimg1 = new QImage((uchar*) ch1.data, ch1.cols, ch1.rows,  ch1.step, QImage::Format_RGB888);
    QImage *qtimg2 = new QImage((uchar*) ch2.data, ch2.cols, ch2.rows,  ch2.step, QImage::Format_RGB888);

    setView(QPixmap::fromImage(*qtimg1),QPixmap::fromImage(*qtimg2),newstat);
}

//refresh view, view-model update the view
void SegController::setView(QPixmap pixmap1, QPixmap pixmap2){
    this->holder -> setPixmap(pixmap1.scaled(this->holder->size().width(),this->holder->size().height(),Qt::KeepAspectRatio));
    this->holder_after->setPixmap(pixmap2.scaled(this->holder_after->size().width(),this->holder_after->size().height(),Qt::KeepAspectRatio));
}

//set all view element
void SegController::setView(QPixmap  map1, QPixmap map2, const QString &stat){
    setView(map1, map2);
    this->holder_stat->setText(stat);
}

//
void SegController::setView(const QString& segstat){
    this->holder_stat->setText(segstat);
}

//show message dialog in current window
void SegController::showDialog(const QString &message){
    QMessageBox::information(this->parentWidget, QGuiApplication::applicationDisplayName(), message);
}

//initialize File dialog
static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

//destructor of controller
SegController::~SegController(){}
