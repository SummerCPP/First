//app
#include "segmodel.h"
#include "segViewModel.h"
#include "segparameter.h"
#include "segview.h"
#include "segparameterpanel.h"

#include <QWidget>
#include <QApplication>

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    segModel *m = new segModel ;
    segView *v = new segView;
    SegViewModel *vm = new SegViewModel;

    //
    vm->view=v;
    vm->modelManager = m;

    //连接-命令
    QObject::connect(v->but_load, &QPushButton::clicked, vm, &SegViewModel::loadImage);
    QObject::connect(v->but_save, &QPushButton::clicked, vm, &SegViewModel::saveModel);
    QObject::connect(v->but_undo, &QPushButton::clicked, vm, &SegViewModel::undo);
    QObject::connect(v->but_stage, &QPushButton::clicked, vm, &SegViewModel::stage);
    QObject::connect(v->but_process,&QPushButton::clicked, vm, &SegViewModel::processImage);

    //数据-v-vm
    QObject::connect(v->algomenu, &QComboBox::currentTextChanged, vm, &SegViewModel::algorithmChanged); //
    QObject::connect(vm, &SegViewModel::imgCh1Changed, v, &segView::update_ch1); //
    QObject::connect(vm, &SegViewModel::imgCh2Changed, v, &segView::update_ch2); //
    QObject::connect(vm, &SegViewModel::algorithmListInitilaized, v, &segView::update_combobox); //
    QObject::connect(vm, &SegViewModel::messageChanged, v, &segView::update_message); //

    segParameterPanel *v_pan = v->para;
    QObject::connect(v_pan, &segParameterPanel::parameterChanged, vm, &SegViewModel::algoParameterChanged);
    QObject::connect(vm, &SegViewModel::parameterPanelChanged, v_pan, &segParameterPanel::handle_parameterChange);

    //启动系统
    vm->startup() ;
    v->show();
    v->show();
    app.exec();
}

