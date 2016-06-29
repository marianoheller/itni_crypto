#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T15:08:03
#
#-------------------------------------------------


#============================
## Qt Config
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


#============================
## UNIX FLAGS
unix:!macx: QMAKE_CXXFLAGS += -Wunused-variable -std=c++98

unix:!macx: QMAKE_LFLAGS += -Wl,-R/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/        #Set runpath
unix:!macx: QMAKE_LFLAGS += -Wl,-R./lib/

#unix:!macx: QMAKE_LFLAGS_DEBUG += -L/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/ -Wl,-Bstatic -Wl,-R/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/ -lcrypto -Wl,-Bdynamic    #No anda
#unix:!macx: QMAKE_LFLAGS_RELEASE += -Wl,-R/usr/lib/ssl/fips/


#============================
## WINDOWS FLAGS
win32: QMAKE_CXXFLAGS += -Wunused-variable -std=c++98
win32: QMAKE_LFLAGS += -Wl,-RD:/usr/local/ssl/lib/      #Set runpath


#============================
## FILES
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
LIBS += -L/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/ -lcrypto -ldl                                #Dynamic Linking




###########################
#NOT USING UNIX AND WINDOWS SEPARATION DUE TO OpenSSL not working on Windows
##########################

##============================
## UNIX LINKING
#unix:!macx: INCLUDEPATH += /home/mariano/firmado/openssl-1.0.1s/ssldir/include
#unix:!macx: DEPENDPATH += /home/mariano/firmado/openssl-1.0.1s/ssldir/include

##Dynamic and static linking - Choose one
#unix:!macx: LIBS += -Wl,-Bstatic -L/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/ -lcrypto -Wl,-Bdynamic -ldl     #Static Linking
#unix:!macx: LIBS += -L/home/mariano/firmado/openssl-1.0.1s/ssldir/lib/ -lcrypto -ldl                                #Dynamic Linking


##============================
## WINDOWS LINKING
#win32: LIBS += -LD:/usr/local/ssl/lib/ -llibeayfips64

#win32: INCLUDEPATH += D:/usr/local/ssl/include
#win32: DEPENDPATH += D:/usr/local/ssl/include

#win32:!win32-g++: PRE_TARGETDEPS += D:/usr/local/ssl/lib/libeayfips64.lib




