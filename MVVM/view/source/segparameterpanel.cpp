#include "config.h"
#include "segparameterpanel.h"

;
void segParameterPanel::handle_parameterChange(int i){
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
    panel_addnoise->setLayout(l);
    QSpinBox * s_strength = new QSpinBox();
    s_strength->setRange(0,100);
    QLabel *   n_strength = new QLabel("Noise Strength : ");
    QDoubleSpinBox * s_mu = new QDoubleSpinBox();
    s_mu->setRange(-10,10);
    QLabel * n_mu = new QLabel("Mean : ");
    QDoubleSpinBox * s_var = new QDoubleSpinBox();
    s_var->setRange(0,100);
    QLabel * n_var = new QLabel("Variance of Noise: ");

    l->addWidget(n_mu,);
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
    panel_fixedvignetting->setLayout(l);
    QSpinBox * s_color = (new QSpinBox());
    s_color->setRange(0,1);
    QLabel *   n_color= new QLabel("Color : ");
    l->addWidget(n_color);
    l->addWidget(s_color);
    QObject::connect(s_color, &QSpinBox::editingFinished, this, &segParameterPanel::reportFixedVignetting);

}
void segParameterPanel::setup_fragment(){
    QVBoxLayout * l = new QVBoxLayout;
    panel_fragment->setLayout(l);
    QSpinBox * s_offset = (new QSpinBox());
    s_offset->setRange(-100,100);
    QLabel *   n_offset= new QLabel("Offset : ");
    l->addWidget(n_offset);
    l->addWidget(s_offset);
    QObject::connect(s_offset, &QSpinBox::editingFinished, this, &segParameterPanel::reportFragment);
}

void segParameterPanel::setup_gsfilter(){
    QVBoxLayout * l = new QVBoxLayout;
    panel_gsfilter->setLayout(l);
    QSpinBox * s_size = (new QSpinBox());
    s_size->setRange(1,100);
    QLabel *   n_size= new QLabel("Kernel Size : ");

    QDoubleSpinBox * s_delta = (new QDoubleSpinBox());
    s_delta->setRange(0.0001,1000);
    QLabel *   n_delta= new QLabel("Delta : ");

    l->addWidget(n_size);
    l->addWidget(s_size);

    l->addWidget(n_delta);
    l->addWidget(s_delta);

    QObject::connect(s_size, &QSpinBox::editingFinished, this, &segParameterPanel::reportGsfilter);
    QObject::connect(s_delta, &QSpinBox::editingFinished, this, &segParameterPanel::reportGsfilter);

}

void segParameterPanel::setup_shift(){
    QVBoxLayout * l = new QVBoxLayout;
    panel_gsfilter->setLayout(l);

    QSpinBox * s_direction = (new QSpinBox());
    s_direction->setRange(1,4);
    QLabel *   n_direction= new QLabel("Direction : ");

    l->addWidget(n_direction);
    l->addWidget(s_direction);

    QObject::connect(s_direction, &QSpinBox::editingFinished, this, &segParameterPanel::reportShift);

}

void segParameterPanel::reportGsfilter(){
    QSpinBox* size =  dynamic_cast<QSpinBox*>(panel_gsfilter->layout()->itemAt(1)->widget());
    QSpinBox* delta = dynamic_cast<QSpinBox*>(panel_gsfilter->layout()->itemAt(3)->widget());
    emit parameterChanged(new segParameter_gsfilter(delta->value(),size->value(),IMG_ALGO_0_GSFILTER));
}

void segParameterPanel::reportShift(){
    QSpinBox* size =  dynamic_cast<QSpinBox*>(panel_gsfilter->layout()->itemAt(1)->widget());
    QSpinBox* delta = dynamic_cast<QSpinBox*>(panel_gsfilter->layout()->itemAt(3)->widget());
     emit parameterChanged(new segParameter_gsfilter(delta->value(),size->value(),IMG_ALGO_0_GSFILTER));
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
