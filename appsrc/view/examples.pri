INCLUDEPATH += E:/5.10.0/msvc2017_64/include
INCLUDEPATH += ../core/header
INCLUDEPATH += ../model/header

LIBS += -L$$E:/qt/5.10.0/msvc2017_6/lib
LIBS += -L$$../core/library
LIBS += -L$$../model/library

TEMPLATE = app

contains(TARGET, qml.*) {
    QT += qml quick
}

target.path = F:/test/$$TARGET
INSTALLS += target
