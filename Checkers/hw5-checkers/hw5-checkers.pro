QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    announcewinnerdialog.cpp \
    board.cpp \
    boardtile.cpp \
    main.cpp \
    mainwindow.cpp \
    piece.cpp \
    piecefactory.cpp \
    playernamedialog.cpp

HEADERS += \
    announcewinnerdialog.h \
    board.h \
    boardtile.h \
    mainwindow.h \
    piece.h \
    piecefactory.h \
    playernamedialog.h

FORMS += \
    announcewinnerdialog.ui \
    mainwindow.ui \
    playernamedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
