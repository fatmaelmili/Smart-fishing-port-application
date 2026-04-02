QT       += core gui
QT += core gui widgets charts
<<<<<<< HEAD:StaffManagement.pro
QT+=sql
=======
QT += sql

>>>>>>> gestion_clients:ClientManagement.pro

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< HEAD:StaffManagement.pro
    Bort.cpp \
    connection.cpp \
    main.cpp

HEADERS += \
    Bort.h \
    connection.h

FORMS += \
    Bort.ui
=======
    bort.cpp \
    clients.cpp \
    connection.cpp \
    editclientdialog.cpp \
    main.cpp

HEADERS += \
    bort.h \
    clients.h \
    connection.h \
    editclientdialog.h

FORMS += \
    clients.ui \
>>>>>>> gestion_clients:ClientManagement.pro

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Ressources.qrc

DISTFILES += \
    Images/logo.png
