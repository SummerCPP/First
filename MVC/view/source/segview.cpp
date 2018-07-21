#include "segview.h"
#include "config.h"

#include <iostream>

segView::segView(){
    widget->setLayout(layout_lv0);
    layout_lv0->addWidget(area_origin);
    layout_lv0->addWidget(area_after);
    layout_lv0->addLayout(layout_control_panel);

    container_origin->setScaledContents(false);
    container_origin->setMinimumSize(QSize(MIN_ST_W, MIN_ST_H));
    container_origin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container_origin->setFocusPolicy(Qt::StrongFocus);

    container_after->setScaledContents(false);
    container_after->setMinimumSize(QSize(MIN_ST_W, MIN_ST_H));
    container_after->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container_after->setFocusPolicy(Qt::StrongFocus);

    container_stat->setScaledContents(false);
    container_stat->setMinimumSize(QSize(MIN_ST_W/3, MIN_ST_H/3));
    container_stat->setMaximumSize(QSize(MIN_ST_W/3, MIN_ST_H/3));

    container_stat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container_stat->setFocusPolicy(Qt::StrongFocus);

    area_origin -> setBackgroundRole(QPalette::Mid);
    area_origin -> setWidget(container_origin);

    area_after->setBackgroundRole(QPalette::Dark);
    area_after->setWidget(container_after);

    area_stat->setBackgroundRole(QPalette::Mid);
    area_stat->setWidget(container_stat);

    algomenu->setEditable(false);

    layout_control_panel->addWidget(algomenu);
    layout_control_panel->addWidget(but_load);
    layout_control_panel->addWidget(but_process);
    layout_control_panel->addWidget(but_undo);
    layout_control_panel->addWidget(but_save);

    layout_control_panel->addWidget(area_stat);

    but_load->setText(QStringLiteral("Load Image"));
    but_process->setText(QStringLiteral("Process Image"));
    but_save->setText(QStringLiteral("Save Result"));
    but_undo->setText(QStringLiteral("Undo"));

    QObject::connect(but_process, &QPushButton::clicked, this, &segView::collect_parameter);
}

void segView::update_menu(const std::string*menu, int n){
    for(int i=0;i<n;i++){
        this->algomenu->addItem(QString(menu[i].data()));
    }
}

void segView::collect_parameter(){
    std::cout <<"Collectin parameter from view! \n" ;
    if(!this->algomenu->currentText().compare(GS_FILTER)){
        emit gsfilter(5,5);//[todo]
    }else{
        std::cout << GS_FILTER << std::endl;
        std::cout << this->algomenu->currentText().toStdString() << std::endl;
        emit gsfilter(10,5);
    }
}

void segView::update_statistics(const QString& stat){
    this->container_stat -> setText(stat);
}

void segView::update_origin(const QPixmap& pix){
    this->container_origin->setFixedSize(pix.size());;
    this->container_origin->setPixmap(pix);
    //this->container_origin->setPixmap(pix.scaled(pix.width(),pix.height(),Qt::KeepAspectRatio));
}
void segView::update_result(const QPixmap& pix){
    this->container_after->setFixedSize(pix.size());;
    this->container_after->setPixmap(pix);
}
void segView::update_init_model(const QPixmap& pix0, const QPixmap& pix1, const QString& stat){
    this->container_origin->setFixedSize(pix0.size());;
    this->container_origin->setPixmap(pix0);

    this->container_after->setFixedSize(pix1.size());;
    this->container_after->setPixmap(pix1);

    //this->container_origin->setPixmap(pix0.scaled(container_origin->width(),container_origin->height(),Qt::KeepAspectRatio));
    //this->container_after->setPixmap(pix1.scaled(container_after->width(),container_after->height(),Qt::KeepAspectRatio));
    this->container_stat->setText(stat);
}
void segView::show(){
    this->widget->showFullScreen();
}

segView::~segView(){}
