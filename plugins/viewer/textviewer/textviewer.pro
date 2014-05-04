TEMPLATE = lib
TARGET   = plugin_textviewer
DESTDIR  = ../../../bin

QT = core gui
CONFIG += c++11

#check Qt version
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

OBJECTS_DIR = ../../../build/textviewer
MOC_DIR     = ../../../build/textviewer
UI_DIR      = ../../../build/textviewer
RCC_DIR     = ../../../build/textviewer

INCLUDEPATH += \
	../../../file-commander-core/src \
	../../../file-commander-core/include \
	$$PWD/src/

DEFINES += PLUGIN_MODULE

LIBS += -L../../../bin -lcore

win*{
	QMAKE_CXXFLAGS += /MP
	QMAKE_CXXFLAGS_WARN_ON = -W4
}

mac*{

}

linux*{

}

linux*|mac*{
	QMAKE_CXXFLAGS += --std=c++11
}

HEADERS += \
	src/QtIncludes.h \
    src/ctextviewerplugin.h \
    src/ctextviewerwindow.h

SOURCES += \
    src/ctextviewerplugin.cpp \
    src/ctextviewerwindow.cpp


win32*:!*msvc2012:*msvc* {
	QMAKE_CXXFLAGS += /FS
}

FORMS += \
    src/ctextviewerwindow.ui
