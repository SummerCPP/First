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

//the view for this application is simply an image
SegController::SegController(QWidget *parentwidget, QLabel *holder, QLabel *holder_after, QLabel *holder_stat)
{
    this->holder = holder ;
    this->holder_after = holder_after;
    this->holder_stat = holder_stat;
    this->parentWidget = parentwidget;
    this->initModel("E:/test/02.jpg"); //this will create a new model manager
}

bool SegController::initModel(const string &filePath){
    //destroy old model manager
    if(this->modelManager) {
        segManager::destroy(this->modelManager);
    }
    //create a new model manager
    //[1] let model manager initialize itself, according to the mode of system
    if(this->modelManager = segManager::generate(filePath, processMode)){
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
        initModel(dialog.selectedFiles().first().toUtf8().constData());
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
    this->modelManager->updateModel(processMode);
}

void SegController::undo(){
   //[TODO]
}

//process Image under current mode
void SegController::processStageView(){
    while(this->segmodel->processStage()){
        updateView();
    }
}

void SegController::process(){
    this->segmodel->process();
    updateView();
}

void SegController::saveModel()
{
    // debug save model
    QFileDialog dialog(parentWidget, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);
    if(dialog.exec() == QDialog::Accepted){
        this->modelManager->saveModel(dialog.selectedFiles().first());
    }
}


//retrieve more info from data model
void SegController::updateView(){
    if(!this->modelManager){
        showDialog("System Error! System has null model manager");return ;
    }
    const uchar *channel1 = modelManager->latestDataCh1();
    const uchar *channel2 = modelManager->latestDataCh2();
    int len1 = modeManager->lenChannel1();
    int len2 = modeManager->lenChannel2();
    const char *lastestStat = modelManager->lateStatistics();
    if(!channel2){
        showDialog("System Error :: Get Null Lastest Data from model.");
        return ;
    }
    setView(uchar2qt(channel1,len1), uchar2qt(channel2,len2), lastestStat);
}

//transform memory space to qt image
QPixmap SegController::uchar2qt(const uchar* dat, len){
    return QPixmap::loadFromData(data,len);
}

//refresh view, view-model update the view
void SegController::setView(QPixmap *pixmap1, QPixmap *pixmap2){
    this->target =  pixmap2;
    this->holder -> setPixmap(pixmap1->scaled(this->holder->size().width(),this->holder->size().height(),Qt::KeepAspectRatio));
    this->holder_after->setPixmap(pixmap2->scaled(this->holder_after->size().width(),this->holder_after->size().height(),Qt::KeepAspectRatio));
}

//set all view element
void SegController::setView(QPixmap *map1, QPixmap *map2, const char* statistics){
    setView(map1, map2);
    this->holder_stat->setText(statistics);
}

//
void SegController::setView(const QString& segstat){
    this->target =  pixmap;
    this->holder -> setPixmap(pixmap->scaled(this->holder->size().width(),this->holder->size().height(),Qt::KeepAspectRatio));
    this->holder_after->setPixmap(pixmap->scaled(this->holder_after->size().width(),this->holder_after->size().height(),Qt::KeepAspectRatio));
}

//show message dialog in current window
void SegController::showDialog(const QString &message){
    QMessageBox::information(this->parentWidget, QGuiApplication::applicationDisplayName(),
                             tr(message));
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
