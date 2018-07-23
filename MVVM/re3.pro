#-------------------------------------------------
#
# Project created by QtCreator 2018-07-20T15:01:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = re3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += E:/qt/5.10.0/msvc2017_64/include
INCLUDEPATH += E:/opencv/opencv/build/include
INCLUDEPATH += core/header
INCLUDEPATH += model/header
INCLUDEPATH += view/header
INCLUDEPATH += viewmodel/header

LIBS += -L$$E:/qt/5.10.0/msvc2017_64/lib
LIBS += E:/opencv/opencv/build/x64/vc15/lib/opencv_world341.lib
LIBS += E:/opencv/opencv/build/x64/vc15/lib/opencv_world341d.lib

SOURCES += \            
    core/source/Gaussian.cpp \
  core/source/Line.cpp \
  core/source/OldMovie.cpp \
  core/source/Sketch.cpp \
  core/source/Fragment.cpp \
  model/source/segmodel.cpp \
   view/source/segview.cpp \
   viewmodel/source/segviewmodel.cpp \
   app/app.cpp \
  view/source/segparameter.cpp \
  view/source/segparameterpanel.cpp
  #  view/source/segFeature.cpp \

HEADERS += \
  core/header/segcore.hpp \
  model/header/segmodel.h \
  model/header/config.h \
  view/header/segview.h \
  #view/header/segFeature.h \
 viewmodel/header/segViewModel.h \
       view/header/segparameter.h \
   view/header/segparameterpanel.h


OTHER_FILES += core/source/* \
               core/header/* \
               core/library/*\
               model/header/* \
               model/source/* \
               model/library/*\
               view/header/* \
               view/source/* \
               view/library/* \
               view/header/*\
               viewmodel/header/* \
               viewmodel/source/* \
               viewmodel/library/*\
               view/*    \
               model/*   \
               viewmodel/* \
               core/*   \
               app/*

