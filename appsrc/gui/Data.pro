#-------------------------------------------------
#
# Project created by QtCreator 2018-07-13T10:25:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Data
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


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    myLibrary/hello.h

FORMS += \
        mainwindow.ui


INCLUDEPATH += "$$PWD/myLibrary"

LC:/Qt/Qt5.5/5.5/mingw492_32/lib -lqtmaind -lshell32 c:/somewhere/myProgram/myLibrary/mylibrary.dll -lQt5Widgetsd -lQt5Guid -lQt5Cored



INCLUDEPATH += D:\program\openCV\opencv\build\include \

               D:\program\openCV\opencv\build\include\opencv \

               D:\program\openCV\opencv\build\include\opencv2 \

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../program/openCV/opencv/build/x64/vc14/lib/ -lopencv_world342
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../program/openCV/opencv/build/x64/vc14/lib/ -lopencv_world342d
else:unix: LIBS += -L$$PWD/../../../../../program/openCV/opencv/build/x64/vc14/lib/ -lopencv_world342

INCLUDEPATH += $$PWD/../../../../../program/openCV/opencv/build/x64/vc14
DEPENDPATH += $$PWD/../../../../../program/openCV/opencv/build/x64/vc14


