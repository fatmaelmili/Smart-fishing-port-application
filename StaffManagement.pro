QT       += core gui
QT += core gui widgets charts
<<<<<<< HEAD


=======
QT+=sql
QT += network
QT += charts
QT += pdf
>>>>>>> zonepeche
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bort.cpp \
<<<<<<< HEAD
    main.cpp

HEADERS += \
    Bort.h
=======
    connection.cpp \
    main.cpp \
    personnel.cpp \
    zonepech.cpp

HEADERS += \
    Bort.h \
    connection.h \
    personnel.h \
    zonepech.h
>>>>>>> zonepeche

FORMS += \
    Bort.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Ressources.qrc

DISTFILES += \
    Images/logo.png
<<<<<<< HEAD
=======


INCLUDEPATH += C:/opencv/build/include

CONFIG(debug, debug|release) {
    LIBS += -LC:/opencv/build/x64/vc16/lib \
            -lopencv_world4120d
} else {
    LIBS += -LC:/opencv/build/x64/vc16/lib \
            -lopencv_world4120
}
>>>>>>> zonepeche
