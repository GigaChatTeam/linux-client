cmake_minimum_required(VERSION 3.20) # for C++23 support

project(gigachat-qt 
	VERSION 0.0.0
	DESCRIPTION "lightweight linux client for GigaChat ecosystem written with Qt6 framework, using gigachat-sqlite-rs library"
	LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets SvgWidgets Network WebSockets)
qt6_standard_project_setup()

add_subdirectory(src)
