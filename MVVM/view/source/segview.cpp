#include "segview.h"
#include "segparameter.h"
#include "config.h"

#include <iostream>
#include <QSize>

segView::segView(){
    widget->setLayout(widget_layout);
    widget_layout ->addLayout(layout_lv0);
    widget_layout ->addLayout(layout_data);

    //layout_data->addWidget(datareport);
    layout_lv0 ->addWidget(area_origin, 2);
    layout_lv0 ->addWidget(area_after, 2);
    layout_lv0 ->addLayout(layout_control_panel,1);

    container_origin->setScaledContents(false);
    container_origin->setMinimumSize(QSize(MIN_ST_W, MIN_ST_H));
    container_origin->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    container_origin->setFocusPolicy(Qt::StrongFocus);

    container_after->setScaledContents(false);
    container_after->setMinimumSize(QSize(MIN_ST_W, MIN_ST_H));
    container_after->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    container_after->setFocusPolicy(Qt::StrongFocus);

    container_stat->setScaledContents(true);
    container_stat->setMinimumSize(QSize(MIN_ST_W, MIN_ST_H));

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
    layout_control_panel->addWidget(but_stage);
    layout_control_panel->addWidget(but_save);
    layout_control_panel->addWidget(para);
    layout_control_panel->addWidget(area_stat);

    but_load->setText(QStringLiteral("Load"));
    but_process->setText(QStringLiteral("Process"));
    but_save->setText(QStringLiteral("Save"));
    but_undo->setText(QStringLiteral("Undo"));
    but_stage->setText(QStringLiteral("Stage"));
}

void segView::update_combobox(const std::string*menu, int n){
    for(int i=0;i<n;i++){
        std::cout << menu[i].data() << std::endl ;
        this->algomenu->addItem(QString(menu[i].data()));
    }
}

void segView::update_message(const QString &stat){
    this->container_stat -> setText(stat);
    this->container_stat -> setAlignment(Qt::AlignHCenter);
}

void segView::update_ch1(const QPixmap& pix){
    this->container_origin->setFixedSize(pix.size());;
    this->container_origin->setPixmap(pix);
    this->container_origin->setPixmap(pix.scaled(pix.width(),pix.height(),Qt::KeepAspectRatio));
}

void segView::update_ch2(const QPixmap& pix){
    this->container_after->setFixedSize(pix.size());
    this->container_after->setPixmap(pix);
    this->container_after->setPixmap(pix.scaled(pix.width(),pix.height(),Qt::KeepAspectRatio));
}

void segView::comboboxChange(){
    emit segView::algorithmModeChanged(this->algomenu->currentIndex());
}

void segView::show(){
    this->widget->showFullScreen();
}
segView::~segView(){
    delete this->but_load;
    delete this->but_process;
    delete this->but_save;
    delete this->but_undo;
    delete this->but_stage;
}
