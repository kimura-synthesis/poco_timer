cmake_minimum_required(VERSION 3.5)
project(poco_timer CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(depbuild)
add_executable(timer_test timer_test.cpp)
target_link_libraries(timer_test PocoUtil PocoFoundation)
