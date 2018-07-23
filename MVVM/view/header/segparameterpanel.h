//算法参数输入面板的代码
#ifndef SEGPARAMETERPANEL_H
#define SEGPARAMETERPANEL_H

#include "config.h"
#include "segparameter.h"

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QVBoxLayout>

;
class segParameterPanel : public QWidget{
    Q_OBJECT
public :
    QHBoxLayout * layout        = new QHBoxLayout;
    QWidget * panel_gsfilter    = new QWidget;
    QWidget * panel_shift       = new QWidget;
    QWidget * panel_addnoise    = new QWidget;
    QWidget * panel_fragment    = new QWidget;
    QWidget * panel_fixedvignetting = new QWidget;

    segParameterPanel();
    ~segParameterPanel();


public slots:
    //内部控制，参数采集
    void modeChanged(int);
    void handle_parameterChange(int);
    void reportGsfilter();
    void reportAddnoise();
    void reportFragment();
    void reportFixedVignetting();
    void reportShift();

    //参数输出
Q_SIGNALS:
    void parameterChanged(struct segParameter*);


private:
    int mode ;
    void setAllVisible(bool);
    void setup_gsfilter();
    void setup_shift();
    void setup_addnoise();
    void setup_fixedvignetting();
    void setup_fragment();
};

#endif
