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

add_executable(Relbatross src/main.cpp src/board/board.h src/board/board.cpp src/uci/uci_interaction.h src/uci/uci_interaction.cpp)
