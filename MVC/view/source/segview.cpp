#include "../header/segview.h"

SegView::SegView(){
    layout_lv0->setParent(this->widget);
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

    area_origin -> setBackgroundRole(QPalette::Dark);
    area_origin -> setWidget(container_origin);

    area_after->setBackgroundRole(QPalette::Dark);
    area_after->setWidget(container_after);

    area_stat->setBackgroundRole(QPalette::Highlight);
    area_stat->setWidget(container_stat);

    algomenu->setEditable(false);

    layout_control_panel->addWidget(algomenu);
    layout_control_panel->addWidget(but_load);
    layout_control_panel->addWidget(but_process);
    layout_control_panel->addWidget(but_save);

    but_load->setText(QStringLiteral("Load Image"));
    but_process->setText(QStringLiteral("Process Image"));
    but_save->setText(QStringLiteral("Save Result"));

    QObject::connect(but_process, QPushButton::clicked, this, collect_parameter);
}

void SegView::setController(SegController contrller){
    this->controller = controller ;
    //link
    QObject::connect(but_load, &QPushButton::clicked, controller,
                     &SegController::selectTarget);
    QObject::connect(but_process, &QPushButton::clicked, controller,
                     &SegController::processImage);
    QObject::connect(but_save, &QPushButton::clicked, controller,
                     &SegController::saveModel);
    QObject::connect(algomenu, &QComboBox::currentTextChanged,controller,
                     &SegController::setAlgorithm); //and update view
    QObject::connect(this, &SegView::gsfilter,controller,
                     &SegController::algo_gsfilter);
    //connect other image process algorithm
}

void SegView::update_menu(const std::string*menu, int n){
    for(int i=0;i<n;i++){
        this->algomenu->addItem(QString(menu[i]));
    }
}

void SegView::collect_parameter(){
    if(this->algomenu->currentText().compare("Guassian Filter")){
        emit gsfilter(10,5);//[todo]
    }else{
        //collect parameter for other algorithm
    }
}
