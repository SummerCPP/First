#include "SegController.h"
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
    this->parentWidget = parentwidget;
    this->holder_after = holder_after;
    this->initModel(init);

}

//load image from file system
bool SegController::loadFile(const QString &fileName)
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
}

void SegController::initModel(QPixmap *pixmap){
    this->target =  pixmap ;
    this->holder -> setPixmap(pixmap->scaled(this->holder->size().width(),this->holder->size().height(),Qt::KeepAspectRatio));
    this->holder_after->setPixmap(pixmap->scaled(this->holder_after->size().width(),this->holder_after->size().height(),Qt::KeepAspectRatio));
}

//change target image
void SegController::setTarget(){
    QFileDialog dialog(this->parentWidget, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    if(dialog.exec() == QDialog::Accepted){
        loadFile(dialog.selectedFiles().first());
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
}

void SegController::undo(){
   //[TODO]
}

//process Image under current mode
void SegController::process(){
    //while(this->segmodel->process()){
    //    updateView();
    //}
}

void SegController::saveImage()
{
    printf("===================");
    QFileDialog dialog(parentWidget, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);
    if(dialog.exec() == QDialog::Accepted){
        /*while(true){
            if(saveFile(dialog.selectedFiles().first())) break;
            else{
                printf("something wrong!");
            }
        }*/
        saveFile(dialog.selectedFiles().first());
    }
}

bool SegController::saveFile(const QString &fileName)
{
    printf("123");
    QImageWriter writer(fileName);
    QImage image = target->toImage() ;
    return true;
    if (!writer.write(image)) {
        QMessageBox::information(this->parentWidget, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());    
        printf("123");
        return false;
    }
    return true;
}

SegController::~SegController(){
    //
}

//refresh view, view-model update the view
void SegController::updateView(){
    //
}
