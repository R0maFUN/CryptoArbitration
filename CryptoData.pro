QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Common/CommonDataStructures.cpp \
        Common/ListModel.cpp \
        Common/RequestsPerformer.cpp \
        Model/MainModel.cpp \
        Model/P2PData.cpp \
        Model/SettingsModel.cpp \
        Model/SpotDataModel.cpp \
        ViewModel/MainViewModel.cpp \
        ViewModel/SettingsViewModel.cpp \
        ViewModel/SpotData.cpp \
        ViewModel/SpotDataStorage.cpp \
        ViewModel/TestViewModel.cpp \
        main.cpp

RESOURCES += qml.qrc \
    image.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Common/CommonDataStructures.h \
    Common/ListModel.h \
    Common/RequestsPerformer.h \
    Model/MainModel.h \
    Model/P2PData.h \
    Model/SettingsModel.h \
    Model/SpotDataModel.h \
    ViewModel/MainViewModel.h \
    ViewModel/SettingsViewModel.h \
    ViewModel/SpotData.h \
    ViewModel/SpotDataStorage.h \
    ViewModel/TestViewModel.h

