#include "../model/header/config.h"
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
#include <QPixMap>
#include <QtWidgets/QComboBox>
#include <QScrollArea>
#include <QTranslator>

#define H 1024
#define W 1024
#define MIN_ST_W
#define MIN_ST_H

int main(int argc, char **argv)
{
    // create a application
    QApplication app(argc, argv);

    //demo image file
    QString imagefilepath = "data/1.jpg";

   // create a widget
    QWidget *widget = new QWidget;

    //create a container for simple view
    QLabel *container_before = new QLabel();
    QLabel *container_after = new QLabel();
    QLabel *container_stat = new QLabel();

    //initial picture
    QPixmap *image0 = new QPixmap(2000,2000);
    image0->fill(QColor(0,1,100));

    QSize screenSize(H,W);

    container_before->setScaledContents(false);
    container_before->setMinimumSize(QSize(screenSize.width(), screenSize.height()));
    container_before->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container_before->setFocusPolicy(Qt::StrongFocus);
    QScrollArea *scrollarea1 = new QScrollArea();
    scrollarea1->setBackgroundRole(QPalette::Dark);
    scrollarea1->setWidget(container_before);

    container_after->setScaledContents(false);
    container_after->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    container_after->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container_after->setFocusPolicy(Qt::StrongFocus);
    QScrollArea *scrollarea2 = new QScrollArea();
    scrollarea2->setBackgroundRole(QPalette::Dark);
    scrollarea2->setWidget(container_after);

    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();

    hLayout->addWidget(scrollarea1, 1);
    hLayout->addWidget(scrollarea2, 1);
    hLayout->addLayout(vLayout);

    widget->setWindowTitle(QStringLiteral("Welcome! SegSystem 1.0"));

    // view parts about controller
    //[0] A Combo Box which controls the mode of system
    QComboBox *algomenu = new QComboBox(widget);
    algomenu -> addItem("Gaussian Filter");
    algomenu -> addItem("Image Segmentation") ;
    algomenu -> addItem("Image Info Hiding") ;
    algomenu -> setEditable(false);

    QPushButton *loadButton = new QPushButton(widget);
    loadButton->setText(QStringLiteral("Load Image"));

    QPushButton *processButton = new QPushButton(widget);
    processButton->setText(QStringLiteral("Process Image"));

    QPushButton *saveImageButton = new QPushButton(widget);
    saveImageButton->setText(QStringLiteral("Save Result"));

    //add basic control widget to layout
    vLayout->addWidget(algomenu);
    vLayout->addWidget(loadButton);
    vLayout->addWidget(processButton);
    vLayout->addWidget(saveImageButton);

    container_after->setScaledContents(false);
    container_after->setMinimumSize(QSize(100,100));
    container_after->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container_after->setFocusPolicy(Qt::StrongFocus);
    QScrollArea *stat = new QScrollArea;
    stat->setMinimumHeight(100);
    stat->setMinimumWidth(100);
    vLayout ->addWidget(stat);
    stat->setWidget(container_stat);

    //add controller, and hand QLabel view to controllerf
    SegController *controller = new SegController(widget,container_before,container_after,container_stat);

    //view to controller
    QObject::connect(loadButton, &QPushButton::clicked, controller,
                     &SegController::setTarget);
    QObject::connect(processButton, &QPushButton::clicked, controller,
                     &SegController::process);
    QObject::connect(saveImageButton, &QPushButton::clicked, controller,
                     &SegController::saveModel);
    QComboBox::connect(algomenu , &QComboBox::currentTextChanged,controller,
                     &SegController::setAlgo);

    //init algorithm
    controller->setAlgo(algomenu->currentText());

}
