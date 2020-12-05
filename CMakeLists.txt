cmake_minimum_required(VERSION 3.17)
project(Assignment4)
find_package (Threads)

set(CMAKE_CXX_STANDARD 14)
aux_source_directory(. DIR_SRCS)

add_executable(Assignment4 ${DIR_SRCS})
#add_executable(Assignment4 main.cpp Matrix.cpp)
target_link_libraries (Assignment4 ${CMAKE_THREAD_LIBS_INIT})

