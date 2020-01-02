TARGET = trakce-sim
TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += SIM_SHARED_LIBRARY

SOURCES += \
	lib-api.cpp \
	lib-main.cpp
HEADERS += \
	lib-api.h \
	lib-main.h \
	lib-events.h \
	lib-api-common-defs.h \
	lib-common-defs.h \
	lib-errors.h

CONFIG += c++14 dll
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic

win32 {
	QMAKE_LFLAGS += -Wl,--kill-at
	QMAKE_CXXFLAGS += -enable-stdcall-fixup
}
win64 {
	QMAKE_LFLAGS += -Wl,--kill-at
	QMAKE_CXXFLAGS += -enable-stdcall-fixup
}

QT += core

VERSION_MAJOR = 0
VERSION_MINOR = 1

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR" \
	"VERSION_MINOR=$$VERSION_MINOR"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}
DEFINES += "VERSION=\\\"$${VERSION}\\\""
