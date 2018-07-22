//app 层
#include "segview.h"
#include "segViewModel.h"
#include "segmodel.h"
#include "segparameterpanel.h"
#include "segparameter.h"

#include <QWidget>
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    segView *v = new segView;
    SegViewModel *vm = new SegViewModel;
    segModel *m = new segModel ;

    //绑定
    v->controller=vm;
    vm->view=v;
    vm->modelManager = m;

    //指令
    QObject::connect(v->but_load, &QPushButton::clicked, vm, &SegViewModel::loadImage);
    QObject::connect(v->but_save, &QPushButton::clicked, vm, &SegViewModel::saveModel);
    QObject::connect(v->but_undo, &QPushButton::clicked, vm, &SegViewModel::undo);
    QObject::connect(v->but_process,&QPushButton::clicked, vm, &SegViewModel::processImage);
    QObject::connect(v->algomenu, &QComboBox::currentTextChanged, vm, &SegViewModel::algorithmChanged); //

    QObject::connect(vm, &SegViewModel::imgCh1Changed, v, &segView::update_ch1); //
    QObject::connect(vm, &SegViewModel::imgCh2Changed, v, &segView::update_ch2); //
    QObject::connect(vm, &SegViewModel::algorithmListInitialized, v, &segView::update_combobox); //
    QObject::connect(vm, &SegViewModel::messageChanged, v, &segView::update_message); //

    segParameterPanel *pan = v->para;
    QObject::connect(pan,&segParameterPanel::parameterChanged,vm, &SegViewModel::algorithmChanged);

    //启动系统
    vm->startup() ;
    v->show();
    app.exec();
}

