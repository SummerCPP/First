#include "../view/header/segview.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char **argv)
{
    // create a application
    QApplication app(argc, argv);
    SegView *v = new SegView;
    SegController *c = new SegControll(v);
    v->setController(c);
    v->show();
    return app.exec();
}
