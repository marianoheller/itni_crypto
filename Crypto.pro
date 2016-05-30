#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T15:08:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Crypto
TEMPLATE = app


debug:   DESTDIR = build/debug
release: DESTDIR = build/release

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui



QMAKE_CXXFLAGS += -Wunused-variable -std=c++98

QMAKE_LFLAGS += -Wl,-R/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/        #Set runpath
QMAKE_LFLAGS += -Wl,-R./lib/
#QMAKE_LFLAGS_DEBUG += -L/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/ -Wl,-Bstatic -Wl,-R/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/ -lcrypto -Wl,-Bdynamic    #No anda

#QMAKE_LFLAGS_RELEASE += -Wl,-R/usr/lib/ssl/fips/



SOURCES += main.cpp\
        mainwindow.cpp \
    cryptoengine.cpp \
    big_num.cpp \
    byte_utils.cpp \
    verificador.cpp \
    firmado.cpp \
    firma.cpp \
    par_de_claves.cpp \
    frasedialog.cpp

HEADERS  += mainwindow.h \
    cryptoengine.h \
    verificador.h \
    open_ssl_state.h \
    byte_utils.h \
    big_num.h \
    firmado.h \
    firma.h \
    par_de_claves.h \
    par_de_claves_default.h \
    frasedialog.h

FORMS    += mainwindow.ui \
    frasedialog.ui

RESOURCES += \
    res.qrc


INCLUDEPATH += /home/mariano/firmado/openssl-1.0.1s/ssldir/include
DEPENDPATH += /home/mariano/firmado/openssl-1.0.1s/ssldir/include


#LIBS += -Wl,-Bstatic -L/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/ -lcrypto -Wl,-Bdynamic -ldl     #Static Linking
LIBS += -L/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/ -lcrypto -ldl     #Dynamic Linking





#======================
#Old stuff

#LIBS += -Wl,-Bstatic -L/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/ -lcrypto -Wl,-Bdynamic
#PRE_TARGETDEPS += /home/mariano/firmado/openssl-1.0.1s/ssldir/lib/libcrypto.a


#QMAKE_RPATHDIR += /home/mariano/firmado/openssl-1.0.1s/ssldir/lib/
#LIBS += -lcrypto

