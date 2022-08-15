QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addgoodsdialog.cpp \
    addsaledatadialog.cpp \
    calculateprofiledialog.cpp \
    findgoodsdialog.cpp \
    findsaledatadialog.cpp \
    goods.cpp \
    main.cpp \
    mainwindow.cpp \
    marketingmanager.cpp \
    newtabletab.cpp \
    sale.cpp

HEADERS += \
    addgoodsdialog.h \
    addsaledatadialog.h \
    calculateprofiledialog.h \
    findgoodsdialog.h \
    findsaledatadialog.h \
    goods.h \
    mainwindow.h \
    marketingmanager.h \
    newtabletab.h \
    sale.h

FORMS += \
    addgoodsdialog.ui \
    addsaledatadialog.ui \
    calculateprofiledialog.ui \
    findgoodsdialog.ui \
    findsaledatadialog.ui \
    mainwindow.ui \
    newtabletab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	res.qrc
