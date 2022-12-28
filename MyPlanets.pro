QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    createdialog.cpp \
    csvview.cpp \
    editdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    sourcedialog.cpp

HEADERS += \
    aboutdialog.h \
    createdialog.h \
    csvview.h \
    editdialog.h \
    mainwindow.h \
    queue.h \
    sourcedialog.h

FORMS += \
    aboutdialog.ui \
    createdialog.ui \
    csvview.ui \
    editdialog.ui \
    mainwindow.ui \
    sourcedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../res/pack1.qrc \
    ../res/pack2.qrc

DISTFILES +=
