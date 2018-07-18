android|ios|winrt {
    error( "This example is not supported for android, ios, or winrt." )
}
!include( ./examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}
SOURCES += main.cpp \
    SegController.cpp \
    ../model/source/segimagemodel.cpp

HEADERS += \
       SegController.h \
    ../model/header/segimagemodel.h

QT += widgets

RESOURCES +=

OTHER_FILES += data/* \
               data/image/* \
               ../model/* \
               ../model/header/* \
               ../model/source/* \
               ../model/library/* \
               ../*.cpp \
               ../*.h \
               ../*.hpp \
               ../core/* \
               ../core/header/* \
               ../core/source/* \
               ../core/library/*
