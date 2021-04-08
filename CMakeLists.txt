cmake_minimum_required(VERSION 3.13)
project(lab_01)


set(CMAKE_CXX_STANDARD 17)
set(SRC ./src)

add_library(vector STATIC ${SRC}/vector/vector.cpp)
add_library(queue STATIC ${SRC}/queue/queue.cpp)
add_library(stack STATIC ${SRC}/stack/stack.cpp)
add_executable(lab_01 ${SRC}/lab_01.cpp)

target_link_libraries(lab_01 vector)
target_link_libraries(lab_01 queue)
target_link_libraries(lab_01 stack)
