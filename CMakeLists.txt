cmake_minimum_required(VERSION 3.16)

project(rpn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Programme principal
add_executable(rpn src/main.cpp)

target_include_directories(rpn PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rpn
)

target_compile_options(rpn PRIVATE
    -Wall -Wextra -Wpedantic
)

# Tests unitaires
enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(rpn_test tests/rpn_test.cpp)

target_include_directories(rpn_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rpn
)

target_link_libraries(rpn_test PRIVATE
    GTest::gtest_main
)

target_compile_options(rpn_test PRIVATE
    -Wall -Wextra -Wpedantic
)

gtest_discover_tests(rpn_test)