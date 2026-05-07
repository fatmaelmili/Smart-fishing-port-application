QT       += core gui
QT += core gui widgets charts
QT+=sql
QT += network
QT += charts
QT += pdf
QT += multimedia
QT+=serialport
QT += datavisualization
QT += core gui widgets pdf 3dcore 3drender 3dinput 3dextras
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Bort.cpp \
    chatbotdialog.cpp \
    client.cpp \
    connection.cpp \
    editclientdialog.cpp \
    equipment.cpp \
    main.cpp \
    personnel.cpp \
    predictiondialog.cpp \
    stock.cpp \
    arduino.cpp \
    vesselstatsdialog.cpp \
    zonepech.cpp

HEADERS += \
    Bort.h \
    chatbotdialog.h \
    client.h \
    connection.h \
    editclientdialog.h \
    equipment.h \
    personnel.h \
    predictiondialog.h \
    stock.h \
    arduino.h \
    vesselstatsdialog.h \
    zonepech.h

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



win32-g++ {
    INCLUDEPATH += C:/opencv-install-mingw/include

    LIBS += -LC:/opencv-install-mingw/x64/mingw/lib \
            -lopencv_core4120 \
            -lopencv_imgproc4120 \
            -lopencv_imgcodecs4120 \
            -lopencv_highgui4120 \
            -lopencv_videoio4120 \
            -lopencv_objdetect4120

    DEFINES += USE_OPENCV
}
