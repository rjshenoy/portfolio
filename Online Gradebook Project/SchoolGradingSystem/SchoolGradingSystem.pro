QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    assignment.cpp \
    assignmentfactory.cpp \
    course.cpp \
    datamanager.cpp \
    datatest.cpp \
    gradestablemodel.cpp \
    main.cpp \
    mainwindow.cpp \
    student.cpp \
    studentcourseviewwindow.cpp \
    studentviewcoursebutton.cpp \
    studentwindow.cpp \
    teacher.cpp \
    teachercourseviewwindow.cpp \
    teacherviewcoursebutton.cpp \
    teacherwindow.cpp

HEADERS += \
    assignment.h \
    assignmentfactory.h \
    course.h \
    datamanager.h \
    datatest.h \
    gradestablemodel.h \
    mainwindow.h \
    student.h \
    studentcourseviewwindow.h \
    studentviewcoursebutton.h \
    studentwindow.h \
    teacher.h \
    teachercourseviewwindow.h \
    teacherviewcoursebutton.h \
    teacherwindow.h

FORMS += \
    mainwindow.ui \
    studentcourseviewwindow.ui \
    studentwindow.ui \
    teachercourseviewwindow.ui \
    teacherwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
