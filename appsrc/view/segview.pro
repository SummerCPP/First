android|ios|winrt {
    error( "This example is not supported for android, ios, or winrt." )
}

!include( ./examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

SOURCES += main.cpp \
    SegController.cpp

HEADERS += \
       SegController.h

QT += widgets

RESOURCES +=

OTHER_FILES += data/* \
               data/image/* \
               ../model/* \
               ../model/header/* \
               ../model/source/* \
               ../* \
               ../core/* \
               ../core/header/* \
               ../core/source/*

