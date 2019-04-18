cmake_minimum_required(VERSION 3.13)
project(Deque)

include_directories(${../gtest/googletest/include})


set(CMAKE_CXX_STANDARD 11)
set(Deque_COMPILE_OPTION -Wall -Werror)

add_executable(Deque test_deque.cc deque.h)

add_subdirectory(./googletest)
set(LIBRARIES gtest pthread)

target_link_libraries(Deque ${LIBRARIES})