cmake_minimum_required(VERSION 3.16)
enable_testing()

set(ProjectName "tests")
project(${ProjectName})

link_directories(
    ${core_BINARY_DIR}
)

file(GLOB_RECURSE TEST_SRC
    "src/*.cpp"
    "src/*.h"
)

add_executable(${ProjectName} ${TEST_SRC})
add_dependencies(${ProjectName} core)

target_include_directories( ${ProjectName}
    PUBLIC ${core_SOURCE_DIR}/src
    PUBLIC ${googletest_SOURCE_DIR}/googletest/include
)

target_link_libraries(${ProjectName}
    PUBLIC core
    PUBLIC GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${ProjectName})