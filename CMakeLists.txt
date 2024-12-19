cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_FOLDER Dependencies)
add_subdirectory("vendor")
set(CMAKE_FOLDER /)

add_subdirectory("core")
add_subdirectory("app")
add_subdirectory("tests")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "app")