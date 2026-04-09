QT       += core gui
QT += core gui widgets charts
QT+=sql
QT += network
QT += charts
QT += pdf
<<<<<<< HEAD
QT += multimedia
=======
>>>>>>> befb43f2ea9a0e885e1306a35140667554d1a96b
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bort.cpp \
    connection.cpp \
    main.cpp \
<<<<<<< HEAD
    personnel.cpp
=======
    personnel.cpp \
    zonepech.cpp
>>>>>>> befb43f2ea9a0e885e1306a35140667554d1a96b

HEADERS += \
    Bort.h \
    connection.h \
<<<<<<< HEAD
    personnel.h
=======
    personnel.h \
    zonepech.h
>>>>>>> befb43f2ea9a0e885e1306a35140667554d1a96b

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


INCLUDEPATH += C:/opencv/build/include

CONFIG(debug, debug|release) {
    LIBS += -LC:/opencv/build/x64/vc16/lib \
            -lopencv_world4120d
} else {
    LIBS += -LC:/opencv/build/x64/vc16/lib \
            -lopencv_world4120
}
