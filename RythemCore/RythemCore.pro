TEMPLATE = app

QT -= gui

QT += network qml

CONFIG += c++11 console
CONFIG -= app_bundle


#LIBS += -L "../PACParserWithQt"
mac:LIBS += "../PACParserWithQt/libpacparser.a"
windows:LIBS += "../PACParserWithQt/pacparser.lib"

mac:LIBS += -framework Security # 申请个性系统权限

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    proxyserver.cpp \
    config.cpp \
    utils.cpp

HEADERS += \
    proxyserver.h \
    config.h

DISTFILES += \
    tool/setupproxy.sh

INCLUDEPATH += $$PWD/../PACParserWithQt
