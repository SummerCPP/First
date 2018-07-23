#include "config.h"
#include "segparameterpanel.h"

#include <iostream>

void segParameterPanel::handle_parameterChange(int i){
    std::cout << " i is : " << i << " \n ";
    if(i != this->mode) {
        setAllVisible(false);
        if(i == IMG_ALGO_0_GSFILTER) {
            this->panel_gsfilter->setVisible(true);
        } else if( i == IMG_ALGO_1_ADD_NOISE) {
            this->panel_addnoise->setVisible(true);
        }  else if( i == IMG_ALGO_2_SHIFTER) {
            this->panel_shift->setVisible(true);
        }  else if( i == IMG_ALGO_3_COLOR_CHAGE) {
            ;
        }  else if( i == IMG_ALGO_4_OLD_IMAGE) {
            ;
        }  else if( i == IMG_ALGO_5_OLD_MOVIE) {
            ;
        }  else if( i == IMG_ALGO_6_FIXED_VIGNETTING) {
            this->panel_fixedvignetting->setVisible(true);
        }  else if( i == IMG_ALGO_7_FRAGMENT) {
            this->panel_fragment->setVisible(true);
        }  else if( i == IMG_ALGO_8_FRAGMENT_LOMO) {
            ;
        }  else if( i == IMG_ALGO_9_OLD_PAPER) {
            ;
        }
    }
    this->mode = i ;
}

void segParameterPanel::modeChanged(int mode){
    this->setAllVisible(false);
    handle_parameterChange(mode);
}

segParameterPanel::segParameterPanel(){
    this->setLayout(layout);

    layout->addWidget(this->panel_addnoise);
    layout->addWidget(this->panel_fixedvignetting);
    layout->addWidget(this->panel_fragment);
    layout->addWidget(this->panel_gsfilter);
    layout->addWidget(this->panel_shift);

    setup_addnoise();
    setup_fixedvignetting();
    setup_gsfilter();
    setup_shift();
    setup_fragment();

    this->setVisible(true);
    this->setAllVisible(false);
    this->panel_addnoise->setVisible(true);
}

void segParameterPanel::setAllVisible(bool t) {
    this->panel_addnoise->setVisible(t);
    this->panel_fixedvignetting->setVisible(t);
    this->panel_fragment->setVisible(t);
    this->panel_gsfilter->setVisible(t);
    this->panel_shift->setVisible(t);
}

void segParameterPanel::setup_addnoise(){
    QVBoxLayout * l = new QVBoxLayout;
    QSpinBox    * s_strength = new QSpinBox();
    QLabel      * n_strength = new QLabel("Noise Strength : ");
    QDoubleSpinBox * s_mu = new QDoubleSpinBox();
    QLabel      * n_mu = new QLabel("Mean : ");
    QDoubleSpinBox * s_var = new QDoubleSpinBox();
    QLabel         * n_var = new QLabel("Variance of Noise: ");
    s_mu->setAccessibleName("S_MU");
    s_var->setAccessibleName("S_VAR");
    panel_addnoise->setLayout(l);
    s_strength->setRange(0,100);
    s_mu->setRange(-10,10);
    s_var->setRange(0,100);

    l->addWidget(n_mu);
    l->addWidget(s_mu);
    l->addWidget(n_strength);
    l->addWidget(s_strength);
    l->addWidget(n_var);
    l->addWidget(s_var);

    QObject::connect(s_strength, &QSpinBox::editingFinished, this, &segParameterPanel::reportAddnoise);
    QObject::connect(s_mu, &QSpinBox::editingFinished, this, &segParameterPanel::reportAddnoise);
    QObject::connect(s_var, &QSpinBox::editingFinished, this, &segParameterPanel::reportAddnoise);
}

void segParameterPanel::setup_fixedvignetting(){
    QVBoxLayout * l = new QVBoxLayout;
    QSpinBox * s_color = (new QSpinBox());
    QLabel *   n_color= new QLabel("Color : ");

    s_color->setAccessibleName("S_COLOR");
    panel_fixedvignetting->setLayout(l);
    s_color->setRange(0,1);
    l->addWidget(n_color);
    l->addWidget(s_color);
    QObject::connect(s_color, &QSpinBox::editingFinished, this, &segParameterPanel::reportFixedVignetting);

}
void segParameterPanel::setup_fragment(){
    QVBoxLayout * l = new QVBoxLayout;
    QSpinBox    * s_offset = (new QSpinBox());
    QLabel      * n_offset= new QLabel("Offset : ");
    s_offset->setAccessibleName("S_OFFSET");

    panel_fragment->setLayout(l);
    s_offset->setRange(-100,100);
    l->addWidget(n_offset);
    l->addWidget(s_offset);
    QObject::connect(s_offset, &QSpinBox::editingFinished, this, &segParameterPanel::reportFragment);
}

