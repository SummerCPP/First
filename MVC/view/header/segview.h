#ifndef SEGVIEW_H
#define SEGVIEW_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
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
#define MIN_ST_W 400
#define MIN_ST_H 400

class SegController;
class segView : public QObject {
    Q_OBJECT
public:
    segView();
    ~segView();
    void show();
    QWidget *widget = new QWidget;
    QHBoxLayout * layout_lv0 = new QHBoxLayout;
    QVBoxLayout * layout_control_panel = new QVBoxLayout;

    QLabel *container_origin = new QLabel;
    QLabel *container_after = new QLabel;
    QLabel *container_stat = new QLabel;

    QScrollArea *area_stat = new QScrollArea ;
    QScrollArea *area_origin = new QScrollArea;
    QScrollArea *area_after = new QScrollArea;

    QComboBox   *algomenu = new QComboBox;
    QPushButton *but_process = new QPushButton;
    QPushButton *but_save = new QPushButton;
    QPushButton *but_load = new QPushButton;
    QPushButton *but_undo = new QPushButton;

    SegController *controller;

public Q_SLOTS:
    void collect_parameter();
    void update_statistics(const QString&);
    void update_origin(const QPixmap&);
    void update_result(const QPixmap&);
    void update_menu(const std::string*, int);
    void update_init_model(const QPixmap&, const QPixmap&, const QString&);

signals:
    void gsfilter(double, int);

};

#endif // SEGVIEW_H
