INCLUDEPATH += E:/5.10.0/msvc2017_64/include
INCLUDEPATH += ../core/header
INCLUDEPATH += ../model/header
INCLUDEPATH += E:/opencv/opencv/build/include

LIBS += -L$$E:/qt/5.10.0/msvc2017_6/lib
LIBS += -L$$../core/library
LIBS += -L$$../model/library
LIBS += -L$$E:/opencv/opencv/build/x64/vc15/lib

TEMPLATE = app

contains(TARGET, qml.*) {
    QT += qml quick
}

target.path = F:/test/$$TARGET
INSTALLS += target
