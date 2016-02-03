cmake_minimum_required(VERSION 2.8)
project(KKY-UI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Node.hpp ClosedList.hpp Core.hpp Executor.hpp Executor.cpp OpenList.hpp)
add_executable(KKY-UI ${SOURCE_FILES})
