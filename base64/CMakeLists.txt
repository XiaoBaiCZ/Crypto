cmake_minimum_required(VERSION 3.6)

project(base64 C)

set(CMAKE_C_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(base64-demo main.c)

add_library(base64 SHARED base64.c)

target_link_libraries(base64-demo base64)