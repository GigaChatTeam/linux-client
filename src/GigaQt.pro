QT += core gui widgets svgwidgets network websockets

CONFIG += c++23
QMAKE_CXXFLAGS += -std=c++2b -Wno-multichar

DEFINES += \
	QT_DISABLE_DEPRECATED_BEFORE=0x060000 \
#        GIGAQT_AUTH_PARSE_TEST

SOURCES += \
	authorizer.cpp \
	main.cpp \
	mainwidgets/gridscrollingwidget.cpp \
	mainwidgets/messanger.cpp \
	mainwidgets/undefinedpage.cpp \
	stylesheets.cpp \
	userinterface.cpp \
	utils/message.cpp \
	utils/nonewlineqlineedit.cpp \
	utils/properties.cpp \
	utils/recentevent.cpp \
	widget.cpp

HEADERS += \
	authorizer.h \
	mainwidgets/gridscrollingwidget.h \
	mainwidgets/messanger.h \
	mainwidgets/undefinedpage.h \
	stylesheets.h \
	userinterface.h \
	utils/concepts_templates.h \
	utils/message.h \
	utils/nonewlineqlineedit.h \
	utils/properties.h \
	utils/recentevent.h \
	widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
	en_GB.qm

RESOURCES += \
    assets/assets.qrc \
    data/data.qrc
