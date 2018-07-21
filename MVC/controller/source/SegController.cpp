#include "segcontroller.h"
#include "config.h"
#include "segmodel.h"
#include "segview.h"
#include "iostream"

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

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>

SegController::SegController(){
    this->modelManager = new segModel;
}
void SegController::undo(){
   if(this->modelManager->undo()) this->updateView();
}
void SegController::saveModel()
{
    QFileDialog dialog(view->widget, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);
    if(dialog.exec() == QDialog::Accepted){
        bool modelsave = this->modelManager->saveModel(dialog.selectedFiles().first().toUtf8().constData());
        if(modelsave){
            emit statisticsUpdated(QString("Model saved successfully !"));
        }else{
            emit statisticsUpdated(QString("Can not save model"));
        }
    }
}

void SegController::initModelView(){
    cv::Mat ch1;
    cv::Mat ch2;

    cv::cvtColor(modelManager->getLatestData(), ch1, CV_BGR2RGB);
    cv::cvtColor(modelManager->getLatestData(), ch2, CV_BGR2RGB);

    const QString newstat("Modify and Observe it !");
    QImage *qtimg1 = new QImage((uchar*) ch1.data, ch1.cols, ch1.rows,  ch1.step, QImage::Format_RGB888);
    QImage *qtimg2 = new QImage((uchar*) ch2.data, ch2.cols, ch2.rows,  ch2.step, QImage::Format_RGB888);
    emit modelLoaded(QPixmap::fromImage(*qtimg1), QPixmap::fromImage(*qtimg2), newstat);
}

void SegController::updateView(){
/*    std::cout <<"updated" << std::endl;
    cv::Mat ch2;;
    cv::cvtColor(modelManager->getLatestData(), ch2, CV_BGR2RGB);
    QImage *qtimg2 = new QImage((uchar*) ch2.data, ch2.cols, ch2.rows,  ch2.step, QImage::Format_RGB888);
    emit this->processFinished(QPixmap::fromImage(*qtimg2));
*/
    cv::Mat ch1;
    cv::Mat ch2;

    cv::cvtColor(modelManager->getInitialData(), ch1, CV_BGR2RGB);
    cv::cvtColor(modelManager->getLatestData(), ch2, CV_BGR2RGB);

    const QString newstat("Modify and Observe it !");
    QImage *qtimg1 = new QImage((uchar*) ch1.data, ch1.cols, ch1.rows,  ch1.step, QImage::Format_RGB888);
    QImage *qtimg2 = new QImage((uchar*) ch2.data, ch2.cols, ch2.rows,  ch2.step, QImage::Format_RGB888);
    emit modelLoaded(QPixmap::fromImage(*qtimg1), QPixmap::fromImage(*qtimg2), newstat);

}

void SegController::showDialog(const QString &message){
    QMessageBox::information(this->view->widget, QGuiApplication::applicationDisplayName(), message);
}

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
    QFileDialog dialog(this->view->widget, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    if(dialog.exec() == QDialog::Accepted){
        bool modelset = this->modelManager->setupModel(dialog.selectedFiles().first().toUtf8().constData());
        if(modelset){
            initModelView();
            emit statisticsUpdated(QString("Model Loaded !"));
        }else{
            emit statisticsUpdated(QString("Can not load image!"));
        }
    }else{
        return;
    }
}

void SegController::algo_gsfilter(double delta,int window_size){
    if(modelManager->gsfilter(delta,window_size)){
        emit statisticsUpdated(QString("Gs Filter Applied Successfully"));
        updateView();
    }else{
        emit statisticsUpdated(QString("Can not apply Gs Filter somehow"));
    }
}
void SegController::algo_others(double some_parameter){
    //[TODO]
}
void SegController::startup(){
    this->modelManager = new segModel;
    emit this->algorithmListUpdated(this->modelManager->algo_list, this->modelManager->algo_list_num);
}
//destructor of controller
SegController::~SegController(){}
