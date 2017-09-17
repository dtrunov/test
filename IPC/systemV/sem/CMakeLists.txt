cmake_minimum_required(VERSION 3.5)
project(sem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp sem.cpp sem.h)
add_executable(sem ${SOURCE_FILES})