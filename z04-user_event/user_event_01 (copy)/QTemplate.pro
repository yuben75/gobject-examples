######################################################################
# Automatically generated by qmake (1.07a) Tue Jan 17 08:57:50 2017
######################################################################
#PRJ_ROOT = $${PWD}
message("====Qxxx.pro============================")
TARGET_NAME=$$QTARGET_NAME
TARGET_PRO=$$TARGET_NAME".pro"
include($$TARGET_PRO)
message("TARGET_NAME="$$TARGET_NAME)
message("TARGET_PRO="$$TARGET_PRO)

#########################################################################################
# copy for qmake generated TARGET_NAME
#########################################################################################
include( ../Object/QTemplate.pri )

#DEPENDPATH += /usr/include/glib-2.0 \
#              /usr/lib/i386-linux-gnu/glib-2.0/include
INCLUDEPATH += /usr/include/glib-2.0 \
			  /usr/lib/i386-linux-gnu/glib-2.0/include

# Input
HEADERS += 
SOURCES += 

SOURCES -= main.c
#SOURCES -= shape.c
SOURCES -= circle.c
SOURCES -= rectangle.c
#TARGET_NAME = test_xxx

#------------------------------------------------------------------
win32: {	#win32
    error ("win32")
    warning()
    message()
}
unix :{ 	#linux
    message("build linux platform....")
} else{
    error ("error build...")
}
#------------------------------------------------------------------
message("QDEFS = "$$QDEFS)
contains(QDEFS, .*x86.*) {
    message("compile x86(debug)")
    TARGET_DIR=debug
    DEFINES += _DEBUG
}
contains(QDEFS, .*arm.*) {
    message("compile am335x(release)")
    TARGET_DIR=release
    DEFINES += _RELEASE
}

#------------------------------------------------------------------
# install

contains(QDEFS, .*app.*) {
    message("compile app")
    TEMPLATE = app
    DESTDIR = ./out_test/$$TARGET_DIR
    TARGET = /$$TARGET_NAME
}
contains(QDEFS, .*static.*) {
    message("compile static library")
    TEMPLATE = lib
    CONFIG += staticlib
    DESTDIR = ./out_lib/$$TARGET_DIR
    TARGET = /$$TARGET_NAME
}
contains(QDEFS, .*shared.*) {
    message("compile shared library")
    TEMPLATE = lib
    DESTDIR = ./out_lib/$$TARGET_DIR
    TARGET = /$$TARGET_NAME
}

#package.path = $${DESTDIR}
#package.files += ./$${DESTDIR}/$$TARGET
#package.CONFIG = no_check_exist
#INSTALLS += package


app.path = ./install_$${TARGET_DIR}/Utility_app
app.files += ./$${DESTDIR}/$$TARGET
app.CONFIG = no_check_exist
INSTALLS += app


inc.path = ./install_$${TARGET_DIR}/Utility_inc
inc.files = inc/*
INSTALLS += inc


lib.path = ./install_$${TARGET_DIR}/Utility_lib
lib.files = out_lib/$$TARGET_DIR/*
INSTALLS += lib


#------------------------------------------------------------------
# object files
OBJECTS_DIR= ./obj/$$TARGET_DIR



#########################################################################################
#
#########################################################################################
QMAKE_CXXFLAGS += $$(CXXFLAGS)
QMAKE_CXXFLAGS += -fmax-errors=1
QMAKE_CXXFLAGS += -fpermissive
#QMAKE_CXXFLAGS += -std=c++11

QMAKE_CFLAGS += $$(CFLAGS)
QMAKE_CFLAGS += -fmax-errors=1
#QMAKE_CFLAGS += -std=c99


QMAKE_CXXFLAGS += `pkg-config --cflags glib-2.0 gthread-2.0 gio-2.0 gmodule-2.0 gobject-2.0`
QMAKE_CFLAGS += `pkg-config --cflags glib-2.0 gthread-2.0 gio-2.0 gmodule-2.0 gobject-2.0`
QMAKE_LFLAGS += `pkg-config --libs glib-2.0 gthread-2.0 gio-2.0 gmodule-2.0 gobject-2.0`


QMAKE_LFLAGS += $$(LDFLAGS) 
QMAKE_LFLAGS += "-ldl"
QMAKE_LFLAGS += "-lrt"
QMAKE_LFLAGS += -Wl,-Map=xxx.map
#QMAKE_LFLAGS += -static


# add the desired -O3 if not present
#QMAKE_CXXFLAGS_RELEASE += -O0
#QMAKE_CFLAGS_RELEASE   += -O0

#QMAKE_CXXFLAGS_WARN_ON += -Wall -Wno-parentheses
QMAKE_CFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON -= -Wall

QMAKE_CXXFLAGS += -std=c++0x -pthread




LIBS += -pthread  -dl
LIBS += -pthread  -lglib-2.0 -lgobject-2.0 -lgio-2.0 -lgobject-2.0 -lgthread-2.0
contains(QDEFS, .*arm.*) {
    #LIBS += -L./library/$$TARGET_DIR -levse
    #LIBS += -L./library/$$TARGET_DIR -lpev
}


CONFIG -= qt
CONFIG += no_lflags_merge


#########################################################################################
# http://doc.qt.io/qt-4.8/qmake-project-files.html
#########################################################################################
isEmpty(VARIABLE) {

}

equals(VARIABLE, foo) {

}

contains(VARIABLE, .*foo.*) {

}


