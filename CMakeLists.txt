project(bong-qt)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(Qt4 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )

add_subdirectory(src)
add_subdirectory(tests)
