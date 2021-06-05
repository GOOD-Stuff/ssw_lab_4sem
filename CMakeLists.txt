cmake_minimum_required(VERSION 3.17)
project(Laba4sem_1)

set(CMAKE_CXX_STANDARD 14)
set(SRC_LIST Stack.cpp main.cpp)

add_executable(Laba4sem_1 main.cpp Stack.cpp Queue.cpp Vector.cpp)