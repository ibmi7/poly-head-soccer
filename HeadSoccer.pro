######################################################################
# Automatically generated by qmake (3.1) Sat Jan 21 14:39:10 2023
######################################################################

TEMPLATE = app
TARGET = HeadSoccer
INCLUDEPATH += .

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += ballon.h \
           button.h \
           cercle.h \
           focushandler.h \
           game.h \
           personnage.h \
           joueur.h \
           score.h
SOURCES += ballon.cpp \
           button.cpp \
           cercle.cpp \
           focushandler.cpp \
           game.cpp \
           main.cpp \
           personnage.cpp \
           joueur.cpp \
           score.cpp
RESOURCES += resources.qrc
QT+=core widgets gui
QT+=multimedia
