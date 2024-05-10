QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql multimedia texttospeech network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    funwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    registerwindow.cpp \
    Audio.cpp \
    Http.cpp \
    Speech.cpp

HEADERS += \
    database.h \
    funwindow.h \
    mainwindow.h \
    registerwindow.h \
    Audio.h \
    Http.h \
    Speech.h

FORMS += \
    funwindow.ui \
    mainwindow.ui \
    registerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
