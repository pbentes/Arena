cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_FOLDER Dependencies)
add_subdirectory("vendor")
set(CMAKE_FOLDER Tests)
add_subdirectory("tests")
set(CMAKE_FOLDER /)