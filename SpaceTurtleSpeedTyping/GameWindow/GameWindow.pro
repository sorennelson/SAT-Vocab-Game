#-------------------------------------------------
#
# Project created by QtCreator 2018-11-20T13:13:40
#
#-------------------------------------------------

QT       += core gui \
            multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameWindow
TEMPLATE = app

DEPENDPATH += . ../GameLib/
INCLUDEPATH += ../GameLib/

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        gamewindow.cpp \
        gameview.cpp \
        ../GameLib/*.cpp

HEADERS += \
        gamewindow.h \
        gameview.h \
        ../GameLib/*.h

FORMS += \
        gamewindow.ui \
        gameview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../src/src.qrc

macx: LIBS += -L$$PWD/../3rdPartyLibraries/Box2D/lib/osx/ -lBox2D
macx: LIBS += -F$$PWD/../3rdPartyLibraries/SFML/Frameworks/

macx: LIBS += -framework sfml-audio
macx: LIBS += -framework sfml-graphics
macx: LIBS += -framework sfml-network
macx: LIBS += -framework sfml-window
macx: LIBS += -framework sfml-system
macx: LIBS += -framework SFML

unix:!macx: LIBS += -lsfml-audio
unix:!macx: LIBS += -lsfml-graphics
unix:!macx: LIBS += -lsfml-network
unix:!macx: LIBS += -lsfml-window
unix:!macx: LIBS += -lsfml-system

INCLUDEPATH += $$PWD/../GameLib
DEPENDPATH += $$PWD/../GameLib
INCLUDEPATH += $$PWD/../3rdPartyLibraries/Box2D/include
DEPENDPATH += $$PWD/../3rdPartyLibraries/Box2D/include

macx: PRE_TARGETDEPS += $$PWD/../3rdPartyLibraries/Box2D/lib/osx/libBox2D.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdPartyLibraries/Box2D/lib/win32/ -lBox2D
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdPartyLibraries/Box2D/lib/win32/ -lBox2D
else:unix:!macx: LIBS += -L$$PWD/../3rdPartyLibraries/Box2D/lib/linux/ -lBox2D

macx: INCLUDEPATH += $$PWD/../3rdPartyLibraries/SFML/include
macx: DEPENDPATH += $$PWD/../3rdPartyLibraries/SFML/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdPartyLibraries/Box2D/lib/win32/libBox2D.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdPartyLibraries/Box2D/lib/win32/libBox2D.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdPartyLibraries/Box2D/lib/win32/Box2D.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdPartyLibraries/Box2D/lib/win32/Box2D.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../3rdPartyLibraries/Box2D/lib/linux/libBox2D.a

unix:!macx: LIBS += -L$$PWD/../3rdPartyLibraries/SpriteGeneratorBuild/linux/ -lSpriteGenerator

INCLUDEPATH += $$PWD/../3rdPartyLibraries/SpriteGeneratorBuild/include
DEPENDPATH += $$PWD/../3rdPartyLibraries/SpriteGeneratorBuild/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../3rdPartyLibraries/SpriteGeneratorBuild/linux/libSpriteGenerator.a

macx: LIBS += -L$$PWD/../3rdPartyLibraries/SpriteGeneratorBuild/osx/ -lSpriteGenerator

macx: PRE_TARGETDEPS += $$PWD/../3rdPartyLibraries/SpriteGeneratorBuild/osx/libSpriteGenerator.a
