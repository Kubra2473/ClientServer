QT       += core gui
QT       += network
QT       += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    sifrecoz.cpp \
    tcpserver.cpp

HEADERS += \
    sifrecoz.h \
    tcpserver.h

FORMS += \
    tcpserver.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Desktop/cryptopp870/release/ -lcryptopp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Desktop/cryptopp870/debug/ -lcryptopp
else:unix: LIBS += -L$$PWD/../../../Desktop/cryptopp870/ -lcryptopp

INCLUDEPATH += $$PWD/../../../Desktop/cryptopp870
DEPENDPATH += $$PWD/../../../Desktop/cryptopp870
