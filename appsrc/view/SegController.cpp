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

//the view for this application is simply an image
SegController::SegController(QWidget *parentwidget, QLabel *holder, QLabel *holder_after, QPixmap*init)
{
    this->holder = holder ;
    this->holder_after = holder_after;
    this->parentWidget = parentwidget;
    this->initModel(init); //this will create a new model manager
}

//load image from file system
/*bool SegController::loadFile(const QString &fileName)
{
    QPixmap *pixmap = new QPixmap(fileName);
    if(pixmap->isNull()){
        QMessageBox::information(this->parentWidget, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1")
                                 .arg(QDir::toNativeSeparators(fileName)));
        return false;
    }
    initModel(pixmap);
    return true;
}*/

void SegController::initModel(const QString &filePath){
    //destroy old model manager
    if(this->modelManager) {
        delete this->modelManager ;
    }
    //create a new model manager
    //[1] let model manager initialize itself, according to the mode of system
    this->modelFlag = new segManager;
    this->modelManager->initModel(filePath, this->processMode);
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

void SegController::saveImage()
{
    printf("===================");
    QFileDialog dialog(parentWidget, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);
    if(dialog.exec() == QDialog::Accepted){
        saveFile(dialog.selectedFiles().first());
    }
}

bool SegController::saveFile(const QString &fileName)
{
    showDialog(fileName);
    QPixmap pixmap;
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
}

SegController::~SegController(){}

//refresh view, view-model update the view
void SegController::updateView(QPixmap *pixmap1)
    this->target =  pixmap;
    this->holder -> setPixmap(pixmap->scaled(this->holder->size().width(),this->holder->size().height(),Qt::KeepAspectRatio));
    this->holder_after->setPixmap(pixmap->scaled(this->holder_after->size().width(),this->holder_after->size().height(),Qt::KeepAspectRatio));

}

//refresh view, view-model update the view
void SegController::updateView(QPixmap *pixmap1, QPixmap *pixmap2){
    //
}

//retrieve more info from data model
void SegController::updateView(){
    if(!this->modelManager){
        showDialog("System Error! System has null");return ;
    }
    const uchar* lastestdata = modeManager->latest();
    int len = modeManager -> latestDataLen();
    if(!lastestdata)
        showDialog("System Error :: Get Null Lastest Data from model.");
        return ;
    }
    updateView(uchar2qt(lastestdata));
}

//transform memory space to qt image
QPixmap SegController::uchar2qt(const uchar* dat, len){
    return QPixmap::loadFromData(data,len);
}

//show message dialog in current window
void SegController::showDialog(const QString &message){
    QMessageBox::information(this->parentWidget, QGuiApplication::applicationDisplayName(),
                             tr(message));
}
