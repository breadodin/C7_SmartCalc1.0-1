QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creditcalc.cpp \
    depositcalc.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    ../../core/s21_input_check.c \
    ../../core/s21_parser.c\
    ../../core/s21_sort.c\
    ../../core/s21_SmartCalc.c \
    qcustomplot.cpp

HEADERS += \
    creditcalc.h \
    depositcalc.h \
    graph.h \
    mainwindow.h \
    ../../model/s21_SmartCalc.h \
    ../../model/s21_check_input.h \
    qcustomplot.h

FORMS += \
    creditcalc.ui \
    depositcalc.ui \
    graph.ui \
    mainwindow.ui
    
DESTDIR = ~/SmartCalc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
