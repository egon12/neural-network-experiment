cmake_minimum_required (VERSION 3.3)

project(NeuralNetwork)

add_library(matrix src/matrix/matrix.c)
add_library(neural_network src/neural_network.c)
target_link_libraries(neural_network m)

add_executable(nn src/neural_network_test.c)
target_link_libraries(nn matrix)
target_link_libraries(nn neural_network)

add_subdirectory(thirdparty/googletest)


add_executable(unit_test test/main_unittest)
target_include_directories(unit_test PRIVATE thirdparty/googletest/googletest/include/ src)
target_link_libraries(unit_test matrix)
target_link_libraries(unit_test gtest)

add_test(unit_test unit_test)

enable_testing()
