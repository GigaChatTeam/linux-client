QT += core gui widgets svgwidgets network websockets

CONFIG += c++23
QMAKE_CXXFLAGS += -std=c++2b -Wno-multichar

#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

qnx: INSTALL_ROOT = /tmp/$${TARGET}
else: unix:!android: INSTALL_ROOT = /opt/$${TARGET}

!isEmpty(INSTALL_DIR): INSTALL_ROOT = $$INSTALL_DIR
BIN_DIR = $$INSTALL_ROOT/bin
release: SHARE_DIR = $$INSTALL_ROOT/share/$${TARGET}
debug: SHARE_DIR = "/home/main/coding/linux-client/build/Debug/share/$${TARGET}"

DEFINES += \
	QT_DISABLE_DEPRECATED_BEFORE=0x060000 \
#       GIGAQT_AUTH_PARSE_TEST \
	ROOT_DIRECTORY="\\\"$${INSTALL_ROOT}\\\"" \
	BIN_DIRICTORY="\\\"$${BIN_DIR}\\\"" \
	SHARE_DIRECTORY="\\\"$${SHARE_DIR}\\\""

SOURCES += \
	authorizer.cpp \
	main.cpp \
	mainwidgets/gridscrollingwidget.cpp \
	utils/messagegroup.cpp \
	mainwidgets/messanger.cpp \
	mainwidgets/undefinedpage.cpp \
	stylesheets.cpp \
	userinterface.cpp \
	utils/message.cpp \
	utils/misc_functions.cpp \
	utils/nonewlineqlineedit.cpp \
	utils/properties.cpp \
	utils/recentevent.cpp \
	widget.cpp

HEADERS += \
	authorizer.h \
	mainwidgets/gridscrollingwidget.h \
	utils/messagegroup.h \
	mainwidgets/messanger.h \
	mainwidgets/undefinedpage.h \
	stylesheets.h \
	userinterface.h \
	utils/concepts_templates.h \
	utils/message.h \
	utils/misc_functions.h \
	utils/nonewlineqlineedit.h \
	utils/properties.h \
	utils/recentevent.h \
	widget.h

target.path = $$BIN_DIR

!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
	en_GB.qm

RESOURCES += \
    assets/assets.qrc \
#   data/data.qrc
