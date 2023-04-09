cmake_minimum_required(VERSION 3.14)

project(header_docu_qt LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(header_docu_qt
  main.cpp
  Includes/cxxopts.hpp
  Includes/inicpp.h
  Includes/rz_inifile.h
  Includes/rz_inifile.cpp
  Includes/rz_snippets.h
  Includes/rz_snippets.cpp
  Includes/rz_header_docu_plugins.h
)
target_link_libraries(header_docu_qt Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS header_docu_qt
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

