#include "segview.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char **argv)
{
    // create a application
    QApplication app(argc, argv);
    segView *v = new segView;
    v->show();
    app.exec();
}
