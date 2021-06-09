QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ball.cpp \
    Button.cpp \
    Game.cpp \
    Players.cpp \
    TcpClient.cpp \
    dialog.cpp \
    jsonConverter.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Ball.h \
    Button.h \
    Game.h \
    Players.h \
    TcpClient.h \
    dialog.h \
    jsonConverter.h \
    widget.h

FORMS += \
    dialog.ui \
    widget.ui

QMAKE_CXXFLAGS += -std=gnu++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
