QT += quick charts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        algo/sort/mergesort.cpp \
        basework.cpp \
        algo/sort/bubblework.cpp \
        algo/sort/insertionsort.cpp \
        main.cpp \
        algo/sort/selectionsortwork.cpp \
        algo/sort/shellsort.cpp \
        algo/sort/sort.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    algo/sort/mergesort.h \
    basework.h \
    algo/sort/bubblework.h \
    algo/sort/insertionsort.h \
    algo/sort/selectionsortwork.h \
    algo/sort/shellsort.h \
    algo/sort/sort.h
