QT += core gui widgets svgwidgets network websockets

CONFIG += c++23
QMAKE_CXXFLAGS += -std=c++23 -Wno-multichar
QMAKE_CXXFLAGS_DEBUG += -Wall -Wextra -Werror
MAKEFILE = QMakefile

#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

qnx: INSTALL_ROOT = /tmp/$${TARGET}
else: unix:!android: INSTALL_ROOT = /opt/$${TARGET}

!isEmpty(INSTALL_DIR): INSTALL_ROOT = $$INSTALL_DIR
BIN_DIR = $$INSTALL_ROOT/bin
release: SHARE_DIR = $$INSTALL_ROOT/share/$${TARGET}
debug: SHARE_DIR = "/home/main/coding/linux-client/build/Debug/share/$${TARGET}"

INCLUDEPATH += include

DEFINES += \
	QT_DISABLE_DEPRECATED_BEFORE=0x060000 \
#       GIGAQT_AUTH_PARSE_TEST \
	ROOT_DIRECTORY="\\\"$${INSTALL_ROOT}\\\"" \
	BIN_DIRICTORY="\\\"$${BIN_DIR}\\\"" \
	SHARE_DIRECTORY="\\\"$${SHARE_DIR}\\\""

SOURCES += \
	src/ui/authorizer.cpp \
	src/main.cpp \
	src/ui/mainwidgets/gridscrollingwidget.cpp \
	src/utils/messagegroup.cpp \
	src/ui/mainwidgets/messanger.cpp \
	src/ui/mainwidgets/undefinedpage.cpp \
	src/ui/stylesheets.cpp \
	src/ui/userinterface.cpp \
	src/utils/message.cpp \
	src/utils/misc_functions.cpp \
	src/utils/nonewlineqlineedit.cpp \
	src/utils/properties.cpp \
	src/utils/recentevent.cpp \
	src/database/wrappers.cpp \
	src/ui/widget.cpp

HEADERS += \
	include/ui/authorizer.hpp \
	include/ui/mainwidgets/gridscrollingwidget.hpp \
	include/utils/messagegroup.hpp \
	include/ui/mainwidgets/messanger.hpp \
	include/ui/mainwidgets/undefinedpage.hpp \
	include/ui/stylesheets.hpp \
	include/ui/userinterface.hpp \
	include/utils/concepts_templates.hpp \
	include/utils/message.hpp \
	include/utils/misc_functions.hpp \
	include/utils/nonewlineqlineedit.hpp \
	include/utils/properties.hpp \
	include/utils/recentevent.hpp \
	include/database/wrappers.hpp \
	include/ui/widget.hpp

target.path = $$BIN_DIR

!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
	en_GB.qm

RESOURCES += \
    assets/assets.qrc \
#   data/data.qrc
