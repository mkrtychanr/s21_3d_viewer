QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ima/giflib/dgif_lib.c \
    ima/giflib/egif_lib.c \
    ima/giflib/gif_err.c \
    ima/giflib/gif_font.c \
    ima/giflib/gif_hash.c \
    ima/giflib/gifalloc.c \
    ima/giflib/quantize.c \
    ima/qgifimage.cpp \
    ../data_containers/dynamic_string.c \
    ../data_containers/lines_vector.c \
    ../data_containers/point_vector.c \
    ../data_containers/polygon_vector.c \
    ../parser/parser.c \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp

HEADERS += \
    ima/giflib/gif_hash.h \
    ima/giflib/gif_lib.h \
    ima/giflib/gif_lib_private.h \
    ima/qgifglobal.h \
    ima/qgifimage.h \
    ima/qgifimage_p.h \
    ../data_containers/headers/common.h \
    ../data_containers/headers/dynamic_string.h \
    ../data_containers/headers/line_vector.h \
    ../data_containers/headers/point_vector.h \
    ../data_containers/headers/polygon_vector.h \
    ../parser/parser.h \
    mainwindow.h \
    myopenglwidget.h

SUBDIRS += \
  ima/gifimage.pro

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