void segParameterPanel::setup_gsfilter(){
    QVBoxLayout * l = new QVBoxLayout;
    QSpinBox    * s_size = new QSpinBox();
    QLabel      * n_size= new QLabel("Kernel Size : ");
    QDoubleSpinBox * s_delta = (new QDoubleSpinBox());
    QLabel      * n_delta= new QLabel("Delta : ");

    s_size->setRange(1,100);
    panel_gsfilter->setLayout(l);
    s_delta->setRange(0.0001,1000);

    l->addWidget(n_size);
    l->addWidget(s_size);
    l->addWidget(n_delta);
    l->addWidget(s_delta);

    QObject::connect(s_size, &QSpinBox::editingFinished, this, &segParameterPanel::reportGsfilter);
    QObject::connect(s_delta, &QDoubleSpinBox::editingFinished, this, &segParameterPanel::reportGsfilter);
}

void segParameterPanel::setup_shift(){
    QVBoxLayout * l = new QVBoxLayout;
    QSpinBox    * s_direction = (new QSpinBox());
    QLabel      * n_direction= new QLabel("Direction : ");

    QSpinBox    * s_step = (new QSpinBox());
    QLabel      * n_step= new QLabel("Step Size : ");

    s_direction->setRange(1,4);
    s_direction->setAccessibleName("S_DIRECTION");
    s_step->setRange(0,100);

    panel_shift->setLayout(l);

    l->addWidget(n_direction);
    l->addWidget(s_direction);

    l->addWidget(n_step);
    l->addWidget(s_step);

    QObject::connect(s_direction, &QSpinBox::editingFinished, this, &segParameterPanel::reportShift);
    QObject::connect(s_step, &QSpinBox::editingFinished, this, &segParameterPanel::reportShift);
}

void segParameterPanel::reportGsfilter(){
    std::cout << "$$$$$$$$$$$$$$$$$report gs filter pra \n " ;
    QSpinBox* size =  dynamic_cast<QSpinBox*>(panel_gsfilter->layout()->itemAt(1)->widget());
    QDoubleSpinBox* delta = dynamic_cast<QDoubleSpinBox*>(panel_gsfilter->layout()->itemAt(3)->widget());
    emit parameterChanged(new segParameter_gsfilter(delta->value(),size->value(),IMG_ALGO_0_GSFILTER));
}

void segParameterPanel::reportShift(){
    QSpinBox* direction =  static_cast<QSpinBox*>(panel_gsfilter->layout()->itemAt(1)->widget());
    QSpinBox* step= static_cast<QSpinBox*>(panel_gsfilter->layout()->itemAt(3)->widget());
    emit parameterChanged(new segParameter_shift(direction->value(),step->value()));
}

void segParameterPanel::reportAddnoise(){
   QDoubleSpinBox* mu =  static_cast<QDoubleSpinBox*>(panel_gsfilter->layout()->itemAt(1)->widget());
   QSpinBox* strength = static_cast<QSpinBox*>(panel_gsfilter->layout()->itemAt(3)->widget());
   QDoubleSpinBox* var = static_cast<QDoubleSpinBox*>(panel_gsfilter->layout()->itemAt(5)->widget());
   emit parameterChanged(new segParameter_addnoise(mu->value(), var->value(),strength->value()));
}
void segParameterPanel::reportFragment(){
    QSpinBox* ofs= static_cast<QSpinBox*>(panel_fixedvignetting->layout()->itemAt(1)->widget());
    emit parameterChanged(new segParameter_fragment(ofs->value()));
}

void segParameterPanel::reportFixedVignetting(){
    QSpinBox* color= static_cast<QSpinBox*>(panel_fixedvignetting->layout()->itemAt(1)->widget());
    emit parameterChanged(new segParameter_fixedvignetting(color->value()));
}

segParameterPanel::~segParameterPanel(){

}
