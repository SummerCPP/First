#include "../model/header/config.h"
#include "../header/SegController.h"
#include "../../view/header/segview.h"
#include "../../model/header/segmodel.h"

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
// opencv support
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

SegController::SegController(SegView *view){
    this->view = view;
    QObject::connect(this,algorithmListChanged,view,update_menu);
    QObject::connect(this,processFinished,view,view->update_result);
    QObject::connect(this,statisticsUpdated,view,view->update_statistics);
    QObject::connect(this,modelLoaded,view,view->update_init_model);
    this->model = new segModel;
    emit this->algorithmListUpdated(segModel::algo_list, segModel::algo_list_num);
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

//
void SegController::setAlgorithm(const QString &algo){
    if(algo.compare())
}

void SegController::undo(){
   //[TODO]
}

void SegController::processImage(){
    this->modelManager->process();
    updateView();
}

void SegController::saveModel()
{
    QFileDialog dialog(parentWidget, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);
    if(dialog.exec() == QDialog::Accepted){
        bool modelsave = this->modelManager->saveModel(dialog.selectedFiles().first().toUtf8().constData());
        if(modelsave){
            emit statisticsUpdated(QString("成功！"));
        }else{
            emit statisticsUpdated(QString("无法保存处理对象"));
        }
    }
}

//retrieve more info from data model
void SegController::updateView(){
    cv::Mat ch1 = modelManager->getLatestData();
    cv::Mat ch2 = modelManager->getLatestData();
    const QString newstat("hello, world!");
    QImage *qtimg1 = new QImage((uchar*) ch1.data, ch1.cols, ch1.rows,  ch1.step, QImage::Format_RGB888);
    QImage *qtimg2 = new QImage((uchar*) ch2.data, ch2.cols, ch2.rows,  ch2.step, QImage::Format_RGB888);
    emit modelLoaded(QPixmap::fromImage(*qtimg1), QPixmap::fromImage(*qtimg2), newstat);
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

//select file
void SegController::selectTarget(){
    QFileDialog dialog(this->parentWidget, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    if(dialog.exec() == QDialog::Accepted){
        bool modelset = this->modelManager->setupModel(dialog.selectedFiles().first().toUtf8().constData());
        if(modelset){
            updateView();
        }else{
            emit statisticsUpdated(QString("无法加载图像!"));
        }
    }else{
        return;
    }

}

//destructor of controller
SegController::~SegController(){}
