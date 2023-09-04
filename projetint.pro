QT       += core gui
QT       += core gui sql printsupport
QT += serialport
QT += network
QT += multimediawidgets
QT += multimedia
QT += quick
QT += charts
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Aides.cpp \
    aide.cpp \
    arduino.cpp \
    beneficiaire.cpp \
    chat.cpp \
    connection.cpp \
    donneur.cpp \
    donneurs.cpp \
    emp.cpp \
    emp2.cpp \
    evenement.cpp \
    event1.cpp \
    exportexcelobject.cpp \
    f_necess.cpp \
    global.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    qcustomplot.cpp \
    qrcodegen.cpp \
    stock.cpp

HEADERS += \
    Aides.h \
    aide.h \
    arduino.h \
    beneficiaire.h \
    chat.h \
    connection.h \
    donneur.h \
    donneurs.h \
    emp.h \
    emp2.h \
    evenement.h \
    event1.h \
    exportexcelobject.h \
    f_necess.h \
    global.h \
    mainwindow.h \
    menu.h \
    qcustomplot.h \
    qrcodegen.hpp \
    stock.h

FORMS += \
    chat.ui \
    donneur.ui \
    emp.ui \
    event1.ui \
    f_necess.ui \
    mainwindow.ui \
    menu.ui \
    stock.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    Aides.pdf \
    Donneurs.pdf \
    Employes.pdf \
    Evenements.pdf \
    ProjetQT.pro.user \
    back.png \
    benef.xls \
    chat.jpg \
    chat1.png \
    login.png \
    pass.png \
    projetint.pro.user \
    rech.png \
    user.png

RESOURCES += \
    style.qrc
