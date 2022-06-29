cmake_minimum_required(VERSION 3.14)
project(Relbatross)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest)

if(GTest_FOUND)
    include(GoogleTest)
    add_executable(board_test src/board/board.h src/board/board.cpp test/board_test.cpp)
    target_link_libraries(board_test GTest::GTest GTest::Main)
    gtest_add_tests(TARGET board_test)
endif()

add_library(basic STATIC src/basic/types.h src/basic/utils.h src/basic/hash.cpp src/basic/hash.h src/basic/init.h src/basic/init.cpp)
add_library(board STATIC src/board/board.h src/board/board.cpp)
target_link_libraries(board basic)
add_library(api STATIC src/api/uci_interaction.h src/api/uci_interaction.cpp)
target_link_libraries(api basic board)

add_executable(Relbatross src/main.cpp)
target_link_libraries(Relbatross board api basic)
