cmake_minimum_required (VERSION 3.10)

project(NeuralNetwork)

add_library(matrix src/matrix/matrix.c)

add_library(neural_network src/neural_network.c)

add_executable(nn src/neural_network_test.c)

target_link_libraries(nn matrix)

target_link_libraries(nn neural_network)
