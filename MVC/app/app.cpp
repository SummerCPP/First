#include "segview.h"
#include "segcontroller.h"

#include <QApplication>
#include <QObject>

int main(int argc, char **argv)
{
    // create a application
    QApplication app(argc, argv);
    segView *v = new segView;
    SegController *c = new SegController;
    v->controller = c;
    c->view = v;

    // v->m
	QObject::connect(v->but_load, &QPushButton::clicked, c,
                     &SegController::selectTarget);
    QObject::connect(v->but_save, &QPushButton::clicked, c,
                     &SegController::saveModel);
    QObject::connect(v->but_undo, &QPushButton::clicked, c,
                     &SegController::undo);
    QObject::connect(v, &segView::gsfilter,c,
                     &SegController::algo_gsfilter);
    //m->v
    QObject::connect(c,&SegController::algorithmListUpdated,v,
                     &segView::update_menu);
    QObject::connect(c,&SegController::processFinished,v,
                     &segView::update_result);
    QObject::connect(c,&SegController::statisticsUpdated,v,
                     &segView::update_statistics);
    QObject::connect(c,&SegController::modelLoaded,v,
                     &segView::update_init_model);
    c->startup();
    v->show();
    app.exec();
}
