cmake_minimum_required(VERSION 3.15)

project(cueigen LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=unused-parameter")

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                   )


file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/cueigen/src/*.cpp)
file(GLOB_RECURSE op_src ${CMAKE_CURRENT_SOURCE_DIR}/operators/*.cpp)
file(GLOB test_src ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp)

add_library(cueigen SHARED ${src} ${op_src})

# add_library(cueigen_ops SHARED ${op_src})

add_executable(cueigen_test ${test_src})
target_link_libraries(cueigen_test PUBLIC cueigen)