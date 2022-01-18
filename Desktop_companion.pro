QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actionbutton.cpp \
    food.cpp \
    klee.cpp \
    main.cpp \
    mainwindow.cpp \
    option.cpp \
    optionscontainer.cpp \
    scene.cpp

#LIBS += commctrl.h

HEADERS += \
    actionbutton.h \
    food.h \
    klee.h \
    mainwindow.h \
    option.h \
    optionscontainer.h \
    scene.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    sprites/klee/klee_catch.png \
    sprites/klee/klee_catch_walk.png \
    sprites/klee/klee_throw.png \
    sprites/klee/klee_idle.png \
    sprites/klee/klee_walk.png \
    sprites/food/cookie.png

RESOURCES += \
    resources.qrc
