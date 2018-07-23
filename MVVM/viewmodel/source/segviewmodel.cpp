#include "config.h"
#include "segviewmodel.h"
#include "segmodel.h"

#include <opencv2/video.hpp>
#include <opencv2/highgui/highgui.hpp>
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
#include "segview.h" // [!conflict] if we move this line up a little bit

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

void SegViewModel::stage(){
    if(this->modelManager->stage()){
        this->updateView();
    }
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
        return ;
    }

    segParameter_gsfilter *p0;
    segParameter_addnoise *p1;
    segParameter_shift    *p2 ;
    segParameter_fixedvignetting *p6;
    segParameter_fragment *p7;

    switch (this->algorithmMode) {
    case IMG_ALGO_0_GSFILTER:
        p0 = static_cast<segParameter_gsfilter*>(this->parameter);
        process_status = this->modelManager->gsfilter(p0->variance, p0->kernal_size);
        break;
    case IMG_ALGO_1_ADD_NOISE:
        p1 = static_cast<segParameter_addnoise*>(this->parameter);
        break;
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
        p7= static_cast<segParameter_fragment*>(this->parameter);
        process_status = this->modelManager->fragment(p7->offset);
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
        cv::cvtColor(modelManager->getLatestData(), ch2, CV_BGR2RGB);
        QImage *qtimg = new QImage((uchar*) ch2.data, ch2.cols, ch2.rows,  ch2.step, QImage::Format_RGB888);
        setImg2(QPixmap::fromImage(*qtimg)); //更新V-M里面的数据
    }else{
        setMessage(" fails!");
    }
}

void SegViewModel::algoParameterChanged(segParameter *p) {
    delete this->parameter;
    this->parameter = p ;
}

void SegViewModel::algorithmChanged(const QString & n){
    std::cout << n.toStdString() << std::endl;
    int code ;
    if(!n.compare(N0_GS_FILTER))
    {
        code = IMG_ALGO_0_GSFILTER;
        this->algorithmMode = IMG_ALGO_0_GSFILTER ;
    }
    else if(!n.compare(N1_ADD_NOISE))
    {
        code = IMG_ALGO_1_ADD_NOISE;
        this->algorithmMode = IMG_ALGO_1_ADD_NOISE ;
    }
    else if(!n.compare(N2_SHIFTER))
    {
        code = IMG_ALGO_2_SHIFTER;
        this->algorithmMode = IMG_ALGO_2_SHIFTER;
    }
    else if(!n.compare(N3_COLOR_CHANGE))
    {
        code = IMG_ALGO_3_COLOR_CHAGE;
        this->algorithmMode = IMG_ALGO_3_COLOR_CHAGE;
    }
    else if(!n.compare(N4_OLD_IMAGE))
    {
        code = IMG_ALGO_4_OLD_IMAGE;
        this->algorithmMode = IMG_ALGO_4_OLD_IMAGE ;
    }
    else if(!n.compare(N5_OLD_MOVIE_FILTER))
    {
        code = IMG_ALGO_5_OLD_MOVIE;
        this->algorithmMode = IMG_ALGO_5_OLD_MOVIE;
    }
    else if(!n.compare(N6_FIXEDVIGNETTING))
    {
        code = IMG_ALGO_6_FIXED_VIGNETTING;
        this->algorithmMode = IMG_ALGO_6_FIXED_VIGNETTING;
    }
    else if(!n.compare(N7_FRAGMENT))
    {
        code = IMG_ALGO_7_FRAGMENT;
        this->algorithmMode = IMG_ALGO_7_FRAGMENT;
    }
    else if(!n.compare(N8_FRAGMEN_MONO))
    {
        code = IMG_ALGO_8_FRAGMENT_LOMO;
        this->algorithmMode = IMG_ALGO_8_FRAGMENT_LOMO ;
    }
    else if(!n.compare(N9_OLDPAPER))
    {
        code = IMG_ALGO_9_OLD_PAPER;
        this->algorithmMode = IMG_ALGO_9_OLD_PAPER;
    }
    else{
        std::cout <<" woops!";
    }

    emit parameterPanelChanged(code);
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

void SegViewModel::loadData(){
    cv::Mat ch1;
    cv::Mat ch2;
    cv::cvtColor(modelManager->getInitialData(), ch1, CV_BGR2RGB);
    cv::cvtColor(modelManager->getLatestData(), ch2, CV_BGR2RGB);

    QImage *qtimg1 = new QImage((uchar*) ch1.data, ch1.cols, ch1.rows,  ch1.step, QImage::Format_RGB888);
    QImage *qtimg2 = new QImage((uchar*) ch2.data, ch2.cols, ch2.rows,  ch2.step, QImage::Format_RGB888);

    setImg1(QPixmap::fromImage(*qtimg1));
    setImg2(QPixmap::fromImage(*qtimg2));
}

SegViewModel::~SegViewModel(){}

SegViewModel::SegViewModel(bool t){

}
void SegViewModel::updateView(){
    loadData();
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
