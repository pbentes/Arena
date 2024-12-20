cmake_minimum_required(VERSION 3.16)
enable_testing()

set(ProjectName "tests")
project(${ProjectName})

file(GLOB_RECURSE TEST_SRC
    "src/*.cpp"
    "src/*.h"
)

add_executable(${ProjectName} ${TEST_SRC})

target_include_directories( ${ProjectName}
    PUBLIC ${googletest_SOURCE_DIR}/googletest/include
)

target_link_libraries(${ProjectName}
    PUBLIC GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${ProjectName})