#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T15:08:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Crypto
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cryptoengine.cpp \
    big_num.cpp \
    byte_utils.cpp \
    verificador.cpp \
    firmado.cpp \
    firma.cpp \
    par_de_claves.cpp

HEADERS  += mainwindow.h \
    cryptoengine.h \
    verificador.h \
    open_ssl_state.h \
    byte_utils.h \
    big_num.h \
    firmado.h \
    firma.h \
    par_de_claves.h \
    par_de_claves_default.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc


INCLUDEPATH += /home/mariano/firmado/openssl-1.0.1s/ssldir/include
DEPENDPATH += /home/mariano/firmado/openssl-1.0.1s/ssldir/include

LIBS += -L$$PWD/../../../../firmado/openssl-1.0.1s/ssldir/lib/ -lcrypto

#INCLUDEPATH += $$PWD/../../../../firmado/openssl-1.0.1s/ssldir/include
#DEPENDPATH += $$PWD/../../../../firmado/openssl-1.0.1s/ssldir/include

PRE_TARGETDEPS += $$PWD/../../../../firmado/openssl-1.0.1s/ssldir/lib/libcrypto.a
