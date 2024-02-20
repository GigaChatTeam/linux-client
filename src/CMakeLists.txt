cmake_minimum_required(VERSION 3.25)

qt6_add_executable(gigachat-qt
	main.cpp
	authorizer.cpp
	widget.cpp

	userinterface.cpp
	mainwidgets/gridscrollingwidget.cpp
	mainwidgets/undefinedpage.cpp
	mainwidgets/messanger.cpp
	utils/messagegroup.cpp
	utils/message.cpp
	utils/nonewlineqlineedit.cpp
	utils/misc_functions.cpp
	utils/recentevent.cpp
	utils/properties.cpp
	utils/misc_functions.cpp

	stylesheets.cpp

	assets/assets.qrc

	# TODO: translations
)

# target_include_directories(
# 	gigachat-qt PRIVATE
# 	utils/
# 	mainwidgets/
# )

set_target_properties(gigachat-qt PROPERTIES
	AUTOMOC true
	AUTORCC true
	CXX_STANDARD 23
)

target_compile_options(gigachat-qt PRIVATE
	-Wall
	-Wextra
	-Werror
	-Wno-multichar
)


target_link_libraries(gigachat-qt PRIVATE 
	Qt6::Core 
	Qt6::Widgets
	Qt6::SvgWidgets
	Qt6::Network
	Qt6::WebSockets
)


