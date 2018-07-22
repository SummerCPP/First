#ifndef SEGVIEW_H
#define SEGVIEW_H

#include "segFeature.h"
#include "segparameter.h"
#include "segparameterpanel.h"

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

#include "segviewmodel.h"
#include "segparameter.h"
#include "segparameterpanel.h"

;

class segView : public QObject {
    Q_OBJECT
public:
    segView();
    ~segView();
    void show();

    QWidget *widget = new QWidget;
    //segFeature * datareport = new segFeature;
    segParameterPanel * para = new segParameterPanel;

    QHBoxLayout * layout_lv0 = new QHBoxLayout;
    QVBoxLayout * layout_control_panel = new QVBoxLayout;
    QHBoxLayout * layout_data = new QHBoxLayout;
    QVBoxLayout * widget_layout = new QVBoxLayout;

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

    SegViewModel *controller;


public Q_SLOTS:

    void comboboxChange();
    void update_ch1(const QPixmap&);
    void update_ch2(const QPixmap&);
    void update_message(const QString&);
    void update_combobox(const std::string*, int);
/*
    void update_datareport(segFeature*);
*/

Q_SIGNALS:
    void algoParameterChanged(segParameter*);
    void algorithmModeChanged(int);
};

#endif // SEGVIEW_H
