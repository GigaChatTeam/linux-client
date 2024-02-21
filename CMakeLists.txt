cmake_minimum_required(VERSION 3.20) # for C++23 support

project(gigachat-qt 
	VERSION 0.0.0
	DESCRIPTION "lightweight linux client for GigaChat ecosystem written with Qt6 framework, using gigachat-sqlite-rs library"
	LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CPP_FILES
	# Main
	src/main.cpp
	# Widgets
	src/ui/widget.cpp
	src/ui/authorizer.cpp
	src/ui/userinterface.cpp
	src/ui/mainwidgets/messanger.cpp
	src/ui/mainwidgets/gridscrollingwidget.cpp
	src/ui/mainwidgets/undefinedpage.cpp
	src/utils/message.cpp
	src/utils/messagegroup.cpp
	src/utils/nonewlineqlineedit.cpp
	src/utils/recentevent.cpp
	# Utility
	src/ui/stylesheets.cpp
	src/utils/properties.cpp
	src/utils/misc_functions.cpp

)
set(HPP_FILES
	# Widgets
	include/ui/widget.hpp
	include/ui/authorizer.hpp
	include/ui/userinterface.hpp
	include/ui/mainwidgets/messanger.hpp
	include/ui/mainwidgets/gridscrollingwidget.hpp
	include/ui/mainwidgets/undefinedpage.hpp
	include/utils/message.hpp
	include/utils/messagegroup.hpp
	include/utils/nonewlineqlineedit.hpp
	include/utils/recentevent.hpp
	# Utility
	include/ui/stylesheets.hpp
	include/utils/properties.hpp
	include/utils/misc_functions.hpp
)
set(ASSET_FILES assets/assets.qrc)
set(TRANSLATION_FILES "")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets SvgWidgets Network WebSockets)
qt6_standard_project_setup()

qt6_add_executable(gigachat-qt ${CPP_FILES} ${HPP_FILES} ${ASSET_FILES} ${TRANSLATION_FILES}) 

set_target_properties(gigachat-qt PROPERTIES 
	CXX_STANDARD 23
	AUTORCC true
	AUTOUIC true
	AUTOMOC true
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

target_include_directories(gigachat-qt PRIVATE
	include
)

target_compile_definitions(gigachat-qt PRIVATE
	SHARE_DIRECTORY="~/.local/share/gigachat"
)

