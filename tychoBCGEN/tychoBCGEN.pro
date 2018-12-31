#-------------------------------------------------
#
# Project created by QtCreator 2012-04-24T20:36:51
#
#-------------------------------------------------

QT       += gui
QT       += widgets


TARGET = tychoBCGEN
TEMPLATE = app

RC_FILE = myapp.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    openfile.cpp \
    viewing.cpp \
    color_segmentation.cpp \
    colormask.cpp \
    tutorial.cpp \
    about.cpp \
    wind_emitter.cpp

HEADERS  += mainwindow.h \
    myscene.h \
    global.h \
    global.h \
    colormask.h \
    image_stack.h \
    about.h \
    ui_colormask.h \
    ui_tutorial.h \
    ui_about.h \
    tutorial.h \
    ui_mainwindow.h

FORMS    += mainwindow.ui \
    colormask.ui \
    tutorial.ui \
    about.ui

