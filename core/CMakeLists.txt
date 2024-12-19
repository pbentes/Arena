cmake_minimum_required(VERSION 3.16)

set(ProjectName "core")
project(${ProjectName})

file(GLOB_RECURSE CORE_SRC
    "src/*.cpp"
    "src/*.h"
)

add_library(${ProjectName} STATIC ${CORE_SRC})

target_include_directories( ${ProjectName}
    PRIVATE ${core_SOURCE_DIR}/include
)