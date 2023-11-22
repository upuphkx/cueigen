cmake_minimum_required(VERSION 3.15)

project(cueigen C CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                   )


file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/cueigen/src/*.cpp)

add_library(cueigen SHARED ${src})

file(GLOB_RECURSE op_src ${CMAKE_CURRENT_SOURCE_DIR}/operators/*.cpp)

add_library(cueigen_ops SHARED ${op_src})


file(GLOB test_src ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp)


add_executable(cueigen_test ${test_src})
target_link_libraries(cueigen_test PUBLIC cueigen cueigen_ops)