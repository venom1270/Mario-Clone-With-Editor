TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11

QSG_RENDER_LOOP=basic

QT     += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
SOURCES += main.cpp \
    editor.cpp \
    world.cpp \
    texturemanager.cpp \
    entity.cpp \
    camera.cpp \
    movableentity.cpp \
    player.cpp \
    collisionmanager.cpp \
    enemy.cpp \
    exit.cpp \
    coin.cpp

INCLUDEPATH += C:\SFML-master\SFML-master\include \
DEPENDPATH += C:\SFML-master\SFML-master\include
LIBS += -LC:\SFML-master\SFML-master-build\lib


CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

HEADERS += \
    editor.h \
    world.h \
    texturemanager.h \
    entity.h \
    camera.h \
    movableentity.h \
    player.h \
    Globals.h \
    collisionmanager.h \
    enemy.h \
    exit.h \
    coin.h

FORMS += \
    editor.ui
