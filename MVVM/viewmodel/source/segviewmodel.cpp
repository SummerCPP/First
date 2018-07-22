#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>

#include "config.h"


#include "segviewmodel.h"
#include "segview.h"
#include "segmodel.h"

#include <iostream>

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
#include <QScrollArea>

void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);


void SegViewModel::loadImage(){
    QFileDialog dialog(this->view->widget, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    if(dialog.exec() == QDialog::Accepted){
        bool modelset = this->modelManager->setupModel(dialog.selectedFiles().first().toUtf8().constData());
        if(modelset){
            loadData();
        }else{
            emit messageChanged(QString("Can not load image!"));
        }
    }else{
        return;
    }
}

void SegViewModel::undo(){
   if(this->modelManager->undo())
        this->updateView();
}

void SegViewModel::saveModel()
{
    QFileDialog dialog(view->widget, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);
    if(dialog.exec() == QDialog::Accepted){
        bool modelsave = this->modelManager->saveModel(dialog.selectedFiles().first().toUtf8().constData());
        if(modelsave){
            emit messageChanged(QString("Model saved successfully !"));
        }else{
            emit messageChanged(QString("Can not save model"));
        }
    }
}

void SegViewModel::processImage(){
    bool process_status = false;
    if(!this->modelManager->getStatus()){
        setMessage("Please load an image!");
    }

    segParameter_gsfilter *p0;
    segParameter_addnoise *p1;
    segParameter_shift *p2 ;
    segParameter_fixedvignetting *p6;

    switch (this->algorithmMode) {
    case IMG_ALGO_0_GSFILTER:
        p0 = static_cast<segParameter_gsfilter*>(this->parameter);
        process_status = this->modelManager->gsfilter(p0->variance, p0->kernal_size);
        break;
    case IMG_ALGO_1_ADD_NOISE:
        p1 = static_cast<segParameter_addnoise*>(this->parameter);
        process_status = this->modelManager->addnoise(p1->mu, p1->variance, p1->strength);
    case IMG_ALGO_2_SHIFTER:
        p2 = static_cast<segParameter_shift*>(this->parameter);
        process_status = this->modelManager->shift(p2->direction, p2->ofs);
        break;
    case IMG_ALGO_3_COLOR_CHAGE:
        process_status = this->modelManager->colorchange();
        break;
    case IMG_ALGO_4_OLD_IMAGE:
        process_status = this->modelManager->oldimage();
        break;
    case IMG_ALGO_5_OLD_MOVIE:
        process_status = this->modelManager->oldmovieimage();
        break;
    case IMG_ALGO_6_FIXED_VIGNETTING:
        p6 = static_cast<segParameter_fixedvignetting*>(this->parameter);
        process_status = this->modelManager->fixedvignetting(p6->color);
        break;
    case IMG_ALGO_7_FRAGMENT:
        process_status = this->modelManager->fragment();
        break;
    case IMG_ALGO_8_FRAGMENT_LOMO:
        process_status = this->modelManager->fragmentlomo();
        break;
    case IMG_ALGO_9_OLD_PAPER:
        process_status = this->modelManager->oldpaperimage();
        break;
    default:
        break;
    }
    if(process_status){
        setMessage("success!");
        cv::Mat ch2;
        cv::cvtColor(modelManager->getInitialData(), ch2, CV_BGR2RGB);
        QImage *qtimg = new QImage((uchar*) ch2.data, ch2.cols, ch2.rows,  ch2.step, QImage::Format_RGB888);
        setImg2(QPixmap::fromImage(*qtimg));
    }else{
        setMessage(" fails!");
    }
}

void SegViewModel::algoParameterChanged(segParameter *p) {
    this->parameter = p ;
}

void SegViewModel::algorithmChanged(int algocode){
    algorithmMode = algocode;
}

void SegViewModel::loadAlgorithmList(){

    for(int i = 0 ;i< IMG_ALGO_N; i++){
        this->algorithmList[i]=this->modelManager->algo_list[i];
    }
    this->algo_num = this->modelManager->algo_list_num;
    emit this->algorithmListInitilaized(this->algorithmList, this->algo_num)  ;

}

void SegViewModel::setMessage(const char* m){
    this->message = QString(m);
    emit messageChanged(this->message);
}

void SegViewModel::setImg1(QPixmap pix){
    this->imgCh1 = pix;
    emit imgCh1Changed(this->imgCh1);
}

void SegViewModel::setImg2(QPixmap pix){
    this->imgCh2 = pix;
    emit imgCh2Changed(this->imgCh2);
}

void SegViewModel::startup(){
    loadAlgorithmList();
}

void SegViewModel::showDialog(const QString &message){
    QMessageBox::information(this->view->widget, QGuiApplication::applicationDisplayName(), message);
}

void SegViewModel::loadData(){
    cv::Mat ch1 = this->modelManager->getInitialData();
    cv::Mat ch2 = this->modelManager->getLatestData() ;
    setImg1(ch1);
    setImg2(ch2);
}

SegViewModel::~SegViewModel(){}
SegViewModel::SegViewModel(){}
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
