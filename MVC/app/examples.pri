INCLUDEPATH += E:/qt/5.10.0/msvc2017_64/include
INCLUDEPATH += ../core/header
INCLUDEPATH += ../model/header
INCLUDEPATH += E:/opencv/opencv/build/include

LIBS += -L$$E:/qt/5.10.0/msvc2017_6/lib
LIBS += F:/POOL/second/First/appsrc/core/library/gsfilter.lib
LIBS += F:/POOL/second/First/appsrc/model/library/segmodel.lib
LIBS += E:/opencv/opencv/build/x64/vc15/lib/opencv_world341.lib
LIBS += E:/opencv/opencv/build/x64/vc15/lib/opencv_world341d.lib

TEMPLATE = app

contains(TARGET, qml.*) {
    QT += qml quick
}

target.path = F:/test/$$TARGET
INSTALLS += target
