android|ios|winrt {
    error( "This example is not supported for android, ios, or winrt." )
}

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

SOURCES += main.cpp \
    SegController.cpp

HEADERS += \
       SegController.h

QT += widgets

RESOURCES +=

OTHER_FILES += ../core/source/*  \
               ../core/header/* \
               ../core/library/* \
               ../model/header/* \
               ../model/source/* \
               ../model/library/* \
               ../view/header/* \
               ../view/source/* \
               ../view/library/* \
               ../view/header/* \
               ../controller/header/* \
               ../controller/source/* \
               ../controller/library/* \
               ../view/*    \
               ../model/*   \
               ../controller/* \
               ../core/*



