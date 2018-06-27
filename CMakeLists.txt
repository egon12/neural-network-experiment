cmake_minimum_required (VERSION 3.3)

project(NeuralNetwork)

#Print some environment variables
#message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
#message(STATUS ${CMAKE_CURRENT_BINARY_DIR})

#include(ExternalProject)
#ExternalProject_Add(cairo
#  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/cairo
#  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/cairo/autogen.sh --prefix=${CMAKE_CURRENT_BINARY_DIR}/thirdparty/cairo
#  BUILD_COMMAND ${MAKE})
#find_library(cairo)

# Internal Library
add_library(matrix src/matrix/matrix.c)
add_library(neural_network src/neural_network.c)
add_library(graph src/graph/line_chart.c)
target_include_directories(graph PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/cairo/include/cairo src)
#target_link_libraries(graph ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/cairo/lib/libcairo.so)
target_link_libraries(graph cairo)
target_link_libraries(graph X11)

# hopefully standard library
target_link_libraries(neural_network m)

# main executeable
add_executable(nn src/neural_network_test.c)
target_link_libraries(nn matrix)
target_link_libraries(nn neural_network)

# for testing
add_subdirectory(thirdparty/googletest)
add_executable(unit_test test/main_unittest)
target_include_directories(unit_test PRIVATE thirdparty/googletest/googletest/include/ src)
target_link_libraries(unit_test matrix)
target_link_libraries(unit_test gtest)
add_test(unit_test unit_test)
enable_testing()

add_executable(graph_test test/graph_test.c)
target_include_directories(graph_test PRIVATE src)
target_link_libraries(graph_test graph)
